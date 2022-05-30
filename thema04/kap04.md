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
* *Gestaltung in HTML Code direkt oder in externer CSS-Datei

## Selektoren - Arten - Beispiele für den Einsatz

<table>
    <thead>
        <tr>
            <td>Typ</td>
            <td>Beschreibung</td>
            <td>Beispiel</td>
        <tr>
    </thead>
    <tbody>
        <tr>
            <td>Typenselektor</td>
            <td>Alle Elemente eines Typs werden angesprochen</td>
            <td>
                ```css
                    h1 { 
                        color: red; 
                    }
                    h1, h2 { 
                        background-color: #ccc;
                        border-radius: .5em; 
                    }
                ```
            </td>
        <tr>
        <tr>
            <td>Klassenselektor</td>
            <td>Ein Klassenselektor spricht Elemente an, die einer bestimmten Klasse zugehörend sind.</td>
            <td>
                ```html
                    <style>
                        .beispiel {font-style: italic;}
                        .beispiel.hinweis {color: green;}
                    </style>
                    <p class="beispiel">Dieser Absatz gehört zur Klasse beispiel und seine Schrift wird deshalb kursiv dargestellt.</p>
                    <p class="beispiel hinweis">Dieser Absatz gehört sowohl zur Klasse beispiel als auch zur Klasse hinweis und sein Text wird deshalb grün und kursiv dargestellt.</p>
                ```
            </td>
        <tr>
        <tr>
            <td></td>
            <td></td>
            <td></td>
        <tr>
        <tr>
            <td></td>
            <td></td>
            <td></td>
        <tr>
    </tbody>
</table>

## Anforderungen an den Browser



## Was besagt das Flexboxmodell und wie wirkt sich dieser in der praktischen Arbeit aus.



## Welche CSS-Anweisungen sind symptomatisch für das Flexboxmodell



## Komplexität von CSS



## Vererbung/Fehlerbehandlung/Debugging



## Welche Unterstützung bieten Frameworks wie Bootstrap an?



## Welche Möglichkeiten bietet dieses Framework und welche Problembereiche werden damit abgedeckt?



## Wer ist der Eigentümer der Bootstrap-Technologie und welche lizenzrechtlichen Vorkehrungen sind zu beachten?



## Wo kann ich mich hinwenden, wenn es Probleme gibt?



## Vor-/Nachteil von Bootstrap



## Aweseome Fonts



## Anfoderungen an den Layouter


