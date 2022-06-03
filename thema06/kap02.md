# Mongoose als Object Document Mapper (ODM)

## Object Document Mapper (ODM)

* In MongoDB wird eine vorherige beliebige Datenstruktur in der Datenbank im JSON-Format als Dokument abgespeichert
* Dieses verwandeln der Datenstruktur (eines Objektes) in das JSON-Format nennt man umwandeln/transformieren (eng. mapping)
* Zusätzlich zu den einfachen Umwandlungen kann ein ODM auch eine hierarchische Struktur abbilden 

Quelle: [https://www.treefrogframework.org/en/user-guide/model/object-document-mapping-on-mongodb.html](https://www.treefrogframework.org/en/user-guide/model/object-document-mapping-on-mongodb.html)

## Was tut ein ODM eigentlich?

* Konvertiert bzw. transformiert ein Objekt in ein dazu passendes JSON-Format
* Dies wird bei den meisten NoSQL Datenbanken mit leichten Schemata, wie es Mongoose ist, benötigt
* Mongoose ist ein ODM, dass eine schemabasierte Lösung bietet, um Anwendungsdaten zusätzlich zu den nativen Treibern von MongoDB zu modellieren. Es umfasst integrierte Typumwandlung, Validierung (die die native Dokumentenvalidierung von MongoDB verbessert), Abfrageerstellung, Hooks

## Mongoose stellt Schema zur Verfügung – was ist das und warum wird Schema eingesetzt?

* Ein Schema ist eine Art Vorlage
* Es sorgt dafür, dass in einer Collection immer ähnliche Daten enthalten sind
* Diese Vorlage kann mit beliebigen Werten, die den jeweiligen Typen der Felder entsprechen, befüllt werden
* In NodeJs kann man ebenfalls Mongoose nutzen; hierfür kann man im Programm das Schema ebenfalls einrichten

```js
const mongoose = require('mongoose');

const UserSchema = new mongoose.Schema({
    username: {
        type: String,
        trim: true,
        unique: true,
        required: [true, 'Username is required']
    },
    password: {
        type: String,
        required: [true, 'Password is required'],
    },
    created: {
        type: Date,
        default: Date.now()
    }
});

module.exports = mongoose.model('User', UserSchema);
```

Quelle: [https://mongoosejs.com/docs/guide.html](https://mongoosejs.com/docs/guide.html )

## Wie funktioniert ein Update/Delete/Query per Mongoose?

#### Finden von Einträgen

```js
const Person = require("../models/person");

// .find() finds all instances in the database that match the query you pass in.
// It returns an array, even if there is only one item in the array.

// No query passed in means "find everything"
Person.find((err, people) => {
    // Note that this error doesn't mean nothing was found,
    // it means the database had an error while searching, hence the 500 status
    if (err) return res.status(500).send(err)
    // send the list of all people
    return res.status(200).send(people);
});

// If query IS passed into .find(), filters by the query parameters
Person.find({name: "John James", age: 36}, (err, people) =>{
    if (err) return res.status(500).send(err)

    // send the list of all people in database with name of "John James" and age of 36
    // Very possible this will be an array with just one Person object in it.
    return res.status(200).send(people);
});
```

#### Erstellen von Einträgen

```js
const Todo = require("../models/todo");

// Assuming this is from a POST request and the body of the
// request contained the JSON of the new "todo" item to be saved
const newTodoObj = new Todo(req.body);
newTodoObj.save(err => {
    if (err) return res.status(500).send(err);
    return res.status(200).send(newTodoObj);
});
```

#### Aktualisieren von Einträgen

```js
const Todo = require("../models/todo");

// This would likely be inside of a PUT request, since we're updating an existing document, hence the req.params.todoId.
// Find the existing resource by ID
Todo.findByIdAndUpdate(
    // the id of the item to find
    req.params.todoId,
    
    // the change to be made. Mongoose will smartly combine your existing 
    // document with this change, which allows for partial updates too
    req.body,
    
    // an option that asks mongoose to return the updated version 
    // of the document instead of the pre-updated one.
    {new: true},
    
    // the callback function
    (err, todo) => {
    // Handle any possible database errors
        if (err) return res.status(500).send(err);
        return res.send(todo);
    }
)
```

#### Löschen von Einträgen

```js
// The "todo" in this callback function represents the document that was found.
// It allows you to pass a reference back to the client in case they need a reference for some reason.
Todo.findByIdAndRemove(req.params.todoId, (err, todo) => {
    // As always, handle any potential errors:
    if (err) return res.status(500).send(err);
    // We'll create a simple object to send back with a message and the id of the document that was removed
    // You can really do this however you want, though.
    const response = {
        message: "Todo successfully deleted",
        id: todo._id
    };
    return res.status(200).send(response);
});
```

Quelle: [https://coursework.vschool.io/mongoose-crud/](https://coursework.vschool.io/mongoose-crud/)

## Inwieweit unterscheidet sich hier der Zugriff auf eine SQL-DB?

* Bei NoSQL Datenbanken, speziell MongoDB, werden die gespeicherten Objekte über die eingebauten JavaScript-Funktionen abgerufen
* Bei SQL-Datenbanken müssen SQL-Statements verfasst werden, um an die Daten zu gelanden.

## Welche Spracheelemente von EcmaScript können verwendet werden?

* Funktionen als NodeJS (JavaScript)
* siehe oben

## Was ist in diesem Sinne eine Collection?

* MongoDB speichert Dokumente in Sammlungen. Sammlungen sind analog zu Tabellen in relationalen Datenbanken.

Quelle: [https://www.mongodb.com/docs/manual/core/databases-and-collections/](https://www.mongodb.com/docs/manual/core/databases-and-collections/)

## Beispiel Mongo DB Atlas – Nodejs

* Kein Unterschied wie eine lokale Instanz eioner MongoDB bei der Verwendung
* s.o.

## Kompatibilität von JSON und Datenformate der von Mongoose eingesetzten Schemata

* In MongoDB wird das BSON Format (ein JSON ähnliches Format) genutzt
* JSON kann nicht direkt in MongoDB importiert werden
* Muss vorher konvertiert werden

Quelle: [https://www.mongodb.com/compatibility/json-to-mongodb](https://www.mongodb.com/compatibility/json-to-mongodb)

## Kann Mongoose nur serverseitig (NodeJS) eingesetzt werden?

* Mongoose kann sowohl ein Client als auch Server aufrufen
* Jedoch sollte eine Datenbankverbindung nur serverseitig aufgebaut werden und die Informationen über Routen bereitstellen => Restful-API

## Funktioniert dies auch bei einem Vue-Client?

* Ja

## Untersützt Mongoose ITSecurity-Maßnahmen?

* Zugriff über Rollen
* Regulierung der Menge an Inhalt die abgebildet wird
* Netzwerkregulierung bzw. Regulierungen der Zugriff pro Zeit
* End-zu-End verschlüsselt

Quelle: [https://www.mongodb.com/de-de/cloud/atlas/security](https://www.mongodb.com/de-de/cloud/atlas/security)

## Wie kann man den Datentransport vor dem Auslesen schützen?

* Verschlüsselte Verbindung nutzen
* End-zu-End Verschlüsselung (Teil der MongoDB-Security)