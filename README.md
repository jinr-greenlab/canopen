# Canopen

## Build
```
make build
```

# http
Since the http server is using ulfius framework we need to clone it first and some other repos (ulfius dependencies).

```
git clone https://github.com/babelouest/orcania.git
git clone https://github.com/babelouest/yder.git
git clone https://github.com/babelouest/ulfius.git
```

Now go to http directory and run
```
make build
```

And now just start the server
```
./server
```

To test it use the following commands
```
curl -X POST -H 'Content-Type: application/json' -d '{"voltage": "0x3FFF"}' http://localhost:5000/api/voltage/10
curl -X GET http://localhost:5000/api/voltage/10
```
