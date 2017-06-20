#include <iostream>
#include <stdio.h>
#include <unistd.h>


using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#ifdef __cplusplus
}
#endif


//示例:结构体定义方法
struct myStru
{
	char name[5];
	int  val;
};

struct myStru s1 = {"lucy", 20}, s2;//定义结构体变量



typedef struct
{
	char name;
	int  val;
}myStru1;

myStru1 s3, s4;//定义结构体变量

int union_my()
{
//示例:联合的定义
//任一时刻，只有一个变量，彼此覆盖。
	union myU
	{
		char v1;
		int  v2;
	};

	union myU mu;
	mu.v1 = 2;
	std::cout << mu.v2;
        
    return 0;
}

//示例:枚举的定义
enum myE
{
	ONE, //数值0
	TWO,
};

enum myE e = ONE;

int myFunc(int a, int b)
{
	return 0;
}
void basic()
{
	
	//示例:字符串数组的定义方法,两种方法的存储方式不同!
	//现代p301
	//元素访问: number[1]表示"two"
	char number[][10] = {"one", "two", "three"};
	const char *number1[] = {"one", "two", "three"};	//要有const，否则警告：不建议使用从字符串常量到‘char*’的转换


	//位操作
	//1ul在32位计算机中存储二进制为0000 0000 0000 0000 0000 0000 0000 0001 <<5 左移5个单位
	//U确保为无符号
	int i = 128, j = 2;
	i |= 1U << j;//将变量i的第j位置位,
	i &= ~(1UL << j);//将变量i的第j位清零


	//函数指针
	typedef int (*func) (int a, int b);
	func p = myFunc; 	//定义指针
	(*p)(2, 3);			//调用


	//强制转换
	//c++用操作符转换!!别再用括号(*)
	double d = 97.0;
	char ch = static_cast<char> (d);

	//static_cast
	void *pvoid = &d;
	double *dp = static_cast<double *> (pvoid);

	//const_cast
	const char *cp = NULL;
	char *pchar = const_cast<char *> (cp); //将const char * 转为char *,不然不能赋值
	
}


#include <memory>
void auto_ptr_test()
{
	class C
	{
		int i;
	};
	std::auto_ptr<C> p(new C);	//如此，便不用delete指针了
}

template<typename T>
void swap_temp(T& a, T& b)
{
	T tmp(a);
	a = b;
	b = tmp;
}


#include <stdexcept>
void exception_test()
{
	int i = 0;
	cin >> i;
	switch(i)
	{
		case 1:
			throw out_of_range("out_of_range");
			break;
		case 2:
			throw runtime_error("runtime error");
			break;
		case 3:
			throw invalid_argument("invalid_argument");
			break;
		default:
			break;
			
	}

	try
	{
		if(true)
			throw out_of_range("out_of_range");
	}
	catch(runtime_error err)
	{
		cout << err.what() << endl;
	}
}

//数组的引用
void ref_of_arr_func(int (&arr)[5])
{
	
}

void new_delete()
{
	//new, delete
	int *p = new int;
	int *p1 = new int();
	int *p2 = new int[10];
	int *p3 = new int(3); //指针指向数字3的地址
	string *p4 = new string[10];
	string *p5 = new string();//按照默认值初始化
	string *p6 = new string(10, 'h');
	int *p7 = new int[10]();  //()用于将数组初始化为0
	delete []p;				//new对应的释放

	cout << p << p1 << p2 << p3 << p4
		<< p5 << p6 << p7 << endl;
}

void new2DArr()
{
	int (*a1)[3] = new int[2][3]();

	cout << a1[1][1];
	
}

using namespace std;

void var_init_test()
{
	class C
	{
		public:
			C(const string &str)
			{
				s = str;
			}
		private:
			string s;
	};

	//C c1 = "c1";	//错误：请求从‘const char [3]’转换到非标量类型‘var_init()::C’
	C c2 = string("c2");
}

class var_init_in_class
{
	public:
		int a = 1;//加上这个变量后,sizeof(cla)就从1变成了4
		const static int d = 2;//这个可以在这里初始化
		// static int b = 3;
		// 错误：ISO C++ 不允许在类内初始化非常量静态成员‘cla::b’
};

void multi_base_class_test()
{
	class C1{};
	class C2{};
	class C3: public C1, public C2{};//多个基类，以逗号隔开
}



class A
{
	public:
	    A() { cout << "A's Constructor Called " << endl;  }
};
class B
{
    static A a;		//这里只是声明，所以不会调用A的构造函数，联想:static内置类型变量
	public:
	    B() { cout << "B's Constructor Called " << endl; }
};
//A a;	//这样这里单独定义A的对象才会调用构造函数。或者如下文				
A a;				
void copy_constructor_test()
{
    B b;
	//A a;	
}
/*
A's Constructor Called
B's Constructor Called
*/


void call_func_of_class_test()
{
	class A2 
	{
		public:
		  int m;
		  void print() {  cout << "A2\n";  } 
	};
	
	//A2::print();   //cpp_1.cpp:36:12: 错误：没有对象无法调用成员函数‘void A2::print()’

	A2 *pa = nullptr;			
	pa->print();	//OK, 只定义指针，依然可以访问成员函数。
}
/*
A2
*/


void switch_do_while()
{
	do
	{
		cout << "haha" << endl;
	}while(1);					//不要忽略;号!!!，不然while和后面的连在一起岂不是有歧义。


	int op = 1;
	switch(op)
	{
		case 1:
			printf("case 1");
			break;
		case 2:
			break;
		default:
			break;
	}
}


//模板分为类模板与函数模板，特化分为全特化与偏特化。全特化就是限定死模板实现的具体类型，偏特化就是如果这个模板有多个类型，那么只限定其中的一部分。

//模版全特化
#include <cstring>
template <typename T1, typename T2, typename T3 > 
T1 myComp(const T2 &v1, const T3 &v2)
{
	if(v1 < v2)return -1;
	if(v1 > v2)return 1;
	return 0;
}
void __test_template_fixed()
{
	cout << myComp<int, int, int>(1,2) ;	//指定模板的type
}


//模板函数 的特化 
template<typename T1, typename T2>  
void fun(T1 a , T2 b)  
{  
    cout<<"模板函数"<<endl;  
}  
  
//全特化,函数模版只存在全特化  
template<>  
void fun<int ,char >(int a, char b)  
{  
    cout<<"specialize :全特化"<<endl;  
}  

//函数不存在偏特化：下面的代码是错误的  ，
/*
至于为什么函数不能偏特化，似乎不是因为语言实现不了，
而是因为偏特化的功能可以通过函数的重载完成。
*/
//错误：函数模板部分特例化‘fun<char, T2>’是不允许的
/* 
template<typename T2> 
void fun<char,T2>(char a, T2 b) 
{ 
    cout<<"偏特化"<<endl; 
} 
*/  
void fun(int a, char b)  			//会优先匹配到，覆盖掉上面的模版特化
{  
    cout<<"reload:重载"<<endl;  
}  
void __test_reload_template()
{
	fun(1, 'c');
}


//类模版的特化
template<typename T1, typename T2>  
class Test  
{  
public:  
    Test(T1 i,T2 j):a(i),b(j){cout<<"模板类"<<endl;}  
private:  
    T1 a;  
    T2 b;  
};  
  
template<>  
class Test<int , char>  
{  
public:  
    Test(int i, char j):a(i),b(j){cout<<"全特化"<<endl;}  
private:  
    int a;  
    char b;  
};  
  
template <typename T2>  //注意T2还是要声明的
class Test<char, T2>  
{  
public:  
    Test(char i, T2 j):a(i),b(j){cout<<"偏特化"<<endl;}  
private:  
    char a;  
    T2 b;  
};  

void __test_template()
{
	//下面3句依次调用类模板、全特化与偏特化：
	Test<double , double> t1(0.1,0.2);  
	Test<int , char> t2(1,'A');  
	Test<char, bool> t3('A',true); 	
}


//泛型版本  
template <class T> int compare(const T &v1, const T &v2)  
{  
  if(v1 < v2) return -1;  
  if(v2 > v1) return 1;  
  return 0;  
}  
//特化版本 为实参类型 const char * 提供 
template <> int compare<const char *>(const char * const &v1, const char * const &v2)  
{  
  return strcmp(v1, v2);  
}  
//为实参类型 char * 提供特化版本  
//template <> int compare(char * const &v1, char * const &v2)  
template <> int compare<char *>(char * const &v1, char * const &v2)  
{  
  std::cout << "template <> int compare<char *>" << std::endl;  
  return strcmp(v1, v2);  
}  
//特化版本 (int *)  
template <> int compare<const int *>(const int * const &v1, const int * const &v2)//v1 和 v2 是指向const 整形变量的const引用;  
{  
  if(*v1 < *v2) return -1;//像指针一样操作，可以理解v1，v2就是指针，因为它是指针的引用；  
  if(*v2 > *v1) return 1;  
}  


//重载
void fff(int)
{}
void fff(char)
{}


//可变长参数函数
#include <stdarg.h>
int var_arg_func(int n, ...) 			// 定参 n 表示后面变参数量，定界用，输入时切勿搞错
{                  
	va_list ap;                         // 定义一个 va_list 指针来访问参数表
	va_start(ap, n);                       // 初始化 ap，让它指向第一个变参

	int maximum = -1 - 0x7FFFFFFF ;            // 这是一个最小的整数
	int temp = 0;
	for(int i = 0; i < n; i++) 
	{
		temp = va_arg(ap, int);             // 获取一个 int 型参数，并且 ap 指向下一个参数
		if(maximum < temp)
			maximum = temp;
	}
	
	va_end(ap);                            // 善后工作，关闭 ap
	return maximum;
}
void  var_arg_func_test() 
{
	cout << var_arg_func(3) << endl;
	cout << var_arg_func(3, 10, 20) << endl;
	cout << var_arg_func(3, 10, 20, 30) << endl;
	cout << var_arg_func(6, 20, 40, 10, 50, 30, 40) << endl;
}
/*
n要准确
1629278126
1627416953
30
50
*/



class class1
{
public:
	class1(){}							//缺省构造函数
	class1(const class1&){}				//拷贝构造函数
	~class1(){}							//析构函数
	class1&operator=(const class1&){}	//赋值运算符
	class1*operator&(){}				//取址运算符
	const class1*operator&()const{}		//取址运算符 const
};

//空类class2会产生class1一样的成员函数
class class2
{
};
void __test_default_func_in_null_class()
{
	class2 obj1;		//默认构造函数
	class2 obj2;
	obj1=obj2;			//赋值运算符
	&obj2;				//取址运算符
	class2 obj3(obj1);	//复制构造函数，方式1
	class2 obj4 = obj3;	//复制构造函数，方式2

	class2 const obj5;
	&obj5;				//取址运算符 const
}


//重载结构体的<号
typedef struct student
{
	int id;
	string name;
	bool operator<(const student &r) const
	{
		if(id < r.id)
			return true;
		if(id == r.id)
			return name.compare(r.name) < 0;
		return false;
	}
}Student;

class Cla_fun
{
	public:
		void fun()
		{
			cout << "__test_fun_in_class";
		}
};
void __test_fun_in_class()
{
	Cla_fun *p;
	p->fun();
}

void change_const_by_ptr()
{
	const int a = 10;
	const int *p = &a;
//	*p = 20;
	cout << a << " " << *p;
};
/*
C++下是编译错误的:
错误：从类型‘const int*’到类型‘int*’的转换无效
错误：向只读位置‘* p’赋值
*/

namespace inheri
{
class A
{
public:
    A(int i) { n=i; }
    A(){ n=1;}
    virtual void f(){ std::cout<<"A.f() is used"<<endl;}
    void g(){ std::cout<<"A.g() is used"<<endl;}
    void k(){ std::cout<<"A.k() is used"<<endl;}
private:
    int n;
};
class B:public A
{
public:
    B(int i) { n=i; }
    B(){ n=1;}
    void f(){ std::cout<<"B.f() is used"<<endl;}
    void g(){ std::cout<<"B.g() is used"<<endl;}
    void h(){ std::cout<<"B.h() is used"<<endl;}
    virtual void j(){ std::cout<<"B.h() is used"<<endl;}
private:
    int n;
};
class C
{
public:
    C(int i) { n=i; }
    C(){ n=1;}
    void w(){ std::cout<<"C.w() is used"<<endl;}
private:
    int n;
};
void _test_inheri()
{
    B b;
    b.k();      //b显然能看到A中的k()
    A *a;
	
    a=&b;
	
    a->f();         //a看到B的f()  【注意是B的】
    a->A::f();      //a看到A的f()
    a->g();         //a看到A的g()
    //a->h();         //a看不到B的h()		,因为a的虚函数表里没有b的函数
    //a->j();          //a看不到B的虚拟函数j()
    //cout<<a->C::n<<endl;  //看不到
    //a->C::w();          //看不到
}
}

void swap_ref(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
void __test_swap()
{
	int a = 1, b=2;
	swap_ref(a, b);
	cout << a << " " << b << endl;
}
int main()
{
	
//	exception_test();
//	new2DArr();
//	__test_reload_template();
//	__test_fun_in_class();
//	change_const_by_ptr();
//	_test_inheri();
	__test_swap();
	return 0;
}




