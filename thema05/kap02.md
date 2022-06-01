# Serverseitiges Javascript

## NodeJS - Grundidee/Konzeption/Struktur, Modulkonzept (Import-/Export)

???

## npm/yarn

* npm
    * Paketmanager für die JavaScript-Laufzeitumgebung Node.js
    * Open-Source-Entwickler verwenden npm, um Softwarepackete zu teilen

* yarn
    * Zusammenarbeit von Facebook, Exponent, Google und Tilde
    * Ziel: Konsistenz-, Sicherheits- und Leistungsprobleme mit großen Codebasen zu lösen

* npm vs yarn
    * Populärer ist NPM bei den allgemeinen Downloads, auf GitHub hat Yarn jedoch ca. das 10-fache an Teilnehmern/Favoriten
    * Die Installation von NPM ist einfacher als jene von Yarn, kommt jedoch immer im vollen Umfang
    * Yarn ist im Vergleich zu NPM jedoch deutlich schneller
    * Nach aktuellem Stand ist NPM in der Version 6, der aktuellen Version, sicherer als Yarn
    * Beim Updaten sind beide Package Manager gleich (effektiv)

Quelle:
* [https://de.wikipedia.org/wiki/Npm_(Software)](https://de.wikipedia.org/wiki/Npm_(Software))
* [https://en.wikipedia.org/wiki/Yarn_(package_manager)](https://en.wikipedia.org/wiki/Yarn_(package_manager))

## Start/Stop von NodeJSAnwendungen

* Starten
    * `node <main js file>`
* Stoppen
    * In der Konsole: `Strg + C`
    * Im SourceCode: `server.close()`

Quelle: [https://serverfault.com/questions/256331/how-to-stop-node-js-server](https://serverfault.com/questions/256331/how-to-stop-node-js-server)

## Debugging

* Ausgabe in die Konsole
* V8 Inspector des Browsers (Plugin)
* Debugger in der Entwicklungsumgebung verwenden

## einfaches Beispiel

* [Webserver Beispiel](https://github.com/htlw-5ahit/matura-syt/tree/main/thema05/webserver-example)

## Management der Module

* Module werden in einem eigenen Ordner gespeichert
* Können mit NPM oder YARN zentral verwaltet (installiert, geupdatet, gelöscht) werden

## Update von Modulen

* Können mit NPM oder YARN zentral verwaltet (installiert, geupdatet, gelöscht) werden
* Version kann auch in den dependencies manuel eingestellt werden, aber Achtung: Es werden dann die angegebenen Versionen versucht herunterzuladen, unabhängig der Stabilität, Funktionalität, etc

Quelle: [https://nodejs.dev/learn/update-all-the-nodejs-dependencies-to-their-latest-version](https://nodejs.dev/learn/update-all-the-nodejs-dependencies-to-their-latest-version)

## Erfolgreiche Module wie ExpressFramework

* Stellt sogenannte Routen zur Verfügung, mittels welchen man versteckte und öffentlich Pfade auf der Website erstellen kann
* Große Anzahl an APIs verfügbar
* Hohe Leistungsfähigkeit bei geringer Leistungsanforderung

Quelle: [https://de.wikipedia.org/wiki/Express.js](https://de.wikipedia.org/wiki/Express.js)

## Passport-Framework

* Modul für Node.JS
* Passport ist eine Authentifizierungsmiddleware
* Bietet Möglichkeiten Passwörter eines Nutzers zu hashen, Eingaben gegen gespeicherte Nutzer zu vergleichen uvm.
* mehrere Strategien für die Authentifizierung: Benutzername und Passwort, Facebook, Twitter und mehr (SSO)

Quelle: [https://www.passportjs.org/](https://www.passportjs.org/)

## Maßnahmen in Bezug auf IT-Security

* Installation von Libraries, die wirklich benötigt werden
* CORS
* WAF ... Web Application Firewall

Quelle: [https://siwecos.de/wiki/Webseite_absichern](https://siwecos.de/wiki/Webseite_absichern)