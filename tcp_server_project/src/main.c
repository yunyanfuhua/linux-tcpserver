#include<stdio.h>
#include"tcp_server.h"
#include"DoubleList.h"

/* According to POSIX.1-2001 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include<pthread.h>

#define DEBUG

//消息结构体
struct CLI_DATA
{
	//time_t time;
	char buf[1024];
	int len;//记录读到的消息的长度
	int fd;//记录从哪一个客服端的读到的消息
}CLI_DATA;

HNODE *cli_l;

//线程函数，处理客户端发送的数据
void *func(void *arg)
{
	pthread_detach(pthread_self());
	struct CLI_DATA *xx = (struct CLI_DATA *)arg;
	FILE * fp = node_search_delet(cli_l,xx->fd,1);
	fwrite(xx->buf,sizeof(char),strlen(xx->buf),fp);
	fflush(fp);
	printf("buf=%s\n",xx->buf);


}



int main(int argc,char *argv[])
{
	//创建一个TCP服务器
	int sockfd = make_tcp_server(argv[1],atoi(argv[2]));
	if(-1 == sockfd)
	{
		printf("make_tcp_server failed\n");
		return -1;
	}
	
	//等待客户端连接，使用多路复用 select
	int max_fd;//保存要监听的文件描述符的最大值
	fd_set set;//监听文件描述符可读的集合
	
	max_fd = sockfd;//暂时还没有其他的客户端，最大值就是服务器的fd
	
	//创建一个双向链表，保存客户端的相关信息
	cli_l = create_list();
	
	while(1)
	{
		//清空set
		FD_ZERO(&set);
		//把要监听服务器的文件描述符添加到set
		FD_SET(sockfd,&set);
		//把要监听客户端的文件描述符添加到set
		//遍历链表，把每一个数据结点的 套接字连接描述符(accept返回值)加入set
		
		NODE *t = cli_l->first;
		while(t)
		{
			FD_SET(t->data.fd,&set);
			//max_fd = max_fd > t->data.fd?max_fd:t->data.fd;//记录集合中的最大值
			t = t->next;
		}

		int ret = select(max_fd+1,&set, NULL,NULL,NULL);
		if(ret <= 0)
		{
			continue;
		}
		
		//集合中有就绪的文件描述符，有可能是 服务器(有新的客户要连接)，客户端(有数据可读)
		if(FD_ISSET(sockfd,&set))//服务器就绪
		{
			struct sockaddr_in cAddr; //表示保存客户端的地址结构体
			socklen_t addrlen = sizeof(cAddr);
			int new_fd = accept(sockfd, (struct sockaddr *)&cAddr, &addrlen);
			if(new_fd > 0)
			{
				printf("client IP:%s prot:%d\n",inet_ntoa(cAddr.sin_addr),ntohs(cAddr.sin_port));
				printf("2\n");
			}
			if(new_fd >max_fd)
			{
				max_fd = new_fd;
			}
			//处理新的连接把
			//保存客户端的相关信息
			CLI_INFO new;
			new.fd = new_fd;
			new.port = ntohs(cAddr.sin_port);
			strcpy(new.ip,inet_ntoa(cAddr.sin_addr));
			//创建一个日志文件(文件名为端口号和IP)
			char log_name[128];
#ifdef DEBUG
printf("xx1\n");
#endif
			memset(log_name,0,sizeof(log_name));
			sprintf(log_name,"%s_%d",new.ip,new.port);
			new.fp = fopen(log_name,"a+");
			//把客户端的信息加入链表
#ifdef DEBUG
printf("xx2\n");
#endif
			tail_insert(cli_l,new);
#ifdef DEBUG
printf("xx1\n");
#endif
			print_list(cli_l);
		}
		//判断客户端是否就绪，遍历链表，查看链表中的结点是否在set中
		t = cli_l->first;
#ifdef DEBUG
printf("xx3\n");
#endif
		while(t)
		{
			if(FD_ISSET(t->data.fd,&set))//客户端发送了信息，可以读
			{
				struct CLI_DATA *d = malloc(sizeof(CLI_DATA));
				memset(d->buf,0,1024);
				
				int n = read(t->data.fd,d->buf,1024);
				if(n<=0)
				{
#ifdef DEBUG
printf("xx4\n");
#endif
					//printf("client close\n");
					//读取失败客户端已经断开连接
					//将节点中的fd close，将fp close，还要删除客户端节点
					close(t->data.fd);
					fclose(t->data.fp);
#ifdef DEBUG
printf("xx5\n");
#endif
					//删除链表中的结点
					node_search_delet(cli_l,t->data.fd,0);
					t=t->next;
#ifdef DEBUG
printf("xx4\n");
#endif
					continue;
				}
				d->len = n;
#ifdef DEBUG
printf("xx5\n");
#endif
				d->fd = t->data.fd;
				printf("buf=%s\n",d->buf);
				/*利用线程池技术或者创建一个新的线程去处理收到的数据
				
				根据d中的fd找到链表中的结点，再找到相应的日志文件的文件指针
				再把数据写进去*/
				pthread_t pid;
				pthread_create(&pid,NULL,func,(void *)d);
	
				
			}
#ifdef DEBUG
printf("xx6\n");
#endif
			t = t->next;
#ifdef DEBUG
printf("xx7\n");
#endif
		}
	}
	return 0;
}

