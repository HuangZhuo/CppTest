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
	for (int i = 2; i <= n / 2; i++) //����ط������ǡ�С�ڵ��ڡ��������ǡ�С�ڡ���
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

// ���IsPrime����������Ϊstatic�ģ���û��Ҫ����thisָ��İ󶨣�д�������������ɣ�
// std::copy_if(v->begin(), v->end(), ostream_iterator<int>(cout, " "), PrimeNumberTest::IsPrime);