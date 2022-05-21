# Systemtechnik 5 - Hardwarenahe Programmierung

## Theorie

- [Bussysteme](./theorie/Bussysteme.md)
  - [UART - Universal Asynchronous Receiver / Transmitter](./theorie/UART.md)
  - [I²C - Inter-Integrated Circuit](./theorie/I2C.md)
  - [SPI - Serial Peripheral Interface](./theorie/SPI.md)
  - [CAN - Controller Area Network](./theorie/CAN.md)

## Protokolle

- [Protokoll 01 - LCD](./protokolle/Protokoll01_LCD.pdf)
- [Protokoll 02 - SD Card](./protokolle/Protokoll02_SDCard.pdf)
- [Protokoll 03 - Bluetooth](./protokolle/Protokoll03_Bluetooth.pdf)
- [Protokoll 04 - Kommunikation](./protokolle/Protokoll04_Kommunikation.pdf)

## Übungen

| Thema | Übungen |
| --- | --- |
| [Raspberry Pi: LCD Display](./lcd/) | [LCD mit CPU Temperatur](./lcd/sensor_rpicpu.c) <br> [LCD mit DS1115](./lcd/sensor_ads1115.c) <br> [LCD mit BH1750](./lcd/sensor_bh1750.c) <br> [LCD mit DHT11](./lcd/sensor_dht11.c) |
| [Raspberry Pi: SD Card](./sdcard/) | [Vorbereitungen am Raspberry Pi](./sdcard/README.md) <br> [Dateiausgabe eines DHT11](./sdcard/sdcard_dht11.c) |
| [Arduino: SD Card](./sdcard_arduino/) | [Dateiausgabe eines LDR](./sdcard_arduino/sdcard_arduino.ino) |
| [Arduino: Bluetooth](./bluetooth/) | [LED Steuerung](./bluetooth/led.ino) <br> [DC Motor Steuerung](./bluetooth/dcmotor.ino) <br> [DHT11 Anzeige](./bluetooth/dht11.ino) <br> [Bewegungssensor mit LED Steuerung](/bluetooth/bewegungssensor_led.ino) |
| [Arduino: Universal Asynchronous Receiver Transmitter (UART)](./uart/) | [Master Arduino](./uart/UART_LEDs_LDR_Master.ino) <br> [Slave Arduino](./uart/UART_LEDs_LDR_Slave.ino) |
| [Arduino: Inter-Integrated Circuit (I2C)](./i2c/) | [Master Arduino](./i2c/I2C_LEDs_LDR_Master.ino) <br> [Slave Arduino](./i2c/I2C_LEDs_LDR_Slave.ino) |
| [Arduino: Serial Peripheral Interface (SPI)](./spi/) | [Master Arduino](./spi/SPI_CircuitDigest_LEDs_LDR_Master.ino) <br> [Slave Arduino](./spi/SPI_CircuitDigest_LEDs_LDR_Slave.ino)
| [Arduino: Controller Area Network (CAN)](./can/) | [Master Arduino](./can/5AHIT_FrKr_MCP2515-CAN_LEDs_LDR_Master.ino) <br> [Slave Arduino](./can/5AHIT_FrKr_MCP2515-CAN-LEDs_LDR_Slave.ino)
