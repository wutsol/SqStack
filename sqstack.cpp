#include "SqStack.h"
#include <iostream>
using namespace std;

int main()
{
	SqStack<int> intSqStack;
	//cout<<intSqStack.conversion(159, 8)<<endl;
	cout << "������ǰ׺���ʽ������#������" << endl;
	char ptr[10],*exp;
	int i = 0,j=0;
	do { cin >> ptr[i]; } while (ptr[i++] != '#');
	cout << "��׺���ʽΪ��";
	exp = intSqStack.change(ptr);
	while (*(exp+j) != '\0')
	{
		cout << *(exp + j);
		j++;
	}
	cout << "���ʽ���Ϊ��";
	cout << intSqStack.EvalExpr_RPN(exp);
	//cout << intSqStack.EvalExpr(ptr);
	system("pause");
	return 0;
}