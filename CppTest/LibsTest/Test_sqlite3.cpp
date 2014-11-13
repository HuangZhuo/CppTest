#include <iostream>
#include <string>

//��Ҫ��Ӱ���Ŀ¼��$(SolutionDir)\Libs;
#include "sqlite3/sqlite3.h"

//����ǰĿ¼���ǽ������Ŀ¼
static const std::string resource_path("./Resources/");

#define TEST_SQLITE3

#ifdef TEST_SQLITE3
int main()
{
	using namespace std;

	//����sqlite���ݿ�
	sqlite3* pdb = nullptr;	//���ݿ�ָ��
	string path = resource_path + "save.db"; //ָ�����ݿ��·��

	string sql;
	int ret;
	//��һ�����ݿ⣬��������ݿⲻ���ڣ��򴴽�һ�����ݿ��ļ�
	ret = sqlite3_open(path.c_str(), &pdb);
	if (SQLITE_OK != ret)
	{
		cout << "Opening database failed! ret=" << ret << "\n";
	}
#ifdef DB_NOT_EXIST
	//�������SQL���
	sql = "create table student(ID integer primary key autoincrement,name text,sex text)";
	//ִ��
	ret = sqlite3_exec(pdb, sql.c_str(), nullptr, nullptr, nullptr);
	if (SQLITE_OK != ret)
	{
		cout << "Create table failed! ret=" << ret << "\n";
	}

	//��������
	sql = "insert into student  values(1,'student1','male')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (ret != SQLITE_OK)
		cout << "insert data failed! ret=" << ret  << "\n";

	sql = "insert into student  values(2,'student2','female')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	sql = "insert into student  values(3,'student3','male')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
#endif
	//��ѯ
	char** result_set;
	int r, c;
	sql = "select * from student";
	ret = sqlite3_get_table(pdb, sql.c_str(), &result_set, &r, &c, nullptr);
	cout << "row:" << r << "  " << "col:" << c << "\n";
	cout << "table student:" << "\n";
	//��ʾ��ѯ���
	//for (int i = 1; i <= r; i++)//2
	//{
	//	for (int j = 0; j<c; j++)
	//	{
	//		log("%s", re[i*c + j]);
	//	}
	//}

	sqlite3_free_table(result_set);

	//ɾ������
	sqlite3_close(pdb);

	return 0;
}
#endif