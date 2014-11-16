#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring> //strlen, strcpy
#include <vector>
#include <iterator> //ostream_iterator
#include <string> //find

std::vector<std::string> _split(const char* str, const char* ct);

//#define TEST_STR
#ifdef TEST_STR
void main()
{
	using namespace std;
	string str = "ID, ,name,,sex";

	vector<string> vec = _split(str.c_str(), ",");
	// 输出
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<string, char>(cout, " "));
	
	// string::find，参数可以是字符串或单个字符
	size_t i = str.find(",");
	if (string::npos != i)
	{
		cout << "find ',' @ pos:" << i << "\n";
	}
}

#endif

/*
 * function : 分割字符串
 * param : str - 待分割的字符串
 *       : ct - 分隔符
 * return: 分割后的字符串数组
 */
std::vector<std::string> _split(const char* str, const char* ct)
{
	std::vector<std::string> _tmpVec;
	char* _tmpStr = new char[std::strlen(str) + 1];
	std::strcpy(_tmpStr, str); //_CRT_SECURE_NO_WARNINGS

	char* p = std::strtok(_tmpStr, ct);
	while (nullptr != p)
	{
		_tmpVec.push_back(std::string(p));
		p = strtok(nullptr, ct);
	}
	delete[] _tmpStr;
	return _tmpVec;
}
