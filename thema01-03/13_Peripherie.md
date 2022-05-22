# Peripherie

- [Echtzeituhr](#echtzeituhr)
- [NFC-Kartenleser](#nfc-kartenleser)
- [SD-Karte am Arduino](#sd-karte-am-arduino)
- [SD-Karte am Raspberry Pi](#sd-karte-am-raspberry-pi)

## Echtzeituhr

* Wir verwenden folgende Echtzeituhr: DS3231
* Der DS3231 zwei einstellbare Alarme mit dem über zwei Ausgängen Interrupts eines Mikrocontrollers zu einem bestimmten Zeitpunkt oder periodisch ausgelöst werden können.
* Der DS3231 ist über den I2C Bus angeschlossen. Zusätzlich kann über die I2C Adresse und Registern zugegriﬀen werden. Zusätzlich hat der DS3231 einen Ausgang für ein 32kHz Signal, was über ein Register ein- oder ausgeschaltet werden kann.
* Es ﬁndet auch alle 64 Sekunden eine Temperaturmessung innerhalb des DS3231 statt, welche dann den Oscillator des Uhr der Umgebungstemperatur zu Korrekturzwecken anpasst. Die Temperatur kann über zwei Register ausgelesen werden und auch eine manuelles Anstossen der Messung ist möglich.

```c
#include <Wire.h>
#include <DS3231.h>

#define LEN_STR 100

DS3231 clock;
RTCDateTime dt;

char timeStr[LEN_STR];

void setup() {
  Serial.begin(112500);

  // Initialize DS3231
  Serial.println("Initialize DS3231");
  clock.begin();

  // Set date and time
  // clock.setDateTime(2020-09-29, 09-00-00-00);
}

void loop() {
  dt = clock.getDateTime();

  sprintf(timeStr, „%04d-%02d-%02d %02d-%02d-%02d",
    dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second
  );
  Serial.println(timeStr);
  
  delay(1000);
}
```

## NFC-Kartenleser

* Folgenden Baustein haben wir verwendet: MFRC-522. Die dafür verwendete Library heißt „MFRC522“ und wird von der Github Community bereitgestellt.
* Der RFID („radio-frequency identiﬁcation“) Reader wird verwendet, um von RFID Sendern (auch „RFID Tags“ genannt) per Funk einen bestimmten Code auszulesen. Jeder Sender hat dabei nur einen einmaligen ganz individuellen Code.

```c
#include <SPI.h>
#include <MFRC522.h>

// Configurable, see typical pin layout above
#define RST_PIN 8
#define SS_PIN 10

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  
  Serial.begin(115200); // Initialize serial communications with the PC
  while (!Serial); // Do nothing if no serial port is opened

  
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  delay(4); // Optional delay. Some board do need more time after init to be ready

  // Show details of PCD - MFRC522 Card Reader details
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader.
  // This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
```

Beispiele:
- [Arduino: NFC-Kartenleser mit LED Steuerung](https://github.com/htlw-5ahit/matura-syt/tree/main/thema01-03/code/nfc_led)
- [Arduino: NFC-Kartenleser mit LED und Taster Steuerung](https://github.com/htlw-5ahit/matura-syt/tree/main/thema01-03/code/nfc_led_taster)

## SD-Karte am Arduino

Grundaufbau:

```c
#include <SD.h>

File myFile;

void sdCardSetup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println("Initializing SD card...");
  if (!SD.begin(SDCARD_PIN)) {
    Serial.println("Initialization failed!");
    while (1);
  }
  Serial.println("Initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
  Serial.println("Open File succeeded.");
}

void setup() {
  // setup sd card
  sdCardSetup();

  // set csv header
  myFile.println("test message");

  // close file
  myFile.close();
}
```

- [SD Karte mit LDR Sensor](https://github.com/htlw-5ahit/matura-syt/tree/main/thema01-03/code/sdcard_arduino/)

## SD-Karte am Raspberry Pi

### SDIO-Einheit aktivieren

Um die sekundäre SDIO-Einheit auf die Raspberry Pi Pins zu aktivieren, muss folgendes in die Bootconfig geschrieben werden:

```
pi@raspi-it-01:~# nano /boot/config.txt
——————————————————————————————————————————————————————
...
dtoverlay=sdio,poll_once=off,bus_width=1
...
```

### Software installieren

Für das weitere Vorgehen, benötigt man den „Device Tree Compiler“ am Raspberry Pi. Um sicher zu gehen, dass die neueste Version installiert wird, laden wir uns die neuen Packetlisten herunter und installieren ausstehende Updates.

```
pi@raspi-it-01:~# sudo apt update

pi@raspi-it-01:~# sudo apt dist-upgrade -y

pi@raspi-it-01:~# sudo apt install device-tree-compiler -y
```

### Device Tree konfigurieren

Es muss ein neues File für die SPI (Serial Peripheral Interface) Bus erstellt werden.

```
pi@raspi-it-01:~# nano mmc_spi.dts
——————————————————————————————————————————————————————

/dts-v1/;
/plugin/;

/ {
   compatible = "brcm,bcm2835", "brcm,bcm2836", "brcm,bcm2708", "brcm,bcm2709";

   fragment@0 {
      target = <&spi0>;
      frag0: __overlay__ {
         status = "okay";
         sd1 {
                reg = <0>;
                status = "okay";
                compatible = "spi,mmc_spi";
                voltage-ranges = <3000 3500>;
                spi-max-frequency = <8000000>;
         };
      };
   };
};
```

Um das File dem Bootloader vom Raspberry Pi zur Verfügung zu stellen, muss das File kompiliert werden.

```
pi@raspi-it-01:~# dtc -@ -I dts -O dtb -o mmc_spi.dtbo mmc_spi.dts
```

Das mit dem oben genannten Befehl erstellte Datei, muss in den Overlays Ordner des Bootloaders verschoben werden. Dazu werden Sudo- beziehungsweise Rootrechte benötigt.

```
pi@raspi-it-01:~# sudo cp mmc_spi.dtbo /boot/overlays/
```

Damit die kompilierte Datei vom Bootloader berücksichtigt wird, müssen noch zwei Konfigurationszeilen im Bootconfig-File hinzugefügt werden.

```
pi@raspi-it-01:~# sudo nano /boot/config.txt
——————————————————————————————————————————————————————

...
dtoverlay=mmc_spi
dtparam=spi=off
```

Nun kann der Raspberry Pi neugestartet werden.

### Partition auf SD Karte erstellen

Zuerst kann man die vorhandenen Partitionen auflisten, um herauszufinden, welche Disk beziehungsweise Partition von uns formatiert wird.

```
root@raspi-it-01:~# lsblk
NAME        MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
mmcblk0     179:0    0  7.4G  0 disk
├─mmcblk0p1 179:1    0  256M  0 part /boot
└─mmcblk0p2 179:2    0  7.1G  0 part /
mmcblk2     179:32   0 14.4G  0 disk
└─mmcblk2p1 179:33   0 14.4G  0 part
```

Die oben markierte Disk formatieren wir jetzt mit ext4.

```
root@raspi-it-01:~# mkfs.ext4 /dev/mmcblk2
mke2fs 1.44.5 (15-Dec-2018)
Found a dos partition table in /dev/mmcblk2
Proceed anyway? (y,N) y
Discarding device blocks: done
Creating filesystem with 3780608 4k blocks and 946560 inodes
Filesystem UUID: 4f893e48-7019-4870-a44f-1838fb3d5f7f
Superblock backups stored on blocks:
	32768, 98304, 163840, 229376, 294912, 819200, 884736, 1605632, 2654208

Allocating group tables: done
Writing inode tables: done
Creating journal (16384 blocks): done
Writing superblocks and filesystem accounting information:
done
```

### Einbinden des EXT4-Dateisystems

Zuerst muss das Zielverzeichnis erstellt werden und die benötigten Zugriffsrechte für den Benutzer „pi“ geben.

```
root@raspi-it-01:~# mkdir /media/sd0/

root@raspi-it-01:~# chmod 775 /media/sd0/

root@raspi-it-01:~# chown pi:pi /media/sd0/
```

Anschließend kann die Disk auf in das Verzeichnis gemountet werden.

```
root@raspi-it-01:~# mount -t ext4 /dev/mmcblk2 /media/sd0/ -o user=pi
```

### Überprüfen der Konfiguration

Man kann sich nach der erfolgreichen Konfiguration, den Mountpoint anzeigen lassen.

```
root@raspi-it-01:~# lsblk
NAME        MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
mmcblk0     179:0    0  7.4G  0 disk
├─mmcblk0p1 179:1    0  256M  0 part /boot
└─mmcblk0p2 179:2    0  7.1G  0 part /
mmcblk2     179:32   0 14.4G  0 disk /media/sd0
```

### Software

- [SD Karten Projekte](https://github.com/htlw-5ahit/matura-syt/tree/main/thema01-03/code/raspberrypi5/sdcard/)