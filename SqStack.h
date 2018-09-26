#pragma once
#ifndef SqStack_h
#include <iostream>
#define SqStack_h
#define Status int
#define StackSize 10
#define StackIncrease 5
#define ERROR 0
#define OK 1
template <class T>
class SqStack
{
private:
	T * base, *top;
	int stacksize;
public:
	SqStack();
	~SqStack();
	Status GetTop(char &e);
	Status Push(T e);
	Status Pop(T &e);
	Status conversion(int num,int a);//数制转换,num为需要转换的数字，n为进制
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
Status SqStack<T>::GetTop(char &e)//用e返回栈顶元素
{
	if (top == base) return ERROR;
	e = *(--top);
	return OK;
}
template <class T>
Status SqStack<T>::Push(T e)//将e放入栈
{
	if ((top - base) >= stacksize)//空间不够，增加容量
	{
		base = new T[StackSize + StackIncrease];
		T *p;
		if (!base) exit(OVERFLOW);
		p = top;
		top = base;
		for (int i = 0; i < stacksize; i++)//复制原来栈的数据
			top[i] = p[i];
		top++;
	}
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
Status SqStack<T>::conversion(int num, int n)//数制转换
{
	int e;
	while (num)//入栈
	{
		Push(num%n);
		num /= n;
	}
	while (top != base)
	{
		Pop(e);//出栈
		cout << e;
	}
	cout << endl;
	return OK;
}

#endif // !SqStack_h
