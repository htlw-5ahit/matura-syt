# Virtual Private Network

- [Foliensatz: Firewall](./Firewall.pdf)
- [Foliensatz: VPN](./VPN.pdf)

## Fragestellung

Ausgangssitation: Nehmen sie an, sie sollen für eine kleinere Firma einen externen Zugang auf ihre Daten in der Firma einrichten. Der Standard hierfür ist VPN.

* Geben sie zunächst einen Überblick über das Prinzip von VPN und Arten von VPN, sowie Anbieter.
    * Prinzip:
        * Client authentifiziert sich auf VPN Server
        * Server baut Tunnel zum Ziel auf
        * Dadurch befindet man sich dann quasi im Netzwerk des Ziels
    * Arten:
        * Point-to-Point (Verbindung zw. 2 Endgeräten)
        * Point-to-Site (Einwählen in ein Firmennetzwerk)
        * Site-to-Site (Zusammenschalten in ein Firmennetzwerk)
        * Intranet VPN (Absichern internen Netzbereiche)
        * Extranet VPN (Business Room)
    * Anbieter:
        * NordVPN
        * Cisco
        * Surfshark
        * ExpressVPN
        * FortyClient
        * OpenVPN

* Vergleichen sie auch mit anderen Zugängen und Lösungsmöglichkeiten, gehen sie dabei auch auf deine eventuell vorhandene Firewall als auch auf SSH, Webdav und FTP ein.
    * SSH:
        * Secure Shell
        * Verschlüsselte Tunnelverbindung zum Ziel
        * Nicht für Weiterleitung von Netzwerkverkehr konzipiert
    * WebDAV:
        * Nur mit https gesichert
        * Stellt nur Dateien zur Verfügung
    * FTP:
        * Ungesichert
        * Rein zur Datenübertragung

* Nehmen Sie weiter an, Sie entscheiden sich für die kostengünstige Lösung über OpenVPN. Welche Voraussetzungen brauchen Sie dazu? Gehen Sie dabei näher auf die notwendigen Zertifikate ein. Erklären Sie dazu den Aufbau von Zertifikaten und diskutieren Sie über den Begriff PKI.

