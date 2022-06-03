# HTTP(s)

## Einordnung im Schichtenmodell

* OSI/ISO Schichtenmodell: in der 7ten Schicht
* TCP/IP: in der 4ten Schicht

## Entstehung

Ab 1989 entwickelten Tim Berners-Lee und sein Team am CERN, dem europäischen Kernforschungszentrum in der Schweiz, das Hypertext Transfer Protocol, zusammen mit den Konzepten URL und HTML, womit die Grundlagen des World Wide Web geschaffen wurden.

Quelle: [https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol](https://de.wikipedia.org/wiki/Hypertext_Transfer_Protocol)

## RFC

* Request for Comments (RFC)
* RFC ist ein nummeriertes Dokument
* RFC setzt sich aus Protokollen, Methoden, Konzepten und Programmen des Internets zusammen, die das Netz beschreiben und definieren.
* Die Mehrzahl der RFCs erreicht zwar nicht den Status eines Standards, dennoch werden sie häufig weltweit als Standards verwendet.
* Schwerpunkt auf die Verbesserung, nicht auf den Standardisierung

## RequestResponse-Modell

* Basiskonzept für die Kommunikation zwischen zwei Computersystemen.
* Der eine Teilnehmer sendet eine Anfrage für einen Satz Daten.
* Der zweite Teilnehmer sendet mit der Antwort die gewünschten Daten zurück.

## Zustandslosigkeit

* Eigenschaft eines Systems, dass Anfragen als voneinander unabhängige Transaktionen behandelt werden.
* zB. kein Austausch von Sitzungsinformationen

## Beschleunigung/Optimierung durch HTTP/2

* HTTP/1.1
    * Seperate TCP/IP-Verbinung je geladener Datei
* HTTP/2
    * Multiplex-Verfahren: einzigen Verbindung für die gesamte Website
    * Server-Push: vorhersehbare Folgedaten an den Client senden, ohne dass dieser danach fragt
    * Datenpakete in der Reihenfolge ihrer Priorität verschickt
    * Komprimierter HTTP/2-Header (entfallen von überflüssigen Informationen)
    * Verwendung eines binärcodierter Nachrichtenaustausch (anstelle von Text-Dateien) bei der Kommunikation

## http-Caching

* HTTP Caching ist eine Technik, um Ressourcen anhand bestimmter Kriterien in einem Cache zwischenzuspeichern
* Verringerung von unnötige Datenübertragungen, Serveranfragen zu vermeiden und Zugriffszeiten
* Sicherstellung, dass übertragene zwischengespeicherte Inhalte nicht veraltet sind
* Im HTTP-Standard sind dafür eine Reihe von Tags definiert, die das Caching auf Proxy- und Clientebene (Browser-Cache) unterstützen.

## Struktur/Aufbau eines http-Transfers

* Die Kommunikationseinheiten zwischen Client und Server werden als Nachrichten bezeichnet
    * Anfrage (Request) vom Client an den Server
    * Antwort (Response) als Reaktion darauf vom Server zum Client.
* Bestandteile einer Nachricht:
    * Header: Informationen über Kodierung, Inhaltstyp, ...
    * Body: enthält die Nutzdaten

## Header-Arten und einige Felder

* HTTP Header (Kopfzeilen) erlauben es dem Client und Server zusätzliche Informationen an eine Anfrage oder eine Antwort zu übergeben. 
* Benutzerdefinierte, proprietäre Header können mit einem 'X-' Präfix hinzugefügt werden.

* Arten von Header
    * General header
        * Header die sowohl für Anfragen als auch für Antworten zutreffen, jedoch keinen Bezug zu den Daten haben, die eventuell im Body übertragen werden.
    * Request header
        * Header die weitere Informationen über die angeforderte Ressource oder den Client selbst enthalten.
    * Response header
        * Header mit weiteren Informationen zur Antwort, wie etwa ihres Orts oder den Server selbst (Name und Version etc.)
    * Entity header
        * Header die weitere Informationen über den Body der Entität enthalten, wie etwa der Inhaltslänge oder ihren MIME-Type.

## Anfragemethoden/-funktionen

| Methode   | Beschreibung                                                                                    |
|-----------|-------------------------------------------------------------------------------------------------|
| `GET`     | Anforderung einer Ressource (Datei) unter Angabe eines URI                                      |
| `POST`    | Senden von Daten (Text, Dateien, ...) im Name-Wert-Paare-Format (Daten im HTTP-Body übertragen) |
| `HEAD`    | Gleiche Methode wie `GET`, jedoch ohne HTTP-Body (zB. Gültigkeit vom Browser-Cache)             |
| `PUT`     | Erstellung bzw. Modifizierung von Ressourcen                                                    |
| `PATCH`   | Änderung von Ressourcen, ohne vollständige Ersetzung wie bei `PUT`                              |
| `DELETE`  | Entfernen einer Ressource                                                                       |
| `TRACE`   | Zurücksenden der Anfrage, wie sie der Server empfangen hat (Debugging)                          |
| `OPTIONS` | Liste von unterstützen Methoden und Merkmalen                                                   |
| `CONNECT` | Verwendung von Proxy-Server, für SSL-Tunneling                                                  |

## Übertragung der Argumente Cookies/Session

* HTTP-GET: Die Daten sind Teil der URL und bleiben deshalb beim Speichern oder der Weitergabe des Links erhalten. Sie müssen URL-kodiert werden, das heißt reservierte Zeichen müssen mit `%<Hex-Wert>` und Leerzeichen mit „+“ dargestellt werden.
* HTTP-POST: Übertragung der Daten mit einer speziell dazu vorgesehenen Anfrageart im HTTP-Nachrichtenrumpf, so dass sie in der URL nicht sichtbar sind.

Ein Cookie ist eine Textinformation, die im Browser auf dem Endgerät jeweils zu einer besuchten Website gespeichert werden kann. Das Cookie wird entweder vom Webserver an den Browser gesendet oder im Browser von JavaScript erzeugt. Der Webserver kann bei späteren, erneuten Besuchen dieser Seite diese Cookie-Information direkt vom Server aus auslesen oder über ein Skript der Website die Cookie-Information an den Server übertragen. Aufgabe dieses Cookies ist beispielsweise die Identifizierung des Surfers (Session ID), das Abspeichern eines Logins bei einer Webanwendung oder das Abspeichern eines Warenkorbs bei einem Online-Händler.

Durch eine Sitzung können Sitzungsdaten einem Benutzer zugeordnet werden. Sitzungsdaten werden serverseitig gespeichert und werden oft für komplexere Transaktionen benötigt. Minimale Sitzungsdaten bestehen nur aus der Session-ID.

## Status-/Responsecode

Jede HTTP-Anfrage wird vom Server mit einem HTTP-Statuscode beantwortet. 

* 1xx – Informationen
* 2xx – Erfolgreiche Operation
* 3xx – Umleitung
* 4xx – Client-Fehler
* 5xx – Server-Fehler

## Fehlerbehandlung

Fehler sind je nach Typ zu behandeln, soll heißen, dass serverseitige Fehler nur angezeigt werden sollen, clientseitige Fehler sollen genauer behandelt werden.

## Funktionen

* C … Create von Eingaben
* R … Lesen von gespeicherten Werten
* U … Updaten von gespeicherten Werten
* D … Löschen von gespeicherten Werten

## Authentifizierung

* Authentifizierung über HTTP-Protokoll
* Verwendung beispielsweise bei WebDAV
* Server meldet Athentifizierung mit dem Statuscode `401 Unauthorized` und dem Header `WWW-Authenticate`
* Browser stellt anschließend Dialog mit Benutzernamen & Passwort zur Verfügung

Basic Authentication
* häufigste Art der HTTP-Authentifizierung
* Authentifizierung mit dem `Authorization`-Header in der Form `Benutzername:Passwort` Base64-codiert
* Base64 biehtet keinen kryptographischen Schutz => beim Einsatz mit HTTPS kann dies als sicher gelten

Digest Access Authentication
* zusätzlich zum `WWW-Authenticate`-Header eine eigens erzeugte zufällige Zeichenfolge (Nonce)
* Browser berechnet den Hashcode der gesamten Daten (Benutzername, Passwort, erhaltener Zeichenfolge, HTTP-Methode und angeforderter URI) und sendet sie im `Authorization`-Header zusammen mit dem Benutzernamen und der zufälligen Zeichenfolge zurück an den Server.
* Durch die Verwendung einer kryptologischen Hashfunktion, können sich die Daten nicht rekonstruieren lassen

## HTTPS

* HTTPS ... Hypertext Transfer Protocol Secure
* Syntaktisch identisch mit HTTP, jedoch geschieht eine zusätzliche Verschlüsselung der Daten mittels SSL/TLS
* Standard-Port für HTTPS-Verbindungen ist 443
* Verwendung von Zertifikaten

## Zertifikate

* Digitaler Datensatz, der bestimmte Eigenschaften von Personen oder Objekten bestätigt und dessen Authentizität und Integrität durch kryptografische Verfahren geprüft werden kann
* Austellung durch eine offizielle Zertifizierungsstelle (Certification Authority (CA))
* Weit verbreitet sind Public-Key-Zertifikate nach dem Standard X.509

## Ablauf einer HTTPS-Kommunikation

<img src="https://www.elektronik-kompendium.de/sites/net/bilder/18112811.gif" width="400">

Der Verbindungsaufbau erfolgt über einen HTTPS-Request vom Client zum Server. Beim Client handelt es sich beispielsweise um einen Webbrowser. Der Server wäre demnach ein Webserver.

1. Client Hello: Der Client kontaktiert den Server über ein Protokoll mit Verschlüsselungsoptionen.
2. Server Hello, Certificate, Server Key Exchange, Server Hello Done: Der Server nimmt die Verbindung an und schickt sein Zertifikat mit dem öffentlichen Schlüssel seines Schlüsselpaares zur Authentifizierung an den Client.
3. Der Client überprüft das Server-Zertifikat und dessen Gültigkeit (Validierung). Erkennt der Client das Zertifikat als ungültig wird die Verbindung an dieser Stelle abgebrochen.
4. Erkennt der Client das Zertifikat als gültig erzeugt der Client den symmetrischen Sitzungsschlüssel.
5. Client Key Exchange, Change Cipher Spec, Encrypted Handshake Message: Mit dem öffentlichen Schlüssel des Servers verschlüsselt der Client den Sitzungsschlüssel und schickt ihn an den Server.
6. Mit seinem privaten Schlüssel kann der Server den verschlüsselten Sitzungsschlüssel entschlüsseln.
7. Encrypted Handshake Message, Change Cipher Spec, Encrypted Handshake Message: Der Server bestätigt den geheimen Sitzungsschlüssel.
8. Danach werden alle HTTP-Requests und -Responses verschlüsselt, bis die Verbindung abgebaut wird.

Quelle: [https://www.elektronik-kompendium.de/sites/net/1811281.htm](https://www.elektronik-kompendium.de/sites/net/1811281.htm)

## REST-Service / REST API

* REST steht für REpresentational State Transfer, API für Application Programming Interface.

## Was muss ein http-Server zur Verfügung stellen?

* statische Dateien aus dem Dateisystem bereitstellen
    * CaseSensitive bei Windows; Linux nicht
* Multithreading (+ Portauslagerung)
* Basis Authorizierung
* Kommunikation mit CGI (Computer Generated Imagery) wie PHP
* Verschlüsselung mit SSL/TLS (Zertifikat)
* Multi-Sites
* Skalierung (+ Reverse Proxy, Load Balancer)
* Schützen von Endpoints
* Sessions / Cookies
    * Cookiesicherheit

## URL/URI

* URI
    * URI ... Uniform Resource Identifier
    * Definition der RFC: eine kompakte Abfolge von Zeichen, die eine abstrakte oder physische Ressource identifizieren.
* URL
    * URL ... Uniform Resource Locator
    * Teilmenge der URIs
    * physische Standort abgerufen, indem der Netzwerkstandort beschrieben wird

Quelle: [https://www.heise.de/tipps-tricks/URI-und-URL-was-ist-der-Unterschied-4655338.html](https://www.heise.de/tipps-tricks/URI-und-URL-was-ist-der-Unterschied-4655338.html)

## Wie kann man eine WebApplikation schützen?

* WAF ... Web Application Firewall
* Authentizifierung
* DirectoryListenings
* Virtuelle Verzeichnisse / Alias
* CORS ... Cross-Origin Resource Sharing

## Was kann ein Hacker bei einem WebServer „angreifen“?

* SQL-Injection
* Cross-Site-Scripting (XSS)
* Session Hijacking
* Cross-Site-Request-Forgery
* Directory Traversal
* E-Mail-Injection
* Man-in-the-Middle-Angriff
* Man-in-the-Browser
* Denial of Service
* Phishing / Identitätsdiebstahl

## Inwieweit spielt hier die IT-Sicherheit eine Rolle – welchen Beitrag kann ein Webserver hier liefern?

s.o.

* Minimuminformation über Webserver (Typ + Version)
* Gleiche Anfragen unterbingen
* Rechtesetzung

## Welche Rolle spielt das Betriebssystem?

* Ressourcenbereitstellung (RAM, Speicher, CPU-Leistung, ...)