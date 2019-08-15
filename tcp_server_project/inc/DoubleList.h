#ifndef __DOUBLE_LIST_H__
#define __DOUBLE_LIST_H__
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

//数据内容结构体
typedef struct cli_info
{
	int fd;// 客户端的连接套接字
	unsigned short port;//客户端的端口号
	char ip[16];//客户端的IP地址字符串
	FILE *fp;//对应的日志文件的标准IO的文件指针
	//struct sockaddr_in *caddr;
}CLI_INFO;


//数据结点类型
typedef struct node
{
	//指针域
	struct node *next;
	struct node *prev;
	//数据域
	CLI_INFO data;
}NODE;

//头结点类型
typedef struct hnode
{
	NODE *first;//指向链表的第一个数据结点的指针  
	NODE *tail;//指向链表的最后一个数据结点的指针
	unsigned int len;//链表的结点个数，客户端的个数
}HNODE;


//创建一个双向链表,返回一个头结点指针
HNODE *create_list();

//把结点信息加入链表
void tail_insert(HNODE* list,CLI_INFO data_buf);

//根据fd找到链表中的结点



//根据fd找到结点并删除结点
/*
结点的删除分为：
删除的是第一个结点
删除的是最后一个结点
删除的是中间的结点
*/
FILE *node_search_delet(HNODE *list,int fd,int search_flag);
void print_list(HNODE *);
#endif


/*
确定链表类型  双向带头节点链表
	1.头结点(管理整个链表)
		内容：
			头指针:指向链表的第一个数据结点的指针  
			尾指针:指向链表的最后一个数据结点的指针
			长度：记录链表结点个数
			....

	2.数据结点(记录结点的数据内容以及下一个结点的地址)
		内容：
			指针域：
				指向下一个数据结点的指针
				指向上一个数据结点的指针				
			数据域：
				根据实际情况设计

*/
