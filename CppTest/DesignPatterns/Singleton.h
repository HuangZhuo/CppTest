class Singleton
{
public:
	static Singleton* getInstance();
	virtual ~Singleton(){}
protected:
	//protected�����ⲿֱ�ӹ������
	Singleton(){}
private:
	static Singleton* _instance;
};

// ���еľ�̬��������������������壨�����ڴ�ռ䣩��
Singleton* Singleton::_instance = nullptr;

// �ض��ġ�������
class MySingleton :public Singleton
{
public:
	MySingleton(){}
};

#ifdef EASY_SINGLETON
// ��򵥵ĵ���������������
inline Singleton* Singleton::getInstance()
{
	if (nullptr == _instance)
	{
		//���Գ�ʼ��
		_instance = new Singleton;
	}
	return _instance;
}
#else
// ����ͨ��������������ڱ�������н׶���ҪһЩ��Ϣ��
// ��Ҫ�����ض��ġ���������ͨ�������������ࡿ
inline Singleton* Singleton::getInstance()
{
	if (nullptr == _instance)
	{
		//const char* singleton_style = getenv("SIN_STYLE");
		//if (������) ͨ��һЩ��Ϣ�����ض�����
		//{
			_instance = new MySingleton;
		//}
	}
	return _instance;
}
#endif
