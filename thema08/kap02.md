# Kryptographie

## Symmetrische Encryption (Block-/Stromchiffren, Hash)

* Es gibt nur einen Schlüssel, der sowohl für die Ver- wie auch für die Entschlüsselung benötigt wird
* Sowohl der Sender als auch der Empfänger benötigen diesen Schlüssel 
* Beim Sender ist das kein Problem, da er den Schlüssel schon zur Verschlüsselung besitzt
* Dem Empfänger fehlt aber natürlich der Schlüssel
* Bei der symmetrischen Verschlüsselung sehr wichtig ist es, dass der Schlüssel auf einem sicheren Übertragungsweg an den Empfänger weitervermittelt wird

#### Blockverschlüsselung
* Verschlüsselt einen Teil eines Texte mittels eine Schlüssels
* Zu Beginn nur schwache Verschlüsselung
* Moderne Blockchain sichern allerdings sehr gute Verschlüsselung zu

#### Stromverschlüsselung
* Klartext wird Zeichen für Zeichen verschlüsselt durchlaufen
* Jedes Zeichen wird mittels des Schlüsselstroms verändert
* Der Schlüsselstrom ist eine pseudozufällige Zeichenfolge, welche aus dem Schlüssel abgeleitet werden
* Ist unabhängiger als die Blockchain, hat aber eine wenig leichtere Verschlüsselung als die moderne Blockchain

#### Hash Verschlüsselung
* Ist eine mathematische Berechnung aus den einzelnen Zeichen und Primzahlen
* Ist eine Einwegverschlüsselung
* Eine Änderung eines einzelnen Zeichens ändert das komplette Hash 


Quelle:
* [https://de.wikipedia.org/wiki/Blockverschl%C3%BCsselung](https://de.wikipedia.org/wiki/Blockverschl%C3%BCsselung)
* [https://de.wikipedia.org/wiki/Stromverschl%C3%BCsselung](https://de.wikipedia.org/wiki/Stromverschl%C3%BCsselung)
* [https://de.wikipedia.org/wiki/Kryptographische_Hashfunktion](https://de.wikipedia.org/wiki/Kryptographische_Hashfunktion)

## Asymmetrische Verfahren(public/private Key->Diffie-Hellman, RSA – Sicherheit von RSA)

* In der asymmetrischen Kryptografie arbeitet man nicht mit einem einzigen Schlüssel, sondern mit einem Schlüsselpaar.
* Jeweils öffentlicher und ein privater Schlüssel

Will der Sender Daten verschlüsselt an den Empfänger senden, benötigt er den öffentlichen Schlüssel des Empfängers. Mit dem öffentlichen Schlüssel können die Daten verschlüsselt, aber nicht mehr entschlüsselt werden (Einwegfunktion). Nur noch der Besitzer des privaten Schlüssels, also der richtige Empfänger kann die Daten entschlüsseln. Wichtig bei diesem Verfahren ist, dass der private Schlüssel vom Schlüsselbesitzer absolut geheim gehalten wird. Kommt eine fremde Person an den privaten Schlüssel muss sich der Schlüsselbesitzer ein neues Schlüsselpaar besorgen.

#### Diffie-Hellman
* Beschreibung des Schlüsselaustauschs
* Es ermöglicht, dass zwei Kommunikationspartner über eine öffentliche, abhörbare Leitung einen gemeinsamen geheimen Schlüssel in Form einer Zahl vereinbaren können, den nur diese kennen und ein potenzieller Lauscher nicht berechnen kann
* Der dadurch vereinbarte Schlüssel kann anschließend für ein symmetrisches Kryptosystem verwendet werden

#### RSA – Sicherheit von RSA (Rivest–Shamir–Adleman)
* Die RSA Verschlüsselung ist ein asymmetrisches Verschlüsselungsverfahren
* häufig im Internet zur sicheren Datenübertragung eingesetzt
* Eigenschaften/ Sicherheit
    * Ein Klartextbuchstabe wird nicht immer auf den gleichen Geheimtextbuchstaben abgebildet. Es ist also nicht monoalphabetisch.
    * Die RSA Verschlüsselung ist ein asymmetrisches Verfahren.
    * Es gibt einen öffentlichen Schlüssel der zum Verschlüsseln eingesetzt wird und einen privaten Schlüssel, der zum Entschlüsseln verwendet wird. Das RSA Verfahren stellt unter anderem deshalb einen sicheren Verschlüsselungsalgorithmus dar, da aus dem öffentlichen Schlüssel nicht der private Schlüssel berechnet werden kann.
    * Das RSA Verfahren eignet sich zur Kommunikation mit vielen Teilnehmern, da der öffentliche Schlüssel allen bekannt sein darf und somit nicht mit jedem Kommunikationsteilnehmer ein Schlüssel geheim ausgetauscht werden muss.
    * Nur der Besitzer des privaten Schlüssels kann eine Nachricht wieder einfach entschlüsseln.
* Der öffentliche Schlüssel wird zum Verschlüsseln eingesetzt und sollte für jeden frei zugänglich sein. Den privaten Schlüssel hingegen sollte nur der Besitzer kennen, da man nur mit diesem Schlüssel die Nachricht wieder entschlüsseln kann.

Quelle:
* [https://www.elektronik-kompendium.de/sites/net/1910111.htm](https://www.elektronik-kompendium.de/sites/net/1910111.htm)
* [https://de.wikipedia.org/wiki/Diffie-Hellman-Schl%C3%BCsselaustausch](https://de.wikipedia.org/wiki/Diffie-Hellman-Schl%C3%BCsselaustausch)
* [https://studyflix.de/informatik/rsa-verschlusselung-1608](https://studyflix.de/informatik/rsa-verschlusselung-1608)

## Grundidee der public/private-Keys und Bedeutung der Mathematik)

* Primzahlen
* Je höher desto schwerer ist dieser zu finden
* Je größer die Primzahl ist, desto komplizierter ist der Rechenweg  Schwer zurückzuverfolgen bzw. schwer zu entschlüsseln von jemanden der den Schlüssel nicht hat

## Vor/Nachteile der symmetrischen/asymmetrischen Verschlüsselung

#### Symmetrische Verschlüsselung

* Vorteile:
    * Einfach einzurichten
    * Einfach durchgeführt
    * Einfach zu verstehen
* Nachteile:
    * Wie teile ich den Schlüssel

#### Asymmetrische Verschlüsselung

* Vorteile:
    * Sicherer wie das direkte Teilen des Schlüssels
    * Unterstützen digitale Signatur
    * Verschlüsselungsgrad ist relativ hoch
* Nachteile:
    * Sehr zeitintensiv zu realisieren
    * Sehr hoher Aufwand in der Realisierung
    * Privater Schlüssel ist nicht wiederherstellbar

Quelle: [https://blog.mailfence.com/de/symmetrische-vs-asymmetrische-verschlusselung-was-ist-der-unterschied/](https://blog.mailfence.com/de/symmetrische-vs-asymmetrische-verschlusselung-was-ist-der-unterschied/)

## Hybride Verschlüsselung

* Bei hybrider Verschlüsselung werden die Private-Key- und Public-Key-Verfahren kombiniert
* Der Sender nutzt einen zufälligen zusätzlichen symmetrischen Schlüssel, der Session-Key
* Mit diesem Session-Key werden die zu schützenden Daten symmetrisch verschlüsselt
* Anschließend wird der Session-Key asymmetrisch mit dem öffentlichen Schlüssel des Empfängers verschlüsselt
* Dieses Vorgehen löst das Schlüsselverteilungsproblem und erhält dabei den Geschwindigkeitsvorteil der symmetrischen Verschlüsselung

Quelle: [https://www.ibau.de/akademie/glossar/public-key/](https://www.ibau.de/akademie/glossar/public-key/)

## Verschlüsselung und TCP - wo bzw. in welchem Bereich greift hier die Verschlüsselung ein?

* Eingegriffen wird auf der Transportschicht des TCP/IP Modells (bzw. schiebt sich als 5te Schicht zwischen Transportschicht und Verarbeitungsschicht)
* TLS verschlüsselt den gesamten Datenverkehr, der über TCP abgewickelt wird, mit einem symmetrischen Verschlüsselungsverfahren.

Quelle: [https://www.ionos.at/digitalguide/server/sicherheit/tls-transport-layer-security/](https://www.ionos.at/digitalguide/server/sicherheit/tls-transport-layer-security/)

## SSL - Zertifikate

* Ein SSL-Zertifikat ist eine kleine Datendatei, die einen kryptografischen Schlüssel digital an die Details einer Organisation bindet
* Wenn es auf einem Webserver installiert ist, aktiviert es das Sicherheitsschloss und das https-Protokoll und ermöglicht sichere Verbindungen von einem Webserver zu einem Browser
* Typischerweise wird SSL verwendet, um Kreditkartentransaktionen, Datentransfers und Logins zu sichern, und wird in jüngerer Zeit immer mehr zur Norm bei der Sicherung des Browsens von Social-Media-Sites
* SSL-Zertifikate binden
    * Domainnamen, Servernamen oder Hostnamen
    * Eine Organisationsidentität (d.h. einen Unternehmensnamen) und einen Standort.

Quelle: [https://www.globalsign.com/de-de/ssl-information-center/was-ist-ein-ssl-zertifikat](https://www.globalsign.com/de-de/ssl-information-center/was-ist-ein-ssl-zertifikat)

## Wo kann man Zertifikate bekommen bzw.kann man sich diese selbst erstellen?

* Zertifikat erhalten
    * Zertifikate können gekauft werden
    * Werden von der CA (Central Authority) verwaltet
    * Gegen diese kann geprüft werden
* Zertifikat erstellen
    * Möglich, allerdings dann keine globale Gültigkeit (gilt als private Signatur)

## Wofür steht ein Zertifikat?

* Absender einer Nachricht kann so als legitim angesehen werden
* Website ist gesichert
* E-Mail Verschlüsselung und Authentifizierung

## Welche unterschiedliche Arten von Zertifikaten gibt es?

* SSL Zertifikat
* TLS Zertifikat
* Public Key
* Private Key

Quelle: [https://www.appvizer.de/magazin/kollaboration/digitale-signatur/ssl-zertifikat](https://www.appvizer.de/magazin/kollaboration/digitale-signatur/ssl-zertifikat)

## Wie kann man das Zertifikat beim Surfen erkennen?

* Hinweis des Browsers, dass Seite nicht gesichert ist, dass beim Aufruf gefragt wird, ob man auf diese Seite möchte
* Hinweise dafür
    * HTTPS
    * Plugin von Browsern, die das Anzeigen

<img src="./Browser_SSL-Zertifikat.png" height="200">

## Kann man eine SSL-geschützte Kommunikation abhören – ManInTheMiddle

* In Netzwerken mit HTTPS (via SSL/TLS) kann eine ManInTheMiddle Attacke eigene Schlüssel ausstellen und so die aktive Kommunikation mitlesen

Quelle: [https://www.ssl.com/de/Artikel/Browser-und-Zertifikats%C3%BCberpr%C3%BCfung/](https://www.ssl.com/de/Artikel/Browser-und-Zertifikats%C3%BCberpr%C3%BCfung/)

## Elektronische Unterschrift

* Die Handy-Signatur ist eine digitale Signatur, die einen Bürger gegenüber dem Staat eindeutig ausweist
* Wird in den kommenden Jahren durch eine EU weite ersetzt werden
* Möglichkeiten: PDF-Dateien signieren (elektronische Unterschrift), aber auch Wahlkarten anfordern, Volksbegehren ansehen und unterzeichnen und Impfzertifikate herunterladen
* Bei der Registrierung erzeugt der Client ein Identity Key Pair, einen Signed Pre Key, sowie mehrere nur einmal verwendbare Keys und sendet jeweils die Public Keys der Schlüsselpaare zum anderen

* Nachdem eine Session erfolgreich aufgebaut wurde, werden die Nachrichten zwischen den Clients mit AES-256 verschlüsselt. 
* Dabei wird jedoch für jede Nachricht ein eigener Key verwendet, der vom Chain Key abgeleitet wird. 
* Dadurch hätte jemand, der es schafft, den Key für eine Nachricht zu knacken, trotzdem keinen Zugriff auf andere Nachrichten.

## WhatsApp-Endverschlüsselung

* WhatsApp Ende zu Ende Verschlüsselung ist ein hybrides Verfahren
* Der Absender verschickt die Nachrichten mit einem Schloss und nur der Schlüssel des gewünschten Empfängers kann ihn öffnen. Dritten, wie z.B. dem Anbieter des Messengers, wird somit der Zugriff verwehrt und der Nachrichteninhalt wird über alle Übertragungsstationen zum Empfänger verschlüsselt versendet. Demzufolge ist das Sicherheitsniveau dieser Verschlüsselungsmethode sehr hoch.

* Für die Verschlüsselung bei WhatsApp ist erforderlich, dass sowohl beim Versender als auch beim Empfänger der Nachricht die aktuelle Version der App installiert ist. 
