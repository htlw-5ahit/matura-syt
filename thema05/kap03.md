# Einsatz von Frameworks wie React, Vue, Angular

## React

* Maintainer: Meta Plattforms (Facebook)
* Grundgerüst für die Ausgabe von User-Interface-Komponenten von Webseiten
* React bildet typischerweise die Basis für Single-Page-Webanwendungen, kann jedoch auch mit Node.js serverseitig (vor-)gerendert werden
* Kritik: Logik für Interaktion und Darstellung innerhalb eines Objekts bündelt

Quelle: [https://de.wikipedia.org/wiki/React](https://de.wikipedia.org/wiki/React)

## Vue

* Maintainer: Evan You (ehemaliger Google-Mitarbeiter im Bereich Angular)
* Clientseitiges JavaScript-Webframework
* MIT-Lizenz
* MVVM-Konzept (Model View ViewModel)
* Progressiv und inkrementell adaptierbar => Struktur der Anwendung nach eigenen Ansprüchen zu richten

Quelle: [https://de.wikipedia.org/wiki/Vue.js](https://de.wikipedia.org/wiki/Vue.js)

## Angular

* 2016 veröffentlicht
* Maintainer: Google LLC
* OpenSource
* TypeScript-basiertes Front-End-Webapplikationsframework
* Mobile-First-Ansatz

Quelle: [https://de.wikipedia.org/wiki/Angular](https://de.wikipedia.org/wiki/Angular)

## Express

* Serverseitiges Webframework für die JavaScript-basierte Plattform Node.js
* Erweitert Node.js um Werkzeuge, mit denen das Entwickeln moderner Webanwendungen einfacher gestaltet wird
* Express.js oft in Kombination mit NoSQL-Datenbanken wie MongoDB verwendet

Quelle: [https://de.wikipedia.org/wiki/Express.js](https://de.wikipedia.org/wiki/Express.js)

## Warum setzt man so etwas überhaupt ein?

* Erstellung von dynamischen HTML-Seiten
* Ermöglicht Reduzierung von Serverressourcen durch clientseitige Frameworks
* Einfache Möglichkeit den DOM zu verändern, ohne komplette Seite neuzuladen (Vgl: PHP)

## Grundidee von Vue

* Modular gehaltenes JavaScript-Framework 
* Kernfunktionalität: Oberflächenentwicklung
* MVVM-Konzept (Model View ViewModel)
* Performance durch virtuell abgebildetem DOM (Document Object Model)

Quelle: [https://blog.oio.de/2018/02/15/welches-javascript-framework-passt-zu-mir-vue-js/](https://blog.oio.de/2018/02/15/welches-javascript-framework-passt-zu-mir-vue-js/)

## Toolchain für Erstellung einer Vuebasierten App

* NodeJS mit NPM-Packetmanager als Basis für JavaScript-Frameworks
* Vue CLI zum Erstellen des Projektes

## Vue2/Vue3

Unterschiede: 
* Erstellung der App
* Mehrere Root-Elemente (div-Elemente für Bereiche) erlaubt
* Funktionen für setup() – Bereich
* Referenz Funktion ref( ) erstellt für Data-Bindings
* Methoden werden im setup( ) – Bereich erstellt

Quelle:
* [https://javascript.plainenglish.io/differences-between-vue-2-and-vue-3-ee627e2c83a8](https://javascript.plainenglish.io/differences-between-vue-2-and-vue-3-ee627e2c83a8)
* [https://visyu.de/blog/vue-2-vs-vue-3-das-sind-die-unterschiede/](https://visyu.de/blog/vue-2-vs-vue-3-das-sind-die-unterschiede/)

## Grundidee der „Reaktivität“

* Bei Reaktivität handelt es sich um ein Programmierparadigma
* Erst realisiert in Vue3
* Komponenten sind dynamisch und zur Laufzeit anpassbar

Quelle: [https://vuejs.org/guide/extras/reactivity-in-depth.html](https://vuejs.org/guide/extras/reactivity-in-depth.html)

## MVVM-Pattern

* MVVM ... Model View ViewModel
* Dient zur Trennung von Darstellung und Logik der Benutzerschnittstelle
* Vorteile:
    * Austauschbarkeit und unabhängige Komponenten
    * Verbesserte Testbarkeit
    * Direkte Ansicht von geänderten Daten

<img src="https://cdn1.vogel.de/unsafe/fit-in/1000x0/images.vogel.de/vogelonline/bdb/1943700/1943749/original.jpg" width="450">

Quelle: [https://www.dev-insider.de/was-bedeutet-mvvm-a-1103448/](https://www.dev-insider.de/was-bedeutet-mvvm-a-1103448/)

## Refresh des GUI

???

## Transpiler

* Transpiler in JavaScript sind Source-to-Source-Compiler
* Umwandlung von Nicht-JavaScript-Sprachen (CoffeeScript, TypeScript, LiveScript usw.) in JavaScript-Quellcode
* Beispiel: Babel oder HipHop (Facebook)

```
Code --(parse)-->AST--(transform)-->AST--(generate)-->Code
```

Quelle:
* [https://devopedia.org/transpiler](https://devopedia.org/transpiler)
* [https://de.wikipedia.org/wiki/Compiler](https://de.wikipedia.org/wiki/Compiler)

## Informations/Datenhaltung in einer VueAnwendung

* Zentral in `App.vue`
* Mittels `ref()`–Funktion zu realisieren
* Im Template-Bereich 

## Progressive Framework

* Progressive Frameworks: Vue, React, Angular
    * Wichtigstes ist Vue
* Wichtige Eigenschaften von progressiven Frameworks sind
    * Leichtgewichtig
    * Neu und modern
    * Relativ einfach zu erlernen
    * Simple ausgerichtet
* Trotz so simpler Ausrichtung sind progressive Frameworks sehr mächtige Werkzeuge

Quelle: [https://www.interactivated.me/blog/progressive-javascript-framework/](https://www.interactivated.me/blog/progressive-javascript-framework/)

## Single-File-Component

* Ist das uns bekannte Format für eine `.vue`-Datei
* In einer solchen Datei ist sowohl das Template, als auch das Skript und das Design inkludiert

```html
<script>
export default {
  data() {
    return {
      greeting: 'Hello World!'
    }
  }
}
</script>

<template>
  <p class="greeting">{{ greeting }}</p>
</template>

<style>
.greeting {
  color: red;
  font-weight: bold;
}
</style>
```

Quelle: [https://vuejs.org/guide/scaling-up/sfc.html](https://vuejs.org/guide/scaling-up/sfc.html)

## Typische Struktur eines *.vue-Files?

```html
<template>
    <div>
        <div id="header">
            <img src="@/assets/logo.png" alt="HTL Logo">
            <h2>Stundenplan für:</h2>
            <h3>{{name}}</h3>
        </div>
    </div>
</template>

<script>
export default {
    name: "Header",
    props: {
        name: {
            type: String,
            required: true,
        },
    },
}
</script>

<style scoped>
#header {
    display: flex;
    flex-wrap: wrap;
    align-items: baseline;
    justify-content: center;
}
#header h3 {
    margin-left: 10px;
}
img {
    height: 100px;
    margin-right: 20px;
}
</style>
```

## Template Syntax

* Format für Vue
* Jedes Vue-Template ist im Prinzip reiner HTML Code (kann mit einem Transpiler übersetzt werden)
* Vue baut in seinem Template einen Vue-DOM auf, also bestehend aus einzelnen Elementen; auch dieser kann 1:1 nach HTML übersetzt werden

Quelle:
* [https://vueschool.io/lessons/vue-js-3-template-syntax-and-expressions](https://vueschool.io/lessons/vue-js-3-template-syntax-and-expressions)
* [https://vuejs.org/guide/essentials/template-syntax.html](https://vuejs.org/guide/essentials/template-syntax.html)

## Wie wird „Reactivity“ realisiert?

* Siehe Reaktivität Beschreibung (für mehr Infos)
* Im export default muss das data( ) { … } Feld genutzt werden müssen

```js
export default {
  data() {
    return {
      count: 1
    }
  },

  // `mounted` is a lifecycle hook which we will explain later
  mounted() {
    // `this` refers to the component instance.
    console.log(this.count) // => 1

    // data can be mutated as well
    this.count = 2
  }
}
```

Quelle: [https://vuejs.org/guide/essentials/reactivity-fundamentals.html](https://vuejs.org/guide/essentials/reactivity-fundamentals.html)

## Properties und deren Verwendung

* Im `export default`-Bereich zu definieren mit dem `props: { ... }`-Feld
* Für jede Eigenschaft in der Objektdeklarationssyntax ist der Schlüssel der Name der zum einzelnen Property
* Properties sind in einer Komponente und in allen Komponenten, die diese Komponente erzeugen verfügbar

```js
export default {
  props: {
    title: String,
    likes: Number
  }
}
```

Quelle: [https://vuejs.org/guide/components/props.html](https://vuejs.org/guide/components/props.html)

## List Rendering

* Ist das durchlaufen eines/r Arrays/Liste und der Anzeige von Daten
* Die Optionen hierfür groß 
* Bekannteste Option ist das Tag v-for

```js
data() {
  return {
    parentMessage: 'Parent',
    items: [{ message: 'Foo' }, { message: 'Bar' }]
  }
}
```

```html
<li v-for="(item, index) in items">
  {{ parentMessage }} - {{ index }} - {{ item.message }}
</li>
```

Quelle: [https://vuejs.org/guide/essentials/list.html](https://vuejs.org/guide/essentials/list.html)

## Handling von Forms

* Tag: `v-model`
* Ansprechbares Tag im Skript-Teil
* Binding für Werte/Methoden ist ebenfalls möglich (Binding über `ref()`)

Quelle: [https://012.vuejs.org/guide/forms.html](https://012.vuejs.org/guide/forms.html)

## Event-Handling (z.B. Button-Click)

* Kann direkt behandelt werden oder Event kann auf den Bus gelegt werden
* Mit dem @-Operator in einem Template-Tag kann eine Funktion aus dem Skript Teil als Handler herangezogen werden

```html
<button @click="count++">Add 1</button>
<p>Count is: {{ count }}</p>
```

Quelle: [https://vuejs.org/guide/essentials/event-handling.html](https://vuejs.org/guide/essentials/event-handling.html)

## Componenten-Orientierung

* Eine Komponente soll universell einsetzbar sein
* Zusätzlich soll eine zentrale Verwaltungsstelle eingerichtet werden
* Mittels Vue3-Router können dann nur gewünschte Komponenten angezeigt werden (Footer, Nav und Header sollen immer angezeigt werden)

Quelle: [https://entwickler.de/javascript/vuejs-tutorial-so-entwickelt-man-komponenten-mit-vuejs](https://entwickler.de/javascript/vuejs-tutorial-so-entwickelt-man-komponenten-mit-vuejs)

## Anforderungen an eine Component

s.o.

## Props

s.o.

## Registrierung

* Registrierung einer Komponente ist notwendig, um sie in einer anderen Komponente nutzen zu können

```html
<script>
    import Stundenplan from "./components/Stundenplan.vue";
    import Header from "./components/Header.vue";
    import Login from "./components/Login.vue";
    import {
        ref
    } from "vue";
...
```

## Konzept der losen Bindung

???

## Error-Handling

* Fehlernachrichten sollten immer in der GUI über ein Elemente mit Text (meist eine `ref`-Variable) darstellt werden.
* Nicht nur Fehler sollen gemeldet werden, auch zB. ein erfolgreiches Speichern sollte dem Benutzer vermittelt werden.

## Asynchronitäten in einer Vue-Anwendung

-- nicht gemacht --

## Debugging

* mittels Konsolenausgaben
* Browser-Plugin von Vue3
* Debugger in der Entwicklungsumgebung

## States

-- nicht gemacht --

## Kommunikation von Components

* über Properties
* `context.emit(<name>, <liste von variablen>`
* [VueX-Store](https://vuex.vuejs.org/guide/) (verwendet beim [Bundesliga-Beispiel](https://github.com/HITWELS/bundesliga-5ahit-5ahit/blob/main/src/store/index.js))

## Nutzung von Modulen

* analog NodeJS
* Module können über `npm install <package name>` nachinstalliert werden.
* Diese werden in der `package.json` im obersten Projektordner abgelegt.