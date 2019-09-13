# mosq_auth_plugin
Authentication Plugin for Mosquitto Broker

Basic plugin for a Mosquitto Broker that relays the authentication to a Python script.

## Prerequisites

### Get include path for Python.h
```bash
python3-config --configdir
```
### Compile plugin
gcc auth_plugin.c -o auth_plugin.so -shared -lpython3.5 -lm -L /usr/lib/python3.5/config-3.5m-arm-linux-gnueabihf -fPIC -I "../mosquitto/src"
