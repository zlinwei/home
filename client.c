#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
	//这个函数是收到消息的函数
	if(message->payloadlen){
		//如果消息长度不为零 就显示收到的消息和topic
		printf("%s %s\n", message->topic, message->payload);
	}else{
		printf("Topic:%s\n",message->topic);
		//消息长度为0 显示topic
	}
	fflush(stdout);
}

void my_connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
	int i;
	if(!result){
		/* Subscribe to broker information topics on successful connect. */
		mosquitto_subscribe(mosq, NULL, "/home", 2);
	}else{
		fprintf(stderr, "Connect failed\n");
	}
}

//void (*on_subscribe)(struct mosquitto *, void *, int, int, const int *));
void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)
{
	int i;

	printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
	for(i=1; i<qos_count; i++){
		printf(", %d", granted_qos[i]);
	}
	printf("\n");
}

void my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
	/* Pring all log messages regardless of level. */
	printf("%s\n", str);
}

void my_disconnect_callback(struct mosquitto *mosq, void *userdata, int result){
	printf("disconnect:%d\n",result);
	
	while(mosquitto_connect(mosq, "hltdoor.com", 1883, 60)){
                     fprintf(stderr, "Unable to connect.\n");
		     sleep(5);		
        }

}

int main(int argc, char *argv[])
{
	if(argc<2){
		printf("need input argv 1 for cliend id\n");
		return 0;
	}
	int i;
	char *host = "hltdoor.com";
	int port = 1883;
	int keepalive = 60;
	bool clean_session = true;
	struct mosquitto *mosq = NULL;
	
	mosquitto_lib_init();
	mosq = mosquitto_new(argv[1], clean_session, NULL);

	if(!mosq){
		fprintf(stderr, "Error: Out of memory.\n");
		return 1;
	}
	mosquitto_log_callback_set(mosq, my_log_callback);
	mosquitto_connect_callback_set(mosq, my_connect_callback);
	mosquitto_message_callback_set(mosq, my_message_callback);
	mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);
	mosquitto_disconnect_callback_set(mosq,my_disconnect_callback);
	mosquitto_username_pw_set(mosq,"zlinwei","z19930809");

	if(mosquitto_connect(mosq, host, port, keepalive)){
		fprintf(stderr, "Unable to connect.\n");
		return 1;
	}

	//
	mosquitto_loop_forever(mosq, -1, 1);

	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	return 0;
}
