#include <iostrenm>

/*
12.34.两个cla类相加
*/
cla add(const cla &c1, const cla &c2)
{
	cla tmp;
	tmp.x = c1.x + c2.x;
	tmp.s = c1.s + c2.s;
	return tmp;
}
class cla
{
	public:
		friend cla add(int a, int b);//要登记
	private:
		int x;
		std::string s;
};


/*
12.35.一个非成员函数，读取istream并存到cla中
*/
istream &read(istream &is, cla &c)
{
	is >> c.x >> c.s;
	if(!is)
		c = cla();//重置
	return is;
}
class cla
{
	public:
		friend istream &read(istream &is, cla &c);//要登记
		cla();
//		cla(int num = 1);//不可以的，这样和上面那个没法重载了
		~cla();
	private:
		int x;
		std::string s;
};

/*
12.38.
*/
class Foo
{
	public:
		Foo(int i):x(i){}
		int get()
		{
			return x;
		};
	private:
		int x;
};

/*
12.40.
*/
//1.h中
class Bar
{
	public:
		Foo callsFooVal()
		{
			++callsFooVal;
			return fval;
		}
	private:
		const static int val = 20;
		static Foo fval;
		static int callsFooVal;
};
//1.cpp中
#include "1.h"
Bar::fval(1); //要在类定义体外部初始化


/*
13.4.复制构造函数
*/
class NoName
{
	public:
		NoName():pstring(new std::string), i(0),d(0){}
		NoName(const NoName &other)
		{
			 pstring = new std::string;
			 *pstring = *(other.pstring);
			 i = other.i;
			 d = other.d;
		}
	private:
		std::string *pstring;
		int i;
		double d;
};

/*
13.9.复制构造函数
*/
class NoName
{
	public:
		NoName():pstring(new std::string), i(0),d(0){}
		NoName &operator=(const NoName &other)
		{
			if(&other == this)
				return *this;
			 pstring = new std::string;
			 *pstring = *(other.pstring);
			 i = other.i;
			 d = other.d;
			 return *this;
		}
	private:
		std::string *pstring;
		int i;
		double d;
};

/*
13.12.析构函数
*/
class NoName
{
	public:
		NoName():pstring(new std::string), i(0),d(0){}
		~NoName()
		{
			delete pstring;
		}
	private:
		std::string *pstring;
		int i;
		double d;
};


/*
13.24.智能指针
*/



/*
13.28.复制构造函数，析构函数
*/
class TreeNode
{
	public:
		TreeNode();
		TreeNode(const TreeNode &t);
		{
			value = t.value;
			count = t.count;
			if(t.pre)
			{
				pre = new TreeNode(*(t.pre));//技巧，不用下面那样

				//pre = new TreeNode;
				//*pre = *(t.pre);
			}
			else
				pre = nullptr;

			nex = t.nex ? TreeNode(*(t.nex)) : nullptr
		}
		~TreeNode()
		{
			delete pre;
			delete nex;
			
		};
	private:
		std::string value;
		int count;
		TreeNode *pre;
		TreeNode *nex;

};




