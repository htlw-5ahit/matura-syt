# SD Card

```bash
sudo apt update
sudo apt dist-upgrade -y
sudo apt install device-tree-compiler
```

<hr>

`/boot/config.txt`

```bash
dtoverlay=sdio,poll_once=off,bus_width=1
```

<hr>

`nano mmc_spi.dts`

```bash
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

<hr>

`dtc -@ -I dts -O dtb -o mmc_spi.dtbo mmc_spi.dts`

`sudo cp mmc_spi.dtbo /boot/overlays/`

<hr>

`sudo nano /boot/config.txt`

```bash
dtoverlay=mmc_spi
dtparam=spi=off
```

<hr>

```bash
dmesg -w | grep mmc_spi
```

<hr>

```bash
root@raspi-it-01:~# lsblk
NAME        MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
mmcblk0     179:0    0  7.4G  0 disk
├─mmcblk0p1 179:1    0  256M  0 part /boot
└─mmcblk0p2 179:2    0  7.1G  0 part /
mmcblk2     179:32   0 14.4G  0 disk
└─mmcblk2p1 179:33   0 14.4G  0 part
```



<hr>

````bash
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
````

<hr>

```bash
root@raspi-it-01:~# mkdir /media/sd0/
root@raspi-it-01:~# chmod 775 /media/sd0/
root@raspi-it-01:~# chown pi:pi /media/sd0/
```

<hr>

`root@raspi-it-01:~# mount -t ext4 /dev/mmcblk2 /media/sd0/ -o user=pi`

<hr>

````bash
root@raspi-it-01:~# lsblk
NAME        MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
mmcblk0     179:0    0  7.4G  0 disk
├─mmcblk0p1 179:1    0  256M  0 part /boot
└─mmcblk0p2 179:2    0  7.1G  0 part /
mmcblk2     179:32   0 14.4G  0 disk /media/sd0
````

<hr>

````bash
pi@raspi-it-01:/media/sd0 $ ls -la
total 24
drwxr-xr-x 3 pi   pi    4096 Oct 14 08:16 .
drwxr-xr-x 3 root root  4096 Oct 14 08:09 ..
drwx------ 2 root root 16384 Oct 14 08:06 lost+found
````

<br><br>

### DHT11 Ausgabe

```bash
pi@raspi-it-01:/media/sd0 $ cat rumpfhuber.log
2021-14-10 10:08:30: Sensor not working...
2021-14-10 10:08:40: Temperature: 24.00 Humidity: 22.00
2021-14-10 10:08:50: Temperature: 24.00 Humidity: 22.00
2021-14-10 10:09:00: Temperature: 24.00 Humidity: 22.00
2021-14-10 10:09:10: Temperature: 24.00 Humidity: 22.00
2021-14-10 10:09:20: Temperature: 24.00 Humidity: 22.00
2021-14-10 10:09:30: Temperature: 24.00 Humidity: 22.00
2021-14-10 10:09:40: Temperature: 24.00 Humidity: 22.00
2021-14-10 10:09:50: Temperature: 24.00 Humidity: 22.00
2021-14-10 10:10:00: Temperature: 24.00 Humidity: 22.00
2021-14-10 10:10:10: Temperature: 24.00 Humidity: 22.00
2021-14-10 10:10:20: Temperature: 24.00 Humidity: 22.00
```
