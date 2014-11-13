#include <iostream>
#include <string>

//需要添加包含目录：$(SolutionDir)\Libs;
#include "sqlite3/sqlite3.h"

//【当前目录】是解决方案目录
static const std::string resource_path("./Resources/");

#define TEST_SQLITE3

#ifdef TEST_SQLITE3
int main()
{
	using namespace std;

	//创建sqlite数据库
	sqlite3* pdb = nullptr;	//数据库指针
	string path = resource_path + "save.db"; //指定数据库的路径

	string sql;
	int ret;
	//打开一个数据库，如果该数据库不存在，则创建一个数据库文件
	ret = sqlite3_open(path.c_str(), &pdb);
	if (SQLITE_OK != ret)
	{
		cout << "Opening database failed! ret=" << ret << "\n";
	}
#ifdef DB_NOT_EXIST
	//创建表的SQL语句
	sql = "create table student(ID integer primary key autoincrement,name text,sex text)";
	//执行
	ret = sqlite3_exec(pdb, sql.c_str(), nullptr, nullptr, nullptr);
	if (SQLITE_OK != ret)
	{
		cout << "Create table failed! ret=" << ret << "\n";
	}

	//插入数据
	sql = "insert into student  values(1,'student1','male')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (ret != SQLITE_OK)
		cout << "insert data failed! ret=" << ret  << "\n";

	sql = "insert into student  values(2,'student2','female')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	sql = "insert into student  values(3,'student3','male')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
#endif
	//查询
	char** result_set;
	int r, c;
	sql = "select * from student";
	ret = sqlite3_get_table(pdb, sql.c_str(), &result_set, &r, &c, nullptr);
	cout << "row:" << r << "  " << "col:" << c << "\n";
	cout << "table student:" << "\n";
	//显示查询结果
	//for (int i = 1; i <= r; i++)//2
	//{
	//	for (int j = 0; j<c; j++)
	//	{
	//		log("%s", re[i*c + j]);
	//	}
	//}

	sqlite3_free_table(result_set);

	//删除对象
	sqlite3_close(pdb);

	return 0;
}
#endif