#pragma once
// main函数过多不方便管理。
// 往后的测试不再采用“TEST_”宏，测试项直接继承这个接口。
class TestInterface{
public:
	virtual void Invoke() = 0;	
};