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

* Richtige interpretieren des CSS-Codes
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



## Vererbung/Fehlerbehandlung/Debugging



## Welche Unterstützung bieten Frameworks wie Bootstrap an?



## Welche Möglichkeiten bietet dieses Framework und welche Problembereiche werden damit abgedeckt?



## Wer ist der Eigentümer der Bootstrap-Technologie und welche lizenzrechtlichen Vorkehrungen sind zu beachten?



## Wo kann ich mich hinwenden, wenn es Probleme gibt?



## Vor-/Nachteil von Bootstrap



## Aweseome Fonts



## Anfoderungen an den Layouter


