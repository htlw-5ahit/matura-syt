# Layout (CSS/Bootstrap)

## CSS - Anforderung an eine Web UI

* CSS ... Cascading Style Sheets
* Gestaltungs- und Formatierungssprache für das Aussehen von HTML-Dokumenten
* Ziel: Trennen von Inhalte und Aussehen
* Standardisierung und Entwicklung von W3C-Gremium
* Problematik: Einschränkungen bei der Darstellung des Layouts bei verschiedenen Browsern

## Responsive Design

* eine Internetseite je nach Bildschirmgröße und/oder Gerät anders dargestellt, um die Besucherfreundlichkeit zu gewährleisten
* Responsive Webdesign mit der Angabe des Viewport gehört heute zum Standard bei der Mobile Optimierung.
* Wird immer wichtiger, da es immer mehr Seitenzugriffe über das Smartphone abgewickelt werden.

## Rolle von CSS

* Gestaltung von Website (Design, Layout, Reaktion auf Eingaben, …) 
* Gestaltung in HTML Code direkt oder in externer CSS-Datei

## Selektoren - Arten - Beispiele für den Einsatz

| Typ               | Beispiel                                                                                                                           |
|-------------------|------------------------------------------------------------------------------------------------------------------------------------|
| Typ-Selektor      | [Beispiel](https://wiki.selfhtml.org/extensions/Selfhtml/frickl.php/Beispiel:CSS-Einstieg-1.html#view_result)                      |
| Klassenselektor   | [Beispiel](https://wiki.selfhtml.org/extensions/Selfhtml/frickl.php/Beispiel:CSS_grundlagen_klassenselektor.html#view_result)      |
| ID-Selektor       | [Beispiel](https://wiki.selfhtml.org/extensions/Selfhtml/frickl.php/Beispiel:CSS_grundlagen_id-selektor.html#view_result)          |
| Universalselektor | [Beispiel](https://wiki.selfhtml.org/extensions/Selfhtml/frickl.php/Beispiel:CSS_universalselektor.html#view_result)               |
| Attributselektor  | [Beispiel](https://wiki.selfhtml.org/extensions/Selfhtml/frickl.php/Beispiel:CSS_grundlagen_attributpr%C3%A4senz.html#view_result) |

### Pseudoklassen

Eine Pseudoklasse in CSS ist ein Schlüsselbegriff, welcher hinter einen Selektor gestellt wird, um einen besonderen Zustand abzufragen. 

* `:active`
* `:checked`
* `:default`
* `:disabled`
* `:enabled`
* `:focus`
* `:hover`
* ... ([alle weiteren Pseudoklassen](https://developer.mozilla.org/de/docs/Web/CSS/Pseudo-classes))

## Anforderungen an den Browser

* Richtiges interpretieren des CSS-Codes
* Problem: Browserkompatibilität nicht bei allen CSS-Befehlen vorhanden.

## Was besagt das Flexboxmodell und wie wirkt sich dieser in der praktischen Arbeit aus.

* Flexible Box Layout Module
* wesentliche Technik zur Gestaltung von Layouts mit CSS
* sehr mächtige und komfortable Anwendung

* Container die Möglichkeit geben, die Breite/Höhe (und Reihenfolge) seiner Elemente zu ändern, um den verfügbaren Platz optimal auszufüllen
* Im Gegensatz zu den regulären Layouts (Block (vertikal basiert), Inline (horizontal basiert)) richtungsunabhängig ist
* Elemente entlang der Hauptachse bzw. der Querachse angeordnet

<img src="https://css-tricks.com/wp-content/uploads/2018/11/00-basic-terminology.svg" width="350">

## Welche CSS-Anweisungen sind symptomatisch für das Flexboxmodell

| Typ | Darstellung | CSS-Befehl |
|---|---|---|
| `flex-direction` | <img src="https://css-tricks.com/wp-content/uploads/2018/10/flex-direction.svg" width="350"> | ```flex-direction: row | row-reverse | column | column-reverse;``` |
| `justify-content` | ![](https://css-tricks.com/wp-content/uploads/2018/10/justify-content.svg) | ```justify-content: flex-start | flex-end | center | space-between | space-around | space-evenly | start | end | left | right ... + safe | unsafe;``` |
| `align-items` | ![](https://css-tricks.com/wp-content/uploads/2018/10/align-items.svg) | ```align-items: stretch | flex-start | flex-end | center | baseline | first baseline | last baseline | start | end | self-start | self-end + ... safe | unsafe``` |
| `align-content` | ![](https://css-tricks.com/wp-content/uploads/2018/10/align-content.svg) | ```align-content: flex-start | flex-end | center | space-between | space-around | space-evenly | stretch | start | end | baseline | first baseline | last baseline + ... safe | unsafe;``` |

## Komplexität von CSS

?

## Vererbung/Fehlerbehandlung/Debugging

Vererbung

* Konzept der Vererbung wurde mit CSS 2 eingeführt
* Übertragung der deklarierten CSS-Werte von einem Element auf das nachfolgende
* Jedes Element des Dokuments seine Werte an seine Kind-Elemente weiter
* Vorteil: Regeln für Kindelemente muss die Regel nun nicht mehr neu definiert werden

Fehlerbehandlung / Debugging

* Überprüfung mit Developer-Tools, welche im Browser eingebaut sind (Rechtsklick > "Untersuchen")
* Aktivierung/Deaktivieren einzelner CSS-Regeln bzw. hinzufügen neuer Regeln

## Welche Unterstützung bieten Frameworks wie Bootstrap an?

* Bootstrap ist ein Frontend-Framework
* Diverse Gestaltungsvorlagen, die auf HTML und CSS basieren, sowie optionale JavaScript-Erweiterungen
* Wichtige Komponente: Bootstrap-Grid-Layout
    * Aufteilung des Layouts in 12 Spalten
    * Erleichtert Abstände und Positionierung der einzelnen Website-Elemente punktgenau zu bestimmen
* Unterstützung des Responsive Webdesigns

## Welche Möglichkeiten bietet dieses Framework und welche Problembereiche werden damit abgedeckt?

* Buttons
* Typographie
* Tabellen
* Formulare
* Navigationselemnte & -bar
* Indikatoren wie Alerts, Prozessbar, ...
* Container
* Modals
* ...

## Wer ist der Eigentümer der Bootstrap-Technologie und welche lizenzrechtlichen Vorkehrungen sind zu beachten?

* Lizenz: MIT-Lizenz
* Entwickler: Twitter

* Anforderungen an den Nutzer
    * Die Lizenzmarkierungen müssen in allen genutzten Dateien von Bootstrap beibehalten werden
* Erlaubter Nutzen für des Nutzers
    * Gratis Download und Nutzen für private, geschäftliche, persönliche oder unternehmensinterne Anwendungen
    * Weiterverarbeitung von Bootstrap
    * Bearbeiten des Ausgangsmaterials
* Verbot für den Benutzer
    * Einreichen für Beschwerden bei Problemen, Bootstrap wird ohne Gewährleistung veröffentlicht
    * Anzeige gegen die Urheber oder Urheberrechtsinhaber von Bootstrap 
    * Löschen von Markenzeichen, die den Nutzen von Bootstrap symbolisieren

## Wo kann ich mich hinwenden, wenn es Probleme gibt?

* An die Entwickler-Community via GitHub
* [https://github.com/twbs/bootstrap/discussions](https://github.com/twbs/bootstrap/discussions)

## Vor-/Nachteil von Bootstrap

* Vorteile
    * Responsive Design
    * Kürzere Entwicklungszeit
    * Templates
    * Verweendung von Icons
    * Dokumentation
    * Freie Verwendbarkeit
* Nachteile
    * Bei kleinen Projekten, viel Overhead

## Aweseome Fonts

* Bibliothek von vielen verschiedenen Icons
* kostenlose sowie kostenpflichtige Version
* 5 Symbolstile: Solid, Regular, Light, Duoton und Thin 

## Anfoderungen an den Layouter

* Einheitliches Layout für die ganze Webseite
    * Fonts, Schriftgrößen, Farben, ..
* Übersichtliche Navigation
* Planung vor Entwicklung!