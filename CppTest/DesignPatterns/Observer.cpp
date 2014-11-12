#include "Observer.h"

//#define TEST_OBSERVER

#ifdef TEST_OBSERVER

void main()
{
	ClockTimer* timer = new ClockTimer();

	DigitalClock* dc = new DigitalClock(timer);
	//�����Զ��������ġ��۲��ߡ�������ģ��ʱ��AnalogClock���Ӿͽӿ�����˵�����ǵ�������һ�µġ�

	//Tick���ڲ���ʱ���Թ̶�ʱ����ã������Ǹ��¡�Ŀ�꡿״̬������֪ͨ������ģ�����һ��
	timer->Tick();

	//��Ҫ�������С��۲��ߡ�����ǰ���Բ�����ǰ������Ŀ�꡿
	delete dc;
	delete timer;
}

#endif

/*
�ܽ᣺
0> �ο��������ģʽ��5.7�½� Observer�۲���ģʽ
1> �����еĹ۲����У�������ÿ�η���������Ҫ���ȼ�顾Ŀ�꡿�Ƿ񻹴��ڡ�
2> �ڡ�Ŀ�꡿֪֮ͨǰ��Ҳ��ü�顣����ʵ���۲��ߡ�������ʱ���Ѿ�detach�ˣ�
3> ��Ŀ�꡿����������ṩһ��ӿڸ����۲��ߡ��������ʡ�Ŀ�꡿�ڲ�״̬��
	���ԡ��۲��ߡ�����ֻ�ܡ�����һ��Ŀ��ABC�������ָ�롱���۲���ABC�����������ָ�롣
*/