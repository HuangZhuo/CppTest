#include <iostream>
#include <iterator> //std::ostream_iterator
#include <algorithm> //std::swap,generate
#include <vector> //std::begin,end
#include <cassert>
#include <ctime> //std::time

//�������� C.A.R.Hoare 1962
void qsort(int v[], int length);

//��������������
//#define TEST_SORT

#ifdef TEST_SORT
void main()
{
	std::srand(unsigned(time(0)));

	int A[10];
	int len = sizeof(A) / sizeof(A[0]);
	std::generate(A, A + len, [](){ return std::rand() % 100; });
	qsort(A, len);
	//std::cout << A; //���Ѿ�������ַ....

	std::ostream_iterator<int, char> op_iter(std::cout, " ");
	std::copy(std::begin(A), std::end(A), op_iter);
}
#endif

void __qsort(int v[], int left, int right)
{
	int i, last;
	void __swap(int v[], int i, int j);
	if (left >= right) return; //�ݹ����
	__swap(v, left, (left + right) / 2); //���м�Ԫ����Ϊ����Ŧ���������һ��Ԫ�ؽ���λ�á�
	last = left; //��last������,��ʼָ���һ��Ԫ��
	for (i = left + 1; i <= right; i++) //��������
	{
		if (v[i] < v[left]) //��ǰ��i������ָ��Ԫ�غ͡���Ŧ�����бȽϡ�
			__swap(v, ++last, i); //С�ڡ���Ŧ����ÿ��ִ�У�����֤��last������ָ��ǰ�ҵ����СԪ�ؼ��ϵ����һ��ֵ��
	}
	__swap(v, left, last); //������Ŧ���ӵ�һ��Ԫ��ת�Ƶ��м�
	__qsort(v, left, last - 1);
	__qsort(v, last + 1, right);
}

void __swap(int v[], int i, int j)
{
	//int t;	t = v[i]; v[i] = v[j]; v[j] = t;
	std::swap(v[i], v[j]);
}

void qsort(int v[], int length)
{
	// ������Ч�Լ�⡣
	assert(nullptr != v);
	// ���ҿ������ְ�װ��ʽ���Ǻ����õģ����װ��������Ч�ԣ������ⲿ�ӿڲ��䡣ͬʱ�ڲ�_func()רע�㷨�����Ҳ�Ӱ��ӿڵ��������ʱ�Ż���
	// ����˵��д��__qsort����BUG���������������ﻻ��std::sort��
	void __qsort(int v[], int left, int right);
	__qsort(v, 0, length - 1);
}
