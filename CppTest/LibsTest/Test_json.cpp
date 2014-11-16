//#define TEST_JSON
#include <iostream>
#include <string>
using namespace std;

//在VS中，库头文件可以不添加到工程项目。"RapidJSON is a header-only C++ library."
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
using namespace rapidjson;

void parseJSON();
void parseArray();


#ifdef TEST_JSON
void main()
{
	//parseJSON();
	parseArray();
}
#endif

void parseJSON()
{
	string jsonStr = "{\"ki\":\"val\"}";
	cout << jsonStr << "\n";
	rapidjson::Document doc;
	doc.Parse<0>(jsonStr.c_str());
	if (doc.HasParseError())
	{
		cout << "parse error" << "\n";
	}
	if (doc.IsObject() && doc.HasMember("ki"))
	{
		cout << doc["ki"].GetString();
	}
}

void parseArray()
{
	string jsonStr = "[{\"ki\":\"val\"}, {\"y\":\"ue\"}]";
	cout << jsonStr << "\n";
	rapidjson::Document doc;
	doc.Parse<0>(jsonStr.c_str());
	if (doc.HasParseError())
	{
		cout << "parse error" << "\n";
		return;
	}
	if (doc.IsArray() && doc[0].IsObject() && doc[0].HasMember("ki"))
	{
		rapidjson::SizeType i = 0;
		cout << doc[i]["ki"].GetString() << endl;
	}
}

/*
 * json语法：http://www.w3school.com.cn/json/json_syntax.asp
 * rapidjson on github : https://github.com/miloyip/rapidjson
 * documents : http://miloyip.github.io/rapidjson/
 */