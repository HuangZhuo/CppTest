#ifndef TEMPLATE_TEST_H
#define TEMPLATE_TEST_H
// 
// STL六大组件：container，algorithm，iterator，adapter，allocater，functor
// C++其他组件：IOStream，string
// “语言设计就是程序库设计，程序库设计就是语言设计”


#include "../TestInterface.h"
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
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

// 非类型模版形参
template<typename _T, size_t N>
void ArrayInitWithZero(_T(&Arr)[N]) //注意：使用引用方式传递数组类型，不同长度数组实参代表不同类型！
{
	for (size_t i = 0; i < N; i++)
	{
		Arr[i] = 0;
	}
}

// 类模版
template<typename _T>
class MyQueueNode
{
	MyQueueNode(const _T& t) :data(t), next(nullptr){}
	_T data;
	MyQueueNode* next;

	template<typename T> friend class MyQueue; //类模版友元
	// or friend class MyQueue<_T>; //用于将访问授权给特定（同类型）实例

	friend std::ostream& operator<< <_T>(ostream& os, const MyQueue<_T>& n); //函数模版友元
};


template<typename T>
class MyQueue
{
public:
	MyQueue() :mHead(nullptr), mTail(nullptr){} //通常，当使用类模板的名字的时候，必须指定模板形参。这一规则有个例外：在类本身的作用域内部，可以使用类模板的非限定名。
	MyQueue(const MyQueue& q) :mHead(nullptr), mTail(nullptr){ _Copy(); } //拷贝构造也是构造，原对象不存在。
	MyQueue& operator=(const MyQueue&);
	~MyQueue(){ _Destroy(); }

	T& Front();
	const T& Front() const;
	void Push(const T& a);
	void Pop();
	bool Empty() const;

private:
	// STL中采用“adapter”模式，这里直接用链表写。
	MyQueueNode<T>* mHead; //Queue 类中的 QueueItem 成员是指针。类模板的指针定义不会对类进行实例化，只有用到这样的指针时才会对类进行实例化。
	MyQueueNode<T>* mTail;

	void _Destroy();
	void _Copy(const MyQueue& q);

	friend std::ostream& operator<< <T>(ostream& os, const MyQueue<T>& n);
};

template<typename _T>
std::ostream& operator<<(ostream& os, const MyQueue<_T>& n)
{
	os << "<";
	MyQueueNode<_T>* p = n.mHead; //友元访问Queue
	while (p != nullptr)
	{
		os << p->data << " "; //友元访问QueueNode
		p = p->next;
	}
	os << ">";
	return os;
}

// 类模版成员函数的定义
#pragma region MyQueue成员函数定义
template<typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& q) //！返回值需要模版参数表
{
	_Destroy();
	_Copy(q);
	return *this;
}

template<typename T>
void MyQueue<T>::_Destroy() //类模板成员函数的模板形参由调用该函数的对象的类型确定。
{
	while (!Empty())
	{
		Pop();
	}
}

template<typename T>
void MyQueue<T>::_Copy(const MyQueue& q)
{
	typedef MyQueueNode<_T>* Iter;
	for (Iter i = q.mHead; i != nullptr; i = i->next)
	{
		Push(i->data);
	}
}

template<typename T>
void MyQueue<T>::Pop()
{
	assert(!Empty());
	MyQueueNode<T>* p = mHead;
	mHead = mHead->next;
	delete p;
}

template<typename T>
T& MyQueue<T>::Front()
{
	assert(!Empty());
	return mHead->data;
}

template<typename T>
bool MyQueue<T>::Empty() const //const有没有构成重载，声明和定义时都需要！
{
	return mHead == nullptr;
}

template<typename T>
void MyQueue<T>::Push(const T& a)
{
	MyQueueNode<T>* p = new MyQueueNode<T>(a); //将依次实例化伙伴类 QueueItem<string> 及其构造函数。
	if (Empty())
	{
		mHead = mTail = p;
	}
	else
	{
		mTail->next = p;
		mTail = p;
	}
}


class TemplateTest :public TestInterface
{
public:
	void Invoke() override;
	int AAA = 100;
protected:

private:
};
#pragma endregion

inline void TemplateTest::Invoke()
{
	cout << MAX<int>(1, 2.1) << endl; //指定函数模版实例，参数能够进行(强制)转换
	cout << MAX(1, 2) << endl;

	int A[5]{1, 3, 2};
	int* p = std::find(A, A + 3, 2);
	int* q = Find(A, A + 3, 2);

	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	Print(v);

	ArrayInitWithZero(A);

	int(*pf)(const int&, const int&) = Compare; //可以使用函数模板对函数指针进行初始化或赋值，编译器使用指针的类型实例化具有适当模板实参的模板版本。


	// 何时实例化类和成员
	MyQueue<int> que; //此时实例化 Queue 类及其默认构造函数
	que.Push(1); //此时实例化 push 成员函数
	que.Push(2);

	cout << que; //为没有定义输出操作符的类创建 Queue 对象是合法的，但输出保存这种类型的 Queue 对象会发生编译时（或链接时）错误。
}

// 编写模板代码时，对实参类型的要求尽可能少是很有益的。

#endif
