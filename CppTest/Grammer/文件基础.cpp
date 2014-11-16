//#define TEST_FILE_1115

#include <iostream>
#include <string>
#include <fstream> //ifstream
#include <sstream> //stringbuf
using namespace std;

//常量默认是【static】，不加也没事。常量一般放在头文件中。
const std::string resource_path("./Resources/");

void test_read_file(); //getStringFromFile
void test_read_file_line_by_line();

#ifdef TEST_FILE_1115
void main()
{
	test_read_file();
	test_read_file_line_by_line();

}
#endif // Test

void test_read_file()
{
	string filePath = resource_path + "shape_of_my_heart.txt";
	ifstream ifs(filePath.c_str());
	// 一次性读取所有内容
	stringbuf sb;
	ifs >> &sb;

	cout << sb.str();
}

void test_read_file_line_by_line()
{
	string filePath = resource_path + "shape_of_my_heart.txt";
	ifstream ifs(filePath.c_str());
	// 一行一行读
	string line;
	while (getline(ifs, line))
	{
		cout << line << "\n";
	}

}

