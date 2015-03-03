#include "../TestInterface.h"

// 如果不是public继承，将不允许基类指针指向子类对象。
class PrimeNumberTest :public TestInterface
{
public:
	void Invoke() override;

	bool IsPrime(int n);
	void Test1();
};

// 质数：指整数在一个大于1的自然数中,除了1和此整数自身外,没法被其他自然数整除的数。
// http://www.zhihu.com/question/26477210/answer/32936952