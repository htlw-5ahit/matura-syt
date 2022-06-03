# Nebenläufigkeiten & Asynchronitäten

## Definition

* Die Nebenläufigkeit, mitunter auch Parallelität (concurrency) genannt, ist in der Informatik die Eigenschaft eines Systems, mehrere Aufgaben, Berechnungen, Anweisungen oder Befehle gleichzeitig ausführen zu können.
* Es kann sich dabei um völlig unabhängige Anweisungen handeln, bis hin zur gemeinsamen Bearbeitung einer Aufgabe. Sie können dabei auch miteinander interagieren (z. B. um Zwischenergebnisse auszutauschen).
* Die Operationen können dabei nur scheinbar nebenläufig (parallel), beispielsweise im sogenannten Multitasking.
* Einige Javascript-Funktionen sind von Haus aus asynchron: das Warten auf ein Event mit `addEventListener`, die Methoden des `XMLHttpRequest`-Objekts, Timer wie `setTimeout` und Animationen mit `requestAnimationFrame()`.

Quelle: [https://www.mediaevent.de/javascript/asynchron-synchron.html](https://www.mediaevent.de/javascript/asynchron-synchron.html)

## Auswirkungen auf die Programmierung

* Programmcode läuft nicht nach der Reihe ab.
* Durch Callbacks, etc. können Methoden zwischendurch aufgerufen werden.

## Vor-/Nachteile

* Vorteile
    * transparente Performanzsteigerung
    * explizite Performanzsteigerung
    * Verbesserung der Antwortzeiten
    * Vereinfachung des Entwurfs von Anwendungen
* Nachteile
    * Vorteile schwer zu realisieren
    * Zugriffskonflikte
    * Verklemmungen
    * Bestimmung einer effizienten Nebenläufigkeitsarchitektur

Quelle: [http://bis.informatik.uni-leipzig.de/de/Lehre/0809/ss/LV/pattern/files?get=sdp09_nebenlaeufigkeit_frommhold_marvin.pdf](http://bis.informatik.uni-leipzig.de/de/Lehre/0809/ss/LV/pattern/files?get=sdp09_nebenlaeufigkeit_frommhold_marvin.pdf)

## GUI-Programmierung

* Achtung: Anwendung darf nie einfrieren, ansonst gibt es keine Ereignisbehandlung
* Man darf nie den Hauptprozess des eigenen Programms nutzen, dieser ist für Routinearbeiten reserviert, und soll daher nicht für andere Dinge genutzt werden
* Wenn mehrere Nebenprozesse gestartet werden, so kann im Hintergrund auf ein Event reagiert (Datei einlesen, …) reagiert werden, ohne das die Anwendung einfriert

## Threads

* In der Informatik bezeichnet Thread einen Ausführungsstrang oder eine Ausführungsreihenfolge in der Abarbeitung eines Programms. Ein Thread ist Teil eines Prozesses.
* Es wird zwischen zwei Arten von Threads unterschieden:
    * Threads im engeren Sinne, die sogenannten Kernel-Threads, laufen ab unter Steuerung durch das Betriebssystem.
    * Im Gegensatz dazu stehen die User-Threads, die das Computerprogramm des Anwenders komplett selbst verwalten muss

## Konzeption

* Mitunter wird auch exakter unterschieden zwischen „nebenläufiger Behandlung“ (englisch concurrency) und „Parallelverarbeitung“ (englisch parallelism)
* Die nebenläufige Behandlung wird dann vor allem als ein Konzept verstanden, reale Vorgänge abzubilden, das auch sinnvoll ist, wenn zur Ausführung nur ein einziger CPU-Kern zur Verfügung steht
* Im Gegensatz dazu fokussiert in diesem Begriffsverständnis die Parallelverarbeitung auf echt-gleichzeitige Mehrkern-Berechnung meist eines Problems

## Semaphore

* Ein Semaphor ist ein Signalgeber
* Dieser gibt an, wie viele Prozesse gleichzeitig in einen kritischen Abschnitt eintreten können
* Jedesmal, wenn ein Prozeß den kritischen Abschnitt betreten möchte, wird der Zähler um eins heruntergesetzt.
* Wenn ein Prozess den kritischen Abschnitt verläßt, setzt er dabei den Zähler um eins hoch.

Quelle: [http://ddi.cs.uni-potsdam.de/HyFISCH/Produzieren/SeminarDidaktik/Nebenlaeufigkeit/semaphor.htm](http://ddi.cs.uni-potsdam.de/HyFISCH/Produzieren/SeminarDidaktik/Nebenlaeufigkeit/semaphor.htm)

## Critical Buffer

* Kritischer Abschnitt ist Problemstelle in Programm
* Um mehr Prozesse in diesen Abschnitt zu lassen müssen Reserven angelegt werden
* Diese Reserven nennt man Critical Buffer

## Deadlock

Deadlock oder Verklemmung bezeichnet in der Informatik einen Zustand, bei dem eine zyklische Wartesituation zwischen mehreren Prozessen auftritt, wobei jeder beteiligte Prozess auf die Freigabe von Betriebsmitteln wartet, die ein anderer beteiligter Prozess bereits exklusiv belegt hat. Eine andere Form der Blockierung von Prozessen ist der Livelock.
Der Zustand eines Deadlocks kann als eine Menge von Prozessen definiert werden, in dem sich ein Deadlock befindet, sofern jeder dieser Prozesse auf ein Ereignis wartet, das nur ein anderer Prozess aus dieser Menge verursachen kann.

Quelle: [https://de.wikipedia.org/wiki/Deadlock_(Informatik)](https://de.wikipedia.org/wiki/Deadlock_(Informatik))

## Fehlerbehebung

* Probleme:
    * Verklemmung (Deadlock)
    * Aushungern (Ressourcenfreigabe abgebrochen)

* Lösung:
    * Transaktion
    * Lock

## Wo werden Nebenläufigkeiten sinnvollerweise eingesetzt?

* Einlesen einer größeren Datei
* Ausführen von großen Berechnungen im Hintergrund
* Mehrere Clients bei einem Server
* Netzwerkkommunikation

## Wo liegen Performance-Bottlenecks und wie kann man diese beheben?

* Mögliche Bottlenecks
    * Hauptspeicher
    * Netzwerk (Bandbreite)
    * Prozessor
    * Schreibgeschwindigkeit der Festplatte
    * Datenbank
    * Wartende Threads auf Ergebnis eines anderen Threads

* Mögliche Lösungen
    * Anschaffung zusätzlicher Hardware
    * Anschaffung besserer Hardware
    * Ausbau der Bandbreite
    * Saubere Programmierung

## Welche Auswirkungen hat der Einsatz von Thread-Technologien auf die Komplexität?

* Ein Thread ist einfach zu überwachen, es kann immer nur eine Sache gleichzeitig bearbeitet werden
* Jeder zusätzliche Thread muss überwacht, ausgestattet und verwaltet werden
* Jeder zusätzliche Thread kann die vorher genannten Bottlenecks auslösen bzw. verschlechtern

## Asynchronitäten (Definition, Auswirkungen auf die Programmierung)

* Gegenteil von synchron
* Nicht Starr im Gleichschritt
* Die zeitliche Relation zueinander von gleichzeitig ablaufenden Vorgängen ist nicht exakt fixiert/ vorhersehbar
* Die Vorgänge laufen zumindest zeitweise unabhängig voneinander
* Auswirkung auf die Programmierung
    * Wenn Threads aufeinander warten, und unterschiedlich ihre Aufgabe beenden, so kann es zu unnötigen Wartezeiten kommen.

Quelle: [https://docplayer.org/75536196-Nebenlaeufigkeit-und-asynchronizitaet-in-eingebetteten-systemen-klaus-kusche-september-2012.html](https://docplayer.org/75536196-Nebenlaeufigkeit-und-asynchronizitaet-in-eingebetteten-systemen-klaus-kusche-september-2012.html)

## Unterschied zur Nebenläufigkeit

* Nebenläufigkeit: Mehrere Dinge geschehen gleichzeitig
* Asynchronität: Mehrere Dinge geschehen, zeitlich ist aber nicht definiert wann

Quelle: [https://docplayer.org/75536196-Nebenlaeufigkeit-und-asynchronizitaet-in-eingebetteten-systemen-klaus-kusche-september-2012.html](https://docplayer.org/75536196-Nebenlaeufigkeit-und-asynchronizitaet-in-eingebetteten-systemen-klaus-kusche-september-2012.html)

## Wann setzt man Callbacks sinnvollerweise ein?

* Callback-Funktion: Rückruffunktion, die aufgerufen wird, wenn die aufrufende Funktion abgeschlossen ist und Ergebnisse/Fehler vorliegen
* Ergebnis einer Funktion in weitere Funktion direkt weiter nutzen

## Auswirkungen auf die Komplexität

* Innerer Aufruf -> Aufruf einer Funktion in einer Funktion
* Problem mit der Analyse und Behebung von Code-Fehlern
* Keine klare Trennung der einzelnen Funktion
* Mehrfachaufruf der „inneren“ Funktionen nicht möglich

## Kaskade von Callbacks

* Eine Callback-Funktion hat immer eine bestimmte Auswirkung, die an bestimmte Umstände gebunden ist.
* Ein gutes Beispiel für Rückruffunktionen sind Event-Handler (dt. Ereignisbehandler), die beispielsweise in HTML-Elementen wie Buttons zum Einsatz kommen.
* Die Callback-Funktion an sich wird vermutlich für eine Weiterleitung auf eine weitere Seite sorgen. Auch die Übergabe eines Werts in einem Formular, das man ausfüllt, ist ein mögliches Szenario.

```js
document.getElementById("Button1").addEventListener("click", function() {
	console.log("Button wurde gedrückt");
}, false);
```

Quelle: [https://www.ionos.at/digitalguide/websites/web-entwicklung/was-ist-eine-callback-function/](https://www.ionos.at/digitalguide/websites/web-entwicklung/was-ist-eine-callback-function/)

## Unterstützung durch Promises

* Das Promise Objekt stellt eine Repräsentation einer eventuellen Ausführung (oder eines Fehlschlags) einer asynchronen Operation und den daraus resultierenden Ergebnissen dar.
* Ein Promise kann sich in einem von drei Zuständen befinden:
    * pending (schwebend): initialer Status, weder fulfilled noch rejected.
    * fulfilled (erfüllt): heisst das die Operation erfolgreich abgeschlossen wurde.
    * rejected (zurück gewiesen): heisst das die Operation gescheitert ist.
* Ein weiterer Begriff beschreibt den Zustand settled (erledigt aber nicht zwingend erfolgreich): Der Promise ist entweder fulfilled oder rejected, aber nicht pending.

```js
new Promise(executor);
new Promise(function(resolve, reject) { ... });
```

Quelle: [https://developer.mozilla.org/de/docs/Web/JavaScript/Reference/Global_Objects/Promise](https://developer.mozilla.org/de/docs/Web/JavaScript/Reference/Global_Objects/Promise)

## Fehlerbehebung

* Debugging durch Konsole und Plugins des Browsers
* Debugging durch conole.log() im JS-Code
* Bekanntesten Fehler von JS: [https://developer.mozilla.org/de/docs/Web/JavaScript/Reference/Errors](https://developer.mozilla.org/de/docs/Web/JavaScript/Reference/Errors)