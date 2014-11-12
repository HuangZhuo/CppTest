/*
运行std::bind测试，本质它是一个Function Template 
参考：http://www.cplusplus.com/reference/functional/bind/

simple(1)
template <class Fn, class... Args>
/- unspecified -/ bind(Fn&& fn, Args&&... args);

with return type(2)
template <class Ret, class Fn, class... Args>
/- unspecified -/ bind(Fn&& fn, Args&&... args);

*/

#include <iostream>    //std::out
#include <functional>  //std::bind

// 测试函数: (同时适用于函数对象: std::divides<double> my_divide;)
double my_divide(double x, double y) { return x / y; }
// 测试类：成员方法以及属性
struct MyPair {
	double a, b;
	double multiply() { return a*b; }

	//下面一个方法用于测试回调
	void multiply_cb(const char* data) { std::cout << data << "\n"; }
};

//#define TEST_BIND

#ifdef TEST_BIND
int main() {
	using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

	// 函数绑定:
	auto fn_five = std::bind(my_divide, 10, 2);               // returns 10/2
	std::cout << fn_five() << '\n';                           // 5

	auto fn_half = std::bind(my_divide, _1, 2);               // returns x/2
	std::cout << fn_half(10) << '\n';                         // 5

	auto fn_invert = std::bind(my_divide, _2, _1);            // returns y/x
	std::cout << fn_invert(10, 2) << '\n';                    // 0.2

	auto fn_rounding = std::bind<int>(my_divide, _1, _2);     // returns int(x/y)
	std::cout << fn_rounding(10, 3) << '\n';                  // 3

	MyPair ten_two{ 10, 2 };

	// 类方法以及public属性绑定:
	auto bound_member_fn = std::bind(&MyPair::multiply, _1);  // returns x.multiply()
	std::cout << bound_member_fn(ten_two) << '\n';            // 20

	auto bound_member_data = std::bind(&MyPair::a, ten_two);  // returns ten_two.a
	std::cout << bound_member_data() << '\n';                 // 10

	// 用对象指针呢？ OK！
	MyPair* pp = new MyPair; //new操作符可以结合列表初始化用吗？
	pp->a = 4; pp->b = 2;
	auto bound_member_fn_2 = std::bind(&MyPair::multiply, pp);  // returns pp->multiply()
	std::cout<< bound_member_fn_2() << '\n';					// 8

	//那么问题来了：作为函数参数，编写原型的时候参数类型是什么？
	//自然联想到了：使用包装器std::function<>。暂时称bind函数返回一个【可调用类型】。
	std::function<void(const char*)> bound_member_fn_3 = std::bind(&MyPair::multiply_cb, pp, _1);
	//It works fine!
	bound_member_fn_3("callback");

	return 0;
}
#endif

/*
1> 用这种方式做方法回调帅呆了！!!
2> 一切细节都通过模板技术封装好了，一切结果都以希望的方式出现。
3> 无论是函数还是方法，都是类似的，无外乎方法比函数多出一个【隐式参数】在第一个位置。最妙的是它无论是【实体】还是【指针】都OK！
*/