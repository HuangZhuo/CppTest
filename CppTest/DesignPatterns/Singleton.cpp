/*
0> �ο��������ģʽ�� 3.5�½� ����ģʽ
1> �����������ǱȽϼ򵥵ģ�����Ҳ����򵥡�
*/

#include <iostream>
#include "Singleton.h"

//#define TEST_SINGLETON

#ifdef TEST_SINGLETON
int main()
{
	//ֻ�е�һ�ε��ù��캯����
	Singleton* s1 = Singleton::getInstance();
	Singleton* s2 = Singleton::getInstance();
	if (nullptr != s1 && s1 == s2)
	{
		std::cout << "There is only one object @" << s1 << "\n";
	}

	return 0;
}

#endif