#include <iostream>

//快速排序 C.A.R.Hoare 1962
void qsort(int v[], int length);

//测试主函数开关
//#define TEST_SORT

#ifdef TEST_SORT
void main()
{
	int A[] = { 7, 5, 3, 8, 2, 6, 4, };
	int len = sizeof(A) / sizeof(A[0]);
	qsort(A, len);
	//std::cout << A; //这货丫的输出地址....
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
	if (left >= right) return; //递归出口
	__swap(v, left, (left + right) / 2); //将中间元素作为【枢纽】，并与第一个元素交换位置。
	last = left; //【last索引】,起始指向第一个元素
	for (i = left + 1; i <= right; i++) //遍历数组
	{
		if (v[i] < v[left]) //当前【i索引】指向元素和【枢纽】进行比较。
			__swap(v, ++last, i); //小于【枢纽】，每次执行，将保证【last索引】指向当前找到左侧小元素集合的最后一个值。
	}
	__swap(v, left, last); //将【枢纽】从第一个元素转移到中间
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
