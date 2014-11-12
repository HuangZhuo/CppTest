/*
0> 参考：《设计模式》 3.5章节 单件模式
1> 【单件】还是比较简单的，变体也还算简单。
*/

#include <iostream>
#include "Singleton.h"

//#define TEST_SINGLETON

#ifdef TEST_SINGLETON
int main()
{
	//只有第一次调用构造函数。
	Singleton* s1 = Singleton::getInstance();
	Singleton* s2 = Singleton::getInstance();
	if (nullptr != s1 && s1 == s2)
	{
		std::cout << "There is only one object @" << s1 << "\n";
	}

	return 0;
}

#endif