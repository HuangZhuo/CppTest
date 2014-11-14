#include <iostream>
#include <string>

//需要添加包含目录：$(SolutionDir)\Libs;
#include "sqlite3/sqlite3.h"

//【当前目录】是解决方案目录。最好是通过【环境变量】或【配置文件】读取。
static const std::string resource_path("./Resources/");

void _showTable(char** table, int r, int c);

//#define TEST_SQLITE3

#ifdef TEST_SQLITE3
int main()
{
	using namespace std;

	// 1>创建sqlite数据库
	sqlite3* pdb = nullptr;	//数据库指针
	string path = resource_path + "save.db"; //指定数据库的路径

	string sql;
	int ret;
	// 2>打开一个数据库，如果该数据库不存在，则创建一个数据库文件
	ret = sqlite3_open(path.c_str(), &pdb);
	if (SQLITE_OK != ret)
	{
		cout << "Opening database failed! ret=" << ret << "\n";
	}
#ifdef DB_NOT_EXIST
	// 3>创建表的SQL语句
	sql = "create table student(ID integer primary key autoincrement,name text,sex text)";
	//执行
	ret = sqlite3_exec(pdb, sql.c_str(), nullptr, nullptr, nullptr);
	if (SQLITE_OK != ret)
	{
		cout << "Create table failed! ret=" << ret << "\n";
	}

	// 4>插入数据
	sql = "insert into student  values(1,'student1','male')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (ret != SQLITE_OK)
		cout << "insert data failed! ret=" << ret  << "\n";

	sql = "insert into student  values(2,'student2','female')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	sql = "insert into student  values(3,'student3','male')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
#endif
	// 5>查询
	char** result_set;
	int r, c;
	sql = "select * from student";
	ret = sqlite3_get_table(pdb, sql.c_str(), &result_set, &r, &c, nullptr);

	// 6>显示查询结果,table是一个【指针数组】
	cout << "row:" << r << "  " << "col:" << c << "\n";
	cout << "table student:" << "\n";
	_showTable(result_set, r, c);

	sqlite3_free_table(result_set);

	// end>关闭数据库防止内存侧漏
	sqlite3_close(pdb);

	return 0;
}
#endif

/*
 * 功能：将表打印到标准输出
 * 参数：（table：表， r：行数， c：列数）
 * 返回值：void
 */
void _showTable(char** table, int r, int c) //错误检查暂时不做
{
	using namespace std;
	for (size_t i = 0; i <= r; i++) //遍历“每一行”，加表头一共四行
	{
		for (size_t j = 0; j < c; j++) //遍历每行各个元素
		{
			cout << table[i*c + j] << "\t";
		}
		cout << "\n";
	}
}

/*
 * 参考：http://cn.cocos2d-x.org/article/index?type=cocos2d-x&url=/doc/cocos-docs-master/manual/framework/native/v3/sqlite/zh.md
 * 关键是会用【SQL】这个结构化查询语言
 * 
 * sqlite3_open, sqlite3_exec, sqlite3_get_table, sqlite3_free_table, sqlite3_close
 * 高级点的内容以后再说。
 * 重点是用面向对象的数据库toolkit
 */