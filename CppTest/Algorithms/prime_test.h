#include "../TestInterface.h"

// �������public�̳У������������ָ��ָ���������
class PrimeNumberTest :public TestInterface
{
public:
	void Invoke() override;

	bool IsPrime(int n);
	void Test1();
};

// ������ָ������һ������1����Ȼ����,����1�ʹ�����������,û����������Ȼ������������
// http://www.zhihu.com/question/26477210/answer/32936952