# DHCP für mehrere Netze

- [Protokoll Clemens & Christoph](./Rumpfhuber_Schmitsberger_UE01_DHCP.pdf)

## Fragestellung

* Hostkonfiguration über DHCP
* Firmennetzwerk mit Windows Server in unterschiedlichen Netzen
* Verbunden über L3-Switch
* Im Netzwerk soll ein DHCP-Dienst eingerichtet werden.
* Problem: in einem Netzwerk gibt es keine IP-Adressen
* Erklärung: Adresszuteilung über DHCP (wesentliche 4 Netzwerke)
* Netzaufbau Skizzieren
* Erörtern Sie mögliche Fehlerquellen bei der Adresszuteilung. Welche Fehler können bei der Konfiguration auftreten?
* Einstellungen an Scopes, L3-Switch
* Diskussion über Netzaufteilung mit VLANs

---

Aufgabenstellung: 
* Skizze Netzaufbau 
* Wie funktioniert eine Adresszuteilung über DHCP 
* Einstellung an Scopes, L3 – Switch 
* Mögliche Fehlerquellen bei der Adresszuteilung 

1. Schritt: 
    * Client schickt DHCP-Discover 
    * Broadcast an alle Netzwerkteilnehmer, um DHCP – Server zu lokalisieren 

2. Schritt: 
    * Server antwortet mit einem DHCP-Offer 
    * Enthält mögliche IP – Adresse 

3. Schritt: 
    * Client wählt IP – Adresse aus 
    * Schickt DHCP-Request an Server 

4. Schritt: 
    * Server speichert Daten ab 
    * Server bestätigt Client mit DHCP-Acknowledge 

Nach Ablauf der Lease Time beginnt der Client wieder beim 3. Schritt und fragt, ob er seine IP-Adresse behalten darf 
Einrichtung Scopes und L3 – Switch: 
* Scopes am DHCP – Server einrichten 
* Scope Name 
* IP-Adressbreich 
* Default Gateway
* Lease Time 

* L3 – Switch einrichten 
    * IP-Helper (Adresse vom Server) setzen 
    * IP-Adresse vom Router setzen 


Gateway leitet DHCP Pakete an einen DHCP Server weiter, der nicht im selben Segment liegt. Man muss den IP-Helper auf den Schnittstellen konfigurieren, auf denen sich kein DHCP-Server im Netz befindet. 
Fehlerquellen bei Adresszuteilung: 
* Falscher IP-Helper 
* Falsches Scope 
* Falsches Gateway 