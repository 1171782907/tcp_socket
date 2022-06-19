#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include "tcp_process.h"
#define SERV_PORT 4567    /*服务器侦听端口地址*/
int main(int argc, char *argv[]){
    int sockfd;                          /*socket描述符*/
    struct sockaddr_in server_addr;			 /*服务器地址结构*/
    int ret;														 /*返回值*/
    
    sockfd = socket(PF_INET, SOCK_STREAM, 0); /*建立流式套接字*/
    if(sockfd < 0){
        printf("socket error!\n");
        return -1;
    }
    
    bzero(&server_addr, sizeof(server_addr));								/*清零*/
    server_addr.sin_family = AF_INET;												/*设置地址族*/
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");		/*服务器地址*/
        server_addr.sin_port = htons(SERV_PORT);    						/*服务器端口*/
    
    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));  /*连接服务器*/
    process_conn_client(sockfd);																							 /*客服端处理过程*/
    close(sockfd);
}																														 /*关闭连接*/