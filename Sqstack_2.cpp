#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 21
#define ERROR 0
#define OK 1
typedef struct NPOD  //数字栈 
{
    int n[MAXSIZE];  //数组 
    int top;
}OPNDStack;
typedef struct OPTR  //字符栈 
{
    char n[MAXSIZE];
    int top;
}OPTRStack;


//下面对数字栈进行基本操作 
void InitOPNDStack(OPNDStack *num) //初始化数字栈 
{
    num->top=NULL;  //栈顶指针置空 
}

int Push(OPNDStack *num,int e)  //数字栈压栈 
{
    if(num->top==MAXSIZE) //若栈满则报错 
        return ERROR;
    num->n[num->top++] = e; //将入栈的数字存入数组 
    return OK;
}
int Pop(OPNDStack *num,int *e) //数字栈出栈 
{
    if(num->top==NULL)  //判空 
        return ERROR;
    *e=num->n[--num->top];  //记录出栈元素 
    return OK;
}
int GetTop(OPNDStack *num,int *e)  //获得数字栈的栈顶元素 
{
    if(num->top==NULL)//判空
        return ERROR;
    *e=num->n[num->top-1];  //将e的值传回 
    return OK;
}
int IsEmpty(OPNDStack *num)  //判空 
{
    return num->top==NULL;
}


//下面对字符栈进行基本操作 
void InitOPTRStack(OPTRStack *sign) //初始化字符栈 
{
    sign->top=NULL;  //置空 
}

int PushOPTRStack(OPTRStack *sign,char e)  //字符栈压栈 
{
    if(sign->top==MAXSIZE) //判满 
        return ERROR;
    sign->n[sign->top++]=e;
    return OK;
}
int PopOPTRStack(OPTRStack *sign,char *e) //字符栈出栈 
{
    if(sign->top==NULL) //判空 
        return ERROR;
    *e=sign->n[--sign->top];
    return OK;
}
int GetOPTRStackTop(OPTRStack *sign,char *e) //获得字符栈栈顶元素 
{
    if(sign->top==NULL)
        return ERROR;
    *e=sign->n[sign->top-1];
    return OK;
}
int IsOPTRStackEmpty(OPTRStack *sign)  //判空 
{
    return sign->top==NULL;
}
int level(char ch)  //符号 
{
    if(ch=='+'||ch=='-')
        return 1;
    else if(ch== '*'||ch=='/')
        return 2;
    else
        return 0;
}
int IsNum(char ch) //数字 
{
    if(ch>='0'&&ch<='9')
        return 1;
    return 0;
}
int Operate(char ch,OPNDStack *num,int *result)  //操作运算 
{
   int a,b;
   Pop(num,&a);
   Pop(num,&b);//将从栈中跳出两个元素，并将他们的值赋给a、b
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
            return ERROR;//如果不符合运算法则，那么返回ERROR
          }
          *result=b/a;
          break;
   }
   return OK;
}
void Operate1(OPNDStack *num,OPTRStack *sign,char *n,char ch,char tmp,int result) 
{
    if(IsOPTRStackEmpty(sign)||level(ch)>level(tmp))//当前符号的优先级大于栈顶符号的优先级，那么直接入栈
		{
	        PushOPTRStack(sign,ch);
	    }
	else   //当前的符号的优先级小于等于栈顶符号的优先级，那么将栈顶元素从OPTR栈中跳出并输出
		{
	        PopOPTRStack(sign,&tmp);
	        printf(" %c",tmp); 
	        if(!Operate(tmp,num,&result))
			{
	            printf("被除数不可以为0，运算错误!\n");
	            return;
	        }
	        Push(num,result);//如果运算符合运算法则，那么将运算结果压入到栈中
	        GetOPTRStackTop(sign,&tmp);
	        Operate1(num,sign,n,ch,tmp,result);//利用goto语句，从而实现当前的符号的优先级小于栈顶符号的优先级，然后将其压入
	        
		}
}
void GetPreExpression(OPNDStack *num,OPTRStack *sign,char *n)
{
    int i,result,j,k = 0,a,b,count=0;  //count统计数字的个数
    char ch,tmp,arr[MAXSIZE];
    for(i=0;n[i]!= '\0';i++)
	{
        ch=n[i];
        if(IsNum(ch))
		{
            j = i;
            k = 0;//重置k
            while(IsNum(n[j]))
			{
                arr[k++] = n[j];
                j++;
            }
            arr[k]='\0';  //字符串最后一位是'\0' 
            i=j-1;
            a=atoi(arr);//将这个数字的字符串转成整形数字
            count++;
            if(count == 1)
                printf("%d",a);//如果是第一个数字，那么前面不需要输出一个空格，否则要在前面输出空格
            else
                printf(" %d",a);
            Push(num,a);//将数字压入栈中
        }
		else
		{
            //如果是运算符，那么需要分情况讨论
            if(IsOPTRStackEmpty(sign)||ch == '(')  //如果栈为空或者当前字符为左括号，直接将当前符号压入栈中
			{
                PushOPTRStack(sign,ch);
            }
			else
			{
                GetOPTRStackTop(sign,&tmp);
                if(tmp=='(')//如果栈顶元素是一个左括号，那么直接入栈
				{
                    PushOPTRStack(sign,ch);
                }
				else  //当前的字符不是一个左括号，那么需要判断当前的符号是否为一个右括号
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
                          printf("被除数不可以为0，运算错误!\n");
                          return;
                       }
                       Push(num,result);//如果运算符合运算法则，那么将运算结果压入到栈中
                       GetOPTRStackTop(sign,&tmp);
                    }
                    PopOPTRStack(sign,&tmp);
                  }
				  else  //当前的符号是一个普通符号，那么需要比较优先级
				  {
                     Operate1(num,sign,n,ch,tmp,result);
                    }
                  }
                }
            }

        }
        
    
    //将num压入到OPTR栈中
    while(!IsOPTRStackEmpty(sign))
	{
         PopOPTRStack(sign,&tmp);
         printf(" %c",tmp);
         if(!Operate(tmp,num,&result))  //将进行相应的运算，然后将对应的运算结果赋值给result
		 {
            printf("被除数不可以为0，运算错误!\n");
            return;
         }
         Push(num,result);//如果运算符合运算法则，那么将运算结果压入到栈中
    }
    printf("\n");
    Pop(num,&a);//将num中的栈顶元素的值赋给a，并将其删除
    printf("%s的运算结果为%d\n",n,a);
}
int main()
{
    OPNDStack *num = (OPNDStack *)malloc(sizeof(OPNDStack));
    OPTRStack *sign= (OPTRStack *)malloc(sizeof(OPTRStack));
    char n[MAXSIZE];
    int i=0;
    InitOPNDStack(num);//将栈进行初始化
    InitOPTRStack(sign);
    printf("请输入中缀表达式:"); 
    scanf("%s",n);//输入字符串
     while(n[i]!=NULL) i++;
    n[i-1]=NULL;
    GetPreExpression(num,sign,n);//将后缀表达式输出，同时将它的运算结果输出
    return 0;
}




