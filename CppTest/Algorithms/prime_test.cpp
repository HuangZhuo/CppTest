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

void AStar::AStarProcess()
{
	const int dirs[8][2] = { { -2, -1 }, { -2, 1 }, { 2, -1 }, { 2, 1 }, { -1, -2 }, { -1, 2 }, { 1, -2 }, { 1, 2 } };//8个移动方向
	KNight t, s;
	while (!mPQ.empty())
	{
		t = mPQ.top(); mPQ.pop(); mVisited[t.x][t.y] = true;
		if (t.x == x2&&t.y == y2)
		{
			mAns = t.step; break;
		}
		for (int i = 0; i < 8; i++)
		{
			s.x = t.x + dirs[i][0]; s.y = t.y + dirs[i][1];
			if (InArea(s) && !mVisited[s.x][s.y])
			{
				s.g = t.g + 23; //23=√5*10
				s.h = Heuristic(s);
				s.f = s.g + s.h;
				s.step = t.step + 1;
				mPQ.push(s);
			}
		}
	}
}

int AStar::Heuristic(const KNight& k)
{
	return (abs(k.x - x2) + abs(k.y - y2)) * 10;
}

bool AStar::InArea(const KNight& a)
{
	return !(a.x < 0 || a.x >= 8 || a.y < 0 || a.y >= 8);
}

void AStar::Invoke()
{
	char input[6];
	while (gets_s(input)) //注3
	{
		if (input[0] == 'q'){ break; }

		x1 = input[0] - 'a'; x2 = input[1] - '1';
		y1 = input[3] - 'a'; y2 = input[4] - '1';
		memset(mVisited, false, sizeof(mVisited));
		mK.x = x1; mK.y = y1; mK.step = mK.g = 0; mK.h = Heuristic(mK); mK.f = mK.g + mK.h;
		while (!mPQ.empty()) //每轮测试清空数据
		{
			mPQ.pop();
		}
		mPQ.push(mK);
		AStarProcess();
		std::cout << mAns << std::endl;
	}
}

