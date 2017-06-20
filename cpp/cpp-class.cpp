#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <queue>
#include <map>
#include <iostream>
#include <vector>
#include<iomanip>
#include<cstring>
#include <stdexcept>

using namespace std;


namespace ycy_stl
{
	
#define ___String___

//---------------------- string 类 -------------------
//下面的程序并没有把String类的所有成员方法实现，只参考教程写了大部分重要的成员函数。
class String
{
    friend ostream& operator << (ostream&, String&);//重载<<运算符,注意:friend放在这里也行。
	friend istream& operator >> (istream&, String&);//重载>>运算符

public:
    String(const char* str=NULL);                	//复制构造兼默认构造函数(char)
    String(const String &oth);                 	//复制构造函数(String)
    String& operator=(const String& oth);       	//operator=
    String 	operator+(const String &oth)const;  	//operator+
    bool 	operator==(const String&);              //operator==
    char& 	operator[](unsigned int);              	//operator[]
    size_t 	size()	{return strlen(pData);}
    ~String() 		{delete[] pData;}
private:
    char *pData; 				// 用于保存字符串
};

inline String::String(const char* str)   //声明为inline函数，则该函数在程序中被执行时是语句直接替换，而不是被调用
{
	if(!str)
		pData=NULL;      
	else 
	{
		pData=new char[ strlen(str)+1 ];
		strcpy(pData,str);
	}
}

inline String::String(const String &oth)
{
	if(!oth.pData)
		pData=NULL;//在类的成员函数内可以访问同种对象的私有成员（同种类则是友元关系）
	else 
	{
		pData=new char[strlen(oth.pData)+1];
		strcpy(pData,oth.pData);
	}
}

inline String& String::operator=(const String& oth)
{
    if (this != &oth)
    {
        delete[] pData;
        if(!oth.pData) 
			pData=NULL;
        else
        {
            pData = new char[strlen(oth.pData)+1];
            strcpy(pData,oth.pData);
        }
    }
    return *this;
}
inline String String::operator+(const String &oth)const
{
    String ret;
    if(!oth.pData)
        return *this;
    else if(!pData)
        return oth;
    else
    {
        ret.pData = new char[strlen(pData)+strlen(oth.pData)+1];
        strcpy(ret.pData,pData);
        strcat(ret.pData,oth.pData);
		return ret;
    }
}

inline bool String::operator==(const String &s)    
{
    return strcmp(pData,s.pData) ? false : true;
}

inline char& String::operator[](unsigned int e)
{
    if (e<0 && e>=strlen(pData))
		throw runtime_error("empty");  
    return pData[e];
}

ostream& operator<<(ostream& os,String& str)
{
    os << str.pData;
    return os;
}

istream &operator>>( istream &input, String &s )
{
   char temp[ 255 ]; //用于存储输入流
   input>>setw(255)>>temp;	//这样即使你输入超过255个字符，则只取255个字符。 
   s = temp; //使用赋值运算符
   return input; //使用return可以支持连续使用>>运算符
}




#define ___Stack___


//链表实现
//shttp://www.cnblogs.com/liuamin/p/6537831.html
template<typename T>
class Stack
{
					//	friend bool operator==(const stack<T>& x, const stack<T >& y);
public:
    Stack():beg(NULL),count(0) {}
    ~Stack() {clear();}

	size_t 	size() const {return count;}
	bool 	empty() const{return beg == NULL;}
	T& 	 	top();    				//返回栈顶元素
	
    void 	push(const T&);  	//插入操作
    void 	pop();  				//弹出操作
    
    void 	clear();

private:
    struct SNode 		//此处是栈的链式存储结构
    {
        T val;
        SNode* next;
        SNode(const T& val, SNode* nextNode=NULL):val(val),next(nextNode)
        { }
    };
	SNode * beg;   //栈顶指针
    size_t 	count;
};

template<typename T>
T& Stack<T>::top()
{
    if (empty())
    	throw runtime_error("empty");  
    return beg->val;
}

template<typename T>
void Stack<T>::push(const T& node)
{
    beg = new SNode(node, beg);			//头插，所以插入节点的下一节点是beg
    ++count;
}

template<typename T>
void Stack<T>::pop()
{
    if (empty())
		throw runtime_error("empty");  
    SNode* tmp= beg;					//头删
    beg = beg->next;
    delete tmp;
    --count;
}

template<typename T>
void Stack<T>::clear()
{
    while (beg)
    {
        SNode* tmp = beg;
        beg = beg->next;
        delete tmp;
    }
   count = 0;
}



//链式队列
#define ___Queue___

//http://blog.csdn.net/cq361106306/article/details/39640059
//http://www.cnblogs.com/liuamin/p/6547253.html


/**********在队头删除节点，队尾添加节点*************/
/*用单链表实现，在链表尾部插入，链表头删除

queue  beg  ->  ->  -> end
[list head] ->  ->  -> 
*/
template<typename T>
class Queue
{
	
public:
    Queue():beg (NULL), end (NULL), count(0){}
    ~Queue(){ clear(); }

	size_t 	size() const { return count;}
    bool 	empty() const { return beg == NULL;}
    T&  	front();
    const T& front() const;
	const T& back() const;
    void 	clear();
    void 	push(const T & node);
    void 	pop();

	
private:       //也可以直接用来链表list直接构造
    struct QNode
    {
        T val;
        QNode* next;
        QNode(const T& val, QNode* nextnode=NULL) :val(val), next(nextnode)
        { }
    };
    QNode * beg;  //队头指针
    QNode * end;  // 队尾指针
    size_t count;
};

template<typename T>
T& Queue<T>::front()
{
    if (empty())
	    throw runtime_error("empty");  
    return beg->val;
}

template<typename T>
const T& Queue<T>::front() const
{
    if (empty())
    	throw runtime_error("empty");  
    return beg->val;
}

template<typename T>
const T& Queue<T>::back() const
{
    if (empty())
    	throw runtime_error("empty");  
    return end->val;
}

template<typename T>
void Queue<T>::push(const T& val)
{
    if(!beg)
        beg = end = new QNode(val);
    else
    {
		QNode * tmp = new QNode(val);
		end->next = tmp;				//队列，当然只可以 尾插,end
		end = tmp;
    }
    ++count;
}

template<typename T>
void Queue<T>::clear()
{
    while (beg)
    {
        QNode * tmp = beg;
        beg = beg->next;
        delete tmp;
    }
    count = 0;
}

template<typename T>
void Queue<T>::pop()
{
    if (empty())
    	throw runtime_error("empty");  
    QNode * tmp = beg;					//队列，当然只可以 头删
    beg = beg->next;
    delete tmp;
    count--;
}


#define ___List___
//http://blog.csdn.net/s0soul/article/details/45970353
  
template<class T>  
class List  
{  
public:  
    List() { beg = NULL; }  
    ~List(){ clear(); }

    size_t  size();
	bool 	empty() const 	{ return beg == NULL; }
	T& 		front();	
	const T& front() const;
	T& 		back();
	
    void 	push_back(const T&);  		//还有 pop_front、push_front等，这里忽略
    void 	pop_back();  
	
    void 	remove(const T&);  
	void 	reverse();  

    void 	clear();  
	
private:  
	struct LNode  
	{  
	    T val;  
	    LNode* next;  		

	    LNode():val( T() ), next(NULL){}  
	    LNode(const T& d, LNode* n=NULL) :val(d),next(n){}  
	    ~LNode(){}  
	}; 
	
    LNode* beg;  
};  

template<class T>  
size_t List<T>::size()		//求长  
{
	size_t count = 0;

    for(LNode* p = beg; p; p = p->next)	
		++count;
	return count;
}  

template<class T>  
T& List<T>::front() 
{
	if(!beg)
		throw runtime_error("empty"); 	
	return beg->val; 
}

template<class T>  
const T& List<T>::front() const	
{
	if(!beg)
		throw runtime_error("empty"); 		
	return beg->val; 
}

template<class T>  
T& List<T>::back()
{
	LNode* p = beg;
	if(!p)
		throw runtime_error("empty");  				//stl源码里，也不会触发异常
	while(p->next)
		p = p->next;
	return p->val;
}

  
template<class T>  
void List<T>::push_back(const T &x)//尾插  
{
    LNode* tmp = new LNode(x); 
	if(!beg)
		beg = tmp;
	else
	{
		LNode* p = beg;
		while(p->next)
			p = p->next;
		p->next = tmp;
	}
}  
  
template<class T>  
void List<T>::pop_back()			//尾删  
{
	LNode* p = beg;
  	if(!p)
		throw runtime_error("pop_back empty");  
	else if(!p->next)
	{
		delete p;
		beg = NULL;
	}
	else
	{
		while(p->next->next)
			p = p->next;
		
		LNode* tmp = p->next;
		p->next = NULL;
		delete tmp;
	}  
}  
  
template<class T>  
void List<T>::remove(const T &val)	//按值删除  
{  

	LNode preHead;
	LNode *p = &preHead, *tmp;
	p->next = beg;

	while(p && p->next)
	{
		if(p->next->val == val)
		{
			tmp = p->next;
			p->next = p->next->next;
			delete tmp;
		}
		else
			p = p->next;
	}
	beg = preHead.next;    
}  
  

template<class T>  
void List<T>::clear()		//清除  
{  
    if(!beg)
		return;
	
	LNode* tmp = NULL;
	while(beg)
	{
		tmp = beg;
		beg = beg->next;
		delete tmp;
	}
}  
  
template<class T>  
void List<T>::reverse()		//逆序  
{  
	LNode *pre = NULL, *next = NULL;
	while(beg)
	{
		next = beg->next;
		beg->next = pre;
		pre = beg;
		beg = next;
	}
	return pre;
}  
  

}//end ycy_stl namespace


//=======================================================
//-------------------- 转换操作符 -----------------------
//=======================================================
/*
usage:
smallInt si;
si = 4;
if(si)
*/
class smallInt
{
	public:
		smallInt(std::size_t i = 0):val(i)
		{
			if(i < 0 || i > 255)
				std::cout << "out of range!";
		}
		operator int() const{ return val;}		//不可有int , 错误：为‘operator int’指定了返回值
	private:
		std::size_t val;
};



//=======================================================
//---------------------- bitmap大数据 -------------------
//=======================================================
/*
http://www.cnblogs.com/dyllove98/archive/2013/07/26/3217741.html
http://www.cnblogs.com/huangxincheng/archive/2012/12/06/2804756.html
*/
class BitMap
{
	public:
		BitMap(unsigned int n)
		{
			arr = new int[(n>>5) + 1]();	//因为/运算会舍去余数，所以+1
			
		}
		~BitMap()
		{
			delete []arr;
		}
		void set(unsigned int i)
		{
			int arr_pos, bit_pos;
			arr_pos = i >> 5;			//除
			bit_pos = i & 0b11111;		//求余
			arr[arr_pos] |= (1 << bit_pos);
		}
		void clear(unsigned int i)
		{
			int arr_pos, bit_pos;
			arr_pos = i >> 5;
			bit_pos = i & 0b11111;
			arr[arr_pos] &= ~(1 << bit_pos);
		}
		bool isExist(unsigned int i)
		{
			int arr_pos, bit_pos;
			arr_pos = i >> 5;
			bit_pos = i & 0b11111;
			return arr[arr_pos] & (1<< bit_pos);  //错(bool在内存中不一定是用1位来表示的):(bool)(arr[arr_pos] >> bit_pos);
		}
	private:
		int *arr;
};



//=======================================================
//---------------------- hash_map 类 -------------------
//=======================================================
//hash_map的简洁实现
//http://www.cnblogs.com/fanzhidongyzby/p/3317516.html

class SimHash
{
	const int SIZE = 100; //地址链个数(哈希表容量)
	struct Node//地址链节点
	{
	    int key;//键
	    int value;//值
	    Node *nex;//链接指针
	    Node(int k,int v):key(k),value(v),nex(NULL){}
	};
	
    Node **map;//地址链数组
    int hash(int key)//hash函数，除留取余法
    {
        return key%SIZE;
    }
public:
    SimHash()
    {
        map = new Node*[SIZE];
        for(int i=0;i<SIZE;i++)
			map[i]=NULL;			//初始化数组为空
    }
    ~SimHash()
    {
        for(int i=0;i<SIZE;i++)//清除所有节点
        {
            Node*p;
            while((p=map[i]))
            {
                map[i]=p->nex;
                delete p;
            }
        }
        delete[] map;//清除数组
    }
    void insert(int key,int value)
    {
        Node*f=find(key);//插入前查询
        if(f)
        {
            f->value=value;//存在键则覆盖
            return;
        }
        Node*p=map[hash(key)];//确定地址链索引
        Node*q=new Node(key,value);//创建节点
        while(p&&p->nex)
			p=p->nex;//索引到地址链末端
        if(p)
			p->nex=q;//添加节点
        else 
			map[hash(key)]=q;//地址链的第一个节点
    }
    void remove(int key)
    {
        Node*p=map[hash(key)];//确定地址链索引
        Node*q=NULL;//前驱指针
        while(p)
        {
            if(p->key==key)//找到键
            {
                if(q)
					q->nex=p->nex;//删除节点
                else 
					map[hash(key)]=p->nex;//删除地址链的最后一个节点
                delete p;
                break;
            }
            q=p;
            p=p->nex;
        }
    }
    Node* find(int key)
    {
        Node*p=map[hash(key)];//确定地址链索引
        while(p)
        {
            if(p->key==key)
				break;//查询成功
            p=p->nex;
        }
        return p;
    }
};


#include <semaphore.h>
//=======================================================
//---------------------- 读写类 -------------------------
//=======================================================
/*
封装成类
http://bbs.csdn.net/topics/370176102
http://www.cnblogs.com/hnrainll/archive/2011/04/21/2024089.html
http://www.cnblogs.com/sanjin/archive/2012/08/09/2629890.html
*/
class RWQ
{
	public:
		RWQ(){}
		~RWQ(){}
		void enQ(const int val)
		{
			sem_wait(&en);
			sem_wait(&q_mux);
			
			q.push(val);
			
			sem_post(&q_mux);
			sem_post(&de);
			
		}
		void deQ(int& val)
		{
			sem_wait(&de);
			sem_wait(&q_mux);
			
			val = q.front();
			q.pop();
			
			sem_post(&q_mux);
			sem_post(&en);
			
		}
		bool empty() const
		{
			bool ret = false;
			
			sem_wait(&q_mux);
			ret = q.empty();
			sem_post(&q_mux);	
			
			return ret;
		}
		
		static sem_t en;
		static sem_t de;
		static sem_t q_mux;
		
	private:
		static std::queue<int> q;

};

typedef struct
{
	RWQ *p;
	int time;
	int val;
}Arg;

std::queue<int> RWQ::q;				//私有的static也可以在这里定义
sem_t RWQ::en, RWQ::de, RWQ::q_mux;	//在局部(下面的函数中)定义会出错
//sem_t : unsigned int

void *rThread(void *pra)
{
	Arg ar;
	memcpy(&ar, pra, sizeof(Arg));
	
	while(ar.time--)
	{
		(ar.p)->deQ(ar.val);
		sleep(1);
		cout << "rThread" << (unsigned)pthread_self() << " : " << ar.val << endl;
	}
	return ((void *)0);
}

void *wThread(void *pra)
{
	Arg ar;
	memcpy(&ar, pra, sizeof(Arg));
	while(ar.time--)
	{
		(ar.p)->enQ(ar.val);
		sleep(1);
		cout  << "wThread" << (unsigned)pthread_self() << " : "<< ar.val << endl;
	}
	return ((void *)0);
}


void __test_String()
{
    ycy_stl::String str1="Aha!";
    ycy_stl::String str2="My friend";
    ycy_stl::String str3 = str1+str2;
    cout<<str3<<"\n"<< "size:" << str3.size()<<endl;
	cout<<str1[2] << endl;

	//cout 后的表达式要有括号
	cout << (ycy_stl::String("") ==  ycy_stl::String("")) <<endl;
	cout << (ycy_stl::String("1") ==  ycy_stl::String("")) <<endl;
	cout << (ycy_stl::String("1") ==  ycy_stl::String("22")) <<endl;
	cout << (ycy_stl::String("33") ==  ycy_stl::String("33")) <<endl;
	cout << (ycy_stl::String("") ==  ycy_stl::String(NULL)) <<endl;
}

void __test_Stack()
{
    ycy_stl::Stack<int> s;
	cout<<"s.size():"<<s.size() << endl;
	cout<<"s.empty():"<<s.empty() << endl;
    for(int i = 0; i < 5; ++i)
    {
        s.push(i);
    }
	cout<<"s.empty():"<<s.empty() << endl;
	cout<<"s.size():"<<s.size() << endl;
    for(int j = s.size()-1 ; j >= 0; --j)
    {
        cout<< "node: " << s.top() <<endl;
        s.pop();
    }

    s.clear();
    cout<<"s.size():"<<s.size() << endl;
}

void __test_Queue()
{
    ycy_stl::Queue<int> q; //声明队列
    int n = 5;
    for (int i = 0; i<n; i++)
    {
		q.push(i );
		cout << q.front() << "..."  << q.back() << endl;
    }
    cout <<  "q.size():" <<  q.size() << endl;    
    while (!q.empty())
    {
        cout << q.front() << "..."  << q.back() << endl;
        q.pop();
    }
//	cout <<q.back() << endl;
    while (!q.empty())
    {
        q.pop();
    }
    cout << endl;

    for (int i = 0; i<n; i++)
    {
		q.push( i);
		cout << q.front() << "..."  << q.back() << endl;
    }
	q.clear();
	cout <<  "q.size():" <<  q.size() << endl; 
}

void __test_List() 
{  
    ycy_stl::List<int> lst; 
    for (int i = 0; i<5; i++)
    {
		lst.push_back(i );
		cout <<  "lst.size():" <<  lst.size() << endl; 
		cout << lst.front() << "..."  << lst.back() << endl;
    }
    for (int i = 0; i<5; i++)
    {
		lst.pop_back();
		cout <<  "lst.size():" <<  lst.size() << endl; 
    }

    for (int i = 0; i<5; i++)
    {
		lst.push_back(i );
    }
	lst.remove(0);
	cout << lst.front() << "..."  << lst.back() << endl;
	lst.remove(4);
	cout << lst.front() << "..."  << lst.back() << endl;	
}


void __test_RWQ()
{
	const int q_begin_size = 10;	//仓库初始量
	const int q_size = 100;			//仓库容量		
	const int max_obj = 10;  
	

	Arg ar;
	
	pthread_t tid[2 * max_obj] = {0}; 
	RWQ *p[max_obj];
	

    sem_init(&RWQ::en, 0, q_size - q_begin_size);
    sem_init(&RWQ::de, 0, q_begin_size);
    sem_init(&RWQ::q_mux, 0, 1);
    cout << dec << "begin" << endl;
    for(int i = 0; i < max_obj; i++)  
    {  
		p[i] = new RWQ; 
		ar.p = p[i];
		ar.time = 30;
		ar.val = i;

		pthread_create(&tid[2*i], NULL, rThread, (void *)&ar);
		pthread_create(&tid[2*i + 1], NULL, wThread, (void *)&ar);
		
		
    }  
	 cout <<  "create ok" << endl;
	for(int i = 0; i < max_obj; i++)  
    {  
        pthread_join(tid[2*i], NULL);
		pthread_join(tid[2*i + 1], NULL);
    }  
}




//无锁环形队列
//http://blog.csdn.net/chen19870707/article/details/39994303



int main()
{
//	__test_String();
//	__test_Stack();
	__test_Queue();
//	__test_List();
	return 0;
}

#define ___REF___ONLY___
#define ___REF___ONLY___
#define ___REF___ONLY___

namespace q_for_ref
{

template <class T>
class node
{
public:
	node<T>* next;
	T val;
	node():next(NULL),val(){};
	node(T v):next(NULL),val(v){};
};
template <class T>
class Stack
{
public:
	Stack();
	~Stack();
	void Init();
	bool empty();
	size_t size();
    T top();
	void push(const T& e);
    void pop(T& e);
	void display();
private:

	
    node<T>* beg;
    size_t len;
};
template <class T>
Stack<T>::Stack()
{
   beg  = NULL;
   len = 0;
}
template <class T>
Stack<T>::~Stack()
{
	// 析构函数  
	node<T> *next;  
	while (beg) 
	{  
		next =beg->next;  
		delete beg;  
		beg = next;  
	}  
	len = 0;
}
template <class T>
bool Stack<T>::empty()
{
	return len == 0;
}
template <class T>
size_t Stack<T>::size()
{
	return len;
}

template <class T>
T Stack<T>::top()
{
	if(!empty())
		return beg->val;
}

template <class T>
void Stack<T>::push(const T& e)
{
   node<T>* tmp = new node<T>(e);
   if (beg == NULL)
   {
	   beg =tmp;
   }
   else
   {
	   tmp->next = beg;
	   beg = tmp;
   }
   ++len;
}
template <class T>
void Stack<T>::pop(T& e)
{
	if(empty())
		throw runtime_error("empty");  
	e = beg->val;
    if (len ==1)
    {
		beg  = NULL;
    }
	else
	{
        node<T>* tmp = beg;
        beg = beg->next;
		delete tmp;
	}
	--len;
   
}
template <class T>
void Stack<T>::display()
{
   node<T>* pre = beg;
   cout << "The stack is: ";
   while(pre)
   {
	   cout << pre->val << " ";
	   pre = pre->next;
   }
   cout << endl;
}




template <typename T> class Queue;
template <typename T> ostream& operator<<(ostream &os, const Queue<T> &que);
template <typename T>
class QueueItem 
{
    //私有类
    friend class Queue<T>;				//Queue和QeueItem之间一一对应
    friend ostream& operator<< <T> (ostream &os, const Queue<T> &que);
    QueueItem(const T &t):item(t), next(0) {}
    T item;
    QueueItem* next;
};

template <typename T>
class Queue 
{
    friend ostream& operator<< <T> (ostream &os, const Queue<T> &que);
    public:
        Queue():beg(0), end(0) {}
        T front() {return beg->item;}
        const T& front() const {return beg->item;}
        //成员模板.用vector初始化Queue
        template <typename U>
        Queue(U beg, U end);
        //assign函数的实现
        template <typename U>
        void assign(U beg, U end);
        //拷贝构造函数（深拷贝，浅拷贝）
        Queue(const Queue& que):beg(0), end(0) 
        {
            copy_item(que);
        }
        //重载赋值操作符
        Queue<T>& operator=(const Queue<T>&);
        bool empty() 
		{
            return beg == 0;
        }
        void pop();
        void push(const T &t);
        ~Queue() {destroy();}
    private:
        QueueItem<T>* beg;
        QueueItem<T>* end;
        //
        inline void copy_item(const Queue& que);
        inline void destroy() 
		{
            //释放每一个节点
            while(!empty()) pop();
            //beg = end = 0;
        }
        template <typename U>
        inline void copy(U beg, U end) 
        {
            while(beg != end) 
			{
                push(*beg);
                ++beg;
            }
        }
};
template <typename T> void Queue<T>::pop() 
{
    QueueItem<T> *p = beg->next;
    delete beg;
    beg = p;
}
template <typename T> void Queue<T>::push(const T &t) 
{
    QueueItem<T> *q = new QueueItem<T>(t);
    //考虑队列是否为空
    if(empty()) 
		beg = end = q;
    else 
	{
        end->next = q;
        end = q;
    }
}
template <typename T> inline void Queue<T>::copy_item(const Queue &que) 
{
    QueueItem<T> *p;
    for(p=que.beg; p; p=p->next) {
        push(p->item);
    }
}
template <typename T> ostream& operator<<(ostream &os, const Queue<T> &que) 
{
    QueueItem<T> *p;
    os << "< ";
    for(p=que.beg; p; p=p->next) os << p->item << " ";
    os << ">" << endl;
    return os;
}
template <typename T> istream& operator>>(istream &is, Queue<T> que) 
{
    T x;
    while(is >> x) que.push(x);
    return is;
}
//定义成员模板。如用vector初始化Queue
template <typename T> template <typename U>
Queue<T>::Queue(U beg, U end):beg(0), end(0) 
{
    copy(beg, end);
}
//assign函数的实现
template <typename T> template <typename U>
void Queue<T>::assign(U beg, U end) 
{
    destroy();
    copy(beg, end);
}

}//namespace



namespace ycy_nostl
{

//循环队列
#define ___Queue__Circle___

template<typename T>
class Queue
{
public:
    Queue(int maxsize = 10);
    Queue(const Queue<T>& rhs);
    Queue<T>& operator=(const Queue<T>& rhs);
    ~Queue();
public:
    bool 	empty() const;
    bool 	IsFull() const;
    int 	size() const;

    void 	push(const T& val);
    void 	pop();
    T& 		front();
    T   	front() const;
    T& 		back();
    T   	back() const;
	
private:
    T*		array;
    int 	beg;
    int 	end;
    int 	capacity;
};

template<typename T>
Queue<T>::Queue(int maxsize) :beg(0), end(0),capacity(maxsize)
{
    array = new T[maxsize];
	if(array == NULL)
		throw out_of_range("NULL");//存储分配失败则退出;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& rhs) :beg(rhs.beg), end(rhs.end),capacity(rhs.capacity)
{
    array = new T[capacity];
    for (int i = 0; i != (this->size()); i++)
        array[i] = rhs.array[i];
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& rhs)
{
    if (this != &rhs)
    {
        delete[] array;
        capacity = rhs.capacity;
        beg = rhs.beg;
        end = rhs.end;
        array = new T[capacity];
        for (int i = 0; i != (this->size()); i++)
            array[i] = rhs.array[i];
    }
    return *this;
}
template<typename T>
Queue<T>::~Queue()
{
        delete[] array;
}

template<typename T>
bool Queue<T>::empty() const
{
    return beg == end;      //此处为循环队列，当front==rear时为空。
}

template<typename T>
bool Queue<T>::IsFull() const
{
    return(end + 1) % capacity == beg;   //当（rear+1）%capacity==front为满,因为为满时差一个元素，但是可能rear>front,也可能rear<front.
}

template<typename T>
int Queue<T>::size() const
{
    return (end - beg + capacity) % capacity;
}

template<typename T>
void Queue<T>::push(const T& val)
{
    if (!IsFull())
    {
        array[end] = val;
        end = (end + 1) % capacity;
    }
    else                                                  //当队列满了之后可进行扩容
    {
        T *newarray=new T[ 2*capacity ];
        for (int i = 0; i != 2*capacity&&!this->empty(); i++)
        {
            newarray[i] =this-> front();
            this->pop();
        }
        delete [ ] array;
        array = newarray;
        beg = 0;
        array[end] = val;
        end =this->end+1;
        capacity = 2*capacity;
    }
}

template<typename T>
void Queue<T>::pop()
{
    if (!empty())
    {
        //array[beg].~T();   //将队头元素析构掉
        beg = (beg + 1) % capacity;
    }
    else
        cout<<"empty queue!"<<endl;
}

template<typename T>
T& Queue<T>::front()
{
    if (empty())
        cerr << "Error, queue is empty!";
    return array[beg];
}
template<typename T>
T Queue<T>::front() const
{
    if (empty())
        cerr << "Error, queue is empty!";
    return array[beg];
}
template<typename T>
T& Queue<T>::back()
{
    if (empty())
        cerr << "Error, queue is empty!";
    return array[end-1];                             //rear类似与尾后指针
}
template<typename T>
T Queue<T>::back() const
{
    if (empty())
        cerr << "Error, queue is empty!";
    return array[end-1];
}
}

void __test_Queue_circle()
{
    ycy_nostl::Queue<int> q(10); //声明队列
    int n;
    cin >> n;
    for (int i = 0; i<n; i++)
        q.push(i + 1);
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
        if (!q.empty()) //此处需要判断此时队列是否为空
        {
            q.push(q.front());
            q.pop();
        }
    }
    cout << endl;
}

