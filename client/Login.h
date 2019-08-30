/**************************************************
	> 文件名：Login.h
	> 模块描述：登录模块函数定义
	> 完成日期：
	> 参与者：刘雅诗，华润洲
/***************************************************/

#ifndef __LOGIN_H
#define __LOGIN_H

#include<stdio.h>
#include <sys/socket.h>
#include <string.h>

void CheckLoginInfo(char* userID, char* pwd);
int SendMsgToServer(char* userID, char* pwd);
int RecvMsgFromServer(char* msg);
int CreateFolder(char* userID);

#endif



