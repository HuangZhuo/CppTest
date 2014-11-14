#include <iostream>
#include <string>
using namespace std;

#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;

static const std::string resource_path("./Resources/");

void makeXml(const std::string& fileName);
void parseXml(const std::string& fileName);

//#define TEST_XML

#ifdef TEST_XML
void main()
{
#ifdef INI_XML_NOT_EXIST
	makeXml("ini.xml");
#endif
	parseXml("ini.xml");
}
#endif

void makeXml(const std::string& fileName)
{
	std::string file_path = resource_path + fileName;

	XMLDocument* pDoc = new XMLDocument();

	XMLDeclaration* pDec = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	pDoc->LinkEndChild(pDec);

	// plist是根节点
	XMLElement* plistElement = pDoc->NewElement("plist");
	plistElement->SetAttribute("version", "1.0");
	pDoc->LinkEndChild(plistElement);
	// 添加xml注释
	XMLComment* pComment = pDoc->NewComment("This is an xml comment");
	plistElement->LinkEndChild(pComment);
	// LinkEndChild-添加一个子【元素节点】/【文本节点】
	XMLElement* pResolution = pDoc->NewElement("resolution");
	plistElement->LinkEndChild(pResolution);
	// Width是一个【元素节点】，480是一个【文本节点】
	XMLElement* pWidth = pDoc->NewElement("Width");
	// 480是Width的【子节点】
	pWidth->LinkEndChild(pDoc->NewText("480"));
	pResolution->LinkEndChild(pWidth);

	XMLElement* pHeight = pDoc->NewElement("Height");
	pHeight->LinkEndChild(pDoc->NewText("320"));
	pResolution->LinkEndChild(pHeight);
	// 保存文件
	pDoc->SaveFile(file_path.c_str());
	// 打印到标准输出
	pDoc->Print();
	// 删除 xml文档对象
	delete pDoc;
}

void parseXml(const std::string& fileName)
{
	string filePath = resource_path + fileName;
	XMLDocument* pDc = new XMLDocument();

	XMLError errId = XMLError::XML_SUCCESS;
	errId = pDc->LoadFile(filePath.c_str());
	if (XML_SUCCESS != errId)
	{
		//XML格式错误
		cout << "Load file error" << errId << "\n";
	}
	// 获取root
	XMLElement* pRoot = pDc->RootElement();
	// 获取root节点的【属性】，返回值是【常指针】（指向常量的指针）
	const XMLAttribute* pAttr = pRoot->FirstAttribute();
	if (nullptr != pAttr)
	{
		cout << pAttr->Name() << "=" << pAttr->FloatValue() << "\n";
	}
	//获取宽和高并打印
	XMLElement* pResolution = pRoot->FirstChildElement("resolution");
	XMLElement* pWidth = pResolution->FirstChildElement("Width");
	//XMLElement* pHeight = pResolution->FirstChildElement("Height");
	XMLElement* pHeight = pWidth->NextSiblingElement();
	int width = atoi(pWidth->GetText());
	int height = atoi(pHeight->GetText());
	cout << "(" << width << "," << height << ")" << "\n";

	delete pDc;
}
/*
** 参考：http://cn.cocos2d-x.org/article/index?type=cocos2d-x&url=/doc/cocos-docs-master/manual/framework/native/v3/xml-parse/zh.md
**
** 总结：心中要想象一颗【DOM节点树】
*/

/*
 * xml : http://www.w3school.com.cn/x.asp
 * tinyxml2 on github : https://github.com/leethomason/tinyxml2
 * documents : http://grinninglizard.com/tinyxml2docs/index.html
 */