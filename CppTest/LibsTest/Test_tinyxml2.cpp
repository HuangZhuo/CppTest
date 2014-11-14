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

	// plist�Ǹ��ڵ�
	XMLElement* plistElement = pDoc->NewElement("plist");
	plistElement->SetAttribute("version", "1.0");
	pDoc->LinkEndChild(plistElement);
	// ���xmlע��
	XMLComment* pComment = pDoc->NewComment("This is an xml comment");
	plistElement->LinkEndChild(pComment);
	// LinkEndChild-���һ���ӡ�Ԫ�ؽڵ㡿/���ı��ڵ㡿
	XMLElement* pResolution = pDoc->NewElement("resolution");
	plistElement->LinkEndChild(pResolution);
	// Width��һ����Ԫ�ؽڵ㡿��480��һ�����ı��ڵ㡿
	XMLElement* pWidth = pDoc->NewElement("Width");
	// 480��Width�ġ��ӽڵ㡿
	pWidth->LinkEndChild(pDoc->NewText("480"));
	pResolution->LinkEndChild(pWidth);

	XMLElement* pHeight = pDoc->NewElement("Height");
	pHeight->LinkEndChild(pDoc->NewText("320"));
	pResolution->LinkEndChild(pHeight);
	// �����ļ�
	pDoc->SaveFile(file_path.c_str());
	// ��ӡ����׼���
	pDoc->Print();
	// ɾ�� xml�ĵ�����
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
		//XML��ʽ����
		cout << "Load file error" << errId << "\n";
	}
	// ��ȡroot
	XMLElement* pRoot = pDc->RootElement();
	// ��ȡroot�ڵ�ġ����ԡ�������ֵ�ǡ���ָ�롿��ָ������ָ�룩
	const XMLAttribute* pAttr = pRoot->FirstAttribute();
	if (nullptr != pAttr)
	{
		cout << pAttr->Name() << "=" << pAttr->FloatValue() << "\n";
	}
	//��ȡ��͸߲���ӡ
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
** �ο���http://cn.cocos2d-x.org/article/index?type=cocos2d-x&url=/doc/cocos-docs-master/manual/framework/native/v3/xml-parse/zh.md
**
** �ܽ᣺����Ҫ����һ�š�DOM�ڵ�����
*/

/*
 * xml : http://www.w3school.com.cn/x.asp
 * tinyxml2 on github : https://github.com/leethomason/tinyxml2
 * documents : http://grinninglizard.com/tinyxml2docs/index.html
 */