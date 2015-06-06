// 
// STL六大组件：container，algorithm，iterator，adapter，allocater，functor
// C++其他组件：IOStream，string
// “语言设计就是程序库设计，程序库设计就是语言设计”

#include "../TestInterface.h"
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

// 函数模版
template<typename T>
inline const T& MAX(const T& a, const T& b)
{
	return a > b ? a : b;
}

template<typename _Iter, typename _T>
inline _Iter Find(_Iter begin, _Iter end, const _T& v)
{
	while (begin++ != end)
	{
		if (*begin == v){ return begin; }
	}
	return nullptr;
}

template<typename _T>
void Print(const _T& contnr)
{
	typedef _T::size_type ST;
	ST count = contnr.size(); //编写模板时，代码不可能针对特定类型，但模板代码总是要对将使用的类型做一些假设。
	for (ST i = 0; i < count; i++)
	{
		std::cout << contnr[i] << " ";
	}
}

template<typename _T>
int Compare(_T a, _T b)
{
	if (a < b) { return -1; }
	if (b < a){ return 1; }
	return 0;
}

// 类模版
template<typename T>
class MyQueue
{
public:

	T& Front();
	const T& Front() const;
	void Push(const T& a);
	void Pop();
	bool Empty() const;

private:
	std::list<T> mList;
};

class TemplateTest :public TestInterface
{
public:
	void Invoke() override;
	int AAA = 100;
protected:
	
private:
};

// 非类型模版形参
template<typename _T, size_t N>
void ArrayInitWithZero(_T(&Arr)[N])
{
	for (size_t i = 0; i < N; i++)
	{
		Arr[i] = 0;
	}
}


inline void TemplateTest::Invoke()
{
	cout << MAX<int>(1, 2.1) << endl; //指定函数模版实例，参数能够进行(强制)转换
	cout << MAX(1, 2) << endl;
	//cout << AAA;

	enum 
	{
		N = 5,
	};
	int A[N]{1, 3, 2};
	int* p = std::find(A, A + 3, 2);
	int* q = Find(A, A + 3, 2);

	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	Print(v);

	ArrayInitWithZero(A);

}

// 编写模板代码时，对实参类型的要求尽可能少是很有益的。