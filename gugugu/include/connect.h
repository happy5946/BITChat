#ifndef HGY
#define HGY
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include <arpa/inet.h>
#define myport 9999
int service_trans_sockfd[10];

void SetSocket(int *n);
void StartListen(int *fd);
void SetIp(struct sockaddr_in *addr);
void SetSocketAddr(struct sockaddr_in *addr);
void ConnectService(int sockfd,struct sockaddr* addr,int size);
void *send_func(int* sockfd);
void *recv_func(int* sockfd);
void SetBind(int *sockfd,struct sockaddr_in *addr);
void SendRecive(int *connfd);
void CreateTransFunc(int count);
void *CreateTransThread(int count);

#endif