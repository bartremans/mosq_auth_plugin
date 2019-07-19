#include <stdint.h>

#include <mosquitto.h>
#include <mosquitto_plugin.h>

// --- ACL CHECK ---
int mosquitto_auth_acl_check(void *user_data, int access, struct mosquitto *client, const struct mosquitto_acl_msg *msg){
  // bypass
  return MOSQ_ERR_SUCCESS;
};

// --- USERNAME/PASSWORD CHECK ---
int mosquitto_auth_unpwd_check(void *user_data, struct mosquitto *client, const char *username, const char *password){
  // bypass
  return MOSQ_ERR_SUCCESS;
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

int mosquitto_auth_security_init(void *user_data, struct mosquitto_opt *opts, int opt_count, bool reload){
  return 0;
};

int mosquitto_auth_security_cleanup(void *user_data, struct mosquitto_opt *opts, int opt_count, bool reload){
  return 0;
};

int mosquitto_auth_psk_key_get(void *user_data, struct mosquitto *client, const char *hint, const char *identity, char *key, int max_key_len){
  return MOSQ_ERR_PLUGIN_DEFER;
};

int mosquitto_auth_start(void *user_data, struct mosquitto *client, const char *method, bool reauth, const void *data_in, uint16_t data_in_len, void **data_out, uint16_t *data_out_len){
  return MOSQ_ERR_PLUGIN_DEFER;
};

int mosquitto_auth_continue(void *user_data, struct mosquitto *client, const char *method, const void *data_in, uint16_t data_in_len, void **data_out, uint16_t *data_out_len){
  return MOSQ_ERR_PLUGIN_DEFER.
};
