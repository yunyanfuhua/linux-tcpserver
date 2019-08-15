#include"tcp_server.h"

//创建一个TCP服务器套接字
/*
@IP:你的TCP服务器的地址
@port:你的TCP服务器的端口号
返回值：
	tcp的连接套接字
*/

int make_tcp_server(const char *ip,unsigned short port)
{
	//创建一个套接字
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		perror("socket error");
		return  -1;
	}
	//2.初始化一个服务器的IPV4结构体
	struct sockaddr_in sAddr;
	memset(&sAddr,0,sizeof(sAddr));//内存设置
	sAddr.sin_family = AF_INET; //指定协议族  AF_INET
	sAddr.sin_port = htons(port);   //端口号
	//sAddr.sin_addr; //ip地址
	//inet_aton(argv[2],&(sAddr.sin_addr));
	sAddr.sin_addr.s_addr = inet_addr(ip);
	
	//3.bind。把一个地址结构体绑定到套接字上面去
	int  res = bind(sock, (struct sockaddr *)&sAddr,sizeof(sAddr));
	if(res == -1)
	{
		perror("bind error");
		return -1;
	}
	
	//4.listen 开启对一个套接字的监听
	listen(sock,MAX_LISTEN);
	
	return sock;
}




