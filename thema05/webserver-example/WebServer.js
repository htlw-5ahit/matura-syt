import http from "http"
import url from "url"

// http server
const HOSTNAME = "127.0.0.1"
const PORT = 3000

function test() {
    return 'test'
}

// create http server
const server = http.createServer((req, res) => {
    // set headers for cors (allow all origins and methods)
    res.setHeader("Access-Control-Allow-Origin", "*")
    res.setHeader("Access-Control-Allow-Methods", "*")

    // prepare objects
    let queryObject = url.parse(req.url, true).query
    let basePath = url.parse(req.url).pathname

    // debug logging
    console.log(`${req.method}: ${req.url}`)

    if (basePath == '/') {
        res.writeHead(200, { 'Content-Type': 'text/plain'} )
        res.end('Hello World')

    } else if (basePath == '/test' && req.method == 'GET') {
        
        res.writeHead(200, { 'Content-Type': 'application/json'} )
        res.end(JSON.stringify(
            // TODO: do something with queryObject.xxx
            test()
        ))

    } else if (basePath == '/test' && req.method == 'DELETE') {
        let clientChunk = ''

        req.on('data', chunk => {
            clientChunk = chunk
        })

        req.on('end', () => {
            let jsonClientObject = JSON.parse(clientChunk)
            console.log(jsonClientObject)

            res.end(JSON.stringify(
                // TODO: do something with jsonClientObject.xxx
                test()
            ))
        })

    } else if (basePath == '/test' && req.method == 'PUT') {
        let clientChunk = ''

        req.on('data', chunk => {
            clientChunk = chunk
        })

        req.on('end', () => {
            let jsonClientObject = JSON.parse(clientChunk)
            console.log(jsonClientObject)

            res.end(JSON.stringify(
                // TODO: do something with jsonClientObject.xxx
                test()
            ))
        })

    } else {
        res.end("Invalid Request")
    }

}).listen(PORT, HOSTNAME, () => {
    console.log(`Webserver is listening on http://${HOSTNAME}:${PORT}`)
})