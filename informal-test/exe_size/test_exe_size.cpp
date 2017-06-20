/*
命令:
$ g++ test_exe_size.cpp -O0; ls -l
$ g++ test_exe_size.cpp -O0 -o main.o; ls -l
$ g++ test_exe_size.cpp -S; ls -l a.exe

$ objdump -SD main.o > ../../1.txt

*/

#include <iostream>
using namespace std;

class A //单纯只定义A，不定义A的对象不占用空间。
{
	public:
		A(){}
		int a;	//不占exe的空间
		static int s;//这里只是声明，不占exe的空间
};

int A::s = 1; //data段，占用exe空间
int gi = 2;   //data段，占用exe空间

int gbss[100];	//这里数组大小从1-->100，不改变exe空间
int gbss2;		//每单独定义一个bss区的变量,exe空间都会增大

//注释不会增加exe空间
//这里是测试性注释
int main()
{	

	static double b = 3;	//data段,占用exe空间
	char c[1] = {0};		//栈，占exe空间!!!!!如下文
	int bb = 2;
	int aa = 5;
	int cc = 9;
	int h = 34653456;	
	int j = 23452345;
	int k = 234634753;	
	int l = 234523423;	
/*
这些变量在汇编文件 .s 或者objdump -SD main.o中都能看到对应的源代码，	
但是是每添加多行变量才会增加，main.o 和 a.exe大小相同，一起增加
【注意】编译时记得用 -o选项，观察文件生成日期是不是最新
*/

//	int m = 235464356;
//	int n = 23452345;	
	
	int e = 9;	

	int *p = NULL;
	int *pp = new int[100]; //堆，不占exe空间
	p = new int[100];	//这里大小从1-->100，不改变exe空间

	bb = aa + bb;
	swap(aa, bb);
	cout << bb << endl;	//每一行代码都占用空间
	
	return 0;
}


