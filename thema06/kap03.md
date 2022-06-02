# Cloud Computing

## Begriffsdefinition

Cloud Computing beschreibt ein Modell, das bei Bedarf – meist über das Internet und geräteunabhängig – zeitnah und mit wenig Aufwand geteilte Computerressourcen als Dienstleistung, etwa in Form von Servern, Datenspeicher oder Applikationen, bereitstellt und nach Nutzung abrechnet. Angebot und Nutzung dieser Computerressourcen ist definiert und erfolgt in der Regel über eine Programmierschnittstelle (API) bzw. für Anwender über eine Website oder App.

Quelle: [https://de.wikipedia.org/wiki/Cloud_Computing](https://de.wikipedia.org/wiki/Cloud_Computing )

## Deployment-/Service Models

### unterschiedliche Typen(Private/Community/Public/Hybrid Cloud)

* Es gibt verschiedene Möglichkeiten, wie man ein Cloud-Computing System verbreitet
    * Private
        * gibt allen Teilnehmern einer Organisation die Ressourcen frei
    * Community
        * gibt allen Teilnehmern mehrere Organisationen die Ressourcen des Netzwerks
    * Public
        * gibt allen Teilnehmern alle verfügbaren Ressourcen
    * Hybrid Cloud
        * Mischung aus private und public Cloud Services

Quelle: [https://www.sciencedirect.com/topics/computer-science/cloud-deployment-model](https://www.sciencedirect.com/topics/computer-science/cloud-deployment-model)

### XaaS (IaaS, PaaS, SaaS)

#### Übersicht

<img src="https://www.redhat.com/cms/managed-files/iaas-paas-saas-diagram3-1638x1046.png" width="450">

#### IaaS

* IaaS ... Infrastructure-as-a-Service
* Ist nur einen Schritt von der lokalen Infrastruktur entfernt
* Pay-as-you-go-Service, bei dem ein Drittanbieter Infrastruktur-Services wie Storage und Virtualisierung nach Bedarf über eine Cloud oder über das Internet zur Verfügung stellt

#### PaaS

* PaaS ... Platform-as-a-Service
* Bei PaaS hostet ein Anbieter die Hardware und Software in seiner eigenen Infrastruktur und stellt diese Plattform dem Nutzer als integrierte Lösung, Lösungs-Stack oder Service über eine Internetverbindung zur Verfügung.

#### SaaS

* SaaS ... Software-as-a-Service
* Cloud Application Services
* Umfassendste Form von Cloud-Computing-Services und stellt eine komplette Anwendung, die vom Anbieter verwaltet wird, über einen Webbrowser bereit

Quelle: [https://www.openintl.com/the-three-service-models-of-cloud-computing/](https://www.openintl.com/the-three-service-models-of-cloud-computing/ )

## Verwendung einer Cloud und DSGVO

* Innerhalb der EU gilt seit 2016 die DSGVO
* Werden Daten innerhalb der EU gespeichert, so sind die Richtlinien der EU einzuhalten

## Cloud aus Sicht der IT-Security

* Eigene Abteilungen, die sich um die Sicherheit des Service kümmert
* Ansprechpartner bei Problemen
* Daten werden meist verschlüsselt
* Meist Spiegelungen über mehrere Rechenzentren von den Daten

## Vor/Nachteile von Cloud

* Vorteile
    * Kosteneinsparung
    * Skalierbarkeit
    * Service durch Fachkräfte von Extern
    * IT-Sicherheit und Sicherheit im Allgemeinen
* Nachteile
    * Datensicherheit, Datenverfügbarkeit und Datenweitergabe
    * Begrenzte Individualisierung
    * Abhängigkeit von Anbieter und Dienstleister
    * Schlechte Portabilität

Quelle: [https://www.dreher-consulting.com/blog/cloud-computing/](https://www.dreher-consulting.com/blog/cloud-computing/)

## Cloud-basierte Lösungen im mobilen Bereich Beispiele

???

## Bekannte Anbieter von solchen Cloud-Lösungen

* Microsoft Azure
* Amazon AWS

## Alternativen zu einer Cloud-Lösung (Zugriff auf Daten)

* Private Cloud (Beispiel: NextCloud, ...)
* NAS-System mit SMB, WebDAV, ... 

## Wie können die Cloud-Daten genutzt werden (Interface, API)

* Mappen als Netzwerklaufwerk (OneDrive, Teams, Sharepoint, …)
* Zugriff über Desktop Applikation
* Zugriff über Weboberfläche
* Abfrage über eine URL

Quelle: [https://www.silver-tipps.de/clouds-grundlage-des-mobilen-internets/](https://www.silver-tipps.de/clouds-grundlage-des-mobilen-internets/)

## Unterschied zu herkömmlichen Nutzung von persistenten Daten (SQL, NoSQL)

???

## Wie können die Services administriert werden?

* Eigene Administration ist relativ selten (nur bei Private Cloud)
* Ansonst wird der Dienst von Zentraler, aber externer Stelle, verwaltet
* Diese haben direkten Zugriff auf die Hard- und Software des gesamten Systems
* Was kann verwaltet werden
    * Hardware Ressourcen
    * Benötigte Software
    * Zugriffsregelung von Extern

Quelle:
* [https://docs.microsoft.com/en-us/learn/paths/cmu-cloud-admin-basics/](https://docs.microsoft.com/en-us/learn/paths/cmu-cloud-admin-basics/)
* [https://www.mygreatlearning.com/blog/cloud-system-administrator/](https://www.mygreatlearning.com/blog/cloud-system-administrator/)

## Was kann alles in die Cloud ausgelagert werden und was soll man sich dazu überlegen.

* Alles kann man theoretisch auslagern
* Was muss man beachten
    * Je mehr man auslagert, desto mehr verliert man die Kontrolle über seine Anwendungen
    * Wenn Daten extern gespeichert werden, so muss sowohl der sichere Zugang als auch die verschlüsselte Speicherung gesichert werden
    * Bei Problemen seitens des Anbieters kann es passieren, das die gesamten Daten verloren gehen für den Kunden

## Kann man bei einer Cloud-Lösung auf den BackupService verzichten?

* Meistens ist dieser im Preis inbegriffen und man kann nicht darauf verzichten

## Wer haftet eigentlich, wenn die in der Cloud gespeicherten Daten verloren gehen.

* Folgende Parameter sind zu klären wer wann und wie haftet
    * Wo steht der Server
    * Was sagt die Rechtslage in diesem Land zum Thema Datenschutz?

* Beispiel Deutschland
    * In Deutschland ist der Datenschutz gesetzlich verankert
    * Große Cloud-Computing Anbieter schreiben in ihre AGBs zwar, dass sie im Verlustfall nicht haften, bei dieser Rechtslage ist jedoch eine Teilschuld oder sogar vollumfängliche Schuld des Anbieters möglich

* Problematisch ist es Dienste im Anbieter im Ausland anzuzeigen
* Diese haben jeweils eine andere Rechtslage und nach dieser ist auch zu urteilen
* Microsoft mit seinem Hauptsitz in Kalifornien wäre nach US-Recht zu klagen, mind. eine Teilschuld würde der Kläger zugesprochen bekommen, da er selbst kein Backup gemacht hat (so sieht es das US-Recht)

Quelle: 
* [https://www.cloudcomputing-insider.de/wer-haftet-bei-datenverlust-in-der-cloud-a-410202/](https://www.cloudcomputing-insider.de/wer-haftet-bei-datenverlust-in-der-cloud-a-410202/)
* [https://www.attingo.at/blog/haftung-bei-datenverlust/](https://www.attingo.at/blog/haftung-bei-datenverlust/)
* [http://rechtundnetz.com/haftung-in-der-cloud/](http://rechtundnetz.com/haftung-in-der-cloud/)

## Welche Ansprüche hat der Cloudanwender?

???