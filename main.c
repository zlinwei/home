#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>


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
		//连接成功
		/* Subscribe to broker information topics on successful connect. */
		mosquitto_subscribe(mosq, NULL, "/mytopic", 2);
	}else{
		//连接失败
		fprintf(stderr, "Connect failed\n");
	}
}

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
	//日志
	/* Pring all log messages regardless of level. */
//	printf("%s\n", str);
}

int main(int argc, char *argv[])
{
	int i;
	//连接配置
	char *host = "hltdoor.com";
	int port = 1883;
	int keepalive = 60;
	bool clean_session = true;
	struct mosquitto *mosq = NULL;
	//初始化mosquitto库
	mosquitto_lib_init();
	//创建一个会话
	mosq = mosquitto_new("main001", clean_session, NULL);

	if(!mosq){
		//创建失败
		fprintf(stderr, "Error: Out of memory.\n");
		return 1;
	}
	//设置日志回调
	mosquitto_log_callback_set(mosq, my_log_callback);
	//设置连接回调
	mosquitto_connect_callback_set(mosq, my_connect_callback);
	//设置收到消息回调
	mosquitto_message_callback_set(mosq, my_message_callback);
	//设置订阅回调
	mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);

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
