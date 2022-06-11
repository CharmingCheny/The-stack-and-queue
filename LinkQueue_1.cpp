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
 	QueuePtr front; //��ͷָ�� 
 	QueuePtr rear;  //��βָ�� 
 }LinkQueue;
 int InitQueue(LinkQueue &Q)
 {
 	Q.front=Q.rear=new QNode; //���ٽ�� 
 	Q.front->next=NULL; //�ÿ� 
 	return OK;
 }
int IsEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear)  //�ж�ͷβָ���Ƿ���� 
	{
		printf("�գ�\n");
		return 1;
	 } 
	else
	{
		printf("�ǿգ�\n");
		return 0;
	}
 } 
int EnQueue(LinkQueue &Q,int e)
{
	QNode *p;
	p=new QNode;  //�����½�� 
	p->data=e;  //��ֵ 
	p->next=NULL; //�½���next���ÿ� 
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}
int DeQueue(LinkQueue &Q)
{
	int e;
	QNode *p;
	if(Q.front==Q.rear) return 0;  //�ж϶����Ƿ�Ϊ�� 
	p=Q.front->next;
	e=p->data;  //������ֵ 
	Q.front->next=p->next;
	if(Q.rear==p)  //�����һ��Ԫ��ɾ�������β��ͷָ����� 
		Q.rear=Q.front;
	delete p;
	return e;
}
int LengthQueue(LinkQueue Q)
{
	QNode *p;
	p=Q.front;
	int i=0;  //���� 
	while(p)  //�������� 
	{
		i++;
		p=p->next;
	}
	printf("�ӳ�Ϊ:%d",i-1);
	return OK;
}
int main()
{
	int i,e; 
	LinkQueue q;
	InitQueue(q);  //��ʼ������ 
	IsEmpty(q);  //�п� 
	for(i=0;i<3;i++)  //�������Ԫ�� 
	{
		printf("�������������:");
		scanf("%d",&e);
		EnQueue(q,e);
	}
	e=DeQueue(q); //����Ԫ��
	printf("����Ԫ��Ϊ:%d\n",e); 
	LengthQueue(q); //����ӳ�
	printf("\n");
	for(i=0;i<3;i++)  //�������Ԫ�� 
	{
		printf("�������������:");
		scanf("%d",&e);
		EnQueue(q,e);
	}
	LengthQueue(q); //����ӳ�
	printf("\n");
	printf("��������Ϊ:"); 
	while(q.front!=q.rear)  //ȫ������ 
	{
		e=DeQueue(q);
		printf("%4d",e);
	}
	return 0;
}
