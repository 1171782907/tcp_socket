#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<signal.h>
#include "tcp_process.h"
#define SERV_PORT 4567    /*服务器侦听端口地址*/
#define BACKLOG 	5				/*侦听队列长度*/

void singal_handle(int sign){
    wait(NULL);
}

int main(int argc, char *argv[]){
    signal(SIGCHLD,singal_handle);
    int client_fd, server_fd;       		/*client_fd为客户端的socket描述符，server_fd为服务器的socket描述符*/
    struct sockaddr_in server_addr;			/*服务器套接字地址结构*/
    struct sockaddr_in client_addr;  		/*客户端套接字地址结构*/
    int ret;														/*返回值*/
    pid_t pid;													/*分叉进程ID*/
    server_fd = socket(PF_INET, SOCK_STREAM, 0); /*建立流式套接字*/
    if(server_fd < 0){
        printf("socket error\n");
        return -1;
    }
    /*设置服务器套接字地址参数*/
    bzero(&server_addr, sizeof(server_addr));					/*清零*/
    server_addr.sin_family = AF_INET;									/*设置地址族*/
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);		/*本地地址*/
    server_addr.sin_port = htons(SERV_PORT);    				/*服务器端口*/
    
    ret = bind(server_fd, (struct  sockaddr*)&server_addr, sizeof(server_addr)); /*绑定地址到套接字描述符*/
    if(ret < 0){
        printf("bind error!\n");
        return -1;
    }
    ret = listen(server_fd, BACKLOG); 	/*设置侦听队列*/
    if(ret < 0){
        printf("listen error!\n");
        return -1;
    }
    for(;;){
        int addrlen = sizeof(struct sockaddr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);			/*接收客服端连接*/
        if(client_fd < 0){ 																	/*出错*/
                continue;																	/*结束本次循环*/
        }
        pid = fork();																		/*建立子进程处理该连接*/
        if(pid == 0){
            close(server_fd);																/*子进程中关闭服务器的的侦听*/
            process_conn_server(client_fd);	                                                /*处理连接*/
            exit(0);                                                                        /*退出子线程*/											
        }else{  
            close(client_fd);																/*在父进程中关闭客户端的连接*/
        }
    }
}