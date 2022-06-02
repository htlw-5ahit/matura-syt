# Internet Information Services (IIS)

- [Ausarbeitung: IIS](./IIS.pdf)

## Fragestellung

Ausgangssitation: Kleine Firma, Internetplattform mit Dateizugriff einrichten, ein WindowsServer 2019 ist vorhanden. Ihre Wahl fällt auf einen Windows Server.

* Geben Sie einen Überblick über den IIS, welche Dienste gibt es im IIS, Eigenschaften
    * Durch IIS können Dokumente und Dateien über das Netzwerk zugänglich gemacht werden
    * Dienste: http, https, pop3, smtp, ftp

* Funktion von Anwendungspools und wieso mehrer in einem IIS sinnvoll sind
    * Abgetrenneter Bereich in dem Webanwendungen laufen
    * Sicherheit: Falls ein Anwendungspool Fehler hat, können die anderen weiterlaufen
    * Leistung: man kann einem Anwendungspool fixe Ressourcen zuweisen

* Erklären Sie das Prinzip von virtuellen Verzeichnissen. Erklären mit einem Beispiel
    * Ist ein Link zu einem vorhandenen physischen Verzeichnis
    * Können als Aliasse benutzt werden

* Erörtern Sie die Sicherheitsaspekte von virtuellen Verzeichnissen, benötigt man mehrere Portnummern
    * Sicherheitsaskept:
        * Abgetrennte Bereiche; Vgl. Virtualisierung
        * Benutzer hat in eigenen Bereich ein Verzeichnis, welches über ein virtuelles Verzeichnis am Webserver eingebunden wird
    * Portnummern: Nein.

* Erörtern Sie, ob man eine gesicherte Verbindung benötigt oder nicht (Zertifikate, etc.)
    * HTTPS ermöglicht eine gesicherte Verbindung
    * Zertifikate werden hierfür benötigt
    * AD Certificate Services kann Zertifikate für die Domaine austellen; oder auch von offizieller CA, wenn der Webserver im Internet hängt

* Erläutern Sie den Dateizugriff, wie wird dieser geregelt (WebDAV, FTP)
    * WebDAV funktioniert über HTTP(S)
    * FTP: aktives & passives FTP (Kann wegen Öffnung von Ports zu Problemen führen -> Firewallregeln)

* Unterschiede, Eigenschaften, Welcher wird von uns genutzt
    * WebDAV kann einfacher in Firewalls, Proxys und NATs konfiguriert werden
    * GZIP Komprimierung bei WebDAV möglich
    * Authentifizierung bei WebDAV einfacher