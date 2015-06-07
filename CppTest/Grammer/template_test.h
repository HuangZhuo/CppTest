#ifndef TEMPLATE_TEST_H
#define TEMPLATE_TEST_H
// 
// STL���������container��algorithm��iterator��adapter��allocater��functor
// C++���������IOStream��string
// ��������ƾ��ǳ������ƣ��������ƾ���������ơ�


#include "../TestInterface.h"
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
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

// ������ģ���β�
template<typename _T, size_t N>
void ArrayInitWithZero(_T(&Arr)[N]) //ע�⣺ʹ�����÷�ʽ�����������ͣ���ͬ��������ʵ�δ���ͬ���ͣ�
{
	for (size_t i = 0; i < N; i++)
	{
		Arr[i] = 0;
	}
}

// ��ģ��
template<typename _T>
class MyQueueNode
{
	MyQueueNode(const _T& t) :data(t), next(nullptr){}
	_T data;
	MyQueueNode* next;

	template<typename T> friend class MyQueue; //��ģ����Ԫ
	// or friend class MyQueue<_T>; //���ڽ�������Ȩ���ض���ͬ���ͣ�ʵ��

	friend std::ostream& operator<< <_T>(ostream& os, const MyQueue<_T>& n); //����ģ����Ԫ
};


template<typename T>
class MyQueue
{
public:
	MyQueue() :mHead(nullptr), mTail(nullptr){} //ͨ������ʹ����ģ������ֵ�ʱ�򣬱���ָ��ģ���βΡ���һ�����и����⣺���౾����������ڲ�������ʹ����ģ��ķ��޶�����
	MyQueue(const MyQueue& q) :mHead(nullptr), mTail(nullptr){ _Copy(); } //��������Ҳ�ǹ��죬ԭ���󲻴��ڡ�
	MyQueue& operator=(const MyQueue&);
	~MyQueue(){ _Destroy(); }

	T& Front();
	const T& Front() const;
	void Push(const T& a);
	void Pop();
	bool Empty() const;

private:
	// STL�в��á�adapter��ģʽ������ֱ��������д��
	MyQueueNode<T>* mHead; //Queue ���е� QueueItem ��Ա��ָ�롣��ģ���ָ�붨�岻��������ʵ������ֻ���õ�������ָ��ʱ�Ż�������ʵ������
	MyQueueNode<T>* mTail;

	void _Destroy();
	void _Copy(const MyQueue& q);

	friend std::ostream& operator<< <T>(ostream& os, const MyQueue<T>& n);
};

template<typename _T>
std::ostream& operator<<(ostream& os, const MyQueue<_T>& n)
{
	os << "<";
	MyQueueNode<_T>* p = n.mHead; //��Ԫ����Queue
	while (p != nullptr)
	{
		os << p->data << " "; //��Ԫ����QueueNode
		p = p->next;
	}
	os << ">";
	return os;
}

// ��ģ���Ա�����Ķ���
#pragma region MyQueue��Ա��������
template<typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& q) //������ֵ��Ҫģ�������
{
	_Destroy();
	_Copy(q);
	return *this;
}

template<typename T>
void MyQueue<T>::_Destroy() //��ģ���Ա������ģ���β��ɵ��øú����Ķ��������ȷ����
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
bool MyQueue<T>::Empty() const //const��û�й������أ������Ͷ���ʱ����Ҫ��
{
	return mHead == nullptr;
}

template<typename T>
void MyQueue<T>::Push(const T& a)
{
	MyQueueNode<T>* p = new MyQueueNode<T>(a); //������ʵ��������� QueueItem<string> ���乹�캯����
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
	cout << MAX<int>(1, 2.1) << endl; //ָ������ģ��ʵ���������ܹ�����(ǿ��)ת��
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

	int(*pf)(const int&, const int&) = Compare; //����ʹ�ú���ģ��Ժ���ָ����г�ʼ����ֵ��������ʹ��ָ�������ʵ���������ʵ�ģ��ʵ�ε�ģ��汾��


	// ��ʱʵ������ͳ�Ա
	MyQueue<int> que; //��ʱʵ���� Queue �༰��Ĭ�Ϲ��캯��
	que.Push(1); //��ʱʵ���� push ��Ա����
	que.Push(2);

	cout << que; //Ϊû�ж���������������ഴ�� Queue �����ǺϷ��ģ�����������������͵� Queue ����ᷢ������ʱ��������ʱ������
}

// ��дģ�����ʱ����ʵ�����͵�Ҫ�󾡿������Ǻ�����ġ�

#endif
