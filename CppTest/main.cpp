#include <iostream>

/*
ÿһ����Զ���main���������ڶ�Ӧ�����ļ��С�
ͨ��һ�����Ƿ�ע�͡���TEST_����������Ϊ�����ء�������һ��main�������С�
*/

//#define TEST_

#ifdef TEST_
void main()
{
	std::cout << "Hello World!" << "\n";
	return;
}
#endif