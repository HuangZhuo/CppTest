//#define TEST_AGIT

#include <iostream> 
#include <iterator> // ostream_iterator
#include <algorithm> //generate, shuffle, copy
#include <vector> //
#include <random> //default_random_engine
#include <ctime> //time

struct c_unique
{
	int _curret;
	c_unique() :_curret(0){}
	int operator()(){ return ++_curret; }
}UniqueNumberGenerator;

#ifdef TEST_AGIT
void main()
{
	using namespace std;
	vector<int> vec(20);

	// 生成不重复数字
	generate(vec.begin(), vec.end(), UniqueNumberGenerator);

	// shuffle
	unsigned seed = unsigned(time(0));
	shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));

	// 逆序
	//reverse(vec.begin(), vec.end());

	// 输出vec
	std::ostream_iterator<int, char> op_iter(std::cout, " ");
	copy(vec.begin(), vec.end(), op_iter);
}
#endif