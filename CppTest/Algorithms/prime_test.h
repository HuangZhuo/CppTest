#include "../TestInterface.h"
#include <queue>

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

class AStar :public TestInterface
{
public:
	struct KNight
	{
		int x, y, step; //注1
		int g, h, f; //f=g+h

		bool operator<(const KNight& comp)const{ return f>comp.f; } //注2
	};
public:
	void Invoke() override;

private:
	void AStarProcess();
	int Heuristic(const KNight& a);
	bool InArea(const KNight& a);

	bool mVisited[8][8]; //关闭列表
	int x1, y1, x2, y2, mAns; // 起点，终点，结果
	std::priority_queue<KNight> mPQ; //开启列表
	KNight mK;
};

// 参考
// http://www.cnblogs.com/chxer/p/4542068.html
// 注1-3
// 要注意结构体成员是没有初始化的！
// http://www.programlife.net/const-member-function-overload.html
// http://www.cnblogs.com/gb2013/archive/2013/03/05/SecurityEnhancementsInTheCRT.html