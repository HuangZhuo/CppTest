#include <iostream>
#include <string>

//��Ҫ��Ӱ���Ŀ¼��$(SolutionDir)\Libs;
#include "sqlite3/sqlite3.h"

//����ǰĿ¼���ǽ������Ŀ¼�������ͨ���������������������ļ�����ȡ��
static const std::string resource_path("./Resources/");

void _showTable(char** table, int r, int c);

//#define TEST_SQLITE3

#ifdef TEST_SQLITE3
int main()
{
	using namespace std;

	// 1>����sqlite���ݿ�
	sqlite3* pdb = nullptr;	//���ݿ�ָ��
	string path = resource_path + "save.db"; //ָ�����ݿ��·��

	string sql;
	int ret;
	// 2>��һ�����ݿ⣬��������ݿⲻ���ڣ��򴴽�һ�����ݿ��ļ�
	ret = sqlite3_open(path.c_str(), &pdb);
	if (SQLITE_OK != ret)
	{
		cout << "Opening database failed! ret=" << ret << "\n";
	}
#ifdef DB_NOT_EXIST
	// 3>�������SQL���
	sql = "create table student(ID integer primary key autoincrement,name text,sex text)";
	//ִ��
	ret = sqlite3_exec(pdb, sql.c_str(), nullptr, nullptr, nullptr);
	if (SQLITE_OK != ret)
	{
		cout << "Create table failed! ret=" << ret << "\n";
	}

	// 4>��������
	sql = "insert into student  values(1,'student1','male')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (ret != SQLITE_OK)
		cout << "insert data failed! ret=" << ret  << "\n";

	sql = "insert into student  values(2,'student2','female')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	sql = "insert into student  values(3,'student3','male')";
	ret = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
#endif
	// 5>��ѯ
	char** result_set;
	int r, c;
	sql = "select * from student";
	ret = sqlite3_get_table(pdb, sql.c_str(), &result_set, &r, &c, nullptr);

	// 6>��ʾ��ѯ���,table��һ����ָ�����顿
	cout << "row:" << r << "  " << "col:" << c << "\n";
	cout << "table student:" << "\n";
	_showTable(result_set, r, c);

	sqlite3_free_table(result_set);

	// end>�ر����ݿ��ֹ�ڴ��©
	sqlite3_close(pdb);

	return 0;
}
#endif

/*
 * ���ܣ������ӡ����׼���
 * ��������table���� r�������� c��������
 * ����ֵ��void
 */
void _showTable(char** table, int r, int c) //��������ʱ����
{
	using namespace std;
	for (size_t i = 0; i <= r; i++) //������ÿһ�С����ӱ�ͷһ������
	{
		for (size_t j = 0; j < c; j++) //����ÿ�и���Ԫ��
		{
			cout << table[i*c + j] << "\t";
		}
		cout << "\n";
	}
}

/*
 * �ο���http://cn.cocos2d-x.org/article/index?type=cocos2d-x&url=/doc/cocos-docs-master/manual/framework/native/v3/sqlite/zh.md
 * �ؼ��ǻ��á�SQL������ṹ����ѯ����
 * 
 * sqlite3_open, sqlite3_exec, sqlite3_get_table, sqlite3_free_table, sqlite3_close
 * �߼���������Ժ���˵��
 * �ص����������������ݿ�toolkit
 */