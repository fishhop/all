#include <iostream>
#include <vector>
#include <bitset>
#include <list>
#include <set>
#include <map>
#include <cstdlib>
#include <cstring>
#include "stdio.h"
using namespace std;

class MyCls1 //类名一般首字母大写
{
	public:
		string findNm() const;
		string findAd() const;

		MyCls1(const string &name, const string &addr):
		nm(name),ad(addr){ }		//const
		
	private:
		string nm;
		string ad;
		
}; //勿丢;


class MyCls2
{
	public:
		typedef string::size_type size;
		MyCls2(size h, size w, const string &str);

		MyCls2 &set(char);
		MyCls2 &move(size, size);
		MyCls2 &disp(ostream &os);
		
	private:
		string str;
		size h;
		size w;
		size curs;
	
};


class Msg;
class Fdr
{
	public:
		Fdr(){}
		Fdr(const Fdr&);  
		Fdr & operator=(const Fdr&);
		~Fdr();

		//在指定的msg的目录集合中增删foder
		void save(Msg &);//因为要删除原值中的一部分，所以用引用
		void rm(Msg &);

		//在当前目录中增加删除消息
		void addMsg(Msg *);
		void rmMsg(Msg *);
	private:
		set<Msg *> msgs;
		void add_fdr_to_msg(const set<Msg *> &rhs);
		void rm_fdr_from_msg();

};

class Msg
{
	public:
		Msg(){}
		Msg(const Msg &);
		Msg &operator=(const Msg &);
		~Msg();

		void save(Fdr &);
		void rm(Fdr &);

		void addFdr(Fdr *);
		void rmFdr(Fdr *);		
	private:
		std::string contents;
		set<Fdr *> fdrs;
		void add_msg_to_fdr(const set<Fdr *> &rhs);
		void rm_msg_from_fdr();				
};


class Item_base
{
	public:
		Item_base(const string &ibn="",
					const double prc=0.0):
					isbn(ibn), price(prc){};

		string book() const //注意此处const
		{
			return isbn;
		}

		//size_t:,size_type主要用于vector、string等
		virtual double net_price(size_t n) const
		{
			return n*price;
		}
		
		virtual ~Item_base();
		
	private:
		string isbn;
		
	protected:
		double price;
};

template <typename T> int _my_comp(const T &v1, const T &v2);

int my_comp(int argc, char *argv[]);

//类模版
template <class Type> class my_list		//class = typename
{
	public:
		my_list();
		my_list(const my_list &);
		my_list operator=(const my_list &);
		~my_list();
		void insert(Type *p, Type v);
		void del(Type *p);
		Type *find(const Type &v);
		Type &get(Type *p);
		bool is_empty() const; //bool
	private:
		
};//勿丢;


template <class Type> class QueueItem
{
	QueueItem(const Type &t);
	Type item;
	QueueItem *nex;
};

template <class Type> class Queue
{
	public:
		Queue(): head(NULL), tail(NULL){}
		~Queue(){destroy();}
		Type &front(){return head->item;}
		const Type &front() const {return head->item;}
		void push(const Type &t);
		void pop();
		bool empty() const{return head == NULL;}
	private:
		QueueItem<Type> * head; //Type 勿丢
		QueueItem<Type> * tail;
		void destroy();
		void copy_elems(const Queue &);
};

struct myS1
{
	int num;
	char name[10];
	double score;
};

typedef struct
{
	int num;
	char name[10];
	double score;
	
} myS2;

union myU
{
	int a;
	double b;
	char c;
	short d;
};

enum myEnum
{
	//这里是,竟然错写
	FIRST, 
	SEC,
	THR
};

int myIterater()
{
	vector<int> vec(10);

	for(vector<int>::iterator it = vec.begin();
		it != vec.end();it++)
		*it = 0;

	return 0;
}

int myVector()
{
	vector<string> vec(10,"hh");

	for(vector<string>::iterator it = vec.begin();
		it != vec.end();it++)
		{
			*it = "y";
			cout << *it << endl;
		}
	vec.push_back("z");
	cout << vec.size() << endl;
	
	return 0;
}

vector<int>::const_iterator _find_val (
	vector<int>::const_iterator beg,
	vector<int>::const_iterator end,
	int val,
	int &num)
{

	vector<int>::const_iterator res_iter = end;

	for(; beg!=end; ++beg)
	{
		if(val == *beg)
		{
			if(res_iter == end)
			{
				res_iter = beg;
			}

			++num;

		}

	}

	return res_iter;
	
}



void find_val_vector (void )
{
	vector<int> vec(10);
	int num = 0;
	
	vec[1] = 3;
	vec[4] = 5;

	_find_val(vec.begin(), vec.end(), 3, num);

	cout << num << endl;
	
	return;
}

int myBitset()
{
	bitset<32> b1(0xff);
	bitset<128> b2(0xff);

	//置位
	unsigned int bitnum = 0;
	bitnum |= 1UL << 27;
	
	cout << b1.any() << endl;
	
	for(size_t i=0; i != b1.size(); i++)
		b1.set(i);

	cout << b1.any() << endl;
		
	cout << b1 << endl << b2 << endl;
	
	return 0;
}

int myNewDelete()
{
	int *p = new int[10]();
	string *ps = new string();
	const int * pconst = new const int();
	
	for(int *i=p, j=0; i != p+10; ++i,++j)
	{
		*i = j;
		cout << *i << endl;
	}

	delete []p;
	p = NULL; //无丢
	
	return 0;
}


int myTry()
{
	bitset<100> bs;
	
	for(size_t i = 0; i!=bs.size(); ++i)
	{
		bs[i]=1;
	}

#if 0
	try
	{
		bs.to_ulong();
	}
	catch(runtime_error err)//from C++ primer但是编译不过
	{
		cout << err.what() << endl;
	}
#endif

	return 0;
}



int _myRefPramOfFunc(int &v1, int &v2)
{
	int tmp;

	tmp = v1;
	v1 = v2;
	v2 = tmp;

	return 0;
}
int &_myRef(int &v1, int &v2)
{

	return ((v1 < v2)? v1 : v2);//注意，函数类型为引用(&)， 返回时和传递参数时也一样! 返回int就好!!
}
int myRefPramOfFunc()
{

	int v1=0, v2=0;
	int min=0;
	int &tmpv1 = v1;

	++tmpv1;
	cout << tmpv1 << endl;
	
	cin >> v1 >> v2;

	_myRefPramOfFunc(v1, v2);	//注意，此处传 v1,v2就好! 不像指针

	min = _myRef(v1, v2);

	cout << min << endl;
//	_myRefPramOfFunc(v1, v2);	//注意，此处传 v1,v2就好!，不像指针

	cout << v1 << " "<< v2 <<endl;

	return 0;
}


//指向函数的指针
string _myPtrOfFunc(string s1, string s2)
{

	return s1+s2;//要有一个是string类型
}
int myPtrOfFunc()
{
	typedef string (*myStrCat)(string s1, string s2);

	myStrCat p1 = _myPtrOfFunc;

	cout << p1("I am", " the king!") << endl;
	
	return 0;
}


int myListContainer()
{
	list<int> L1(10, 2);
	list<int>::iterator it = L1.begin(),
						iter1 = L1.end();
	
	int i = 0;
	
	for(;it != iter1; ++it)
	{
		*it = ++i;
	}

	it = L1.begin();

	while(it != iter1)
	{
		cout << *(--iter1) << endl;
	}

	return 0;
	
}


int myMap()
{
	map<string, int> wdCnt;

	//注意:不可以在此处定义it，移到wdCnt赋值之后，就好了
//	map<string, int>::const_iterator it = wdCnt.begin();
	string key;
	int val=0;

	while(cin >> key && key!="!")
	{
		++(wdCnt[key]);

	}
	
	map<string, int>::const_iterator it = wdCnt.begin();

//	cout << wdCnt.count("aa") << endl;

//	for(map<string, int>::const_iterator it = wdCnt.begin();
//		it!=wdCnt.end();
//		++it)
//		{
//			cout << it->first << " " << it->second << endl;
//			
//		}

	
	while(it != wdCnt.end())
	{
		cout << it->first << " " << it->second << endl;
		++it;
				
	}
	cout << "part 1 finished" << endl;
	
	while(cin >>key >> val && key!="!")
	{
		wdCnt[key] = val;
		it++;
	}
	
	return 0;	
}


string MyCls1::findNm()const
{
	return nm;
}

string MyCls1::findAd()const
{
	return ad;
}


MyCls2::MyCls2(size hv, size wv, const string &strv):str(strv), h(hv), w(wv),curs(0)
{
}

MyCls2 &MyCls2::set(char c)
{
	str[curs] = c;	
	return *this;
}
MyCls2 &MyCls2::move(size r, size c)
{
	size row = r * w;
	curs = row + c;
	
	return *this;
}
MyCls2 &MyCls2::disp(ostream &os)
{
	os << str;
	return *this;
}

int myCls2Main()
{
	MyCls2 cls(5, 6, "aaaaa\naaaaa\naaaaa\naaaaa\naaaaa\naaaaa\n");

	cls.move(3, 1).set('#').disp(cout); //每个都会返回MyCls2对象
	
	return 0;
}


/////////// foder /////////

Fdr::Fdr(const Fdr &f):msgs(f.msgs)
{
	add_fdr_to_msg(msgs);
}

void Fdr::add_fdr_to_msg(const set<Msg *> &rhs)
{
	for(set<Msg *>::const_iterator beg = rhs.begin();
		beg != rhs.end();
		++beg)
		{
			(*beg)->addFdr(this);
		}
}

void Fdr::rm_fdr_from_msg()
{
	for(set<Msg *>::const_iterator beg = msgs.begin();
		beg != msgs.end();
		++beg)
		{
			(*beg)->rmFdr(this);
		}

}

Fdr &Fdr::operator=(const Fdr &rhs)
{
	if(this != &rhs)
	{
		rm_fdr_from_msg();
		msgs = rhs.msgs;
		add_fdr_to_msg( rhs.msgs);//注意,此处用msgs和rhs.msgs不同，要是const
	}
	return *this;
	
}

Fdr::~Fdr()
{
	rm_fdr_from_msg();
}

void Fdr::save(Msg &m)
{
	addMsg(&m);
	m.addFdr(this);
}

void Fdr::rm(Msg &m)
{
	rmMsg(&m);
	m.rmFdr(this);
}

void Fdr::addMsg(Msg *m)
{
	msgs.insert(m);
}

void Fdr::rmMsg(Msg *m)
{
	msgs.erase(m);
}

////////////  msg  ///////////////

Msg::Msg(const Msg &m):
	contents(m.contents),fdrs(m.fdrs)
{
	add_msg_to_fdr(m.fdrs);
}

void Msg::add_msg_to_fdr(const set<Fdr *> &rhs)
{
	for(set<Fdr *>::const_iterator beg = rhs.begin();
		beg != rhs.end();
		++beg)
		{
			(*beg)->addMsg(this);
		}
}

Msg& Msg::operator=(const Msg &rhs)
{
	if(&rhs != this)
	{
		rm_msg_from_fdr();
		contents = rhs.contents;
		fdrs = rhs.fdrs;
		add_msg_to_fdr(rhs.fdrs);
	}

	return *this;
}

void Msg::rm_msg_from_fdr()
{
	for(set<Fdr *>::const_iterator beg = fdrs.begin();
		beg != fdrs.end();
		++beg)
		{
			(*beg)->rmMsg(this);
		}
}


void Msg::save(Fdr &f)
{
	addFdr(&f);
	f.addMsg(this);
}

void Msg::rm(Fdr &f)
{
	rmFdr(&f);
	f.rmMsg(this);
}

void Msg::addFdr(Fdr *f)
{
	fdrs.insert(f);
}

void Msg::rmFdr(Fdr *f)
{
	fdrs.erase(f);
}

Msg::~Msg()
{
	rm_msg_from_fdr();
}

template <typename T> void print(const T & t)
{
	typename T::const_iterator it;
	for(it = t.begin();
		it != t.end();
		++it)
		{
			cout << *it << endl;
		}
	
}


template <class Type> void Queue<Type>::destroy() //注意:Queue<Type>::destroy
{
	while(!empty())
	{
		pop();
	}
}

template <class Type> ostream &operator<<(ostream &os, const Queue<Type>&p)
{
	QueueItem<Type> *q = NULL;
	
	for(q = p.head;
		q ;
		q = q->nex)
		{
			os << q->item << " ";
		}

	return os;
}



template <typename T> int _my_comp(const T &v1, const T &v2) 
{
	if(v1 < v2)
	{
		return -1;
	}
	
	if(v2 < v1)
	{
		return 1;
	}

	return 0;
	
}

int my_comp(int argc, char *argv[])
{
	if(argc != 3)
	{
		cerr << "parm err" << endl;
		return EXIT_FAILURE;
	}
	
	int ret = 0;
	
	ret = _my_comp(atoi(argv[1]), atoi(argv[2]));
//	ret = _my_comp(2, 3);
	cout << atoi(argv[1]) << atoi(argv[2]) << endl;
	cout << ret << endl;

	//下面这种以字符串的形式调用，不能正确处理。
//	ret = _my_comp("hi", "hello");
	
	string s1="hi", s2="hello";
	ret = _my_comp(s1, s2);
	cout << ret << endl;

	return 0;
}


//二维数组
void twoDimArr()
{
	#define TWO_DIM_ARR_ROW 5
	#define TWO_DIM_ARR_COL 4
	
	int a[TWO_DIM_ARR_ROW][TWO_DIM_ARR_COL] = {0};
	int i = 0, j = 0;
	
	for(i = 0; i < TWO_DIM_ARR_ROW; ++i)
	{
		for(j = 0; j < TWO_DIM_ARR_COL; ++j)
		{
			a[i][j] = i + j;
		}
	}

	return;
}

//二维数组
void twoDimArr_ptr()
{
	#define TWO_DIM_ARR_ROW 5
	#define TWO_DIM_ARR_COL 4
	
	int a[TWO_DIM_ARR_ROW][TWO_DIM_ARR_COL] = {0};
	int *p = NULL;

	//注意:下面要 -1，因为数组的下标从0开始
	//下面 p = &a 也是不行的，GCC:不能在赋值时将‘int (*)[5][4]’转换为‘int*’
	for(p = &a[0][0]; p <= &a[TWO_DIM_ARR_ROW - 1][TWO_DIM_ARR_COL - 1]; ++p)
	{
		*p = p - &a[0][0];
		cout << *p << endl;
	}
	
	//a[i] = &a[i][0]
	int i = 0;
	for(p = a[0]; p <= a[TWO_DIM_ARR_ROW - 1] + TWO_DIM_ARR_COL - 1; ++p)
	{
		*p = p - a[0];
		cout << *p << endl;
	}
	
	
	return;
}

void union_struct_enum()
{
	myU u;
	struct myS1 s1;
	myS2 s2;
	enum myEnum e;
	
	u.c = 'a';
	u.b = 5/2;

	//笑话，下面这怎么行!
	//s1.name = "morgan";
	
	strcpy(s1.name, "morgan");
	
	s1.num = 2;

	e = SEC;

	//enum从0开始计数
	cout << e << endl;
	//sizeof(u)是union中最大的那个类型的空间，即double
	cout << sizeof(u)<< " " << u.b << " " << u.c << endl;
	cout << sizeof(s1)<< " "  <<s1.name << " " << s1.num<< endl;
	
}

void all(void)
{
	int a = 2;
	char c = 'a';

	//c要用()括起来
	a = static_cast<int>(c); 
	cout << a << c << endl;

	int i = 5;
	do
	{
		cout << i << endl;	
		
	}while(--i);


	return;
}

void _arr_ref(int (&arr)[10])
{
	cout << arr[2] << endl;
	arr[2] = 22;
	cout << sizeof(arr) << endl;
	cout << arr[2] << endl;

}

//函数参数传递: 数组的引用
void arr_ref()
{
	//不可以使用直接初始化:
//	int arr[](10, 1);

	int arr[10] = {0};

	//arr就好，没有多余的&号,同int等变量的情况
	_arr_ref( arr);
}


void _test_sizeof(char p3[10])
{
	cout << __func__ << ": "<< sizeof(p3) << endl;
}
void _test_sizeof_ref(char (&p3)[10])
{
	cout << __func__ << ": " << sizeof(p3) << endl;
}
void test_sizeof()
{
	char a[10] = {};
	cout << __func__ << " a[10] : " << sizeof(a) << endl;	

	
	char *p1 = new char[10];
	cout << __func__ << " *p1 = new char[10]: " << sizeof(*p1) << endl;	
	cout << __func__ << " *p1 = new char[10]:: " << sizeof(p1) << endl;

	
	char p2[] = "abcde";
	cout << __func__ << " p2[] = : " << sizeof(p2) << endl;


	char str[10] = "abcde";
	cout << __func__ << " str[10] =: " << sizeof(str) << endl;


	char *pstr = "abcde";
	cout << __func__ << " *pstr =: " << sizeof(pstr) << endl;


	
	char p3[10] = {};
	_test_sizeof(p3);
	_test_sizeof_ref(p3);
	
}
/*
test_sizeof a[10] : 10
test_sizeof *p1 = new char[10]: 1
test_sizeof *p1 = new char[10]:: 4
test_sizeof p2[] = : 6
test_sizeof str[10] =: 10
test_sizeof *pstr =: 4
_test_sizeof: 4
_test_sizeof_ref: 10

*/

void test_sizeof_str()
{
	cout << "sizeof(\"\"):" << sizeof("") << endl;
	cout << "strlen(\"\"):" <<  strlen("") << endl;
	cout << "sizeof(\"\\0\"):" <<  sizeof("\0") << endl;	
	cout << "strlen(\"\\0\"):" <<  strlen("\0") << endl;
	cout << "sizeof(\'\\0\'):" <<  sizeof('\0') << endl;	
}
/*
sizeof(""):1
strlen(""):0
sizeof("\0"):2
strlen("\0"):0
sizeof('\0'):1

*/
class s1
{
	public:
		int a;
		string b;
		void test()
		{
			int c;
			vector<int> d;
		}
	private:
		int e;
		int f;
};
class s2//空类也至少是1个字节
{
	public:
		void test()
		{
			int c;
			vector<int> d;
		}
	private:

};
class s3
{
	public:
		int a;
		void test()
		{
			int c;
			vector<int> d;
		}
	private:

};
void test_sizeof_class()
{
	s1 ss1;
	cout << "ss1: " << sizeof(ss1) << endl;

	s2 ss2;
	cout << "ss2: " << sizeof(ss2) << endl;

	s3 ss3;
	cout << "ss3: " << sizeof(ss3) << endl;


	vector <int> v;
	cout << " v: " << sizeof(v) << endl;
	vector <int>::iterator it = v.begin();
	v.insert(it, 10, 10);

	v.push_back(1);
	cout << " v: " << sizeof(v) << endl;

	string str;
	cout << " str: " << sizeof(str) << endl;	


	map<int, string> m;
	cout << " m: " << sizeof(m) << endl;	
	
}
/*
ss1: 16
ss2: 1
ss3: 4
 v: 12
 v: 12
 str: 4
 m: 24

*/

void general()
{
	3*3;			//警告：语句不起作用 [-Wunused-value]
}

int main()
{


	cout << 10 << endl; //因为上面用hex将 cout设置为16进制，所以这个文件内都是16进制了
	return 0;
}
