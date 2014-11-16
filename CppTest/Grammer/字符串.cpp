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
	// ���
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<string, char>(cout, " "));
	
	// string::find�������������ַ����򵥸��ַ�
	size_t i = str.find(",");
	if (string::npos != i)
	{
		cout << "find ',' @ pos:" << i << "\n";
	}
}

#endif

/*
 * function : �ָ��ַ���
 * param : str - ���ָ���ַ���
 *       : ct - �ָ���
 * return: �ָ����ַ�������
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
