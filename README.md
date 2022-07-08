# Canopen

## http
Since the http server is using ulfius framework we need to clone it first and some other repos (ulfius dependencies).

```
git clone https://github.com/babelouest/orcania.git
git clone https://github.com/babelouest/yder.git
git clone https://github.com/babelouest/ulfius.git
```

## Command Line Argument Parser
Сargs is a command line argument parser library which can be used to parse argv and argc parameters passed to a main function.

Download the library
```
git clone -b stable git@github.com:likle/cargs.git
```
Use the following to compile Cargs
```
mkdir cargs/build
cd cargs/build
cmake ..
make
```

# Install application
```
make build
```

Start server
```
./build/demo/demo -c /path_to_yaml
```

Start Log journal
```
journalctl -t Demo -f
```

Command line interface
```
cd cmd
sudo python setup.py develop
cli
```

To test it use the following commands
```
curl -X POST -H 'Content-Type: application/json' -d '{"voltage_dac": "0x3FFF"}' http://localhost:5000/api/voltage/<number node>/<number channel>
curl -X GET http://localhost:5000/api/voltage/<number channel>
```


# Modify permissions for usb devices
```
find /dev/bus/usb -type c | sudo xargs chown root:adm
```
