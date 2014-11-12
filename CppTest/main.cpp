#include <iostream>

/*
每一项测试都有main函数出现在对应测试文件中。
通过一个【是否注释】的TEST_×××宏作为【开关】决定哪一个main函数运行。
*/

//#define TEST_

#ifdef TEST_
void main()
{
	std::cout << "Hello World!" << "\n";
	return;
}
#endif