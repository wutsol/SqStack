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
	Status conversion(int num,int a);//����ת��,numΪ��Ҫת�������֣�nΪ����
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
Status SqStack<T>::GetTop(char &e)//��e����ջ��Ԫ��
{
	if (top == base) return ERROR;
	e = *(--top);
	return OK;
}
template <class T>
Status SqStack<T>::Push(T e)//��e����ջ
{
	if ((top - base) >= stacksize)//�ռ䲻������������
	{
		base = new T[StackSize + StackIncrease];
		T *p;
		if (!base) exit(OVERFLOW);
		p = top;
		top = base;
		for (int i = 0; i < stacksize; i++)//����ԭ��ջ������
			top[i] = p[i];
		top++;
	}
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
Status SqStack<T>::conversion(int num, int n)//����ת��
{
	int e;
	while (num)//��ջ
	{
		Push(num%n);
		num /= n;
	}
	while (top != base)
	{
		Pop(e);//��ջ
		cout << e;
	}
	cout << endl;
	return OK;
}

#endif // !SqStack_h
