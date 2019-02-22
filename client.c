#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
int sock;
void * reciever(void *);
int main(){

	sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8080);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	pthread_t id;
	int ret;
	ret = pthread_create(&id,NULL,&reciever,NULL);
	char buffer[1024];
	while(1){
	memset(buffer,'\0',1024);
	scanf("%s",buffer);
	send(sock,&buffer,strlen(buffer),0);
	}

	return 0;
}
void * reciever(void * args){
	char buffer[1024];
	while(1){
	memset(buffer,'\0',1024);
	int stat = recv(sock,&buffer,1024,0);
	if(stat==0||stat==-1){
		break;
	}
	printf("%s\r\n",buffer);
	}
	exit(1);
}