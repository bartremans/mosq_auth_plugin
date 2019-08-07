# mosq_auth_plugin
Authentication Plugin for Mosquitto Broker

Compile plugin
gcc auth_plugin.c -o auth_plugin.so -shared -lpython3.5 -lm -L /usr/lib/python3.5/config-3.5m-arm-linux-gnueabihf -fPIC -I "../mosquitto/src"
