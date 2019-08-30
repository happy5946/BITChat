#include"../include/connect.h"

void SetSocket(int *sockfd){
    *sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(*sockfd<0){
        perror("socket");
        exit(1);
    }
    printf("succeed to socket\n");
    return 0;
}
/****************************************************/
/*名称：SetSocket
/*描述：设置套接字句柄，防止结束函数后销毁句柄使用指针，封装报错函数
/*完成日期：2019.8.30
/*参数：int指针，sockfd，套接字句柄
/*返回值：空
/*作者：霍高原
/****************************************************/

void SetSocketAddr(struct sockaddr_in *addr){
    (*addr).sin_family=AF_INET;
    (*addr).sin_port=htons(myport);
    (*addr).sin_addr.s_addr=htonl(INADDR_ANY);
    printf("succeed to set socket\n");
}

/****************************************************/
/*名称：SetSockAddr
/*描述：设置套接字属性封装报错函数
/*完成日期：2019.8.30
/*参数：sockaddr_in结构指针，addr，套接字指针
/*返回值：空
/*作者：霍高原
/****************************************************/

void SetIp(struct sockaddr_in *addr){
    char ip[12];
    printf("input the ip of server:\n");      //还有个ip输入错误处理
    scanf("%s",&ip);   
    getchar();
    in_addr_t server;
    server=inet_addr(ip);
    (*addr).sin_addr.s_addr=server;
}

/****************************************************/
/*名称：SetIp
/*描述：设置套接字的IP
/*完成日期：2019.8.30
/*参数：指向套接字结构体的指针
/*返回值：空
/*作者：霍高原
/****************************************************/

void SetBind(int *sockfd,struct sockaddr_in *addr){
    int on=1;
    int ret=(*sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    if(bind(*sockfd,(struct sockaddr*)addr,sizeof(*addr))<0){
        perror("bind");
        exit(1);
    }
    printf("succeed to bind\n");
}

/****************************************************/
/*名称：SetBind
/*描述：连接套接字和句柄
/*完成日期：2019.8.30
/*参数：int*套接字句柄,套接字
/*返回值：空
/*作者：霍高原
/****************************************************/

void ConnectService(int sockfd,struct sockaddr* addr,int size){
    if(connect(sockfd,addr,size)<0){
        perror("connect");
        exit(1);
    }
    printf("succeed to connect the server\n");
}

/****************************************************/
/*名称：ConnectService
/*描述：客户端向服务器发送链接请求
/*完成日期：2019.8.30
/*参数：同connect函数参数
/*返回值：空
/*作者：霍高原
/****************************************************/

void *SendMessage(int* sockfd){
    int fd=*sockfd;
    char s[100];
    while(1){
        //printf("input:");
        gets(s);
        //格式为目标+空格+内容；
        //scanf("%s",&s);
        if(send(fd,s,100,0)==-1){
            perror("send");
            pthread_exit("FAIL");
        }
        memset(s,0,sizeof(s));
    }
    pthread_exit("OK");
}

/****************************************************/
/*名称：SendMessage
/*描述：利用套接字发送信息，用于创建线程
/*完成日期：2019.8.30
/*参数：套接字句柄指针
/*返回值：空
/*作者：霍高原
/****************************************************/

void *RecvMessage(int* sockfd){
    char s[100];
    int fd=*sockfd;
    while(1){
        if(recv(fd,s,100,0)==-1){
            perror("recv");
            pthread_exit("FAIL");
        }
        printf("receive:%s\n",s);
        memset(s,0,sizeof(s));
	sleep(1);
    }
    pthread_exit("OK");
}

/****************************************************/
/*名称：RecvMessage
/*描述：接受信息线程函数，用于创建线程
/*完成日期：2019.8.30
/*参数：套接字句柄
/*返回值：空
/*作者：霍高原
/****************************************************/

void StartListen(int *sockfd){
    if(listen(*sockfd,10)<0){
        perror("listen");
        exit(1);
    }
    printf("succeed to listen\n");
}

/****************************************************/
/*名称：StartListen
/*描述：服务器端开始监听
/*完成日期：2019.8.30
/*参数：套接字句柄
/*返回值：空
/*作者：霍高原
/****************************************************/

void SendRecive(int *connfd){     //2层
    void* thread_result;
    pthread_t send_t,recv_t;
    pthread_create(&send_t,NULL,SendMessage,connfd);
    pthread_create(&recv_t,NULL,RecvMessage,connfd);
    
    pthread_join(send_t,thread_result);
}

/****************************************************/
/*名称：SendRecive
/*描述：客户端收发信息函数
/*完成日期：2019.8.30
/*参数：套接字句柄
/*返回值：空
/*作者：霍高原
/****************************************************/

void CreateTransFunc(int count){
    pthread_t deal_thread;
    //用于接收数据并向其他客户端转发的线程
    //connfd=service_trans_sockfd[count];
    pthread_create(&deal_thread,NULL,CreateTransThread,count);

    //pthread_join(deal_thread,NULL);//加入后会导致后面新客户无法进入
}

/****************************************************/
/*名称：CreateTransFunc
/*描述：创建服务器端处理客户端收发信息的函数
/*完成日期：2019.8.30
/*参数：int count，为处理用套接字的地址
/*返回值：空
/*作者：霍高原
/****************************************************/

void *CreateTransThread(int count){//*sockfd,int i){          //服务器转发线程函数
    char s[100];
    int fd=service_trans_sockfd[count];
    int target;
    while(1){
        if(recv(fd,s,100,0)==-1){
            //perror("trans_recv");
            pthread_exit("FAIL");
        }
        target=service_trans_sockfd[(int)(s[0]-'0')];        //先写一位的
        if(target<0){
            perror("target:");
            //pthread_exit("FAIL");  //一旦出错就炸了
            continue; //还存在问题，error位置
        }
        s[0]=(char)(count+'0');s[1]=':';
        //用于使接受者收到发送者位置
        if(send(target,s,100,0)==-1){
            perror("trans_send");
            //pthread_exit("FAIL");
            continue;
        }
        memset(s,0,sizeof(s));
	    sleep(1);
    }
    pthread_exit("OK");
}

/****************************************************/
/*名称：
/*描述：
/*完成日期：2019.8.30
/*参数：
/*返回值：空
/*作者：霍高原
/****************************************************/
