/*
����std::bind���ԣ���������һ��Function Template 
�ο���
	http://www.cplusplus.com/reference/functional/bind/
	http://www.cplusplus.com/reference/functional/function/function/

simple(1)
template <class Fn, class... Args>
/- unspecified -/ bind(Fn&& fn, Args&&... args);

with return type(2)
template <class Ret, class Fn, class... Args>
/- unspecified -/ bind(Fn&& fn, Args&&... args);

*/

#include <iostream>    //std::out
#include <functional>  //std::bind

// ���Ժ���: (ͬʱ�����ں�������: std::divides<double> my_divide;)
double my_divide(double x, double y) { return x / y; }
// �����ࣺ��Ա�����Լ�����
struct MyPair {
	double a, b;
	double multiply() { return a*b; }

	//����һ���������ڲ��Իص�
	void multiply_cb(const char* data) { std::cout << data << "\n"; }
};

//#define TEST_BIND

#ifdef TEST_BIND
int main() {
	using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

	// ������:
	auto fn_five = std::bind(my_divide, 10, 2);               // returns 10/2
	std::cout << fn_five() << '\n';                           // 5

	auto fn_half = std::bind(my_divide, _1, 2);               // returns x/2
	std::cout << fn_half(10) << '\n';                         // 5

	auto fn_invert = std::bind(my_divide, _2, _1);            // returns y/x
	std::cout << fn_invert(10, 2) << '\n';                    // 0.2

	auto fn_rounding = std::bind<int>(my_divide, _1, _2);     // returns int(x/y)
	std::cout << fn_rounding(10, 3) << '\n';                  // 3

	MyPair ten_two{ 10, 2 };

	// �෽���Լ�public���԰�:
	auto bound_member_fn = std::bind(&MyPair::multiply, _1);  // returns x.multiply()
	std::cout << bound_member_fn(ten_two) << '\n';            // 20
	std::cout << bound_member_fn(&ten_two) << '\n';           // also works with pObj

	auto bound_member_data = std::bind(&MyPair::a, ten_two);  // returns ten_two.a
	std::cout << bound_member_data() << '\n';                 // 10

	// �ö���ָ���أ� OK��
	MyPair* pp = new MyPair; //new���������Խ���б��ʼ������
	pp->a = 4; pp->b = 2;
	auto bound_member_fn_2 = std::bind(&MyPair::multiply, pp);  // returns pp->multiply()
	std::cout<< bound_member_fn_2() << '\n';					// 8

	//��ô�������ˣ���Ϊ������������дԭ�͵�ʱ�����������ʲô��
	//��Ȼ���뵽�ˣ�ʹ�ð�װ��std::function<>����ʱ��bind��������һ�����ɵ������͡���
	std::function<void(const char*)> bound_member_fn_3 = std::bind(&MyPair::multiply_cb, pp, _1);
	//It works fine!
	bound_member_fn_3("callback");

	//����Ҫ�󶨡���ʽ��������ͨ����thisָ�룬Ҳ����__target__����������������ʱ��
	//std::function���Ѿ���ǿ���ˡ�

	//std::function<double(const MyPair&)> func_obj = &MyPair::multiply;

	//����һ�仰������û���⣬������VS2013�³��������±������
	//error C2664 : ��void std::_Func_class<_Ret, const MyPair &>::_Set(std::_Func_base<_Ret, const MyPair &> *)�� : �޷������� 1 �ӡ�_Myimpl *��ת��Ϊ��std::_Func_base<_Ret, const MyPair &> *��

	//���ǿ���ʹ��mem_fn������Convert member function to function object��
	auto func_obj = std::mem_fn(&MyPair::multiply);
	std::cout << func_obj(ten_two) << "\n";
	std::cout << func_obj(&ten_two) << "\n";
	//��ʱ���Ҿ���������ǿ���ͷ�ˣ����func_obj�����ǡ�ָ�롿���ǡ�ʵ�塿��OK��

	return 0;
}
#endif

/*
0> �÷���
	a> ��Ҫ��ǰ�󶨲�����std::bind(),��������ʽ�������İ󶨡�
	b> ����Ҫ�󶨲�����ֱ����std::function��Ĺ�����������std::mem_fn(&Class::Method)����һ�����������󡿡�
1> �����ַ�ʽ�������ص�˧���ˣ�!!
2> һ��ϸ�ڶ�ͨ��ģ�弼����װ���ˣ�һ�н������ϣ���ķ�ʽ���֡�
3> �����Ǻ������Ƿ������������Ƶģ�����������Ⱥ������һ������ʽ�������ڵ�һ��λ�á���������������ǡ�ʵ�塿���ǡ�ָ�롿��OK��
4> std::function���Ѿ���ǿ���ˣ�����std::bind()�ú����ص���ǿ��,������ǰ��һЩ������������һ����Function Object��
   ��֮C++��<functional>�ǳ�֮�����ܷǳ�ǿ��
*/