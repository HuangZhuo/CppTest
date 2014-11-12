class Singleton
{
public:
	static Singleton* getInstance();
	virtual ~Singleton(){}
protected:
	//protected避免外部直接构造对象。
	Singleton(){}
private:
	static Singleton* _instance;
};

// 类中的静态变量必须在类外给出定义（分配内存空间）。
Singleton* Singleton::_instance = nullptr;

// 特定的【单件】
class MySingleton :public Singleton
{
public:
	MySingleton(){}
};

#ifdef EASY_SINGLETON
// 最简单的单件像下面这样。
inline Singleton* Singleton::getInstance()
{
	if (nullptr == _instance)
	{
		//惰性初始化
		_instance = new Singleton;
	}
	return _instance;
}
#else
// 更加通常的情况是我们在编译或运行阶段需要一些信息。
// 需要构造特定的【单件】，通过【单件的子类】
inline Singleton* Singleton::getInstance()
{
	if (nullptr == _instance)
	{
		//const char* singleton_style = getenv("SIN_STYLE");
		//if (×××) 通过一些信息构造特定单件
		//{
			_instance = new MySingleton;
		//}
	}
	return _instance;
}
#endif
