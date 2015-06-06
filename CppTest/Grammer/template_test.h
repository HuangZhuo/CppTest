// 
// STL���������container��algorithm��iterator��adapter��allocater��functor
// C++���������IOStream��string
// ��������ƾ��ǳ������ƣ��������ƾ���������ơ�

#include "../TestInterface.h"
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

// ����ģ��
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
	ST count = contnr.size(); //��дģ��ʱ�����벻��������ض����ͣ���ģ���������Ҫ�Խ�ʹ�õ�������һЩ���衣
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

// ��ģ��
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

// ������ģ���β�
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
	cout << MAX<int>(1, 2.1) << endl; //ָ������ģ��ʵ���������ܹ�����(ǿ��)ת��
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

// ��дģ�����ʱ����ʵ�����͵�Ҫ�󾡿������Ǻ�����ġ�