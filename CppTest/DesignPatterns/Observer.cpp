#include "Observer.h"

//#define TEST_OBSERVER

#ifdef TEST_OBSERVER

void main()
{
	ClockTimer* timer = new ClockTimer();

	DigitalClock* dc = new DigitalClock(timer);
	//还可以定义其他的【观察者】，比如模拟时钟AnalogClock，从就接口上来说，它们的类型是一致的。

	//Tick由内部计时器以固定时间调用，作用是更新【目标】状态并发布通知。这里模拟调用一次
	timer->Tick();

	//重要：在所有【观察者】析构前绝对不能提前析构【目标】
	delete dc;
	delete timer;
}

#endif

/*
总结：
0> 参考：《设计模式》5.7章节 Observer观察者模式
1> 在所有的观察者中，按道理每次方法调用需要事先检查【目标】是否还存在。
2> 在【目标】通知之前，也最好检查。（其实【观察者】析构的时候已经detach了）
3> 【目标】的子类必须提供一组接口给【观察者】用来访问【目标】内部状态。
	所以【观察者】子类只能“保存一个目标ABC的子类的指针”，观察者ABC并不保存这个指针。
*/