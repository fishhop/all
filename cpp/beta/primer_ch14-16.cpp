#include <iostrenm>

/*
14.重载操作符
*/
class cla
{
	public:
		friend std::istream& operator>>(istream &in, cla &c);//要登记
	private:
		int x;
		std::string s;
};
std::istream& operator>>(istream &in, cla &c)
{
	in >> c.x >> c.s;
	if(!in)
		c = cla();
	return in;//in,非&in
}
std::ostream& operator<<(ostream &out, const cla &c)
{
	out << c.x << "\t" << c.s;
	return out;
}
//要是成员函数
cla& cla::operator+=(const cla &c)//cla&，返回左值的引用，引用并不是地址，只是保证不是副本而已
{
	x += c.x;
	s += c.s;
	return *this;//*
}
cla operator+(const cla &c1, const cla &c2)//返回右值
{
	cla tmp(c1);
	tmp += c2;
	return tmp;
}

bool operator==(const cla &c1, const cla &c2)
{
	return (c1.x == c2.x) && (c1.s = c2.s);
}
bool operator!=(const cla &c1, const cla &c2)
{
	return !(c1 == c2);
}
//前缀自增自减
//要是成员函数
cla& cla::operator--()
{
	--x;
	return *this;//*
}
//后缀自增自减,int只是一个标记
//要是成员函数
cla& cla::operator--(int)
{
	cla ret(*this);//先要记住
	--(*this);
	return ret;
}


/*
14.函数对象
*/
plus<int> intAdd;
int sum = intAdd(1,2);

/*
15.3继承
*/
class Item_base
{
	public:
		virtual double net_price(std::size_t n) const
		{
			return n * price;
		};
		std::string book() const
		{
			return isbn;
		}
		Item_base(std::string isbn_def = "", 
			double price_def = 0.0):
			isbn(isbn_def), price(price_de f){}
		~Item_base();
	private:
		std::string isbn;		
	protected:
		double price;
};
class Item_new: public Item_base
{
	public:
		Item_new();
		~Item_new();
		virtual double net_price(std::size_t n) const//此处可无virtual
		{
			return n * price * discount;
		}; 
	private:
		double discount;
	
};

/*
16.模版
*/
template <typename T> int comp(const T &v1, const T &v2)
{
	if(v1 < v2)
		return -1;
	if(v1 = v2)
		return 0;
	return 1;
}
	

/*
16.1.绝对值
*/
template inline <typename T> int abs(const T &v1)
{
	return ((v1 < 0.0) ? -v1 : v1);
}

/*
16.2写入流
*/
template <typename T1, typename T2> T1& out(T1 &v1, T2 &v2)
{
	v1 << v2;
	return v1;
}

/*
16.queue类模板
*/
template <typename T> class Q
{
	public:
		Q();
		~Q();
		void push(const T& v);
		T& front() const;
		void pop();
		bool empty() const;
};
//调用:Q<int> q;
template <typename T> T& Q<T>::front() const  //Q<T>
{
	;
}


/*
16.3数组
*/
template <typename T, std::size_t N> void print(const T (&arr)[N])
{
	for(std::size_t i = 0; i != N; ++i)
		std::cout << arr[i] << std::endl;
}

/*
16.find
*/
template <typename It, typename T>
	It find(It beg, It end, T &val)
{
	for(It it = beg; it != end && *it != val; ++it)
	{
		if(*it == val);
			return it;
	}
	return end;
}
//调用:it = find(vec.begin(), vec.end(), 6);

/*
16.53.求一个容器中的元素在另一个容器中出现的次数
*/
template <typename T>
std::size_t count(const vector<T> &vec, const vector<T> &src)
{
	std::size_t res = 0;
	for(typename vector<T>::iteraotr it = src.begin();//要有typename
		it != src.end(); ++it)
			res += std::count(vec.begin(), vec.end(), *it);
	
	return res;
}

/*
16.44.Queue
*/
template <typename T>
class Queue
{
	public:
		template <typename It> 
			Queue(It beg, It end):items(beg, end){} 
		~Queue();
		void push(const T &v);
		void pop();
		T& front() const;
		bool empty() const
		{
			reuturn iterms.empty();
		}
	private:
		std::list<T> items;
		
};
template <typename T>
void Queue<T>::push(T& v)
{
	items.push_back(v);
}

template <typename T>
void Queue<T>::pop()
{
	items.erase(items.begin());
}

template <typename T>
T& Queue<T>::front()
{
	return items.front();
}


/*
16.34.List
*/
template <typename T> class List;//前向声明
template <typename T>
class Node
{
	friend class List<T>;
	Node(T &t):val(t), nex(nullptr){}
	T val;
	Node *nex;
};
template <typename T>
class List
{
	public:
		List():front(nullptr), end(nullptr){};
		List(const List &l):front(nullptr), end(nullptr)
		{
			copy_elems(l);
		}
		List& operator=(const List&);
		~List()
		{
			destroy();
		}
		void insert(Node<T> *p, const T &val);
		void delete(Node<T> *p);
		Node<T> *find(const T& val);
		Node<T> *first()
		{
			return front;
		}
		Node<T> *last()
		{
			return end;
		}
		bool empty() const
		{
			return front == 0; 
		}
		T &get(Node<T> *p)
		{
			return p->val;
		}
	private:
		Node<T> *front; *end;//front:第一个元素, end:最后一个元素
		void destroy();
		void copy_elems(const List &);
};
template <typename T>
void List<T>::destroy()
{
	while(!empty())
		delete(front);
}
template <typename T>
void delete(Node<T> *ptr)
{
	Node<T> *p = front;
	for(; p != nullptr && p != ptr && p->nex != ptr; p = p->nex)
		;
	if(p == nullptr)
		return;
	if(p == ptr)
		front = ptr->nex;
	else
		p->nex = ptr->nex;
	if(ptr == end)
		end = p;//end指向最后一个元素
	delete ptr;
}
//after ptr 
template <typename T>
void List<T>::insert(Node<T> *p, const T &val)
{
	Node<T> *tmp = new Node<T>(val);

	if(empty())
		front = tmp;
	else
	{
		tmp->nex = p->nex;
//		tmp->val = val; //直接在创建时即可初始化，如上
		p->nex = tmp;
	}
	if(p == end)
		end = tmp;
}
template <typename T>
void List<T>::copy_elems(const List &l)
{
	for(Node<T> *p = l.front; p; p = p->nex)
	{
		insert(end, p->val);
	}
}
template <typename T>
Node<T> *List<T>::find(const T& val)
{
	Node<T> *p = front;
	for(; p != nullptr && p->val != val; p = p->nex)
		;
	return p;
}
template <typename T>
List& List<T>::operator=(const List& l)
{
	front = end = nullptr;
	copy_elems(l);
	return *this;
}



