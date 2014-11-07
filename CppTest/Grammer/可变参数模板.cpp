#include <iostream>
#include <ostream>
#include <string>
using namespace std;

//���أ���ʾ���һ��Ԫ��ʱ�ỻ�У�������������š�
//�����õݹ������ֹ��
template <typename T>
void zprinto(std::ostream& os, const T& t)
{
	os << t << endl;
}

//�ݹ������������ȡ����һ�����������������
template <typename T, typename... Args>//ģ�������
void zprinto(std::ostream& os, const T& t, const Args&... args)//����������
{
	os << t << ',';
	zprinto(os, args...);//����������չ��
}

//int main()
//{
//	zprinto(cout, 1, 2, 3.14, "hello");
//	return 0;
//}