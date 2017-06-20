#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;
//或
using std::cin;		//如此,下文可直接使用std命名空间的cin
using std::string;
using std::vector;

//示例: 构造函数初始化方法一:列表初始化
class s1
{
	public:
		s1(const string &book):
		name(book), num(0), price(0.0)
		{ 
		}
		const s1& display(ostream &out) const //const函数只能返回const的this引用，否则编译出错
		{
			return *this;
		}
	
	private:
		std::string name;	//注意要加std域，否则编译错:‘string’不是一个类型名
		int num;
		double price;
};

//构造函数初始化方法二:计算初始化
class s2
{
	public:
		s2(const string &book);//注意这里声明，不要加{}
	
	private:
		string name;
		int num;
		double price;
};
s2::s2(const string &book)
{
	name = book;
	num = 0;
	price = 0.0;

}


//引用:必须且只能使用初始化列表这种方式来初始化
class constRef
{
	public:
		constRef(int ii);
	private:
		const int num;
		int &ref;
};
constRef::constRef(int ii): num(ii), ref(ii) {}


//static, const, static const
//--std=c++11
class A
{
	public:
		A(int i):val(i){}
	private:
		int val;
};

class B0
{
	public:
		B0(int ii):c(i), i(ii), r(ii){}
		const int c;	
		static int s;	
		const static int cs = 1; 
		int i;
		int &r;
};
int B0::s = 2;	

class B
{
	public:
//		B(int i):a(i),cs(1){} 错，static、const static不能在这里初始化
		B(int i):a(i){}
		A a;
		const int c = 1;	//OK	//不要丢掉int...
		static int s;		//错:static int s = 1;不允许在类内初始化非常量静态成员
		const static int cs = 1; 	//OK	
		int i = 1;			//OK	
		int &r = i;			//OK	
};
int B::s = 2;				//OK,必须这样做	//定义并初始化
//const int B::cs = 1; 	//OK too	
void testInitVal()
{
	cout << B::cs << endl;
}

class NoName
{
	public:
		NoName();
		NoName(NoName &c);
	private:
		string *pstring;
		int num;
};
//复制构造函数
NoName::NoName(NoName &c)//这种方式定义的话，要先在上面类里声明
{
	pstring = new std::string;
	*pstring = *(c.pstring);
	num = c.num;
}

class NoCopy
{
	public:
		void nullFunc();		//可以只声明，不定义
	private:
		NoCopy(const NoCopy&);	//只声明不定义，连友元也禁止复制了。
};


//综合示例:雇员
class Employ
{
	public:
		Employ(): name("default"), id(count)
			{
				++count;
			}
		Employ(std::string nm): name(nm), id(count)
			{
				++count;
			}
		Employ(const Employ& r): name(r.name), id(count)
			{
				++count;
			}
		Employ &operator = (const Employ &r)
		{
			name = r.name;
			return *this;
		}
		Employ & operator+=(const Employ &e);
		int& operator[](size_t n);
			
		~Employ(){};
		int commonVal;
	private:
		std::string name;
		int id;
		vector<int> vec;
		static int count;
};
int Employ::count=2;

int& Employ::operator[](size_t n)
{
	return vec[n];
}



//不要定义为成员函数
ostream& operator <<(ostream& out, const Employ &c)
{
	//out << c.name; 错，私有的，不能访问
	out << c.commonVal;
	return out;
}

istream & operator >> (istream &in, Employ &c) 
{
	in >> c.commonVal;
	if(!in)
		c = Employ();//reset use constructor
	return in;
}

Employ & Employ::operator+=(const Employ &e)
{
	commonVal += e.commonVal;
	
	return *this;
}


Employ operator + (const Employ &l, const Employ &r)
{
	Employ ret(l);
	ret += r;//技巧，借用+=
	return ret;
}


//重载++, --操作符
class s4
{
	public:
		s4(int *b, int *e):beg(b),end(e),cur(b){}
		s4& operator++();
		s4 operator++(int);//都需要在这里声明
	private:
		int *beg;
		int *end;
		int *cur;
};
s4& s4::operator++()	//前缀,返回引用,a++即 a=a+1,即同赋值操作符返回引用
{
	if(end == cur)
		throw out_of_range("end");
	++cur;
	return *this;
}
s4 s4::operator++(int)	//后缀操作符，返回值(与内置类型一致,int表示值)
{
	s4 ret(*this);
	++(*this);	//调用前缀操作符
	return ret;
}

//函数对象: 重载函数调用符()
struct abInt
{
	int operator()(int val)
	{
		return val < 0 ? -val : val;
	}
};
void test_abInt()
{
	abInt abj;
	cout << abj(-3) << endl;
}

template <typename T, typename P>
class Queue
{
	public:
		Queue();
		T &front();
		const T &front() const;
		void push(const T &);
		T &pop();
		bool empty() const;
};


template <typename T> void print(const T &c)
{
	typename T::size_type ix;
	for(ix = 0; ix != c.size(); ++ix)
	{
		cout << c[ix] << endl;
	}
}

//函数重载
void f();
void f(int &);
void f(const int &);
void f(int &, double = 3.14159);
void f(int &, int &);
//强制重载
//f(2, static_cast<int>(2.3));//从而调用f(int &, int &)


//类作用域:类内--形参、成员函数体;类外--返回类型


//友元
class s3;		//part1:类的某个成员函数作为友元
class Window_2	//part2:类的某个成员函数作为友元
{
	public:
		Window_2& change_2(s3 &s);
};
class s3
{
	public:
		friend class Window;	//想要用我的private，先在这里登记

		//很麻烦，因为要使用某个类内部成员，必须先看到它的完整声明。
		//所以，只能先把Window_2在前面声明，其函数必须在这个s3之后定义。
		friend Window_2& Window_2::change_2(s3 &s);	
		friend void print(s3 &s);
		s3(const string &book):
		name(book), num(0), price(0.0){}
	
	private:
		std::string name;	//注意要加std域，否则编译错:‘string’不是一个类型名
		int num;
		double price;
};
class Window
{
	public:
		Window& change(s3 &s)
		{
			s.name += ";";
			s.num += 1;
			return *this;
		}
};
Window_2& Window_2::change_2(s3 &s)	//part3:类的某个成员函数作为友元
{
	s.name += ";";
	s.num += 1;
	return *this;
}

void print(s3 &s)
{
	cout << s.name;
}


//函数对象
void func_object()
{
	plus<int> myadd;
	cout << myadd(1, 4) << endl;
}


//派生
class Item_base
{
	public:
		Item_base(string s = "", double pri = 10):isbn(s),price(pri){} 
		virtual double net_price(size_t n) const
		{return n * price;}
		virtual ~Item_base(){}
	private:
		string isbn;
	protected:
		double price;
};
class Bulk_item: public Item_base
{
	public:
		//下面可以不考虑基类的成员，但要求基类成员有默认值,如:string s = ""
		Bulk_item(double dis = 0.9, double pri = 10):discount(dis){}
		double net_price( size_t n) const
		{return (n * price * discount);}
	private:
		double discount;
};
//错:void print(Item_base &b, size_t n)。因非成员函数后面不能有const 
void print(const Item_base &b, size_t n)
{
	cout <<b.net_price(n)<<endl;
}
void func_protected()
{
	Item_base base("b1", 10);
	Bulk_item bulk(0.8);
	print(base, 1);
	print(bulk, 1);
	double d = bulk.Item_base::net_price(1);//法1:使用作用域::,在派生类中调用基类里的方法
	cout << d << endl;

	Item_base *pbase = &bulk;
	d = pbase->net_price(1); //这里依然调用bulk的
	cout << d << endl;

	d = pbase->Item_base::net_price(1); 	//法2:这样，才调用base的
	cout << d << endl;
}
//private继承
class Derived_0 : private Item_base
{
	public:
		using Item_base::net_price; //这样保持父类成员的public属性
	protected:
		using Item_base::price;
	private:
};



//---- 变量初始化规则:primer p399
//如果不在默认构造函数中显式初始化，或只依赖合成构造函数，
//这个对象中的变量值将依对象所处的局部/全局而定，规则同基本内置变量初始化规则
class Bulk_item_no_init: public Item_base
{
	public:
		//下面可以不考虑基类的成员，但要求基类成员有默认值,如:string s = ""
		Bulk_item_no_init(){}
		void pri_discount()
		{cout << discount << endl;}
	private:
		double discount;	
};
Bulk_item_no_init b_global;
void test_bulk_item_no_init()
{
	Bulk_item_no_init b;
	b.pri_discount();	 	//1.局部:discount将是随机值，同基本内置类型变量规则。函数调用要加上()
	b_global.pri_discount();//2.全局:discount会被初始化为0，
}


//派生类的构造函数
//注意下面的Item_base(is, pri)嵌入在列表里,要放在列表第一个!!!，否则编译警告
//虽然初始化列表次序和初始化顺序无关，但是在这里是为什么呢?
class Bulk_item_construct: public Item_base
{
	public:
		Bulk_item_construct(double dis, string is,double pri):
		Item_base(is, pri),discount(dis){}
		
		double net_price( size_t n) const
		{return (n * price * discount);}
	private:
		double discount;
};
void test_Bulk_item_construct()
{
	Bulk_item_construct b(0.89, "book", 10);
}

//派生类的复制构造函数
class Derived_1:public Item_base
{
	public:
		Derived_1(const Derived_1 &d):Item_base(d)
		{}
};

//派生类的赋值操作符
class Derived_2: public Item_base
{
	public:
		Derived_2 & operator=(const Derived_2 &d)
		{
			if(&d != this)	//【注意】
				Item_base::operator=(d);
			
			return *this;
		}
};


//虚析构函数
class s5
{
	public:
		s5(){}
		virtual ~s5()
		{delete p;}
	private:
		string *p;
};
class s6:public s5
{
	public:
		~s6(){}
};
void test_s5()
{
	s5 *p = new s5;
	delete p;	//调用s5的析构

	p = new s6;
	delete p;	//调用s6的析构
}


//抽象基类，将继承来的函数设为纯虚函数
class false_class: public Item_base	//没有public Item_base时会编译出错
{
	public:
		double net_price(std::size_t) const = 0;
};

//函数模版
template <size_t N, typename Arr>
void gethead(Arr (&arr)[N]) //数组引用，是&arr而不是arr&
{
	cout << sizeof(arr) << endl;
}
void test_template_arr_ref()
{
	int a[5] = {};
	gethead(a);
}

//类模版
template <class T>
class s7
{
	public:
		s7(){}		//这里别写成;......
		T &front(){};
};
s7<int> q;


class __Test_return_const_this
{
	// 错误：将类型为‘__Test_return_const_this&’的引用初始化为类型为‘const __Test_return_const_this’的表达式无效
//	__Test_return_const_this &dis() const
	const __Test_return_const_this &dis() const		//返回值也必须是const，因为是通过const成员函数得来的
	{
		return *this;
	}
};



//全局变量、成员变量的访问方法
int height = 2;
class c_member
{
	public:
		c_member()
		{
		}
		c_member(int i):height(i)
		{
		}
		void disp()
		{
			cout << height << endl;
			cout << ::height << endl;
			cout << c_member::height << endl;
			cout << this->height << endl;
		}
	public:
		int height = 1;
};
void __test_use_global_member()
{
	c_member c;
	c.disp();
}
/*
1
2
1
1
*/

//数组，成员为类类型
void __test_class_arr()
{
	c_member arr[] = 
	{
		1,
		2,
		c_member(3)
	};
	cout << arr[0].height <<endl;
	cout << arr[1].height <<endl;
	cout << arr[2].height <<endl;
}

class base_c
{
	private:
		int bi;
	protected:
		double bd;
};
class derived_c:public base_c
{
	protected:
		void disp()
		{
//			cout << bi ;		// 错误：‘int base_c::bi’是私有的
			cout << bd ;
			cout << di ;
			cout << dd ;
		}
	private:
		int di;
	protected:
		double dd;
};

//空类的大小，对齐?
class Size_of_null_class
{};
void _test_Size_of_null_class()
{
	Size_of_null_class c1,c2,c3;
	cout << sizeof c1 << endl;
	cout << &c1 << endl;
	cout << &c2 << endl;
	cout << &c3-&c2 << endl;	//这个其实是指针距离，不是地址值相减，需要int转换
	
}
/*
注意:栈往下增长的
1
0x62cc5f
0x62cc5e
-1
*/

//有一个char成员的对象大小，对齐?
class Size_of_class_with_char
{
	char c;
};
class Size_of_class_with_short
{
	short c;
};			//只有一个变量，当然sizeof是 2，不存在对齐问题，
class Size_of_class_with_short_int
{
	short c;
	int i;
};			//内存对齐，8字节

void _test_Size_of_class_with_char_short()
{
	Size_of_class_with_char c1;
	Size_of_class_with_short c2,c3;
	Size_of_class_with_short_int c4;

	
	cout << sizeof c1 << endl;
	cout << sizeof c2 << endl;
	cout << &c3-&c2 << endl;	//指针距离
	cout << (int)&c3 - (int)&c2 << endl;	//这才是地址值相减

	cout << sizeof c4 << endl;

	Size_of_class_with_char c5,c6,c7;		//多个类，也不存在对齐问题
	cout << (int)&c5 << endl <<  (int)&c6 << endl <<  (int)&c7 << endl;

	Size_of_class_with_short c8,c9;		//多个类，注意起始地址，整数倍的地方
	cout << (int)&c8 << endl <<  (int)&c9 << endl;	
}
/*
注意:栈往下增长的
1
2
-1
-2
8
2280543
2280542
2280541
2280538		//注意这里,38_39
2280536


- 3 2 1
- 8 8 6
6 - - -
*/


int main() //void编译错误:错误：‘::main’必须返回‘int’
{
//	testInitVal();
//	func_object();
//	func_protected();
//	test_bulk_item_no_init();
//	test_template_arr_ref();
//	__test_use_global_member();
//	__test_class_arr();
//	_test_Size_of_null_class();
	_test_Size_of_class_with_char_short();

	return 0;
}




