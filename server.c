#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

void * reciever(void *);
int client_sock;

int main(){
	
	int serv_sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serv_addr;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(8080);
	serv_addr.sin_family = AF_INET;

	bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	listen(serv_sock,100);
	client_sock = accept(serv_sock,NULL,NULL);
	printf("Client connected\r\n");
	pthread_t id;
	int ret;
	ret = pthread_create(&id,NULL,&reciever,NULL);
	char buffer[1024];
	while(1){
	memset(buffer,'\0',1024);
	int stat = recv(client_sock,&buffer,1024,0);
	if(stat==0||stat==-1){
		break;
	}
	printf("%s\r\n",buffer);
	}

	return 0;
}

void * reciever(void *args){
	char buff[1024];
	while(1){
	memset(buff,'\0',1024);
	scanf("%s",buff);
	send(client_sock,&buff,strlen(buff),0);
	}
}