# Projeto Pico W - Monitoramento de Temperatura e Controle de Joystick

Este projeto utiliza o microcontrolador **Pico W** para monitorar a temperatura interna da placa, verificar o estado de um botão e capturar as leituras de um joystick. Através de um servidor web, o usuário pode acessar essas informações via navegador. O projeto também exibe uma interface simples, que permite atualizar as leituras a cada segundo.

## Funcionalidades

- **Leitura de temperatura interna**: A temperatura da placa é lida periodicamente e exibida na interface web.
- **Leitura do botão**: O estado do botão conectado à GPIO 5 é monitorado, exibindo se ele está pressionado ou solto.
- **Leitura do joystick**: A posição do joystick é capturada e traduzida para uma direção (Norte, Sul, Leste, Oeste, etc.), sendo exibida na interface.
- **Servidor Web**: A Pico W hospeda um servidor web simples que exibe os dados capturados, com a atualização automática a cada segundo.

## Componentes

- **Pico W**: Utilizado para controle de hardware e servidor web.
- **Botão**: Conectado à GPIO 5 para capturar seu estado.
- **Joystick analógico**: Conectado às entradas ADC 0 e ADC 1 (X e Y) para capturar as coordenadas e determinar a direção.

## Requisitos

### Hardware:

- Raspberry Pi Pico W.
- Botão .
- Joystick analógico (2 eixos).

### Software:

- Ambiente de desenvolvimento C.
- Biblioteca `lwip` para funcionalidade de rede.
- Ferramentas para programar o microcontrolador.


### 2. Programação do Pico W

Clone este repositório e compile o código utilizando as ferramentas mencionadas. O código será carregado no microcontrolador Pico W para execução.


git clone c:https://github.com/vanessapereiracunha/pico-w-monitoramento.git
cd pico-w-monitoramento
mkdir build
cd build
cmake ..
make

### 3. Conexão Wi-Fi

Edite as credenciais Wi-Fi no código (`WIFI_SSID` e `WIFI_PASSWORD`) para conectar o Pico W à sua rede local.

### 4. Acesso via navegador

Após o Pico W se conectar à rede Wi-Fi, ele estará acessível no navegador via o IP atribuído pela rede. A interface da página web exibirá a temperatura interna, o estado do botão e a direção do joystick.

## Como funciona

- **Temperatura**: A temperatura interna é lida a partir do ADC da Pico W e exibida na interface web.
- **Botão**: O estado do botão é verificado periodicamente. Se pressionado, ele é exibido na interface como "Pressionado"; caso contrário, "Solto".
- **Joystick**: O código lê as posições X e Y do joystick e determina a direção com base nas leituras analógicas.
- **Serviço Web**: O servidor web hospeda uma página simples que exibe os dados de temperatura, estado do botão e direção do joystick. A página é atualizada automaticamente a cada segundo.

## Contribuições

Se desejar contribuir para o projeto, fique à vontade para criar pull requests. Envie suas melhorias ou correções, e elas serão analisadas para possível integração.

## Licença

Este projeto é licenciado sob a [Licença MIT](https://opensource.org/licenses/MIT).
