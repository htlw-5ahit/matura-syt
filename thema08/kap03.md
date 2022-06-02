# Paketfilter mit IP-Tables

- [Foliensatz: Firewall](./Firewall.pdf)
- [Foliensatz: iptables](./iptables.pdf)

## Fragestellung

Ausgangssitation: Nehmen sie an, sie sollen einen kostengünstige Firewall mit einem Linuxrechner für ein kleines Netzwerk mit DMZ und LAN-Bereich mit Hilfe von Paketfiltern (IP-Tables) implementieren.

* Erläutern sie kurz, welche andere Möglichkeiten eventuell nicht möglich und sinnvoll wären. Zählen sie dazu verschiedene Software- und Hardwarelösungen auf und beurteilen sie diese kurz.
    * Hardwarelösungen (bei hohem Durchsatz benötigt, eher teuer): 
        * Fortigate, Barracuda, …
        * Cisco ASA und FirePower
        * Router mit PaketFilter

    * Softwarelösungen (kostengünstig):
        * Proxy
        * Firewall auf separaten Rechner (meist Linux)

* Im Beiblatt 2 haben sie eine Netzwerkskizze vorgegeben. Vergeben sie dort entsprechende IP-Adressen und weitere Netzwerkeinstellungen. Erklären sie auch den Begriff NAT in den verschiedenen Varianten und wozu diese notwendig sind.
    * NAT = Network Address Translation … kann Ziel und Quell Adressen eines Pakets verändern, wird verwendet, da mit IPv4 nicht mehr genügend öffentliche Adressen übrig wären.
    * Beispielkonfiguration:

    ```
    Extern 173.16.10.32 / 29 (vom Provider)
    LAN 192.168.20.0/24
    DMZ 192.168.30.0/24
    Gateway des Providers: 173.16.10.33

    Gateway-Firewall:
    IP-extern: 173.16.10.34
    IP-LAN: 192.168.20.1
    IP-DMZ: 192.168.30.1
    Gateway: 173.16.10.33

    Server DMZ:
    IP-intern: 192.168.30.100
    Gateway: 192.168.30.1
    IP-extern: 173.16.10.35
    ```

* Im Beiblatt 3 finden sie ein Skript mit IP-Tables vor. Nehmen sie an, sie haben diese im Internet gefunden. Erstellen sie darauf ein eigenes Skript, das den Zugriff aus dem Internet auf den Webserver in der DMZ erlaubt, und jeglichen Zugriff auf die Firewall aus dem Internet verhindert. Erläutern sie die entsprechende Befehle.
