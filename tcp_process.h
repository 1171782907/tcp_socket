#ifdef  __TCP_PRO__
#define __TCP_PRO__
extern void process_conn_server(int client_fd);
extern void process_conn_client(int sockfd);
#endif