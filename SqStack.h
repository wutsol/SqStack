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
	int StackLength();//ջ�ĳ���
	Status IsEmpty();//�ж�ջ�Ƿ�Ϊ��
	int conversion(int num,int a);//����ת��,numΪ��Ҫת�������֣�nΪ����
	int EvalExpr(char *ptr);//���ʽ��ֵ����׺��ʾ��
	int In(char c);//�ж��Ƿ��������
	char Precede(char op, char c);//�Ƚ���������ȼ�
	int Operate(int a, char theta, int b);//����ֵ�����������
	char *change(char*ptr);//��׺ʽ���׺ʽ
	int EvalExpr_RPN(char *exp);//���ʽ��ֵ����׺��ʾ��
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
Status SqStack<T>::GetTop(T &e)//��e����ջ��Ԫ��
{
	if (top == base) return ERROR;
	e = *(top-1);
	return OK;
}
template <class T>
Status SqStack<T>::Push(T e)//��e����ջ
{
	/*if ((top - base) >= stacksize)//�ռ䲻������������
	{
		base = new T[StackSize + StackIncrease];
		T *p;
		if (!base) exit(OVERFLOW);
		p = top;
		top = base;
		for (int i = 0; i < stacksize; i++)//����ԭ��ջ������
			top[i] = p[i];
		top++;
	}*/
	if (top - base >= stacksize) return FULL;
	*top++ = e;//�ȸ�ֵ���ٺ���
	return OK;
}
template <class T>
Status SqStack<T>::Pop(T &e)//ɾ��ջ��Ԫ�أ���e������ֵ
{
	if (top == base) return ERROR;
	e = *(--top);//��ǰ�ƣ���ȡֵ
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
int SqStack<T>::conversion(int num, int n)//����ת��
{
	int e,result=0;
	while (num)//��ջ
	{
		Push(num%n);
		num /= n;
	}
	while (IsEmpty()!=EMPTY)
	{
		Pop(e);//��ջ
		result=result*10+e;
	}
	return result;
}
template <class T>
int SqStack<T>::EvalExpr(char *ptr)//���ʽ��ֵ����׺��ʾ��
{
	SqStack<char> OPTR;//������ջ
	OPTR.Push('#');
	SqStack<int> OPND;//������ջ
	char op, c, theta, x;
	int a, b,m;
	c = *ptr++;
	OPTR.GetTop(op);
	while (c!='#'||op!='#')
	{
		if (!In(c))//��������֣����������ջ
		{
			m = c - 48;
			OPND.Push(m);
			c = *ptr++;
		}
		else//����Ƿ��ţ���������ջ�����űȽϴ�С
		{

			switch (Precede(op,c))
			{
			case'<'://ջ����������ȼ��ͣ���c��ջ
				OPTR.Push(c);
				c = *ptr++;
				break;
			case'='://������
				OPTR.Pop(x);
				c = *ptr++;
				break;
			case'>'://ջ����������ȼ��ߣ���������
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
char* SqStack<T>::change(char *ptr)//��׺ʽ���׺ʽ
{
	char *result = new char;
	int i = 0;
	SqStack<char> OPTR;//������ջ
	OPTR.Push('#');
	char e, op;
	while (*ptr!='#')
	{
		if (!In(*ptr))//�ж��Ƿ�Ϊ����
			*(result + i++) = *ptr;
		else
		{
			if (*ptr == '(') OPTR.Push(*ptr);//����ǣ���ֱ�����������ջ
			else if(*ptr==')')//����ǣ�����ջ��ֱ��������
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
				case '<'://ջ�����ȼ��ͣ�*ptr��ջ
					OPTR.Push(*ptr);
					break;
				case'=':
				case'>'://ջ�����ȼ��ߣ���ջ���ٽ�*ptr��ջ
					OPTR.Pop(e);
					*(result + i++) = e;
					OPTR.Push(*ptr);
				}
			}
		}
		ptr++;
	}
	while (OPTR.IsEmpty()!= EMPTY)//��������ַ����󣬲�����ջ��Ϊ�գ������ջ
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
int SqStack<T>::Operate(int a, char theta, int b)//����ֵ�����������
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
int SqStack<T>::In(char c)//�ж��Ƿ��������
{
	if (c >= '0'&&c <= '9')
		return 0;
	else
		return 1;
}
template <class T>
char SqStack<T>::Precede(char op, char c)//�Ƚ���������ȼ�
{
	char Table[8][8] = { 
		' ','+','-','*' ,'/' ,'(',')','#',      /*��������ȼ����*/
		'+','>','>','<','<','<','>','>',
		'-','>','>','<','<','<','>','>',
		'*','>','>','>','>','<','>','>',
		'/','>','>','>','>','<','>','>',
		'(','<','<','<','<','<','=',' ',
		')','>','>','>','>',' ','>','>',
		'#','<','<','<','<','<',' ','=',
	};
	int i, j;
	for (i = 0; i<8; i++)                   /*������Ѱ��*/
		if (Table[0][i] == c)
			break;
	for (j = 0; j<8; j++)                   /*������Ѱ��*/
		if (Table[j][0] == op)
			break;
	return Table[j][i];                  /*���رȽϽ��*/
}
#endif // !SqStack_h
