/*version:1.0
*   实现功能主要为客户端链接服务端及信息的接受发送 √
*/
#include"../include/connect.h"

int main(int argc,char *argv[]){
    int connfd;
    struct sockaddr_in addr_in;
    //分别为句柄和套接字
    SetSocket(&connfd);
    //套接字句柄
    SetSocketAddr(&addr_in);
    //建立套接字
    SetIp(&addr_in);
    //设置服务器ip
    ConnectService(connfd,(struct sockaddr*)&addr_in,sizeof(addr_in));
    //建立与服务器通讯
    while(1){
        SendRecive(&connfd);
    }    
}
