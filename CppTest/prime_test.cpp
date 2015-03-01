#include "prime_test.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

void PrimeNumberTest::Invoke()
{
	Test1();
}

bool PrimeNumberTest::IsPrime(int n)
{
	if (n < 2) return false;

	bool bRet = true;
	for (int i = 2; i <= n / 2; i++) //这个地方条件是【小于等于】，而不是【小于】。
	{
		if (n%i == 0)
		{
			bRet = false;
			break;
		}
	}
	return bRet;
}

void PrimeNumberTest::Test1()
{
	using namespace std;
	auto v = new std::vector<int>();
	for (size_t i = 0; i < 100; i++)
	{
		v->push_back(i);
	}
	std::copy_if(v->begin(), v->end(), ostream_iterator<int>(cout, " "), bind(&PrimeNumberTest::IsPrime, this, placeholders::_1));
	
}

// 如果IsPrime函数被声明为static的，就没必要进行this指针的绑定，写成下面这样即可：
// std::copy_if(v->begin(), v->end(), ostream_iterator<int>(cout, " "), PrimeNumberTest::IsPrime);