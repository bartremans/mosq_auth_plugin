def someFunction(topic, clientid, acc):
	if "test" in topic:
		print(topic, clientid, acc)
		return True
	else:
		return False

def anotherFunction(username, password):
	print(username, password)
	return True
