import time, hashlib, hmac

def createHash(key, word):
	# Generate the hash
	digester = hmac.new(key, word, hashlib.sha1)
	hs = digester.hexdigest()
	return hs

def ACLcheck(topic, clientid, acc, username):
	return True
	'''
	if "tml" in topic:
		print("ok \n")
		return True
	else:
		print("nok \n")
		raise Exception('NOK')
	try:
		print(topic, acc, username, clientid)
		clientid = clientid.split("_")
		# Check length of Device MAC
		if len(clientid[1]) != 12:
			return False

		# Subscribing to special topics only for users with correct identifiers.
		# SUB: 4, PUB: 2, READ: 1, NONE: 0
		if acc = "4":
			if topic == "ALARMS" and str(username)[0] == "A":
				return True
			if topic[:4] == "$SYS" and str(username)[0] == "M":
				return True

		# Check if Device MAC is in Topic
		if clientid[1] not in topic  and topic != "ALARMS":
			return False
	except Exception as e:
		print(str(e))
		return False
	'''
def anotherFunction(username, password):

	print("start unpwd function")
	proto_id = username[0]
	port = "08886"

	secrets = {
			"2": ["gd9ee6xzlr", "35deuu6p5w"]
		  }

	# Get the secrets
	try:
		keys = secrets[proto_id]
		us_key = bytes(keys[0], "UTF-8")
		pw_key = bytes(keys[1], "UTF-8")
	except Exception as e:
		print("Protocol Identifier Incorrect: ", str(e))
		raise Exception("NOK")

	# Create a key
	try:
		key = str(time.time())[0:7] + port
		key = bytes(key, 'UTF-8')
	except Exception as e:
		print("Creating Key Failed: ", str(e))
		raise Exception("NOK")

	# Get the hash
	try:
		signature = createHash(key, us_key)
		srv_pw = createHash(key, pw_key)
		# Drop the last chr from the signature
		signature = str(signature)[:-1]
		# Add proto_id to reassemble username
		srv_un = proto_id + signature
	except Exception as e:
		print("Reassembling username failed: ", str(e))
		raise Exception("NOK")

	# Validate credentials
	try:
		if(username != srv_un):
			print("u:", username, srv_un)
			raise Exception("NOK")
		if(password != srv_pw):
			print("p:", password, srv_pw)
			raise Exception("NOK")
		else:
			return "OK"
	except Exception as e:
		print("Validating Credentials failed: ", str(e))
		raise Exception("NOK")
