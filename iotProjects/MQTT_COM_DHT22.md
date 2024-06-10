# MQTT com DHT22

**Link do Projeto:** [MQTT com DHT22](https://wokwi.com/projects/399609546694759425)

## Descrição
Este projeto integra um sensor de temperatura e umidade DHT22 com um módulo ESP32 para enviar dados via protocolo MQTT. Ideal para aplicações de monitoramento remoto de ambiente.

## Componentes
- ESP32
- Sensor DHT22
- Broker MQTT
- Fonte de alimentação

## Funcionalidades
- Leitura da temperatura e umidade através do sensor DHT22.
- Envio dos dados coletados para um broker MQTT.
- Publicação dos dados em tópicos específicos para monitoramento remoto.

## Como Usar
1. Conecte o DHT22 ao ESP32 conforme o esquema.
2. Configure o broker MQTT e atualize as credenciais no código.
3. Carregue o código no ESP32.
4. Monitore os dados enviados para o broker MQTT usando um cliente MQTT.
