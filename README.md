# mosq_auth_plugin
Authentication Plugin for Mosquitto Broker

Basic plugin for a Mosquitto Broker that relays the authentication to a Python script.

## Prerequisites

### Get include path for Python.h
```bash
python3-config --configdir
```
### Compile plugin
For example:
```
gcc auth_plugin.c -o auth_plugin.so -shared -lpython3.6 -lm -L <configdir> -fPIC -I "../mosquitto/src"
```
