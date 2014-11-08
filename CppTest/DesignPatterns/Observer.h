#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <list>
#include <ctime> //�õ�����ʱ��
#include <iostream> //�����Ϣ��cout

class Observer;

//Ŀ��������
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

//�۲��߳������
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
		//this�ǡ�Ŀ�꡿�����ڡ��۲��ߡ�o��˵�������������ֲ�ͬ��Ŀ�ꡣ
		o->Update(this);
	}
}

inline Observer::Observer(){}
inline Observer::~Observer(){}

//***************************************
//�����ǹ۲���ģʽ��Ӧ��
//***************************************
class ClockTimer : public Subject
{
public:
	ClockTimer();
	~ClockTimer();


	//���۲��ߡ���ȡ��Ŀ�꡿״̬�Ľӿڡ�������СʱΪ����
	virtual int GetHour();

	//Tick�������ڲ���ʱ���Թ̶�ʱ�������á�
	void Tick();
private:
	//�����ڲ�״̬����ʱ�䡣
	time_t _time;
};

inline ClockTimer::ClockTimer(){}
inline ClockTimer::~ClockTimer(){}

inline void ClockTimer::Tick()
{
	//�����ڲ�״̬����ʱ�䡣Ҫע���ȸ���״̬��Ȼ�󷢲���Ϣ��
	time(&_time);
	//��Ϣ�㲥
	Notify();
}

inline int ClockTimer::GetHour()
{
	//tm* pt = localtime(&_time);
	tm ptmr;
	//ʹ��localtime��������ɱ������ԭ����localtime�Ѿ������ˡ���Ҳ����localtimeƾ�շ���һ��ָ�벻���߼���
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
	//���졾�۲��ߡ�����ʱ�ӵ�ʱ��˳�㴫�롾Ŀ�꡿������attach
	DigitalClock(ClockTimer* s);
	//������ʱ��detach
	~DigitalClock();
	//��д���۲��ߡ���update����
	virtual void Update(Subject* theChangeSubject) override;

	//ʵ��Widget�Ľӿ�
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
	//����ģ����ƣ���ʱ����ʾ�ڿ���̨
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