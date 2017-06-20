#include <iostream>
#include <vector>
#include <bitset>
#include <list>
#include <set>
#include <map>
#include <cstdlib>
#include <cstring>
#include "stdio.h"
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <time.h>  
#include <stdlib.h>  
#include <stdio.h>  


using namespace std;


//指针，引用，数组，字符串数组
void ptr_ref_arr_test()
{
	//加const 消除了编译警告，常量指针，注意字符串常量定义的方式，
	const char *s = "abcde";  
	
	cout << s << ":" << sizeof(s) << endl;  
	cout << *s << ":" << sizeof(*s) << endl;
	cout << &s << ":" << sizeof(&s) << endl;

	char arr[] = "abcde";
	cout << arr << ":" << sizeof(arr) << endl;  
}
/*
abcde:4
a:1
0x62cc5c:4
abcde:6
*/

void ptr_of_ptr_test()  
{  
    char a[20]="You_are_a_girl";  
    char *p=a;  
    char **ptr=&p;
	
	printf("p=%p\n",p);  //用%p打印，消除了警告
	printf("ptr=%p\n",ptr);  
	printf("*ptr=%p\n",*ptr);  
    printf("**ptr=%d\n",**ptr);  
	
    ptr++;  
	printf("ptr=%p\n",ptr);  
	printf("*ptr=%p\n",*ptr);  
    printf("**ptr=%c\n",**ptr);  
}  
/*
p=2673752
ptr=2673748
*ptr=2673752
**ptr=Y
ptr=2673752 //栈内的存放位置，p在高处。
*ptr=1601531737
Segmentation fault (核心已转储)
*/


void ptr_num_convert_to_ptr_test()
{
	//法1
	unsigned int len = 0x22554c;
	unsigned int *p = (unsigned int *)len;

	//法2
	unsigned int *p1 = (unsigned int *)0x22554c;
	
	//*(int *)0x22554c = 0x100;
 	std::cout << p << ":"  << p1 << std::endl;
}
/*
可以定义指针指向任意地址，但是不能通过该指针访问任意的地址*p,会段错误
cout << *p 
Program received signal SIGSEGV, Segmentation fault.
*/


void ptr_struct()
{
	typedef struct s
	{
		int id;
		char name;
	}S;
	
	S mys[2] = {0};
	S *p = mys;
	//S *pref = &mys;//错误：不能在赋值时将‘S (*)[2]’转换为‘S*

	S mys1 = {0};
	S *pp = &mys1;
}


void arr_addr_test()
{
	int a[30];

	cout << a << " : " << sizeof(a) <<endl;
	cout << &a << " : " <<  sizeof(&a) <<endl;

	cout << a+1 <<" : " <<  sizeof(a+1) <<endl;
	cout << &a+1 <<" : " <<  sizeof(&a+1) <<endl;
}
/*
0x22cbf8 : 120
0x22cbf8 : 4
0x22cbfc : 4
0x22cc70 : 4
*/


void arr_n_test()
{
	const int ia = 5;
	int ib = 4;
	double d = 3.3;
	int a[ia];
	int b[ib];
	a[3] = static_cast<int> (d);
	std::cout << a[3] << " " << b[3] << std::endl; 
}

#include <assert.h>
//assert(expression):断言expression 成立（真），并往后执行。假则abort。
/*
在发布版中，插入 #define NDEBUG 来禁用assert调用
*/
void assert_test()
{
    int s[] = {1,2,3,4,5};
	int d[10] = {};
//	memcpy(d, nullptr, sizeof(s));
	memcpy(d, s, sizeof(s));
}
/*
assertion "dst && src" failed: file "libc.cpp", line 20, function: void* memcpy_my(void*, void*, size_t)
*** starting debugger for pid 5760, tid 5676
*** continuing pid 5760 from debugger call (1)
Aborted (核心已转储)

*/


/*
1. int数值在PC上内存中的排布
2. 【知识点】注意以16进制输出的方法: hex << 
*/
void int_mem_area_test()
{
	int i = 0x56789abc;
	cout << hex << (int)&i << " - "  <<(int)*((unsigned char *)(&i))<< endl;
	cout << (int)&i + 1 << " - " <<(int)*((unsigned char *)((int)&i + 1)) << endl;
	cout << (int)&i + 2 << " - "  <<(int)*((unsigned char *)((int)&i + 2)) << endl;
	cout << (int)&i + 3 << " - " <<(int)*((unsigned char *)((int)&i + 3)) << endl;
	
}/*
29cc4c - bc
29cc4d - 9a
29cc4e - 78
29cc4f - 56
*/
//	cout << 10 << endl; //因为上面用hex将 cout设置为16进制，所以这个文件内都是16进制了



void malloc_on_win64_test()
{
	struct node1
	{
		int a,b,c;
	}n1,n2,n3;
	struct node2
	{
		int a,b,c,d,e;
	};
	struct node3
	{
		int a,b,c,d,e,f,g;
	};
	struct node4
	{
		int a,b,c,d,e,f,g,h;
	};
	struct node1 *p1 = NULL;
	struct node2 *p2 = NULL;
	int *p0 = NULL;
	printf("%d\n", sizeof(n1));
	printf("%p,%p,%p\n", &n1,&n2,&n3);
	printf("p0\n");
	for(int i = 0; i != 5; ++i)
	{
		p0 = (int *)malloc(sizeof(*p0));
		printf("%p\n", p0);
	}
	
	printf("p1\n");
	for(int i = 0; i != 5; ++i)
	{
		p1 = (struct node1 *)malloc(sizeof(*p1));
		printf("%p\n", p1);
	}
	
	printf("p2\n");
	for(int i = 0; i != 5; ++i)
	{
		p2 = (struct node2 *)malloc(sizeof(*p2));
		printf("%p\n", p2);
	}
}
//不足16字节，按照16字节提供，超过16字节，按照8字节对齐
/*
$ ./a.exe
12
0x0,0x401890,0x611ccfb2
p0
0x800482a0
0x800482b0
0x800482c0
0x800482d0
0x800482e0
p1
0x800482f0
0x80048300
0x80048310
0x80048320
0x80048330
p2
0x80048340
0x80048358
0x80048370
0x80048388
0x800483a0
*/


void printf_var_order_test()
{
	int a = 1;
	int ar[] = {10, 20, 30};
	int *p = ar;
	int *p2 = ar;
	printf("%d,%d,%d\n", ++a, ++a, ++a);
	std::cout << ++a <<","<<  ++a <<","<<  ++a <<endl;

	printf("%d,%d,%d\n", *p, *(p++), *p);
	std::cout << *p2 << ","<< *(p2++)<<","<< *p2 <<endl;

	 char s[] = "012345678", *p = s;
	 printf("%c, %c, %c, %c\n" ,*++p, *(++p),++*p,++(*p));	//注意与上面区分
}
/*
警告：‘p’上的运算结果可能是未定义的 [-Wsequence-point]
4,4,4
7,7,7
20,10,10
20,10,10
2, 1, 2, 1
*/


//从外部重定向
void cerr_test_1() 
{  
	int a = 5;
    cout << "hello world---cout" << endl ;  
    cerr << "hello world---cerr:" << a << endl ;
	fprintf(stderr, "fprintf(stderr: %d", a);
}   
/*
执行1:重定向
$ g++ all.cpp ;a 2> 1.txt
hello world---cout

$ cat  1.txt
hello world---cerr:5
fprintf(stderr: 5

执行2:不重定向。
$ g++ all.cpp ;a 
hello world---cout
hello world---cerr:5
fprintf(stderr: 5
*/

//从代码内部重定向
void cerr_test_2() 
{  
	int a = 5;
    cout << "hello world---cout" << endl ;  
    cerr << "hello world---cerr:" << a << endl ;
	freopen("d:\\stderror.txt","w",stderr);	
	fprintf(stderr, "fprintf(stderr: %d", a);
	
}   
/*
$ g++ all.cpp ;a

hello world---cout
hello world---cerr:5

$ cat ../../stderror.txt
fprintf(stderr: 5
*/


//***********  内存对齐 ******************
//答题时按照10进制作答了。。。我去。。。。
void alli_tx_exam()
{
	typedef struct aaa
	{
		int a;		//0-3,
		char c[3];	//4-6,
		short s;	//8-9,
		double d;	//16-23,【这里注意，是从16开始,8的整数倍】
	}AAA;

	AAA *p = (AAA *)0x10000000;
	printf("%x, %x, %x, %x\n", sizeof(*p), p+10, (char *)p + 10, (int *)p + 10);
	printf("p->a:%x, DEC:%d\n", &(p->a), &(p->a));
	printf("p->c:%x, DEC:%d\n", &(p->c[0]), &(p->c[0]));
	printf("p->s:%x, DEC:%d\n", &(p->s), &(p->s));
	printf("p->d:%x, DEC:%d\n", &(p->d), &(p->d));
}
/*
abcdefg
18, 100000f0, 1000000a, 10000028
p->a:10000000, DEC:268435456
p->c:10000004, DEC:268435460
p->s:10000008, DEC:268435464
p->d:10000010, DEC:268435472
*/


void alli_pack()
{
#pragma pack(5)			//pack(value)，value常见为:1、2、4、8，其他值则相当于未设置pack
	struct Args
	{
	        int i;
	        double d;
	        char *p;	 //注意指针
	        char ch; 
	        int *pi;	

	}args;	

    printf("args length:%d\n",sizeof(args));
    printf("%ld\n",(unsigned long)&args.ch-(unsigned long)&args.p);
    printf("%ld\n",(unsigned long)&args.pi-(unsigned long)&args.ch);
	
#pragma pack()
}
/*
pack(8):32
pack(4):24
pack(3)、pack(5)、pack(6)、pack(7):32
pack(2):22
*/


void alli_arr_struct()
{
	struct AA
	{
        char ch; 	//0----------
        double d;	//8----------15
        char ca[9];	//16---------23
        char c;		//ca|c|s-|   31
		short s;	
	} aa;	
	cout << (unsigned long)&aa.ch << endl;
	cout << (unsigned long)&aa.d << endl;
	cout << (unsigned long)&aa.ca << endl;
	cout << (unsigned long)&aa.ca[8] << endl;	
	cout << (unsigned long)&aa.c << endl;
	cout << (unsigned long)&aa.s << endl;	
}
/*
2280528
2280536
2280544
2280552
2280553
2280554
*/


int alli_pack_2()
{
	//内存对齐
#pragma pack(8)
	struct Args
	{
	        char ch; 
	        double d;
	        short st; 
	        char rs[9];
	        int i;
	} args;
	struct Argsa
	{
	        char ch; 
	        Args test;
	        char jd[10];
	        int i;
	}arga;
#pragma pack(8)

	// cout <<sizeof(char)<<" "<<sizeof(double)<<" "<<sizeof(short)<<" "<<sizeof(int)<<endl;
	//cout<<sizeof(long)<<" "<<sizeof(long long)<<" "<<sizeof(float)<<endl;
	cout<<"Args:"<<sizeof(args)<<endl;
	cout<<".ch:"<<(unsigned long)&args.ch<< endl;
	cout<<".d:"<<(unsigned long)&args.d << endl;
	cout<< ".st:"<<  (unsigned long)&args.st << endl;
	cout<<".rs:"<<(unsigned long)&args.rs << endl;
	cout<<".rs[8]:"<<(unsigned long)&args.rs[8] << endl;
	cout<<".i:"<< (unsigned long)&args.i << endl;	
	
	cout<<"Argsa:"<<sizeof(arga)<<endl;
	cout<< ".ch:"<<  (unsigned long)&arga.ch << endl;
	cout<< ".test:"<<  (unsigned long)&arga.test << endl;
	cout<<".jd:"<<(unsigned long)&arga.jd << endl;
	cout<<".jd[9]:"<<(unsigned long)&arga.jd[9] << endl;
	cout<<".i:"<< (unsigned long)&arga.i << endl;	

#pragma pack()		//取消对齐设定
	
	return 0;
}
/*
[ch|            ]
[----double-----]
[st|rs[0]------5]
[rs-8   |i------]

Args:32
.ch:4268064
.d:4268072
.st:4268080
.rs:4268082
.rs[8]:4268090
.i:4268092
Argsa:56
.ch:4268096
.test:4268104
.jd:4268136
.jd[9]:4268145
.i:4268148
*/



//结构体之后的char不会被塞入结构体的缝隙
void alli_char()
{
	struct AA
	{
        char ch; 	//0----------
        double d;	//8----------15
        char c;		//ca|c|s-|   31
	} aa;
	struct BB
	{
        char c1; 	//不会被塞入后一个结构体的缝隙!!!!
        struct AA aaaa;//占用整整的一个sizeof(aa)
        char c2;	//不会被塞入前一个结构体的缝隙!!!!
	} bb;
	cout << sizeof(aa) << "," << sizeof(bb) << endl;
	cout << (unsigned long)&bb.c1<< endl;
	cout << (unsigned long)&bb.aaaa<< "--" << (unsigned long)&bb.aaaa.c<< endl;
	cout << (unsigned long)&bb.c2<< endl;
}

void alli_class()
{
	struct
	{
		char c;
		long l;
		//static int ii;	//错误:局部类‘struct alli_static()::A’不应当拥有静态数据成员
	}A;

	class B
	{
		public:
			B(){}
	};
	cout << "sizeof(A):" << sizeof(A) << endl;
	cout << sizeof(long) << endl;
	cout << sizeof(B *) << endl;
	cout << sizeof(short *) << endl;
	cout << sizeof(size_t) << endl;

}

struct alli_static_A
{
	short c;
	static int st;
	int i;
};
class alli_static_B
{
	char c;
	static int st;
	int i;
};
int alli_static_A::st = 1;
void alli_static()
{

	
	cout << sizeof(alli_static_A) << endl;
	cout << sizeof(alli_static_B) << endl;

	
	alli_static_A a1, a2;
	
	
	cout << &(a1.c)  << endl;
	cout << &(a1.st)  << endl;	//可见，static成员 地址和结构体无关
	cout << &(a2.st)  << endl;
}
/*
8
8
0x62cc58
0x405008
0x405008

*/
void size_t_test()
{
	size_t a = 0xfffffffff;
	printf("%d\n", a);	

}


/*Windows可以new到的最大的内存 / 进程可以new到的最大的内存*/
void max_size_can_new()
{
	//注意:数组的下标是size_t,最大:0~2^32-1(4394967295)
	//1024MB=1024×1024KB=1024×1024×1024B
	size_t size = 1.98 * 256*1024*1024;//1G(int占4字节): 256*1024*1024， 即约为:250，000，000

	int *p = new int[size]; 
	
//	cout << sizeof(p) << endl;//4//
	cout << size << endl;

	p[size - 1] = '\0';

	delete []p;
	
}
/*
Windows测试结果:
1	GB:   这里依据系统当前内存剩余大小而定
1.98GB:   throwing an instance of 'std::bad_alloc'
		只是系统当前空余内存过少
2   GB:   throwing an instance of 'std::bad_array_new_length'
		超出系统理论限制
见<linux进程.doc>

*/


#include <vector>	//<> 里包含空格也会编译报错
void vector_size_increase_test()
{
	vector<int> v1;		//capacity为0
	vector<int> v2(1);	//capacity为1
	
	cout << v1.capacity() << endl;
	cout << v2.capacity() << endl;

	for(int i = 1; i<15; ++i)
	{
		v1.push_back(i);
		cout << i << "  "<< v1.capacity() << endl;
	}
}
/*
按照 2倍递增
0
1
1  1
2  2
3  4
4  4
5  8
6  8
7  8
8  8
9  16
10  16
11  16
12  16
13  16
14  16
*/

void for_pram()		//for的第二个语句不成立，第一个语句也会被执行。
{
	int i = 5;
	for(i = 2; false; )
	{}
	cout << i << endl;		//.2
}

void question_mark_expression()
{
	int a = 2,b = 2;
	2 > 1 ? a-- : b--;		//短路求值特性
	cout << a << endl;		//:1
	cout << b << endl;		//:2

	cout << (-1 ? 1 : 0);	//1,
}

void ifdef_test()
{
	cout << " ifdef_test" << endl;
#ifdef TURE
	cout << " #ifdef 1" << endl;		//不会有
#endif
}

void while_n_test()
{
	int n = 5;
	while(n--)
		cout << n << endl;
}
/*
4
3
2
1
0
*/


#if defined CONST_PTR
void const_ptr_arr_string_test()  
{  
	const char *ptr_str = "123465";  //要加const，否则 警告：不建议使用从字符串常量到‘char*’的转换 [-Wwrite-strings]
	ptr_str[2] = 'a';

	char arr_str[] ="123465";		//OK
	arr_str[2] = 'a';
	
	const char c_arr_str[] ="123465";// 错误：向只读位置‘c_arr_str[2]’赋值
	c_arr_str[2] = 'a';

}  
#endif



//指向多维数组的指针，C++P p139
void ptr_arr_test()
{
	int a[3][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
	int (*p)[4] = a; //这是1个指针(1个!)! 指向的类型只能是int (*)[4]，即这个指针的步长为4个int,C++P p223

	//int (*p)[3] = a;
	//错误：不能在赋值时将‘int (*)[4]’转换为‘int (*)[3]’

	//若要访问每行的其他元素
	std::cout << p[2][0] << " " << p[2][1] << endl;
	//或者，这样处理
	int *p1 = p[2];	
	std::cout << p1[0] << " " << p1[1] << endl;
	
	std::cout << **p << " " << **(p+1) << endl;

	std::cout << (*p)[0] << " " << (*p)[1] << endl;
	
	p = &a[2];
	std::cout << **p << " " << **(p+1) << endl;



}


//默认实参 C++P P232
void def_func_arg(int a = 3)
{
	std::cout << a << std::endl;
}
void def_func_arg_test()
{
	def_func_arg();	//没有传递参数，采用默认实参
	
	int a;
	std::cin >> a;
	def_func_arg(a);	
}

void overflow_var()
{
	unsigned int a = 0xffffffff;
	unsigned int b = 0xffffffff;
	unsigned int c = 0xffffffff;

	cout << a << "\n" 
		<< a+b+b+b+b+b-a-a-a-a-a << "\n" 
		<< a+b-c<< endl;
	
	unsigned int d = 0;
	d = a+b+b+b+b+b;
	cout << d << "\n" 
		<<d-a-a-a-a-a << "\n" 
		<<endl;

}
/*
4294967295
4294967295
4294967295
4294967290
4294967295

*/


#define __NO__SEE__

//【位域】
//表示日期，CP P388
struct bit_date
{
	unsigned int day:5, month:4, year:7;
};
void bit_date_test()
{
	struct bit_date myD;
	myD.year = 47; // 1970 + 47 = 2017
	myD.month = 1;
	myD.day = 18;
	cout << 1970 + myD.year << "-" << myD.month << "-" << myD.day << endl;
}

void bit_shift()
{
	int a = - 0x1122;
	cout <<  bitset<32>(a) << endl;
	cout <<  bitset<32>(a >> 1) << endl;

	int a1 = 0x1122;
	cout <<  bitset<32>(a1) << endl;
	cout <<  bitset<32>(a1 >> 1) << endl;
}
/*注意负数右移后符号位补1

*/


//正数、负数求余问题 C++P p145
void mod_devide_test()
{
	cout << "-21/-8:\t" <<(-21/-8) << endl;
	cout << "21/8:\t" <<(21/8) << endl;
	cout << "21%8:\t" <<(21%8) << endl;
	cout << "-9/7:\t" <<(-9/7) << endl;	
	cout << "-9%7:\t" <<(-9%7) << endl;
	cout << "-9%-7:\t" <<(-9%-7) << endl;
	cout << "9%-7:\t" <<(9%-7) << endl;
	cout << "-21%-8:\t" <<(-21%-8) << endl;	
	cout << "21%-5:\t" <<(21%-5) << endl;
	cout << "9%-7:\t" <<(9%-7) << endl;
	
}
/*
-21/-8: 2
21/8:   2
21%8:   5
-9/7:   -1
-9%7:   -2
-9%-7:  -2
9%-7:   2
-21%-8: -5
21%-5:  1
9%-7:   2
*/


//溢出后，自动回绕
void overflow_num()
{
	unsigned int uc = 4294967295;
	cout << uc << endl;
	cout << (uc+1) << endl;
}
/*
$
4294967295
0
*/

class base1
{
	public:
	virtual void print()
	{
	        cout << "base1" << endl;
	}
	virtual void print1()
	{
	        cout << "base1" << endl;
	}
	int i = 0;
};

class der1 : public base1
{
    public:
		virtual void print()
		{
		        cout << "der1" << endl;
		}
		virtual void pri()
		{
		        cout << "der1" << endl;
		}
	int ii = 0;
};

void __test_vtbl()
{
	class base1 b1;
	class der1 d1;
	
}

int main()
{

    return 0;
}


int main()
{
//	question_mark_expression();
//	ifdef_test();
	
//	while_n_test();
	bit_shift();
	alli_static();
	return 0;
}
