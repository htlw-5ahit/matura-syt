# HTML

## Auszeichnungssprache

* maschinenlesbare Sprache für die Gliederung und Formatierung von Texten und anderen Daten
* Beispiele: Hypertext Markup Language (HTML), LaTeX, Markdown

## W3Consortium

* Gremium zur Standardisierung der Techniken im World Wide Web
* Gründung: 1. Oktober 1994 am MIT Laboratory for Computer Science in Cambridge (Massachusetts)
* Gründer und Vorsitzender ist Tim Berners-Lee, der als Erfinder des World Wide Web gilt
* W3C entwickelt technische Spezifikationen und Richtlinien

## XML

* Extensible Markup Language 
* Auszeichnungssprache zur Darstellung hierarchisch strukturierter Daten im Format einer Textdatei
* XML wird auch für den plattform- und implementationsunabhängigen Austausch von Daten zwischen Computersystemen eingesetzt
* Beispiele für XML-Sprachen sind: RSS, MathML, GraphML, XHTML, XAML, Scalable Vector Graphics (SVG), GPX, aber auch das XML-Schema selbst
* wichtigste Struktureinheit: Element
    * Enthält Text oder auch weitere Elemente als Inhalt
    * Elemente bilden die Knoten des Strukturbaumes eines XML-Dokumentes
* Tags
    * ein Starttag: `<Elementname>`
    * ein Endtag: `</Elementname>`
    * ein Leertag: `<Leer/>`

## DOM

* DOM ... Document Object Model 
* Wird vom World Wide Web Consortium definiert
* Für den gesamten Baum gibt es genau 1 Root Element

<src img="https://wiki.selfhtml.org/images/thumb/0/01/DOM-1.svg/1000px-DOM-1.svg.png" width="500">

## HTML-Code

[https://www.html-seminar.de/befehlsuebersicht.htm](https://www.html-seminar.de/befehlsuebersicht.htm)

## Ähnlichkeiten zu anderen Auszeichnungssprachen wie Latex

* Behandeln unterschiedliche Probleme
* HTML zielt auf einen Webbrowser ab, während LaTeX auf Papier abzielt.
* Herausforderung bei HTML: nicht zu wissen, wie jemand anderes das Dokument verwendet; Unterschiedliche Browser, variable Auflösungen, ...
* HTML durch CSS graphisch anpassbar 

## Unterschied zu Winword

* HTML-Dateien sind in Plaintext abgespeichert und können von jedem Texteditor geöffnet und bearbeitet werden.
* Word-Dateien sind Binärdateien, die nur mit kompatiblen Programmen geöffnet werden können.

## Links

* Durch Links können auf andere im Internet verfügbaren Ressourcen verlinkt werden.
* Beispiel: `<a href="https://de.w3docs.com/">W3Docs.com</a>`

## HTML 5 mit Dokumentenstruktur (Seiten-/Textstrukturierung, Links, Formulare, Multimedia, Tabellen)

### Seitenstrukturierung

| HTML-Befehle                       | Beschreibung                                                  |
|------------------------------------|---------------------------------------------------------------|
| `<!DOCTYPE html>`                  | HTML5-Doctype, erste Zeile der HTML-Datei                     |
| `<head>`                           | Head-Bereich, der Metainformationen über die Webseite enthält |
| `<meta charset="UTF-8">`           | Verwendete Codierung                                          |
| `<title>HTML5-Grundgerüst</title>` | Titelzeile im Browserfenster                                  |
| `</head>`                          |                                                               |
| `<body>`                           | Umschließt den Inhalt, der im Browserfenster angezeigt wird   |
| `...`                              | alle weiteren HTML-Befehle                                    |
| `</body>`                          |                                                               |
| `</html>`                          | Ende der HTML-Seite                                           |

### Textstrukturierung

| HTML-Befehle                      | Beschreibung                  |
|-----------------------------------|-------------------------------|
| `<h1> … </h1>`                    | Hauptüberschrift              |
| `<h2> … </h2>` bis `<h6> … </h6>` | Unterüberschriften            |
| `<p> … </p>`                      | Absatz                        |
| `<br>`                            | erzwungener Zeilenumbruch     |
| `<hr>`                            | Trennlinie                    |
| `<b> … </b>`                      | Schrift wird fett angezeigt   |
| `<i> … </i>`                      | Schrift wird kursiv angezeigt |
| `<del> … </del>`                  | durchstrichener Text          |

### Links

| HTML-Befehle                                   | Beschreibung                   |
|------------------------------------------------|--------------------------------|
| `<a href="URL">BESCHREIBUNG</a>`               | interne und externe Links      |
| `<a href="#xy"> … </a>`                        | Sprungmarke                    |
| `<a href="mailto:abc@xyz.com">abc@xyz.com</a>` | E-Mail Adresse verlinken       |

### Formulare

### Multimedia

### Tabellen

## Trennung zwischen Layout und Text

- HTML legt fest, was auf der Seite stehen soll (struktureller Aufbau einer Webseite)
- CSS legt fest, wie es dargestellt werden soll (Formatierung & Gestaltung)
- JavaScript legt fest, was passieren soll (interaktive Elemente)

## Kann man unter HTML5 noch Layout-Tags verwenden?

* Ja, kann man.
* Nicht mehr aktuell => Strenge Trennung zwischen Layout und Inhalt
* Beispiele: `<header>`, `<nav>`, `<section>`, `<article>`, `<aside>`, `<details>`, `<summary>` ([https://www.w3schools.com/html/html_layout.asp](https://www.w3schools.com/html/html_layout.asp))

## Kann eine HTML-Seite manipuliert werden und wie kann man sich gegebenenfalls davor schützen?

* HTML-Seiten können über Developer-Tools bearbeitet werden. Dies passiert nur lokal im Browser, und deshalb sicherheitstechnischer weniger relevant.
* Jedoch können Eigenschaften (Typ, Minimum, Maximum, ...) Input-Felder verändert werden. Um dies auszuschließen, muss serverseitig ebenfalls auf die Kriterien geprüft werden.

## CORS

* CORS ... Cross-Origin Resource Sharing
* Same-Origin-Policy (SOP) verbietet beim Besuch einer Website das Nachladen von anderen Server
    * Alle Daten sollen von der gleichen Quelle kommen, also dem gleichen Server entspringen.
* Ist aber beiden Websitebetreibern der Datenaustausch bekannt und von diesen auch gewünscht, kann man den Vorgang per Cross-Origin Resource Sharing erlauben.

<img src="https://www.ionos.at/digitalguide/fileadmin/DigitalGuide/Schaubilder/cross-origin-resource-sharing-ablauf.png" width="400">

Quelle: [https://www.ionos.at/digitalguide/websites/web-entwicklung/cross-origin-resource-sharing-erklaert/](https://www.ionos.at/digitalguide/websites/web-entwicklung/cross-origin-resource-sharing-erklaert/)

### CORS-Header

* Access-Control-Allow-Origin: Welche Herkunft ist erlaubt?
* Access-Control-Allow-Credentials: Sind Anfragen auch dann erlaubt, wenn der Credentials Mode auf include gesetzt ist?
* Access-Control-Allow-Headers: Welche Header dürfen verwendet werden?
* Access-Control-Allow-Methods: Welche HTTP-Request-Methoden sind erlaubt?
* Access-Control-Expose-Headers: Welche Header dürfen angezeigt werden?
* Access-Control-Max-Age: Wie alt darf die Preflight-Anfrage sein, bevor sie ihre Gültigkeit verliert?
* Access-Control-Request-Headers: Welcher HTTP-Header ist in der Preflight-Anfrage angegeben?
* Access-Control-Request-Method: Welcher HTTP-Methode ist in der Preflight-Anfrage angegeben?
* Origin: Was ist die Quelle der Anfrage?

```
Access-Control-Allow-Origin: http://example.com
Access-Control-Allow-Methods: PUT, POST, DELETE
```

## HTML eine Programmiersprache?

Nein, eine Auszeichnungssprache.

## Statisches/Dynamisches HTML?

* statisches HTML
    * separate Dokumente entwickelt und anschließend auf dem Server platziert
* dynamisches HTML
    * Beispiel: CMS- oder Shop-Systeme
    * Serverseitung: Perl, PHP, ASP, ...
    * Clientseitig: JavaScript, JS-Frameworks, ...

| Statische Webseiten                                      | Dynamische Webseiten                                      |
|----------------------------------------------------------|-----------------------------------------------------------|
| ![](https://img.kompaktdesign.com/statische-website.png) | ![](https://img.kompaktdesign.com/dynamische-website.png) |