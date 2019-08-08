#include <stdint.h>
#include <stdio.h>

#include <python3.6/Python.h>

#include <mosquitto.h>
#include <mosquitto_broker.h>
#include <mosquitto_plugin.h>

PyObject *myModule;
PyObject *ACL_Function;
PyObject *UNPWD_Function;


int mosquitto_auth_security_init(void *user_data, struct mosquitto_opt *opts, int opt_count, bool reload){

  Py_Initialize();
  /*
  if(opt_count){
    for(int i=0; i < opt_count; i++){
	  printf("%s %s", opts[i].key, opts[i].value);
    };
  };
  */
  PyRun_SimpleString("import sys; sys.path.insert(0, '/home/ubuntu/mqtt/mosq_auth_plugin')");
  myModule = PyImport_ImportModule("auth");
  if(myModule != NULL){
    ACL_Function = PyObject_GetAttrString(myModule, (char*)"ACLcheck");
    UNPWD_Function = PyObject_GetAttrString(myModule, (char*)"anotherFunction");
    return 0;
  };

};

// --- ACL CHECK ---
int mosquitto_auth_acl_check(void *user_data, int access, struct mosquitto *client, const struct mosquitto_acl_msg *msg){

  if(myModule != NULL){
    ACL_Function = PyObject_GetAttrString(myModule, (char*)"ACLcheck");
  };

  if(ACL_Function != NULL){

    PyObject *topic = PyUnicode_FromString(msg->topic);
    PyObject *clientid = PyUnicode_FromString(mosquitto_client_id(client));
    PyObject *un = PyUnicode_FromString(mosquitto_client_username(client));
    PyObject *acc = PyLong_FromLong(access);
    PyObject *myResult = PyObject_CallFunctionObjArgs(ACL_Function, topic, clientid, acc, un, NULL);

    Py_DECREF(topic);
    Py_DECREF(clientid);
    Py_DECREF(un);
    Py_DECREF(acc);

    if(myResult != NULL){
      Py_DECREF(myResult);
      Py_DECREF(ACL_Function);
      return MOSQ_ERR_SUCCESS;
    } else {
      Py_DECREF(ACL_Function);
      return MOSQ_ERR_ACL_DENIED;
    };

  } else {
    return MOSQ_ERR_ACL_DENIED;
  }
};

// --- USERNAME/PASSWORD CHECK ---
int mosquitto_auth_unpwd_check(void *user_data, struct mosquitto *client, const char *username, const char *password){
  // Username Password get checked when allow_anonymous is False in config
 return MOSQ_ERR_SUCCESS;
 /*
 if(UNPWD_Function != NULL){
    PyObject *un = PyUnicode_FromString(username);
    PyObject *pwd = PyUnicode_FromString(password);
    PyObject *unpwd_result = PyObject_CallFunctionObjArgs(UNPWD_Function, un, pwd, NULL);
    if(unpwd_result != NULL){
      return MOSQ_ERR_SUCCESS;
    } else {
      printf("failed");
      return MOSQ_ERR_AUTH;
    };
  };
 */
};

int mosquitto_auth_plugin_version(void){
  return MOSQ_AUTH_PLUGIN_VERSION;
};

int mosquitto_auth_plugin_init(void **user_data, struct mosquitto_opt *opts, int opt_count){
  return 0;
};

int mosquitto_auth_plugin_cleanup(void *user_data, struct mosquitto_opt *opts, int opt_count){
  return 0;
};

int mosquitto_auth_security_cleanup(void *user_data, struct mosquitto_opt *opts, int opt_count, bool reload){
  Py_Finalize();
  return 0;
};

int mosquitto_auth_psk_key_get(void *user_data, struct mosquitto *client, const char *hint, const char *identity, char *key, int max_key_len){
  return MOSQ_ERR_PLUGIN_DEFER;
};

int mosquitto_auth_start(void *user_data, struct mosquitto *client, const char *method, bool reauth, const void *data_in, uint16_t data_in_len, void **data_out, uint16_t *data_out_len){
  return MOSQ_ERR_PLUGIN_DEFER;
};

int mosquitto_auth_continue(void *user_data, struct mosquitto *client, const char *method, const void *data_in, uint16_t data_in_len, void **data_out, uint16_t *data_out_len){
  return MOSQ_ERR_PLUGIN_DEFER;
};
