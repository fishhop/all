#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <stdio.h>
#include <queue>
#include <stdlib.h>
using namespace std;

//注意:按位或!!!!!!!
//大小端互换,这里不必转为unsigned，
#define BIT_SWAP32(A)  		((((A) & 0xff000000) >> 24) 		| 		\
                            (((A) & 0x00ff0000) >> 8) 	| 		\
                            (((A) & 0x0000ff00) << 8) 	| 		\
                            (((A) & 0x000000ff) << 24))

//转为大写
#define TUPER(c) ((((c)<='z')&&(c)>='a')?((c)-'a'+'A'):(c))


//求3个中的最大值
#define MAX3(a,b,c) (((a)>(b)?(a):(b))>(c) ? ((a)>(b)?(a):(b)) : (c)) 


//宏定义求三个数的中间值
//二分法画出情况，再翻译到代码，最后再给每一个字母加上(),这里省略。。。
#define MID3(a,b,c) (a>b?( a>c?(b>c?b:c):a  ):( c>a?(b>c?c:b):a  ))


/*
$ g++ alg/subject-smart.cpp -DAA;./a
alg/subject-smart.cpp:32:2: 错误：#error AA || BB
 #error AA || BB
  ^
*/
//#error的用法: 遇到#error，则编译时中断
#if defined AA || BB
#error "haha~"
#endif

//#pragma message("show only in compile")


//用x替换#号后面的x
#define REP(x) "hi,"#x"!"

//连接
#define CONNECT(x,y) x##y


#define EXP2(a, b)	((a)*(a) + (b)*(b))
//EXP2(a++, a++)  : 3*4 + 5*6


#define VAR_ARG_PRINT(fmt, args...) printf(fmt, args)
#define VAR_ARG_PRINT_1(fmt, ...) printf(fmt, __VA_ARGS__)

void VAR_ARG_PRINT_test()
{
	VAR_ARG_PRINT("shenzhen is in :%s\n", 				"guangdong");
	VAR_ARG_PRINT("shenzhen is in :%s, age:%d\n", 		"guangdong", 	30);
	VAR_ARG_PRINT_1("shenzhen is in :%s, age:%d\n", 	"guangdong", 	30);
}

#define INC_SAT(val)    (val= ( (val)+1 > (val) )   ?   (val)+1   :   (val))

void __test_INC_SAT()
{
	
	int i = 2;
	short s = 32767;		//不可以起到防溢出作用,和类型提升有关??
	int val = 2147483647;
	unsigned int val_ll = 2147483647;

	cout << "__test_INC_SAT" << endl;
	cout << INC_SAT(i)	 << endl;
	cout << INC_SAT(s) << endl ;
	cout << INC_SAT(val) << endl ;
	cout << INC_SAT(val_ll) << endl ;
	cout << ++val 		<< endl;

	//错误：赋值运算的左操作数必须是左值
	//cout << INC_SAT(2147483647) << endl ;
}
/*
3
-32768
2147483647
2147483648
-2147483648
*/

void macro_test()
{
//	cout << MID3(1,2,3) << endl;
//	cout << MID3(3,2,1) << endl;
//	cout << MID3(3,1,2) << endl;
//	cout << MID3(1,3,2) << endl;
//	cout << MID3(3,3,1) << endl;
//	cout << MID3(3,2,2) << endl;

//	cout << REP(Colin) << endl;

//	int a1,a2,a3;
//	CONNECT(a,1)=0;
//	CONNECT(a,2)=12;
//	a3=4;
//	printf("a1=%d \t a2=%d \t a3=%d",a1,a2,a3);


//	cout << __FILE__ << " " << __LINE__ << endl; 

	int a = 3;
	cout << EXP2(3, 4) << endl;
	cout << EXP2(a++, a++) << endl;		//3*4 + 5*6
}


#include <bitset>
int __test_bitset()
{
//	macro_test();

	int a1 = - 0x1a2b3c4d;
	cout <<  bitset<32>(a1) << endl;
	cout <<  bitset<32>(a1 >> 1) << endl;
	cout <<hex << a1 <<" : " << BIT_SWAP32(a1) << endl;	
	int a = 0x1a2b3c4d;
	cout << hex << a <<" : " << BIT_SWAP32(a) << endl;




	return 0;
}


//C99里的预定义宏
void __test__predefined_macro()
{
	cout << __FILE__ << endl;			//必须是大写!!!
	cout << __LINE__ << endl;			//必须是大写!!!
	cout << __DATE__ << endl;			//必须是大写!!!
	cout << __TIME__ << endl;			//必须是大写!!!
	cout << __func__ << endl;			//必须是小写!!!
}

//有时候考虑到整数溢出，要用长整型符号L，或者是无符号长整型。
void __test_macro_num()
{
	#define MAX_LONG 2147483647
	#define MAX_ULONG 2147483647UL		//这里有UL不然会溢出，默认int型
	#define MAX_LONG_LONG 2147483647LL	//这里有LL不然会溢出
	
	cout << MAX_LONG << endl;
	cout << MAX_LONG + 1 << endl;
	cout << MAX_ULONG + 1 << endl;
	cout << MAX_LONG_LONG + 1 << endl;
}
/*
2147483647
-2147483648
2147483648
2147483648
*/



int main()
{
//	macro_test();
//	__test__predefined_macro();
//	__test_INC_SAT();

	__test_macro_num();

	return 0;
}


