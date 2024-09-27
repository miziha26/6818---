#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linklist.h"

/*
	create_double_circle_linklist_head:创建双向循环链表的头节点
	返回值：
		DulLinklist *
*/
DulLinklist *create_double_circle_linklist_head(void)
{
	DulLinklist *dl = (DulLinklist *)malloc(sizeof(DulLinklist));
    dl->first = NULL;
    dl->last = NULL;
    dl->num = 0;
    return dl;
}

/*
    tail_insert:使用尾插法创建双向循环链表
    @head:双向循环链表的头结点的地址
    @data:保存的数据
    返回值：
        void
*/
void tail_insert(DulLinklist *head, Elemtype data) //   "./1.bmp"
{
    if(head == NULL) //链表不存在
    {
        return ;
    }

    //1.先为数据创建一个数据节点
    Dulnode *p = (Dulnode*)malloc(sizeof(Dulnode));
    p->data = (Elemtype)malloc(strlen(data) + 1);
    strcpy(p->data, data);
    p->next = NULL;
    p->prev = NULL;

    //2.将数据节点使用尾插法插入到链表中
    if(head->first == NULL) //空链表
    {
        head->first = head->last = p;
        p->prev = p;
        p->next = p;
    }
    else //第二个数据节点及以后的节点的情况
    {
        head->last->next = p;
        p->prev = head->last;
        head->last = p;
        head->first->prev = head->last;
        head->last->next = head->first;
    }
    
    head->num++;
}


/*
    print_dul_cir_linklist:打印带头结点的双向循环链表
    @head:链表的头节点的地址
    返回值：
        void
*/
void print_dul_cir_linklist(DulLinklist *head)
{
    if(head == NULL) //链表不存在
    {
        return ;
    }

    Dulnode *p = head->first;
    while(p)
    {
        printf("%s\n", p->data);
        p = p->next;
        if(p == head->first)
        {
            break;
        }
    }
}

/*
    delete_linklist:删除整张链表
    @head:链表的头结点的地址
    返回值：
        void *
*/
void* delete_linklist(DulLinklist *head)
{
    if(head == NULL)
    {
        return NULL;
    }

    //先环断开
    if(head->first != NULL)
    {
        head->first->prev = NULL;
        head->last->next = NULL;
    }

    Dulnode *del = head->first;
    while(del)
    {
        head->first = head->first->next;
        if(head->first != NULL)
        {
            head->first->prev = NULL; //必然段错误
        }
        del->next = NULL;
        free(del->data);
        del->data = NULL;
        free(del);
        del = head->first;
    }

    free(head);
    head = NULL;
    return head;
}

