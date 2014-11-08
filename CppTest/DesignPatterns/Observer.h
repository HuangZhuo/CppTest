#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <list>
#include <ctime> //得到本地时间
#include <iostream> //输出信息到cout

class Observer;

//目标抽象基类
class Subject
{
public:
	virtual ~Subject();
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
protected:
	Subject();
private:
	std::list<Observer*> _observers;
};

//观察者抽象基类
class Observer
{
public:
	virtual ~Observer();
	virtual void Update(Subject* theChangeSubject) = 0;
protected:
	Observer();
};

inline Subject::Subject(){}
inline Subject::~Subject(){}

inline void Subject::Attach(Observer* o)
{
	_observers.push_back(o);
}
inline void Subject::Detach(Observer* o)
{
	_observers.remove(o);
}
inline void Subject::Notify()
{
	for each (auto o in _observers)
	{
		//this是【目标】，对于【观察者】o来说，参数用来区分不同的目标。
		o->Update(this);
	}
}

inline Observer::Observer(){}
inline Observer::~Observer(){}

//***************************************
//下面是观察者模式的应用
//***************************************
class ClockTimer : public Subject
{
public:
	ClockTimer();
	~ClockTimer();


	//【观察者】获取【目标】状态的接口。这里以小时为例。
	virtual int GetHour();

	//Tick操作由内部定时器以固定时间间隔调用。
	void Tick();
private:
	//保存内部状态，即时间。
	time_t _time;
};

inline ClockTimer::ClockTimer(){}
inline ClockTimer::~ClockTimer(){}

inline void ClockTimer::Tick()
{
	//更新内部状态，即时间。要注意先更新状态，然后发布消息。
	time(&_time);
	//消息广播
	Notify();
}

inline int ClockTimer::GetHour()
{
	//tm* pt = localtime(&_time);
	tm ptmr;
	//使用localtime函数会造成编译错误，原因是localtime已经废弃了。我也觉得localtime凭空返回一个指针不合逻辑。
	localtime_s(&ptmr, &_time);
	return ptmr.tm_hour;
}

class Widget
{
public:
	virtual void Draw() = 0;
};

class DigitalClock : public Widget, public Observer
{
public:
	//构造【观察者】数码时钟的时候顺便传入【目标】，并且attach
	DigitalClock(ClockTimer* s);
	//析构的时候detach
	~DigitalClock();
	//重写【观察者】中update函数
	virtual void Update(Subject* theChangeSubject) override;

	//实现Widget的接口
	virtual void Draw() override;
private:
	ClockTimer* _subject;
};

inline DigitalClock::DigitalClock(ClockTimer* s)
{
	_subject = s;
	_subject->Attach(this);
}

inline DigitalClock::~DigitalClock()
{
	_subject->Detach(this);
}

inline void DigitalClock::Draw()
{
	//这里模拟绘制：将时间显示在控制台
	int hour = _subject->GetHour();
	std::cout << "Hour:" << hour << std::endl;
}

inline void DigitalClock::Update(Subject* theChangeSubject)
{
	if (theChangeSubject == _subject)
	{
		Draw();
	}
}


#endif