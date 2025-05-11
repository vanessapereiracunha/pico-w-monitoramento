#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/netif.h"

#define WIFI_SSID "Vanessa"
#define WIFI_PASSWORD "42871598"

#define LED_PIN CYW43_WL_GPIO_LED_PIN
#define BUTTON_A 5
#define JOYSTICK_X_PIN 0
#define JOYSTICK_Y_PIN 1

#define ADC_MAX ((1 << 12) - 1)

static char last_direction[16] = "Norte";

const char* get_direction(uint adc_x_raw, uint adc_y_raw) {
    if (adc_y_raw < ADC_MAX / 4 && adc_x_raw < ADC_MAX / 4) {
        return "Sudoeste";
    } else if (adc_y_raw < ADC_MAX / 4 && adc_x_raw > 3 * ADC_MAX / 4) {
        return "Noroeste";
    } else if (adc_y_raw > 3 * ADC_MAX / 4 && adc_x_raw < ADC_MAX / 4) {
        return "Sudeste";
    } else if (adc_y_raw > 3 * ADC_MAX / 4 && adc_x_raw > 3 * ADC_MAX / 4) {
        return "Nordeste";
    } else if (adc_y_raw < ADC_MAX / 3) {
        return "Oeste";
    } else if (adc_y_raw > 2 * ADC_MAX / 3) {
        return "Leste";
    } else if (adc_x_raw < ADC_MAX / 3) {
        return "Sul";
    } else if (adc_x_raw > 2 * ADC_MAX / 3) {
        return "Norte";
    } else {
        return "Centro";
    }
}

static char button_status[16] = "Solto";

void check_button_status() {
    if (!gpio_get(BUTTON_A)) { 
        strncpy(button_status, "Pressionado", sizeof(button_status) - 1);
    } else {
        strncpy(button_status, "Solto", sizeof(button_status) - 1);
    }
    button_status[sizeof(button_status) - 1] = '\0';
}

static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (!p) {
        tcp_close(tpcb);
        tcp_recv(tpcb, NULL);
        return ERR_OK;
    }

    char *request = (char *)malloc(p->len + 1);
    memcpy(request, p->payload, p->len);
    request[p->len] = '\0';

    adc_select_input(4);
    uint16_t raw_value = adc_read();
    const float conversion_factor = 3.3f / (1 << 12);
    float temperature = 27.0f - ((raw_value * conversion_factor) - 0.706f) / 0.001721f;

    adc_select_input(JOYSTICK_X_PIN);
    uint adc_x_raw = adc_read();
    adc_select_input(JOYSTICK_Y_PIN);
    uint adc_y_raw = adc_read();
    const char* direction = get_direction(adc_x_raw, adc_y_raw);
    strncpy(last_direction, direction, sizeof(last_direction) - 1);
    last_direction[sizeof(last_direction) - 1] = '\0';

    check_button_status();

    char html[2048];

    snprintf(html, sizeof(html),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "\r\n"
             "<!DOCTYPE html>\n"
             "<html>\n"
             "<head>\n"
             "<title>Status da Pico W</title>\n"
             "<style>\n"
             "body { font-family: 'Roboto', sans-serif; background-color:rgb(148, 220, 220); color: #333; text-align: center; margin: 0; padding: 20px; }\n"
             "h1 { font-size: 48px; margin-bottom: 20px; color:rgb(17, 17, 19); }\n"
             "button { font-size: 24px; margin: 10px; padding: 15px 30px; border-radius: 5px; border: none; background-color:rgb(28, 29, 31); color: white; cursor: pointer; transition: background-color 0.3s; }\n"
             "button:hover { background-color:rgb(15, 16, 17); }\n"
             ".temperature { font-size: 24px; margin-top: 20px; color: #333; }\n"
             ".status { font-size: 24px; margin: 10px 0; }\n"
             "</style>\n"
             "</head>\n"
             "<body>\n"
             "  <script>\n"
             "    setTimeout(function() {\n"
             "      window.location = window.location.pathname;\n"
             "    }, 1000);\n"
             "  </script>\n"
             "<h1>Status da Pico W</h1>\n"
             "<p class=\"temperature\">Temperatura Interna: %.2f &deg;C</p>\n"
             "<p class=\"status\">Estado do Botao: %s</p>\n"
             "<p class=\"status\">Direcao do Joystick: %s</p>\n"
             "</body>\n"
             "</html>\n",
             temperature, button_status, last_direction);

    tcp_write(tpcb, html, strlen(html), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);

    free(request);
    pbuf_free(p);

    return ERR_OK;
}

static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    tcp_recv(newpcb, tcp_server_recv);
    return ERR_OK;
}

int main()
{
    stdio_init_all();

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    while (cyw43_arch_init()) {
        printf("Falha ao inicializar Wi-Fi\n");
        sleep_ms(100);
        return -1;
    }

    cyw43_arch_gpio_put(LED_PIN, 0);
    cyw43_arch_enable_sta_mode();

    printf("Conectando ao Wi-Fi...\n");
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_WIFI_TIMEOUT_MS)) {
        printf("Falha na conexão Wi-Fi\n");
        sleep_ms(100);
    }

    printf("Conectado ao Wi-Fi!\n");

    struct tcp_pcb *pcb = tcp_new();
    if (!pcb) {
        printf("Erro ao criar PCB TCP\n");
        return -1;
    }

    tcp_bind(pcb, IP_ADDR_ANY, 80);
    pcb = tcp_listen(pcb);
    tcp_accept(pcb, tcp_server_accept);

    while (1) {
        cyw43_arch_poll();
        sleep_ms(100);
    }

    return 0;
}
