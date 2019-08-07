def ACLcheck(topic, clientid, acc, username):
	return True
	'''
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
	print(username, password)
	return True
