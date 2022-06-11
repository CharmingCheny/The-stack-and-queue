#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 21
#define ERROR 0
#define OK 1
typedef struct NPOD  //����ջ 
{
    int n[MAXSIZE];  //���� 
    int top;
}OPNDStack;
typedef struct OPTR  //�ַ�ջ 
{
    char n[MAXSIZE];
    int top;
}OPTRStack;


//���������ջ���л������� 
void InitOPNDStack(OPNDStack *num) //��ʼ������ջ 
{
    num->top=NULL;  //ջ��ָ���ÿ� 
}

int Push(OPNDStack *num,int e)  //����ջѹջ 
{
    if(num->top==MAXSIZE) //��ջ���򱨴� 
        return ERROR;
    num->n[num->top++] = e; //����ջ�����ִ������� 
    return OK;
}
int Pop(OPNDStack *num,int *e) //����ջ��ջ 
{
    if(num->top==NULL)  //�п� 
        return ERROR;
    *e=num->n[--num->top];  //��¼��ջԪ�� 
    return OK;
}
int GetTop(OPNDStack *num,int *e)  //�������ջ��ջ��Ԫ�� 
{
    if(num->top==NULL)//�п�
        return ERROR;
    *e=num->n[num->top-1];  //��e��ֵ���� 
    return OK;
}
int IsEmpty(OPNDStack *num)  //�п� 
{
    return num->top==NULL;
}


//������ַ�ջ���л������� 
void InitOPTRStack(OPTRStack *sign) //��ʼ���ַ�ջ 
{
    sign->top=NULL;  //�ÿ� 
}

int PushOPTRStack(OPTRStack *sign,char e)  //�ַ�ջѹջ 
{
    if(sign->top==MAXSIZE) //���� 
        return ERROR;
    sign->n[sign->top++]=e;
    return OK;
}
int PopOPTRStack(OPTRStack *sign,char *e) //�ַ�ջ��ջ 
{
    if(sign->top==NULL) //�п� 
        return ERROR;
    *e=sign->n[--sign->top];
    return OK;
}
int GetOPTRStackTop(OPTRStack *sign,char *e) //����ַ�ջջ��Ԫ�� 
{
    if(sign->top==NULL)
        return ERROR;
    *e=sign->n[sign->top-1];
    return OK;
}
int IsOPTRStackEmpty(OPTRStack *sign)  //�п� 
{
    return sign->top==NULL;
}
int level(char ch)  //���� 
{
    if(ch=='+'||ch=='-')
        return 1;
    else if(ch== '*'||ch=='/')
        return 2;
    else
        return 0;
}
int IsNum(char ch) //���� 
{
    if(ch>='0'&&ch<='9')
        return 1;
    return 0;
}
int Operate(char ch,OPNDStack *num,int *result)  //�������� 
{
   int a,b;
   Pop(num,&a);
   Pop(num,&b);//����ջ����������Ԫ�أ��������ǵ�ֵ����a��b
   switch(ch)
   {
      case '+':
          *result=b+a;
           break;
      case '-':
          *result=b-a;
           break;
      case '*':
          *result=b*a;
           break;
      case '/':
          if(a==0)
		  {
            return ERROR;//������������㷨����ô����ERROR
          }
          *result=b/a;
          break;
   }
   return OK;
}
void Operate1(OPNDStack *num,OPTRStack *sign,char *n,char ch,char tmp,int result) 
{
    if(IsOPTRStackEmpty(sign)||level(ch)>level(tmp))//��ǰ���ŵ����ȼ�����ջ�����ŵ����ȼ�����ôֱ����ջ
		{
	        PushOPTRStack(sign,ch);
	    }
	else   //��ǰ�ķ��ŵ����ȼ�С�ڵ���ջ�����ŵ����ȼ�����ô��ջ��Ԫ�ش�OPTRջ�����������
		{
	        PopOPTRStack(sign,&tmp);
	        printf(" %c",tmp); 
	        if(!Operate(tmp,num,&result))
			{
	            printf("������������Ϊ0���������!\n");
	            return;
	        }
	        Push(num,result);//�������������㷨����ô��������ѹ�뵽ջ��
	        GetOPTRStackTop(sign,&tmp);
	        Operate1(num,sign,n,ch,tmp,result);//����goto��䣬�Ӷ�ʵ�ֵ�ǰ�ķ��ŵ����ȼ�С��ջ�����ŵ����ȼ���Ȼ����ѹ��
	        
		}
}
void GetPreExpression(OPNDStack *num,OPTRStack *sign,char *n)
{
    int i,result,j,k = 0,a,b,count=0;  //countͳ�����ֵĸ���
    char ch,tmp,arr[MAXSIZE];
    for(i=0;n[i]!= '\0';i++)
	{
        ch=n[i];
        if(IsNum(ch))
		{
            j = i;
            k = 0;//����k
            while(IsNum(n[j]))
			{
                arr[k++] = n[j];
                j++;
            }
            arr[k]='\0';  //�ַ������һλ��'\0' 
            i=j-1;
            a=atoi(arr);//��������ֵ��ַ���ת����������
            count++;
            if(count == 1)
                printf("%d",a);//����ǵ�һ�����֣���ôǰ�治��Ҫ���һ���ո񣬷���Ҫ��ǰ������ո�
            else
                printf(" %d",a);
            Push(num,a);//������ѹ��ջ��
        }
		else
		{
            //��������������ô��Ҫ���������
            if(IsOPTRStackEmpty(sign)||ch == '(')  //���ջΪ�ջ��ߵ�ǰ�ַ�Ϊ�����ţ�ֱ�ӽ���ǰ����ѹ��ջ��
			{
                PushOPTRStack(sign,ch);
            }
			else
			{
                GetOPTRStackTop(sign,&tmp);
                if(tmp=='(')//���ջ��Ԫ����һ�������ţ���ôֱ����ջ
				{
                    PushOPTRStack(sign,ch);
                }
				else  //��ǰ���ַ�����һ�������ţ���ô��Ҫ�жϵ�ǰ�ķ����Ƿ�Ϊһ��������
				{
                  
                  if(ch==')')
				  {
                    GetOPTRStackTop(sign,&tmp);
                    while(tmp!='(')
					{
                       PopOPTRStack(sign,&tmp);
                       printf(" %c",tmp);
                       if(!Operate(tmp,num,&result))
					   {
                          printf("������������Ϊ0���������!\n");
                          return;
                       }
                       Push(num,result);//�������������㷨����ô��������ѹ�뵽ջ��
                       GetOPTRStackTop(sign,&tmp);
                    }
                    PopOPTRStack(sign,&tmp);
                  }
				  else  //��ǰ�ķ�����һ����ͨ���ţ���ô��Ҫ�Ƚ����ȼ�
				  {
                     Operate1(num,sign,n,ch,tmp,result);
                    }
                  }
                }
            }

        }
        
    
    //��numѹ�뵽OPTRջ��
    while(!IsOPTRStackEmpty(sign))
	{
         PopOPTRStack(sign,&tmp);
         printf(" %c",tmp);
         if(!Operate(tmp,num,&result))  //��������Ӧ�����㣬Ȼ�󽫶�Ӧ����������ֵ��result
		 {
            printf("������������Ϊ0���������!\n");
            return;
         }
         Push(num,result);//�������������㷨����ô��������ѹ�뵽ջ��
    }
    printf("\n");
    Pop(num,&a);//��num�е�ջ��Ԫ�ص�ֵ����a��������ɾ��
    printf("%s��������Ϊ%d\n",n,a);
}
int main()
{
    OPNDStack *num = (OPNDStack *)malloc(sizeof(OPNDStack));
    OPTRStack *sign= (OPTRStack *)malloc(sizeof(OPTRStack));
    char n[MAXSIZE];
    int i=0;
    InitOPNDStack(num);//��ջ���г�ʼ��
    InitOPTRStack(sign);
    printf("��������׺���ʽ:"); 
    scanf("%s",n);//�����ַ���
     while(n[i]!=NULL) i++;
    n[i-1]=NULL;
    GetPreExpression(num,sign,n);//����׺���ʽ�����ͬʱ���������������
    return 0;
}




