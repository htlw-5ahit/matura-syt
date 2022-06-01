# Eigenheiten der WebProgrammierung

## Eigenheiten der WebProgrammierung

* das Eingabeproblem: insbesondere bei tastaturlosen Geräten (Touchscreen-Geräten)
* das Darstellungsproblem: z.B. Screengröße, Kontrast, Farbdarstellung
* das Vollständigkeitsproblem: Vollständigkeit versus Übersichtlichkeit
* das Limitationsproblem: in Bezug auf unterstützte Inhalte (z.B. Flash)

Quelle: [https://mfg.fhstp.ac.at/development/die-vier-kernprobleme-der-mobilen-webentwicklung/](https://mfg.fhstp.ac.at/development/die-vier-kernprobleme-der-mobilen-webentwicklung/)

## Unterschied zu herkömmlicher Anwendungs-Programmierung

* Design
    * Softwareentwicklung meist einfach und unkompliziert
    * Webentwicklung ist grafisch relativ aufwendig 
* Anpassung
    * Die Anpassung hat Nachteile bei der Softwareentwicklung
    * Webbasierte Apps sind leichter zu adaptieren bzw. zu verändern
* Inhalt
    * In der Softwareentwicklung ist der große Teil der Anwendung mit statischen Texten
    * In der Webentwicklung geht es darum immer gleich relativ viel Text darzustellen
* System
    * Eine Software kann nur auf Maschinen laufen, wenn alle benötigten Komponenten auf dem Zielsystem verfügbar sind
    * In der Webentwicklung ist für das Zielgerät nur ein Browser notwendig
* Sicherheit
    * Abhängig der Anwendung ist mehr oder weniger Sicherheit in das System zu integrieren
    * Bei Webentwicklung ist sehr viel Sicherheit in das System zu integrieren

Quelle: [https://www.cisin.com/coffee-break/de/enterprise/key-differences-between-web-development-vs-software-development.html](https://www.cisin.com/coffee-break/de/enterprise/key-differences-between-web-development-vs-software-development.html)

## Welche Problemstellungen können besser mit dem web-basierten Konzept gelöst werden?

* Darstellung vieler verschiedener Texte
* Zugriff von diversen Systemen auf eine Plattform
* Sicherung einer einzigen Instanz gewünscht
* Zentrale Speicherung sämtlicher Daten
* Sichere Arbeitsumgebung
* Automatische, zentralisierte Updates und synchronisierte Lizenzen

Quelle:
* [https://www.yuhiro.de/was-ist-webentwicklung/](https://www.yuhiro.de/was-ist-webentwicklung/)
* [https://www.secondreality.com/was-ist-webbasierte-software-und-warum-setzen-wir-darauf/](https://www.secondreality.com/was-ist-webbasierte-software-und-warum-setzen-wir-darauf/)

## Erforderliche Komponenten im WebBereich

* Clientseitig: Browser
* Serverseitig: Webserver

## Erforderliche Technologien

???

## Programmiersprachen

* JavaScript (client- sowie serverseitig)
* C++ (serverseitig)
* Go (serverseitig)
* Java (serverseitig)
* Python (serverseitig)
* PHP (serverseitig)
* ...

## Layout-Technologie (Prinzipielle Methoden für die UI-Gestaltung – zum Vergleich Java/Windows/Android/Apple Web), Kopplung GUI-Betriebssystem)

???

## Deklarative Technologien

* *Kennzeichnend für die deklarativen Programmiersprachen ist, dass sie immer ein gewünschtes Endergebnis beschreiben, statt alle Arbeitsschritte aufzuzeigen
* Die bekanntesten deklarativen Programmiersprachen:
    * Prolog
    * Lisp
    * Haskell
    * Miranda
    * Erlang

<img src="https://www.ionos.at/digitalguide/fileadmin/DigitalGuide/Schaubilder/uebersicht-deklarative-imperative-programmierparadigmen.jpg" width="400">

Quelle: [https://www.ionos.at/digitalguide/websites/web-entwicklung/deklarative-programmierung/](https://www.ionos.at/digitalguide/websites/web-entwicklung/deklarative-programmierung/)

## Mögliche Fehlerquellen

* Vernachlässigkeit bei der Sicherheit
* Unzureichendes Testen
* Unzureichende Planung
* Verwenden von veralteten Funktionen bzw. Frameworks

Quelle:
* [https://www.it-daily.net/it-management/business-software/fehlerquellen-bei-der-web-app-programmierung](https://www.it-daily.net/it-management/business-software/fehlerquellen-bei-der-web-app-programmierung)

## Anforderung seitens der IT-Security

* Zentrale abgesicherte Datenspeicherung
* Sichere Übertragung (Verschlüssel, End-End-Verschlüsselung, Verbindung über HTTPs, …)
* Least-Priviledge Prinzip
* Aufbauen mehrerer Sicherheitsinstanzen (nicht nur eine, mehrere geschachtelt)
* Externe Computersysteme zur Überwachung