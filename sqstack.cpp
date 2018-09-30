#include "SqStack.h"
#include <iostream>
using namespace std;

int main()
{
	SqStack<int> intSqStack;
	//cout<<intSqStack.conversion(159, 8)<<endl;
	cout << "请输入前缀表达式：（以#结束）" << endl;
	char ptr[10],*exp;
	int i = 0,j=0;
	do { cin >> ptr[i]; } while (ptr[i++] != '#');
	cout << "后缀表达式为：";
	exp = intSqStack.change(ptr);
	while (*(exp+j) != '\0')
	{
		cout << *(exp + j);
		j++;
	}
	cout << "表达式结果为：";
	cout << intSqStack.EvalExpr_RPN(exp);
	//cout << intSqStack.EvalExpr(ptr);
	system("pause");
	return 0;
}