#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef char* Elemtype; //数据类型
//数据结点
typedef struct dulnode
{
	Elemtype data; //保存结点的数据  “数据域”
	struct dulnode *next; //保存下一个结点的地址
	struct dulnode *prev; //保存上一个结点的地址
}Dulnode;

//头节点
typedef struct dullinklist
{
	Dulnode *first; //指向链表中的第一个数据结点
	Dulnode *last; //指向链表中的最后一个数据结点
	int num; //链表的数据结点的个数
}DulLinklist;

DulLinklist *create_double_circle_linklist_head(void);
void tail_insert(DulLinklist *head, Elemtype data);
void print_dul_cir_linklist(DulLinklist *head);
void* delete_linklist(DulLinklist *head);

#endif