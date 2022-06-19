#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>


void process_conn_server(int client_fd){   												/*服务器建立子进程处理客户端请求*/
  	ssize_t size = 0;
  	char buffer[1024];																						/*数据缓冲区*/
  	for(;;){
      	size = read(client_fd, buffer, 1024);											/*从套接字中读取数据放到缓冲区buffer中*/
      	if(size == 0){																						/*没有数据*/
          	return;
        }
      	sprintf(buffer, "%d bytes altogether!\n", size);          /*构建响应字符，为接收到客户端字节的数量*/
      	write(client_fd, buffer, strlen(buffer) + 1);							/*发给客户端*/
    }
}

void process_conn_client(int sockfd){
  	ssize_t size = 0;
  	char buffer[1024];
  	
  	for(;;){
      	size = read(0, buffer, 1024);       /*从标准输入中读取数据放到缓冲区buffer中， 0代表标准输入文件描述符*/
		buffer[size - 1] = '\0';
		size = strlen(buffer);
		if(size == 0){
			write(sockfd, buffer, size); 
			break;
		} 
		if(size > 0){
          	write(sockfd, buffer, size);        /*发送服务器*/
          	size = read(sockfd, buffer, 1024);  /*从服务器读取数据*/
          	write(1, buffer, size);							/*写到标准输出， 1为标准输出文件描述符*/
        }
    }
}