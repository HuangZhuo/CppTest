#include <iostream>
#include <string> // std::getline
/*
 * 每一项测试都有main函数出现在对应测试文件中。
 * 通过一个【是否注释】的TEST_×××宏作为【开关】决定哪一个main函数运行。
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
	//std::getline(std::cin, name); //换行符留在了标准输出中
	//std::cout << "Hello," << name << "\n";
	//return;
}
#endif