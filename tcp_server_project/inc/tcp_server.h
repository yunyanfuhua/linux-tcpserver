#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <stdlib.h>

#define MAX_LISTEN 128

//创建一个TCP服务器套接字
/*
@IP:你的TCP服务器的地址
@port:你的TCP服务器的端口号
返回值：
	tcp的连接套接字
*/

int make_tcp_server(const char *ip,unsigned short port);




#endif