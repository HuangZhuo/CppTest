#include "../TestInterface.h"
#include <queue>

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

class AStar :public TestInterface
{
public:
	struct KNight
	{
		int x, y, step; //ע1
		int g, h, f; //f=g+h

		bool operator<(const KNight& comp)const{ return f>comp.f; } //ע2
	};
public:
	void Invoke() override;

private:
	void AStarProcess();
	int Heuristic(const KNight& a);
	bool InArea(const KNight& a);

	bool mVisited[8][8]; //�ر��б�
	int x1, y1, x2, y2, mAns; // ��㣬�յ㣬���
	std::priority_queue<KNight> mPQ; //�����б�
	KNight mK;
};

// �ο�
// http://www.cnblogs.com/chxer/p/4542068.html
// ע1-3
// Ҫע��ṹ���Ա��û�г�ʼ���ģ�
// http://www.programlife.net/const-member-function-overload.html
// http://www.cnblogs.com/gb2013/archive/2013/03/05/SecurityEnhancementsInTheCRT.html