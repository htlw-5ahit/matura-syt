# NoSQL

## Grundstruktur eines SQL-Datenbestandes

* Sie besteht aus Tabellen
    * Diese Tabellen bestehen aus Zeilen und Spalten
    * Die Zeilen stellen den so genannten Datensatz dar
    * Die Spalten beinhalten die einzelnen Komponenten eines Datensatzes
    * Jede Spalte muss einen bestimmten Datentyp haben
* Über Schlüssel werden die Tabellen miteinander verknüpft

## Was ist eine Relation?

* Beziehung zwischen zwei Elementen
* Umsetzung: Tupel werden über Schlüsseln (meist Primärschlüssel) miteinander verbunden.
* Beispiel: <img src="https://image.jimcdn.com/app/cms/image/transf/dimension=516x10000:format=png/path/s834d64c225dfb243/image/icf557f1702e8db7e/version/1567464597/image.png" width="400">

## Was besagt die relationale Algebra?

* Menge von Operationen zur Manipulation von Relationen
* Ermöglicht es, Relationen zu filtern, zu verknüpfen, zu aggregieren oder anderweitig zu modifizieren, um Anfragen an eine Datenbank zu formulieren.

## Was ist ein Schema?

* Formale Beschreibung der Struktur von Daten

<img src="http://www.gitta.info/DBSysConcept/de/image/analogie.gif" width="400">

## Was versteht man unter Normalisieren?

Normalisierung ist eine Sammlung von Regeln, die eingehalten werden sollten, um Probleme wie ... zu vermeiden.
* Übersichtlichkeit
* Redundanzen (doppelt Gespeicherte Informationen)
* Anomalien/Inkonsistenzen (widersprüchliche Daten, logische Brüche in der DB)
* [Exkurs: Normalisierung aus dem SEW/INSY-Teil]/(https://htlw-5ahit.github.io/matura-sew-insy/thema08/kap04.html)

Sie gliedert sich in fünf Normalformen plus vier Sonderformen.

## Welche sinnvoll verwendbare Normalisierungsformen gibt es

Für normale Anwendungen reichen die ersten drei Normalformen aus.

## SQL als Abfragesprache

* SQL ... Structured Query Language
* Sprache für die Kommunikation mit relationalen Datenbanken
* Mit SQL-Befehlen lassen sich Daten relativ einfach einfügen, verändern oder löschen
* Die meisten der existierenden Datenbanksysteme verfügen über SQL-Schnittstellen

## Vor-/Nachteile von SQL

* Vorteile
    * Schnellere Abfrageverarbeitung
    * Keine Programmierkenntnisse
    * Standardisierte Sprache
    * Portabel (Plattformunabhängig)
    * Mehrere Datenansichten (Views)
* Nachteile
    * Abrufen von Daten bei mehreren Tabellen

Quelle: [https://de.acervolima.com/vor-und-nachteile-von-sql/](https://de.acervolima.com/vor-und-nachteile-von-sql/)

## Für welche Problembereiche eignet sich eine SQL-DB?

???

## Verwendung von SQL in einer Applikationssprache wie Java/Javascript – wie können beispielsweise Objekte abgespeichert werden?

* Durch die Verwendung eines Object Document Mapper (ODM)
* [siehe Thema 06 Kapitel 02](./kap02.md)

## Daten als Mengen – ist dies ein Problem?

????

## JSON als Datenformat für web-basierte Lösungen (Java-Script) – Wo liegt hier der Vorteil?

* JSON ... JavaScript Object Notation
* Auf der Basis von JavaScript entwickelt
* JSON ist keine eigene formale Sprache

## Können JSON-basierte Daten in einer SQL-DB abgespeichert werden?

* Ja.

## Json & Strukturierung (komplexe Datenstrukturen)?

???

## Wo stößt SQL an die „Grenzen“?

???

## Was versteht man unter „Big Data“?

* Der Begriff „Big Data“ bezieht sich auf Datenbestände, die so groß, schnelllebig oder komplex sind, dass sie sich mit herkömmlichen Methoden nicht oder nur schwer verarbeiten lassen. Das Speichern großer Datenmengen oder der Zugriff darauf zu Analysezwecken ist nichts Neues.

* Definition von Big Data mit dem 3-V-Modell:
    * Volume (Masse)
    * Velocity (Geschwindigkeit)
    * Variety (Vielfalt)

Quelle: [https://www.sas.com/de_at/insights/big-data/what-is-big-data.html](https://www.sas.com/de_at/insights/big-data/what-is-big-data.html)

## Was sind NoSQL oder doumentenorientierte Datenbanken?

* NoSQL = „not only SQL“
* verteilte und horizontale Skalierbarkeit, gleichrangige Knoten (verteilte Hardware -> hohe Ausfallsicherheit)
* kostengünstige Rechnersysteme zur Datenspeicherung
* kein relationales Datenmodell (kein SQL)
* schemafrei / schwache Schemarestriktionen
* keine Transaktionen (nach gewisser Zeit konsistenter Zustand)
* für spezifische Problemstellungen (zB. BigData-Anwendungen)
* Einteilung
    * Document Store
    * Key/Value Store
    * Graph
    * Wide Column Store (spaltenorientiert)

## Was versteht man in diesem Kontext unter einem „Document“?

<img src="https://htlw-5ahit.github.io/matura-sew-insy/thema10/MongoDB_Datenbankstruktur.png" width="400">

## Schemenlosen Datenbanken – was muss man hier alles beachten?

???

## Einsatzgebiet von NoSQL-Datenbanken – für welche Problembereiche besonders geeignet?

* Die horizontale Skalierbarkeit
* Das Vermeiden von unnötiger Komplexität,
* Eine hohe Performance und ein hoher Durchsatz,
* Die Nutzung von allgemein gebräuchlicher Hardware,
* Die Vermeidung von relationalen Ansätzen des Datenmappings,
* Die Einfachheit in der Installation und Konfiguration von verteilten Datenbank-Clustern

## Mongo als Beispiel für eine schemenlose DB – gehe auf Mongo näher ein

* Dokumentenorientiertes NoSQL-Datenbankmanagementsystem
* Verwaltung von Sammlungen von JSON-ähnlichen Dokumenten
* Weitest verbreitete NoSQL-Datenbank
* Replikation
* Sharding

Quelle: [https://de.wikipedia.org/wiki/MongoDB](https://de.wikipedia.org/wiki/MongoDB)

## Können Documents auch per Update verändert werden?

* Ja
* `update()`
* `updateOne()`
* `updateMany()`

## Was muss man dann beim Zugriff auf dieses Objekt wissen? 

* Die verwendeten Keys eines Dokuments, da bei schemenlosen Datenbanken nicht alle Keys vorhanden sind.
* Abfrage auch `null` bzw. `undefined` bevor damit gearbeitet werden kann.

## Abfragesprache für Mongo?

* MongoDB verzichtet auf eine Abfragesprache wie SQL.
* Stattdessen erfolgen die Datenmanipulation und -Abfrage anhand von Objektspezifischen Methoden, die für alle gängige Programmiersprachen verfügbar sind.