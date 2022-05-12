# Install
To install the cli package use the command
```
pip install -r requirements.txt
python3 setup.py develop
cli
```
Example of sending a message to the server
```
cli set-channel --channel 1 --voltage 0x3FFF
```

Server read example
```
cli read-channel --channel 1
```
