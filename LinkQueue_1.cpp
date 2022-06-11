#include <stdio.h>
#include <stdlib.h>
#define MAXQSIZE 5
#define OK 1
typedef struct QNode
{
	int data;
	struct QNode *next;
 } QNode,*QueuePtr;
 typedef struct 
 {
 	QueuePtr front; //队头指针 
 	QueuePtr rear;  //队尾指针 
 }LinkQueue;
 int InitQueue(LinkQueue &Q)
 {
 	Q.front=Q.rear=new QNode; //开辟结点 
 	Q.front->next=NULL; //置空 
 	return OK;
 }
int IsEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear)  //判断头尾指针是否相等 
	{
		printf("空！\n");
		return 1;
	 } 
	else
	{
		printf("非空！\n");
		return 0;
	}
 } 
int EnQueue(LinkQueue &Q,int e)
{
	QNode *p;
	p=new QNode;  //开辟新结点 
	p->data=e;  //赋值 
	p->next=NULL; //新结点的next域置空 
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}
int DeQueue(LinkQueue &Q)
{
	int e;
	QNode *p;
	if(Q.front==Q.rear) return 0;  //判断对列是否为空 
	p=Q.front->next;
	e=p->data;  //数字域赋值 
	Q.front->next=p->next;
	if(Q.rear==p)  //若最后一个元素删除，则队尾对头指针相等 
		Q.rear=Q.front;
	delete p;
	return e;
}
int LengthQueue(LinkQueue Q)
{
	QNode *p;
	p=Q.front;
	int i=0;  //计数 
	while(p)  //遍历链表 
	{
		i++;
		p=p->next;
	}
	printf("队长为:%d",i-1);
	return OK;
}
int main()
{
	int i,e; 
	LinkQueue q;
	InitQueue(q);  //初始化队列 
	IsEmpty(q);  //判空 
	for(i=0;i<3;i++)  //逐个插入元素 
	{
		printf("请输入插入数字:");
		scanf("%d",&e);
		EnQueue(q,e);
	}
	e=DeQueue(q); //出队元素
	printf("出队元素为:%d\n",e); 
	LengthQueue(q); //计算队长
	printf("\n");
	for(i=0;i<3;i++)  //逐个插入元素 
	{
		printf("请输入插入数字:");
		scanf("%d",&e);
		EnQueue(q,e);
	}
	LengthQueue(q); //计算队长
	printf("\n");
	printf("出队序列为:"); 
	while(q.front!=q.rear)  //全部出队 
	{
		e=DeQueue(q);
		printf("%4d",e);
	}
	return 0;
}
