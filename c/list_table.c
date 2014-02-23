/*
 * 线性表
 */
#include <stdio.h>
#include <malloc.h>
typedef struct Llist{
	int data;
	struct Llist *next;
} Llist;
typedef struct Llist *LinkList;
void list_insert(LinkList *, int);
void list_remove(LinkList *, int);
void list_print(LinkList);
void list_clear(LinkList *);
void list_reverse(LinkList *);
int main(void)
{
	struct Llist *list;
	int  num, state;
	char opp;
	state = initList(&list);	//初始化链表
	if(!state)
	{
		printf("内存分配失败\n");
		return 0;
	}
	while(state != '0')
	{
		printf("请选择您要做的操作：\n1、增加    2、删除	3、清空链表		4、翻转链表		0、退出\n");
		scanf("%c", &opp);
		if(opp == '1'){
			printf("请输入要插入的数字：");
			scanf("%d", &num);
			list_insert(&list, num);
			list_print(list);
		}else if(opp == '2'){
			printf("请输入要删除的数字：");
			scanf("%d", &num);
			list_remove(&list, num);
			list_print(list);
		}else if(opp == '3'){
			list_clear(&list);
			list_print(list);
		}else if(opp == '4'){
			list_reverse(&list);
			list_print(list);
		}else{
			//exit(0);
		}
	}
	free(list);
	return 0;
}

int initList(LinkList *list)
{
	*list = (LinkList)malloc(sizeof(Llist));	//申请内存
	if(!(*list))	//申请失败
	{
		return 0;
	}
	(*list)->next = NULL;	//头结点
	return 1;
}

void list_insert(LinkList *head, int num)
{
	struct Llist *p, *tmp, *pre;
	p = (LinkList)malloc(sizeof(Llist));
	p->data = num;
	tmp = *head;	//指向头结点
	if(*head == NULL){	//空表
		printf("empty");
		*head = p;
		p->next = NULL;
	}else{
		while(tmp->next && num > tmp->data){	//寻找插入的位置
			pre = tmp;
			tmp = tmp->next;
		}
		if(tmp->next == NULL){	//插入到表尾
			printf("last");
			tmp->next = p;
			p->next = NULL;
		}else if(*head == tmp){	//插入在表头
			printf("head");
			p->next = (*head)->next;
			(*head)->next = p;
		}else{	//插入在表中
			pre->next = p;
			p->next = tmp;
		}
	}
}

void list_remove(LinkList *head, int num)
{
	LinkList tmp, p;
	tmp = *head;
	while(tmp->next && num != tmp->data){
		p = tmp;
		tmp = tmp->next;
	}
	//找到
	if(num == tmp->data){
		p->next = tmp->next;
		free(tmp);
	}
}

void list_clear(LinkList *head)
{
	LinkList p, tmp;
	tmp = (*head)->next;
	while(tmp->next){
		p = tmp->next;
		free(tmp);
		tmp = p;

	}
	(*head)->next = NULL;
}

void list_reverse(LinkList *head)
{
	LinkList p, tmp;
	tmp = (*head)->next;
	while(tmp->next){
		p = tmp->next;
		tmp->next = p->next;
		p->next = (*head)->next;
		(*head)->next = p;
	}
}

void list_print(struct Llist *head)
{
	LinkList p = head->next;
	printf("\n");
	while(p){
		printf("%3d", p->data);
		p = p->next;
	}
	printf("\n");
	free(p);
}
