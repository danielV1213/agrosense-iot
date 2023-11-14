# AgroSense - Internet of Things (IoT)

Este repositorio contiene el código fuente en C++ para la funcionalidad IoT de AgroSense, un proyecto de monitoreo remoto para invernaderos.

## Descripción

AgroSense utiliza dispositivos IoT para medir y transmitir datos cruciales de temperatura y humedad en tiempo real. Este código, implementado en el archivo `agrosense-iot.ino`, establece la comunicación entre los sensores y la plataforma en la nube, permitiendo a los agricultores monitorear y recibir alertas sobre las condiciones ambientales de sus invernaderos.

## Requisitos

- Placa de desarrollo ESP32, Arduino con adaptación WiFi o similares que cuenten con capacidad de conexión a internet.
- Sensores de temperatura y humedad compatibles (p. ej., DHT11, DHT22, DS18B20).
- Acceso a una plataforma en la nube para el almacenamiento y procesamiento de datos.

## Instrucciones de Uso

1. Clona este repositorio en tu entorno de desarrollo.
2. Abre el archivo `agrosense-iot.ino` en el entorno de desarrollo de Arduino.
3. Asegúrate de tener las bibliotecas necesarias instaladas para los sensores que estás utilizando.
4. Configura la conexión a internet y los detalles de la plataforma en la nube (sigue las instrucciones en el código).
5. Carga el código en tu placa de desarrollo.

## Configuración

- **Librerías utilizadas:** ArduinoJson, WiFi, PubSubClient, DHT.
- **Credenciales WiFi:** Configura las credenciales de tu red WiFi en las variables `ssid` y `password`.
- **Credenciales MQTT:** Configura el usuario y contraseña MQTT en las variables `mqttUser` y `mqttPass`.

## Contribuciones

¡Las contribuciones son bienvenidas! Si encuentras mejoras o correcciones, por favor, envía un pull request. Si tienes problemas o ideas nuevas, abre un problema.