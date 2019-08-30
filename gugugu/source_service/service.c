/*version:1.0
*   实现功能主要为服务器对客户端的信息的接受发送 √
*   ip显示，客户端相互通信 √
*   多用户互联，群发功能 ×
*/
#include"../include/connect.h"

int main(int argc,char *argv[]){
    int listenfd,pin_addr_size;
    struct sockaddr_in sin_addr,pin_addr;
    //监听和传输套接字
    SetSocket(&listenfd);
    //建立监听套接字句柄
    SetSocketAddr(&sin_addr);
    //建立套接字
    SetBind(&listenfd,&sin_addr);
    //连接套接字句柄
    StartListen(&listenfd);
    //开始监听
    int count=0;
    //记录用户个数
    while(1){
        if(count<10){
            service_trans_sockfd[count]=accept(listenfd,(struct sockaddr*)&pin_addr,&pin_addr_size);
            if(service_trans_sockfd[count]<0){
                perror("accept");
                exit(1);
            }
            CreateTransFunc(count);
            count++;
        }
        else{
            printf("服务端已满！\n");
            exit(1);  //到时候要改成拒绝连接
        }
        
    }
}