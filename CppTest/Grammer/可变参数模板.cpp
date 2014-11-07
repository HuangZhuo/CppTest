#include <iostream>
#include <ostream>
#include <string>
using namespace std;

//重载，显示最后一个元素时会换行，而不是输出逗号。
//并且让递归得以终止。
template <typename T>
void zprinto(std::ostream& os, const T& t)
{
	os << t << endl;
}

//递归调用自身，不断取出第一个参数并输出至流。
template <typename T, typename... Args>//模板参数包
void zprinto(std::ostream& os, const T& t, const Args&... args)//函数参数包
{
	os << t << ',';
	zprinto(os, args...);//函数参数包展开
}

//int main()
//{
//	zprinto(cout, 1, 2, 3.14, "hello");
//	return 0;
//}