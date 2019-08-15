
#include"DoubleList.h"

HNODE *pool;

HNODE *create_list()
{

	HNODE *pool = (HNODE *)malloc(sizeof(HNODE));
	pool->first = NULL;
	pool->tail  = NULL;
	pool->len   = 0;
	return pool;
}

void tail_insert(HNODE* list,CLI_INFO data_buf)
{
	if(list->first == NULL)
	{
		NODE *node =(NODE *)malloc(sizeof(NODE));
		list->first = node;
		list->tail  = node;
		node->data.fd = data_buf.fd;
		node->data.port = data_buf.fd;
		strcpy(node->data.ip,data_buf.ip);
		node->data.fp = data_buf.fp;


	}
	else
	{
		NODE *node=(NODE *)malloc(sizeof(NODE));
		node->prev = list->tail;
		list->tail = node;
		node->next = NULL;
		node->data.fd = data_buf.fd;
		node->data.port = data_buf.fd;
		strcpy(node->data.ip,data_buf.ip);
		node->data.fp = data_buf.fp;
	}
}

FILE *  node_search_delet(HNODE *list,int search_fd,int search_flag )
{
	if(NULL == list)
	{
		return 0;
	}

	printf("1224\n");
	NODE *search_node = list->first;
	if(list->first == list->tail && list->first != NULL)
	{

		if(search_node->data.fd == search_fd)
		{
			if(0 == search_flag)
			{	
				search_node->prev = NULL;
				search_node->next = NULL;
				list->first = NULL;
				list->tail = NULL;
			}
			else
			{
				return search_node->data.fp;

			}
		}
		
	}
	else
	{
		while(search_node)
		{
			if(search_node->data.fd == search_fd)
			{
				if(NULL == search_node->next )
				{
					if(0  == search_flag )
					{	
						list->tail = search_node->prev;
						search_node->prev = NULL;
						free(search_node);
					}
					else
					{
						return search_node->data.fp;

					}
				}
				else
				{	
					if(0 == search_flag)
					{
						search_node->prev->next = search_node->next;
						search_node->next->prev = search_node->prev;
						search_node->prev = NULL;
						search_node->next = NULL;
						free(search_node);
					}
					else
					{
						return search_node->data.fp;
					}
				}
			search_node = search_node->next;
		}
	}
	return 0;
	
}
}
void print_list(HNODE *list)
{
	if(NULL == list)
	{
		return ;
	}
	NODE *p = list->first;
	while(p)
	{
		printf("ip;%s,port:%d\n",p->data.ip,p->data.port);
		printf("%d\n",p->next == NULL);
		p=p->next;
	}

}

