#ifndef PART2_H
#define PART2_H
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;

/*
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring
cases.
For example,
擜 man, a plan, a canal: Panama?is a palindrome.
攔ace a car?is not a palindrome.
Note: Have you consider that the string might be empty? This is a good question to ask during an
interview.
For the purpose of this problem, we define empty string as valid palindrome.

*/

class s31_cstr
{
	public:
		inline bool alNum(char c)
		{
			return ((c >= '0' && c <= '9') 
				||(c >= 'a' && c <= 'z')
				||(c >= 'A' && c <= 'Z'));
		}
		inline char toLow(char c)
		{
			return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
		}
		bool isMirror(char *s)
		{
			if(!s || strlen(s) <= 1)		//"" 长度为0，但不是null
				return true;				//小写
			int b = 0, e = strlen(s) - 1;
			for(; b < e ; ++b, --e)
			{
				while(b < e && !alNum(s[b]))
					++b;
				while(b < e && !alNum(s[e]))
					--e;
				if(toLow(s[b]) != toLow(s[e]))
				{
					return false;
				}
			}
			return true;
		}
};




//中心扩展法
class s35_cstr
{
	public:
		const char *longestPalindrome(const char *s, int *n)
		{
			if(!s || !(*s))
				return NULL;
			int b, e, i, mark, len = strlen(s);	//计算一次len，避免下文重复计算
			*n = 0;
			for(i = 0; i < len; ++i)
			{
				b = e = i;
				if(s[e] == s[e+1])
					++e;
				for(;b >= 0 && e < len; --b, ++e)
				{
					if(s[b] != s[e])
						break;
				}
				if(*n < (e-1) - (b+1) + 1)		//看，上面用int也有好处，这里可以不用考虑溢出问题
				{
					mark = b+1;
					*n = (e-1) - (b+1) + 1;
				}
			}
			return (const char *)(&s[mark]);		//字符串要定义为const char*； 警告：不建议使用从字符串常量到‘char*’的转换 [-Wwrite-strings]	
		}
};


//纵向扫描
class s38_c
{
	public:
		int longestCommonPrefix(char **s, int n)
		{
			if(!s || !(*s) || n < 1)
				return 0;
			if(n == 1)
				return strlen(s[0]);
			
			int min = 0, i = 0, j = 0;
			for(i = 0; i < n; ++i)
				min = min > strlen(s[i]) ? min : strlen(s[i]);
			for(j = 0; j < min;++j)
			{
				for(i = 0; i<n; ++i)
				{
					if(s[i][j] != s[0][j])
						return j;
				}
			}
			return min;
		}
};
//			int min = i = j = 0;	//形式错!!!




/*
注意总结:
此类题目的思路，
先考虑完每一个阶段可能出现的情况，之后从前往后过滤，
一票否决制,类似于打游戏通关，一关不过则return false，

例如6230000000000;我们可以用6.23E12表示，而它表示的是将6.23×10^12 E数形式6.23E12
*/
class s39
{
	public:
		inline bool isDigit(const char *s)				//inline
		{
			return (*s >= '0' && *s <= '9') ? true : false;
		}
		bool isNum(const char *s)
		{
			// 1. 头
			if(!strlen(s))
				return false;
			while(*s == ' ')
				++s;
			if(*s == '-' || *s == '+')
				++s;
			if(!*s)
				return false;

			// 2. 中
			if(*s == '0')		//赶走02** , 留下0，0.** ，
			{
				if(*(s+1) == '\0')
					return true;
				if(*(s+1) != '.')
					return false;
				s += 2;		//上面判断的是s+1,这里要跳到s+2
			}
			while(isDigit(s))
				++s;
			if(*s == 'e')
			{
				if(!isDigit(s+1))
					return false;
				s += 2;
				while(isDigit(s))
					++s;				
			}
			if(*s == '.')
			{
				if(!isDigit(s+1))
					return false;
				s += 2;
				while(isDigit(s))
					++s;
			}

			//3.尾
			while(*s == ' ')//末尾的空格
				++s;
			if(*s != '\0')
				return false;
			else
				return true;
		}
};

#define __C__PP__


class s41
{
	public:
		bool validParentheses(string &s)
		{
			if(s.size() < 1)
				return false;
			
			string b = "([{";
			string e = ")]}";
			stack<char> ps;
			for(int i = 0, j; i < s.size(); ++i)
			{
				if(string::npos != b.find(s[i]))//npos,表示一个不存在的位置，no position
					ps.push(s[i]);
				else if(string::npos != e.find(s[i]))//npos,表示一个不存在的位置，no position
				{
					if(ps.empty() || ps.top() != b[e.find(s[i])])										
						return false;
					ps.pop();
				}
			}
			return ps.empty(); //技巧
		}
};

/*
题目:(())也包含在内的
*/


/*
这道题可以用一维动态规划逆向求解。假设输入括号表达式为String s，
维护一个长度为s.length()的一维数组dp[]，数组元素初始化为0。 
dp[i]表示从s[i]到s[s.length - 1]最长的有效匹配括号子串长度。则存在如下关系：
dp[s.length - 1] = 0;从i - 2 到0逆向求dp[]，并记录其最大值。
若s[i] == '('，则在s中从i开始到s.length - 1计算s[i]的值。
这个计算分为两步，通过dp[i + 1]进行的（注意dp[i + 1]已经在上一步求解）：
在s中寻找从i + 1开始的有效括号匹配子串长度，即dp[i + 1]，跳过这段有效的括号子串，
查看下一个字符，其下标为j = i + 1 + dp[i + 1]。若j没有越界，并且s[j] == ‘)’，
则s[i ... j]为有效括号匹配，dp[i] =dp[i + 1] + 2。
在求得了s[i ... j]的有效匹配长度之后，若j + 1没有越界，
则dp[i]的值还要加上从j + 1开始的最长有效匹配，即dp[j + 1]。
*/
//动态规划
//http://blog.csdn.net/doc_sgl/article/details/12252443
class s42_dp
{
	public:
		int lenOfPar(string &s)
		{
			int sl = s.size(), maxl = 0;
			if(sl < 2)
				return 0;
			int *dp = new int[sl]();//在数组后面跟一对圆括号，对数组元素做值初始化，且是把数组元素都设置为0。
			for(int i = sl - 2, j = 0; i >= 0; --i)
			{
				if(s[i] == '(')					//从后往前，故这里只用每次考虑(
				{
					j = i + dp[i+1] + 1;		//匹配的 ) 的位置
 					if(j < sl && s[j] == ')')
					{
						dp[i] = dp[i+1] + 2;
						if(j + 1 < sl)			//[(] () [)] ()
							dp[i] += dp[j + 1];//在求得了s[i ... j]的有效匹配长度之后，若j + 1没有越界，则dp[i]的值还要加上从j + 1开始的最长有效匹配，即dp[j + 1]。
					}
				}
				maxl = max(dp[i], maxl);
			}
			return maxl;
		}
};

//不是基础字符处理函数,
//用string类型，网上也多是string类型
class s34
{
	public:
		string addBin(string &a, string &b)
		{
			if(a.empty())
				return b;
			if(b.empty())
				return a;
				
			int al = a.size(), bl = b.size();//字符串求长度，不必用while(*s != '\0')...
			int sum = 0, x = 0, y = 0, up = 0;
			int len = al > bl ? al : bl;
			string sumstr;
			for(int i = len - 1; i >= 0; --i)			
			{
				x = (al >= len - i) ? a[al + i - len] - '0' : 0;
				y = (bl >= len - i) ? b[bl + i - len] - '0' : 0;
				sum = x + y + up;
				up = sum / 2;
				sumstr.insert(sumstr.begin(), '0' + sum % 2);
			}
			if(up == 1)			
				sumstr.insert(sumstr.begin(), '1');
			return sumstr;//因为此处返回不可以是指向局部变量地址的指针，所以addBin函数要定义为string而不是 string&,不然会编译警告
		}
};
//知识点:如上，注意很少用返回引用


class s414
{
	public:
		int CalExpression(vector<string> &str)
		{
			if(str.size() < 1)
				return 0;
			
			stack<int> ss;
			int res = 0;
			for(int i = 0; i < str.size(); ++i)
			{
				if(string("*/+-").find(str[i]) == string::npos)//知识点:字符串搜索
				{
					ss.push( atoi(str[i].c_str()) ); //注意继承自 C 的此类函数需要转换为C的字符串""风格
					continue;
				}
				res = rmTop(ss);	
				if(str[i] == "*")				//string可以直接比较
					res = rmTop(ss) * res;					
				else if(str[i] == "/")
					res = rmTop(ss) / res;					
				else if(str[i] == "+")
					res = rmTop(ss) + res;					
				else if(str[i] == "-")
					res = rmTop(ss) - res;					
				ss.push(res);
			}
			return res;
		}
	private:
		int rmTop(stack<int> &ss)
		{
			if(ss.empty())
				return 0;
			int tmp = ss.top();
			ss.pop();
			return tmp;
		}
};





//http://blog.csdn.net/sbitswc/article/details/36152677
//注意:题目中已经说明是绝对路径
//以/号中间的字符串为单位
class s314
{
	public:
		string simplifyPath(string path) 
		{
			if(path.size() <= 1)
				return path;
			
			vector<string> vec;
			int b = 0;
			while(b < path.size())
			{
				int e = b+1; 							//b=0时为 /，故此处从1开始
				while(e < path.size() && path[e] != '/')//path[e]
					e++;
				string sub = path.substr(b+1, e-b-1);//e-(b+1)+1为长度,上面多了1，这里再减一
				if(sub.length() > 0)
				{
					if(sub == "..")		//考虑:这里也可以是:/..，这样的话最后就不用添加/了
					{
						if(!vec.empty()) 
							vec.pop_back();
					}
					else if(sub != ".")//如果不是.
						vec.push_back(sub);
				}
				b = e;
			}
			
			if(vec.empty()) 
				return "/";
			
			string res;
			for(int i = 0; i < vec.size(); i++)
				res += "/" + vec[i];
			return res;
		}
};

#define __NO__SEE__
#define __NO__SEE__
#define __NO__SEE__

//----------------------------以下暂时忽略-----------------------------------


/*
http://www.cnblogs.com/easonliu/p/3643595.html
http://blog.csdn.net/doc_sgl/article/details/12314555
http://www.2cto.com/kf/201402/277914.html
回文构词法有一个特点：单词里的字母的种类和数目没有改变，
只是改变了字母的排列顺序。

思路：用map<string, int>记录排序后的字符串以及首次出现的位置。
步骤如下： 从strs第一个元素开始遍历，对每一个元素获取其按字典
序排序后的结果String tmp
判断hashmap里是否存在
tmp若不存在，将tmp和该字符串首次出现的下标loc存入hashmap中
若存在，从hashmap里取出该字符串首次出现的下标loc，
将str[loc]和当前字符串str[i]存入结果集中，
并置hashmap关于str[loc]的下标为-1,防止再次存入 
*/
class s313
{
	public:
		vector<string> anagrams(vector<string> &str)
		{
			if(str.size() <= 1)
				return str;
			
			map<string, int> m;
			string s;
			vector<string> res; //错:string res;
			size_t vsize = str.size();	//避免下面多次求解
			for(int i = 0; i < vsize; ++i)
			{
				s = str[i];
				sort(s.begin(), s.end());
				if(m.find(s) == m.end())
					m[s] = i;//只有第一次出现:m[s]才会>0，
				else
				{
					if(m[s] >= 0)//这个字符串(已排序)第一次出现,下面要把它也一并压入
					{
						res.push_back(str[m[s]]);
						m[s] = -1;//将已排序的这一类字符串标记为已存在
					}
					res.push_back(str[i]);//将新出现的同类压入
				}
			}
			return res;
		}
};



class s31
{
	public:
		//如果参数是const char*则在内部 string s(str);之后按照c++来做
		bool isMirror(string s) 
		{	
			if(s.size() <= 1)
				return true;
			
			transform(s.begin(), s.end(), s.begin(), ::tolower);	//::，全局作用域符号，避免与局部变量因为重名而被覆盖。
			string::iterator b = s.begin(), e = s.end() - 1;
			for(; b < e; ++b, --e)								//b == e 时已没必要判断了,所以<
			{
				while(b < e && !::isalnum(*b))					//答案中为if,在多个空格时不能正确处理，此处已改正
					++b;
				while(b < e && !::isalnum(*e))
					--e;
				if(*b != *e)
					return false;
			}
			return true;
		}
};


//中心扩展法
class s35_mirror
{
	public:
		string longestPalindrome(string &s)
		{
			if(s.size() <= 1)//注意此种情况判断
				return s;
			int b, e, len = 0, pos = 0;
			for(int i = 1; i < s.size(); ++i)
			{
				b = i - 1, e = i + 1;
				if(s[i] == s[i + 1])
					e = i + 2;
				while(b >= 0 && e < s.size() && (s[b] == s[e]))
				{
					--b;
					++e;
				}
				if(len < (e - 1) - (b + 1) + 1)//:初始状态b和e指向两个待测验(未必相等)的值,所以这里要各自往回收一步
				{
					pos = b + 1;
					len = (e - 1) - (b + 1) + 1;
				}
			}
			return s.substr(pos, len);
		}
};



//纵向扫描
class s38
{
	public:
		string longestCommonPrefix(vector<string> &str)
		{
			int nvec = str.size();//即vector的size
			if(nvec == 0)
				return "";
			if(nvec == 1)
				return str[0];
			int nmin = str[0].size();
			for(int i = 0; i < nvec; ++i)
			{
				if(str[i].size() < nmin)
					nmin = str[i].size();
			}
			
			int j = 0;
			for(; j < nmin; ++j)//列
			{
				for(int i = 1; i < nvec; ++i)//行
				{
					if(str[i][j] != str[0][j])
						return str[0].substr(0, j);//j:因substr第二个参数表示子串长度，所以本身是匹配到j-1，但长度是j
				}
			}
			return str[0].substr(0, j);//因为这里返回j,所以上面j不可以定义在for中
		}
};




//动态规划
class s35_dp
{
	public:
		string longestPalindrome(string &s)
		{
			int maxLen = 0, maxBeg = 0;
			const int len = s.size();
			if(len <= 1)//注意此种情况判断
				return s;
			bool dp[len][len] = {0};
			//bool (*dp)[len] = new bool[len][len];
//			memset(dp, 0, len*len);//这样之后，下面不用再单独赋值为false了
			for(int i = 0; i < len - 1; ++i)//初始化
			{
				dp[i][i] = true;
				if(s[i] == s[i + 1])
				{
					dp[i][i+1] = true;
					maxBeg  = i;
					maxLen = 2;
				}
					
			}
			dp[len-1][len-1] = true;//上面初始化没有完

			for(int l = 2, j; l <= len; ++l)//字符串长度
			{
				for(int i = 0; i <= len - l; ++i)   //字符串开始处
				{
					j = i + l - 1;//j <= len - 1    //字符串结束处
					if(dp[i+1][j-1] && s[i] == s[j])//dp[i+1][j-1]:子串是否为回文
					{
						dp[i][j] = true;
						maxBeg = i;//这里不必判断l和maxLen，因为l越来越大
						maxLen = l;						
					}
				}
			}
			return s.substr(maxBeg, maxLen);
		}
};
/*
动态二维数组的new、使用
const int len = s.size();
之后，
len在 bool dp[len][len];中可以
在:
bool (*dp)[len] = new bool[len][len];
中不可以，要是常数
*/



//KMP算法
//原理与Algorithm_ .doc文件对应看，一目了然
/*
知识点:
   C++中string参数如何传递
*/
//可以举例:abcabd
class Kmp
{
	public:
		void makeNext(string &P, int *nex)
		{
			int k, len = P.size();//知识点:tmp.size() = tmp.length()
			nex[0] = 0;
			for(int i = 1; i < len; ++i)
			{
				k = nex[i-1];//假设为子串的前缀长度
				while(k != 0 && P[i] != P[k])//循环递归
					k = nex[k-1];
				if(P[i] == P[k])
					nex[i] = k + 1;
				else
					nex[i] = 0;
			}
		}
		
		void kmp(string &T, string &P, int *nex)//string参数传递
		{
			int pl = P.size(), tl = T.size();
			int i, k = 0;
			makeNext(P, nex);
			for(i = 0; i < tl; ++i)
			{
				//精髓:原本在一个i内，还需要一个内循环来逐个比较P[j],现在只需要利用next,简化了操作
				while(k != 0 && P[k] != T[i])//不等时i卡住,patern智能调整滑动窗口位置
					k = nex[k-1];
				if(P[k] == T[i])
					++k;
				if(k == pl)//可以匹配多次, 如果只要首次，在这里return即可
					cout << "match begin at:" << i << endl;
			}
		}
};


class s42
{
	public:
		int lenOfPar(string &s)
		{
			stack<int> ps;

			int maxLen = 0;
			for(int i = 0, len = 0, last = 0; i < s.size(); ++i)
			{
				if( s[i] == '(' )
					ps.push(i);
				else				//是')'
				{
					if(ps.empty())
						last = i;	//ps为空了，需要标记当前位置
					else    		//pop时才需要计算长度
					{
						ps.pop();
						if(ps.empty())
							len = i - last;		//ps又为空了,计算()个数
						else
							len = i - ps.top();//ps不为空，实时更新len
					}
				}
				maxLen = maxLen < len ? len : maxLen;
			}
			return maxLen;
		}
};

#endif



