#include <iostream>

//�������� C.A.R.Hoare 1962
void qsort(int v[], int length);

//��������������
//#define TEST_SORT

#ifdef TEST_SORT
void main()
{
	int A[] = { 7, 5, 3, 8, 2, 6, 4, };
	int len = sizeof(A) / sizeof(A[0]);
	qsort(A, len);
	//std::cout << A; //���Ѿ�������ַ....
	for each (int i in A)
	{
		std::cout << i << " ";
	}
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
	int t;	t = v[i]; v[i] = v[j]; v[j] = t;
}

void qsort(int v[], int length)
{
	void __qsort(int v[], int left, int right);
	__qsort(v, 0, length - 1);
}
