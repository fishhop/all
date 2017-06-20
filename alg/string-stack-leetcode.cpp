#include <iostream>
#include <vector>
#include <stdio.h>
#include "string-stack-leetcode.h"
using namespace std;

void test_s31_cstr()
{
	s31_cstr c;

	char * str = "A man, a plan, a canal: Panama";
	char * str1 = "a,  x   X v  a";
	char * str2 = "Aa";

	cout << c.isMirror(str) << endl;
	cout << c.isMirror(str1) << endl;
	cout << c.isMirror(str2) << endl;
	
}


void test31()
{
	string str = "A man, a plan, a canal: Panama";
	string str1 = "a,  x   X v  a";
	string str2 = "a,  x   X x  a";
	class s31 s;
	cout << s.isMirror(str2) << endl;
	
}


void test_kmp()
{

	unsigned int i;
	class Kmp s;
	string T = "ababxbababababcadd";
	string P = "ababa";
	//int *nex = new int(strlen(P));这样是指定初值!!!!而不是个数!!!!
	int *nex = new int[P.size()];
	s.kmp(T, P, nex);
	cout << "nex:" << endl;
	for (i = 0; i < P.size(); ++i)
	{
		cout << nex[i] << endl;
	}
	delete []nex;
}


void test34()
{
	string str = "1101";
	string str1 = "111";
	class s34 s;
	string tmp = s.addBin(str, str1) ;

	cout << tmp << endl;
}


void test_s35_cstr()
{
	char *s[] = {
	"01aeaxxffxx",
	"2232x11xb",
	"22",
	"",
	};
	
	int n = 0;
	class s35_cstr c;
	for(int i = 0; i < 4; ++i)
	{
		cout << c.longestPalindrome(s[i], &n) << " : ";
		cout << n << endl;
	}
}


void test_s35_mirror()
{
	string str = "01aba1dxdxx";
	string str1 = "abd1bdx11xb";
	class s35_mirror s;
	
	string tmp = s.longestPalindrome(str);
	cout << tmp.size() << " " << tmp.length() << endl; 
	cout << tmp << endl;
}


void test_s35_dp()
{
	string str = "01aba1dxddxdxaba";
	string str1 = "abd1bdx11xb";
	class s35_dp s;
	
	string tmp = s.longestPalindrome(str);
	cout << tmp << endl;
}


void test_s38_c()
{
	s38_c c;
//	char **strs={		//错误：标量对象‘strs’在初始值设定中需要一个元素

	char *strs[]={
		"273389",
		"273325324",
		"273322434",
		"2733232",
		"2"};
	cout << c.longestCommonPrefix(strs, 5) << endl;
}


void test_s38()
{
    vector<string> strs={"273389","273325324","273322434","2733232","2733234"};
    s38 s;
    cout << s.longestCommonPrefix(strs) << endl;
}


void test_s39()
{
	s39 c;
//	string str;
//	char str[20]
//	cin.getline(str, 20);
//	cout << "input:" << endl;
//	getline(cin, str);//getline的两种用法
//	const char *str1 = str.c_str();

	const char *s[]={
		" ",
		" 01",
		" 0.x",
		" 0.1",
		" 0",
		" 2e",
		" 2e.2",
		" 2e0.2",
		" -22",
		" -0.3",
		};
	for(int i = 0; i < 10; ++i)
	{
		cout << s[i] << "\t"<< c.isNum(s[i]) << endl;
	}
}

void test_s313()
{
	string tmp[] = {"set","tes","ets","ette","sets"};
	vector<string> str(tmp, tmp+5);//注意vector初始化方法
	s313 s;
	vector<string> res;
	res = s.anagrams(str) ;
	
	for(vector<string>::iterator it = res.begin(); it != res.end(); ++it )
	{
		cout << *it << endl;
	}
}

void test_s314()
{
	string str = "/home/../yu/s/..//./c/";
	s314 s;
	cout << s.simplifyPath(str) << endl;
}

void test_s41()
{
	string str = "h{asdf}[2[23]]]s()";
	s41 s;
	cout << s.validParentheses(str) << endl;
	
}

void test_s42()
{
	string str = ")(d)()(()(())()";
	s42 s;
	cout << str << endl;
	cout << s.lenOfPar(str) << endl;
	
}
void test_s42_dp()
{
	string str = ")(d)((()))()";
	s42_dp s;
	cout << str << endl;
	cout << s.lenOfPar(str) << endl;
	
}
void test_s414()
{
	vector<string> str = {"50","6","3","*","-"};
	s414 s;
	
	cout << s.CalExpression(str) << endl;

}


int main()
{
	test_s31_cstr();
//	test32();
//	test35();
//	test31();
//	test33();
//	test_s35_cstr();
//	test_s35_mirror();
//	test_s35_dp();
//	test_s38();
//	test_s38_c();
//	test_s39_auto_machine();
//	test_s39();
//	test_s314();
//	test_s41();
//	test_s42();
//	test_s42_dp();
//	test_s414();

	return 0;
}

