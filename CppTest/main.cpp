#include <iostream>
#include <string> // std::getline
/*
 * ÿһ����Զ���main���������ڶ�Ӧ�����ļ��С�
 * ͨ��һ�����Ƿ�ע�͡���TEST_����������Ϊ�����ء�������һ��main�������С�
 */
#include "algorithm_common.h"

#define TEST_
#ifdef TEST_
void main()
{
	TestInterface* p = new PrimeNumberTest();
	p->Invoke();
	getchar();
	//std::string name;
	//std::cout << "What's your name? ";
	//std::getline(std::cin, name); //���з������˱�׼�����
	//std::cout << "Hello," << name << "\n";
	//return;
}
#endif