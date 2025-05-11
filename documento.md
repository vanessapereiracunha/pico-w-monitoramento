# Projeto IoT com Raspberry Pi Pico W e Sensores

## 1 INTRODUÇÃO

A Internet das Coisas (IoT) representa um dos campos mais promissores da tecnologia moderna, permitindo a interconexão de dispositivos físicos com a rede mundial de computadores. Por meio da IoT, é possível monitorar ambientes, controlar equipamentos e coletar dados em tempo real para tomada de decisões eficientes. Essa tecnologia é amplamente aplicada em áreas como automação residencial, saúde, agricultura, cidades inteligentes e indústria 4.0.

O presente projeto visa desenvolver uma aplicação prática utilizando o microcontrolador Raspberry Pi Pico W, equipado com o chip RP2040, para coletar dados de sensores integrados como um botão físico, um joystick e o sensor de temperatura interno. Todos esses dados serão processados e enviados via conexão Wi-Fi para uma interface web acessível através de um navegador.

Com esse trabalho, busca-se explorar a integração entre sensores analógicos e digitais com comunicação em rede, aprofundando os conhecimentos sobre sistemas embarcados, programação em linguagem C, protocolos de comunicação e visualização de dados em tempo real. O projeto também se propõe a oferecer uma base sólida para futuras implementações e melhorias em soluções IoT.

## 2 OBJETIVOS DO PROJETO

### 2.1 Objetivo Geral

Desenvolver um sistema IoT utilizando a Raspberry Pi Pico W (RP2040) para coletar e transmitir dados de sensores, permitindo a visualização das informações em tempo real por meio de uma interface web.

### 2.2 Objetivos Específicos

* Capturar a temperatura interna da placa Raspberry Pi Pico W utilizando seu sensor integrado.
* Monitorar o estado de um botão físico, identificando se está pressionado ou não.
* Ler os valores dos eixos X e Y de um joystick analógico para determinar direções.
* Determinar a direção apontada pelo joystick em termos de rosa dos ventos.
* Estabelecer a conexão Wi-Fi da placa para enviar os dados coletados ao servidor.
* Exibir os dados na interface web de forma responsiva e atualizada automaticamente.

## 3 MATERIAIS UTILIZADOS

### 3.1 Componentes de Hardware

* Raspberry Pi Pico W
* Joystick analógico
* Sensor de temperatura interno (embutido no RP2040)


### 3.2 Ferramentas de Software

* Visual Studio Code
* CMake
* SDK da Raspberry Pi Pico
* GCC ARM Toolchain


## 4 CONFIGURAÇÃO DO AMBIENTE DE DESENVOLVIMENTO

### 4.1 Instalação das Ferramentas

Instale os seguintes recursos:

* Visual Studio Code com extensões C/C++
* Compilador GCC
* CMake
* SDK da Raspberry Pi Pico
* Python 3

### 4.2 Estrutura de Diretórios

```text
projeto_iot/
├── exercicio.c
├── CMakeLists.txt
├── lwipopts.h
└── build/```

## 4.3 CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.12)
project(iot_project)
add_executable(main exercicio.c)
target_link_libraries(main pico_stdlib hardware_adc pico_cyw43_arch_lwip_threadsafe_background)

## 5 DIAGRAMA DE CIRCUITO E LIGAÇÕES

### 5.1 Conexões Utilizadas

| Componente   | Pino Pico W      |
|--------------|------------------|
| Botão A      | GP5              |
| Joystick X   | GP26 (ADC0)      |
| Joystick Y   | GP27 (ADC1)      |
| Temp. int.   | ADC4             |

## 6 DESCRIÇÃO DO CÓDIGO

### 6.1 Wi-Fi

```c
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "senha"
6.2 Temperatura
c
Copiar
Editar
adc_select_input(4);
uint16_t raw = adc_read();
float voltage = raw * 3.3f / 4095.0f;
float temp = 27.0f - (voltage - 0.706f) / 0.001721f;
6.3 Botão
c
Copiar
Editar
gpio_init(5);
gpio_set_dir(5, GPIO_IN);
6.4 Joystick
c
Copiar
Editar
adc_select_input(0); uint x = adc_read();
adc_select_input(1); uint y = adc_read();
6.5 Página Web
Geração via snprintf no código com HTML e CSS embutido.

7 INTERFACE WEB
A interface exibe:

Temperatura atual

Estado do botão

Direção do joystick

HTML básico com CSS e auto-refresh a cada segundo via setTimeout.

8 UTILIZAÇÃO E EXECUÇÃO DO SISTEMA
8.1 Passos
Compilar e carregar código via USB.

Conectar Wi-Fi automaticamente.

Acessar IP no navegador (porta 80).

9 TESTES REALIZADOS
9.1 Botão
Funcionou com precisão e resposta imediata.

9.2 Joystick
Direções identificadas corretamente com base na rosa dos ventos.

9.3 Temperatura
Comparada com termômetro externo com variação < 0.5ºC.

10 RESULTADOS OBTIDOS
Estabilidade na leitura e envio dos dados

Interface clara e funcional

Coleta confiável dos sensores

11 MELHORIAS FUTURAS
Armazenamento em nuvem (Firebase, Google Sheets)

Integração com WhatsApp

Implementação de segurança via HTTPS

Inclusão de sensores externos (umidade, luminosidade)

12 CONCLUSÃO
O projeto foi eficaz ao demonstrar na prática os conceitos de IoT. A utilização da Raspberry Pi Pico W mostrou-se viável e didática, promovendo um aprendizado significativo na integração entre sensores, comunicação sem fio e desenvolvimento embarcado.

13 ANEXOS
Código main.c, CMakeLists.txt, lwipopts.h

Captura de tela da interface

Diagrama do circuito (opcional via Fritzing)

14 REFERENCIAL TEÓRICO
A Internet das Coisas (IoT) é uma tecnologia emergente que permite a comunicação e troca de dados entre dispositivos físicos, como sensores, atuadores e dispositivos móveis, por meio da internet. Esses dispositivos podem coletar dados do ambiente, processá-los e enviar para sistemas que analisam as informações para tomar decisões automáticas ou fornecer feedback em tempo real.

A Raspberry Pi Pico W é um microcontrolador de baixo custo e com recursos de conectividade Wi-Fi, ideal para aplicações IoT. O RP2040, chip central da placa, oferece uma boa performance para projetos de computação embarcada com um desempenho satisfatório para a maioria das tarefas de coleta e envio de dados.

Sensores como o DHT11/DHT22 são amplamente utilizados para medições de temperatura e umidade. O uso de ADCs (Conversores Analógico-Digital) permite a leitura de sinais analógicos de dispositivos como joysticks, onde os valores dos eixos podem ser usados para determinar a direção e intensidade de movimentos.

Os protocolos de comunicação como o MQTT ou HTTP são essenciais para o envio de dados de dispositivos IoT para servidores ou interfaces web. A comunicação sem fio, neste caso via Wi-Fi, proporciona flexibilidade, permitindo que os dispositivos sejam acessados remotamente.

15 IMAGENS E CAPTURAS DE TELA (SUGESTÕES)
Adicionar capturas de tela da interface web em funcionamento.

Imagens de diagramas de circuitos.

Prints de código em execução no ambiente de desenvolvimento (VSCode).