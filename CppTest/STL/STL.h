#pragma once

#include "../TestInterface.h"
#include <set>
using namespace std;

class STLTest :public TestInterface
{
public: 
	void Invoke() override;


};

struct MyLess
{
	bool operator()(const int& l, const int& r)
	{
		return l < r;
	}
};

inline void STLTest::Invoke()
{
	set<int, MyLess>* s = new set<int, MyLess>(MyLess());
}