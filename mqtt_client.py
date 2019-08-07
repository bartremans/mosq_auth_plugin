import paho.mqtt.client as mqtt
import time, hashlib, hmac, ssl
from uuid import getnode as get_mac

mac = get_mac()
cpath='C:\\Users\\Service2\\Documents\\Dekimo\\ISRG_Root_X1.crt'

broker_address = "mqtt.entrahome.com"
#broker_address = "35.159.24.11"
proto_id = "1"
us_key = bytes("xldke33eny", "UTF-8")
pw_key = bytes("lsi23uo78v", "UTF-8")

def createHash(key, word):
    # Generate the hash
    digester = hmac.new(key, word, hashlib.sha1)
    hs = digester.hexdigest()
    return hs

def on_message(client, userdata, message):
    print("TOPIC: ", message.topic, " : ", str(message.payload))

# Create key from first 7 digits of the Epoch Timestamp
key = str(time.time())[0:7]
key = bytes(key, 'UTF-8')
signature = createHash(key, us_key)
mqtt_password = createHash(key, pw_key)

# Drop the last chr from the signature
signature = str(signature)[:-1]
# Add the protocol identifier to recreate the username
mqtt_username = proto_id + signature

#print(username, password)

print("Creating new instance")
device_mac = "50f14ad65ca2"
user_id = str(mac) + "_" + device_mac
client = mqtt.Client(user_id)
#client = mqtt.Client()
client.username_pw_set(mqtt_username, password= mqtt_password)
#client.tls_set(ca_certs=cpath, tls_version=ssl.PROTOCOL_TLSv1_2)
client.on_message=on_message
print("Connection to Broker")
client.connect(host=broker_address, port=8886)
client.loop_start()

client.subscribe('#')

try:
    while True:
        print("Publish")
        client.publish("/dev/" + device_mac + "/3489835192/3466870002/SenseStatus", "Help help! : " + str(time.time()))
        client.publish(device_mac + "/rrrr/dd", 'mlsqkdjfsqmlj')
        client.publish("tmlqjk", "lkjsqf")
        time.sleep(3)
        
except KeyboardInterrupt:
    print("Exit")
    client.disconnect()
    client.loop_stop()


