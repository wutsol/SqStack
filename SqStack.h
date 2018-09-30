#pragma once
#ifndef SqStack_h
#include <iostream>
#include <stdlib.h>
#define SqStack_h
#define Status int
#define StackSize 10
#define StackIncrease 5
#define ERROR 0
#define OK 1
#define FULL 0
#define EMPTY 0
#define NOT_EMPTY 1
template <class T>
class SqStack
{
private:
	T * base, *top;
	int stacksize;
public:
	SqStack();
	~SqStack();
	Status GetTop(T &e);
	Status Push(T e);
	Status Pop(T &e);
	int StackLength();//栈的长度
	Status IsEmpty();//判断栈是否为空
	int conversion(int num,int a);//数制转换,num为需要转换的数字，n为进制
	int EvalExpr(char *ptr);//表达式求值，中缀表示法
	int In(char c);//判断是否是运算符
	char Precede(char op, char c);//比较运算符优先级
	int Operate(int a, char theta, int b);//对数值进行运算操作
	char *change(char*ptr);//中缀式变后缀式
	int EvalExpr_RPN(char *exp);//表达式求值，后缀表示法
};
template <class T>
SqStack<T>::SqStack()
{
	base = new T[StackSize];
	if (!base) exit(OVERFLOW);
	top = base;
	stacksize = StackSize;
}
template <class T>
SqStack<T>::~SqStack()
{
	delete[] base;
}
template <class T>
Status SqStack<T>::GetTop(T &e)//用e返回栈顶元素
{
	if (top == base) return ERROR;
	e = *(top-1);
	return OK;
}
template <class T>
Status SqStack<T>::Push(T e)//将e放入栈
{
	/*if ((top - base) >= stacksize)//空间不够，增加容量
	{
		base = new T[StackSize + StackIncrease];
		T *p;
		if (!base) exit(OVERFLOW);
		p = top;
		top = base;
		for (int i = 0; i < stacksize; i++)//复制原来栈的数据
			top[i] = p[i];
		top++;
	}*/
	if (top - base >= stacksize) return FULL;
	*top++ = e;//先赋值，再后移
	return OK;
}
template <class T>
Status SqStack<T>::Pop(T &e)//删除栈顶元素，用e返回其值
{
	if (top == base) return ERROR;
	e = *(--top);//先前移，再取值
	return OK;
}
template <class T>
int SqStack<T>::StackLength()
{
	return top - base;
}
template <class T>
Status SqStack<T>::IsEmpty()
{
	if (top == base)
		return EMPTY;
	else
		return NOT_EMPTY;
}
template <class T>
int SqStack<T>::conversion(int num, int n)//数制转换
{
	int e,result=0;
	while (num)//入栈
	{
		Push(num%n);
		num /= n;
	}
	while (IsEmpty()!=EMPTY)
	{
		Pop(e);//出栈
		result=result*10+e;
	}
	return result;
}
template <class T>
int SqStack<T>::EvalExpr(char *ptr)//表达式求值，中缀表示法
{
	SqStack<char> OPTR;//操作符栈
	OPTR.Push('#');
	SqStack<int> OPND;//操作数栈
	char op, c, theta, x;
	int a, b,m;
	c = *ptr++;
	OPTR.GetTop(op);
	while (c!='#'||op!='#')
	{
		if (!In(c))//如果是数字，就入操作数栈
		{
			m = c - 48;
			OPND.Push(m);
			c = *ptr++;
		}
		else//如果是符号，将符号与栈顶符号比较大小
		{

			switch (Precede(op,c))
			{
			case'<'://栈顶运算符优先级低，将c入栈
				OPTR.Push(c);
				c = *ptr++;
				break;
			case'='://脱括号
				OPTR.Pop(x);
				c = *ptr++;
				break;
			case'>'://栈顶运算符优先级高，先做运算
				OPTR.Pop(theta);
				OPND.Pop(b);
				OPND.Pop(a);
				OPND.Push(Operate(a,theta,b));
				break;
			}
		}
		OPTR.GetTop(op);
	}
	OPND.GetTop(a);
	return a;
}
template<class T>
char* SqStack<T>::change(char *ptr)//中缀式变后缀式
{
	char *result = new char;
	int i = 0;
	SqStack<char> OPTR;//操作符栈
	OPTR.Push('#');
	char e, op;
	while (*ptr!='#')
	{
		if (!In(*ptr))//判断是否为数字
			*(result + i++) = *ptr;
		else
		{
			if (*ptr == '(') OPTR.Push(*ptr);//如果是（，直接输入操作符栈
			else if(*ptr==')')//如果是），出栈，直到遇到（
				do
				{
					OPTR.Pop(e);
					if (e != '(')
						*(result + i++) = e;
				} while (e!='(');
			else
			{
				OPTR.GetTop(op);
				switch (Precede(op,*ptr))
				{
				case '<'://栈顶优先级低，*ptr进栈
					OPTR.Push(*ptr);
					break;
				case'=':
				case'>'://栈顶优先级高，出栈，再将*ptr入栈
					OPTR.Pop(e);
					*(result + i++) = e;
					OPTR.Push(*ptr);
				}
			}
		}
		ptr++;
	}
	while (OPTR.IsEmpty()!= EMPTY)//如果遍历字符串后，操作符栈不为空，将其出栈
	{
		OPTR.Pop(e);
		if (e != '#') *(result + i++) = e;
	}
	*(result + i) = '\0';
	return result;
}
template<class T>
int SqStack<T>::EvalExpr_RPN(char *exp)
{
	SqStack<int> s;
	int a, b, e;
	while (*exp != '\0')
	{
		if (!In(*exp)) s.Push(*exp-48);
		else
		{
			s.Pop(b);
			s.Pop(a);
			s.Push(Operate(a, *exp, b));
		}
		exp++;
	}
	s.Pop(e);
	return e;
}
template<class T>
int SqStack<T>::Operate(int a, char theta, int b)//对数值进行运算操作
{
	if (b != 0)
	{
		if (theta == '+') return a + b;
		else if (theta == '-') return a - b;
		else if (theta == '*') return a * b;
		else return  a / b;
	}
	else
		return ERROR;
}
template <class T>
int SqStack<T>::In(char c)//判断是否是运算符
{
	if (c >= '0'&&c <= '9')
		return 0;
	else
		return 1;
}
template <class T>
char SqStack<T>::Precede(char op, char c)//比较运算符优先级
{
	char Table[8][8] = { 
		' ','+','-','*' ,'/' ,'(',')','#',      /*运算符优先级表格*/
		'+','>','>','<','<','<','>','>',
		'-','>','>','<','<','<','>','>',
		'*','>','>','>','>','<','>','>',
		'/','>','>','>','>','<','>','>',
		'(','<','<','<','<','<','=',' ',
		')','>','>','>','>',' ','>','>',
		'#','<','<','<','<','<',' ','=',
	};
	int i, j;
	for (i = 0; i<8; i++)                   /*纵坐标寻找*/
		if (Table[0][i] == c)
			break;
	for (j = 0; j<8; j++)                   /*横坐标寻找*/
		if (Table[j][0] == op)
			break;
	return Table[j][i];                  /*返回比较结果*/
}
#endif // !SqStack_h
