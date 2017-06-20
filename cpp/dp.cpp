#include <iostream>

using namespace std;


//Scott Meyer在《Effective C++》item 4


//Scott Meyer在《Effective C++》中提到的 单例模式
//单实例，参见:dp_creational.doc
class Singleton
{
	public:
		static Singleton &getInstance()
		{
			//lock(); 					//为了线程安全，c++11不需要
			static Singleton instance;
			//unlock(); 				//c++11不需要
			return instance;
		}
	private:
		Singleton(){}							//必须这样实现,不然上面static Singleton instance; 就会出错
		~Singleton(){}							//必须这样实现
		Singleton(const Singleton &);			//不需要实现
		Singleton &operator=(const Singleton &);//不需要实现
};


/*
1. 如果要通过该实例返回的是指针而不是引用:
		static CSingleton * getInstance()
		{
			static CSingleton instance;//局部静态变量
			return &instance;
		}
2. 考虑Singleton 可以继承时，需要将构造函数等声明为 protected
*/

void test_singleton()
{
	
	Singleton &obj1 = Singleton::getInstance();	//这里不可以是Singleton obj1 = ,因为copy构造函数为私有
	Singleton &obj2 = Singleton::getInstance();

	if(&obj1 == &obj2)	//判断两个对象的地址，因为没有定义对象的==操作符，无法直接判断obj1和obj2相等
		cout << "same!" << endl;
}


//懒汉式，直到用到时，才实例化
#if defined SINGLETON_LANHAN
//最好使用模版
class Singleton
{
	public:
		static Singleton* getInstance()
		{
//			lock();			//多线程下
			if(!instance)
				instance = new Singleton();
//			unlock();		//多线程下
			
			return instance;
		}
	private:
		static Singleton *instance = NULL;
		Singleton(){}
		~Singleton(){}
		Singleton(Singleton &);
		Singleton & operator=(Singleton &);
};
#endif


#if defined SINGLETON_TEMPLATE

template <class T>
class Singleton
{
	public:
		static inline T& getInstance()
		{
			static T instance;
			return instance;
		}
	private:
		Singleton(){}
		Singleton(const Singleton<T>& );
		Singleton<T>& operator=(const Singleton<T>& );
		~Singleton(){}
		
};

#endif



//MS金典 MP65 中说:单例，工厂
//简单工厂模式，实现四则运算
//BTDP P30
class Operation
{
	public:
		Operation(double n1, double n2):numA(n1),numB(n2)
		{}
		virtual double getRes() const{return 0;}		//若不加 "const = 0;"，则报错:对‘vtable for Operation’未定义的引用
	protected:
		double numA = 0;
		double numB = 0;
};
class OperationAdd:public Operation
{
	public:
		OperationAdd(double n1, double n2):Operation(n1, n2)
		{}
		double getRes() const
		{
			return numA + numB;
		}
};
class OperationSub: public Operation
{
	public:
		OperationSub(double n1, double n2):Operation(n1, n2)
		{}		
		double getRes() const
		{
			return numA - numB;
		}
};
class OperationFactory
{
	public:
		static Operation* createOperate(double n1, double n2, char s)
		{
			switch(s)			//不可以是字符串，如: "+"
			{
				case '+':
					return new OperationAdd(n1, n2);
					break;
				case '-':
					return new OperationSub(n1, n2);
					break;
			}
			return NULL;
		}
};
void __test_OperationFactory()
{
	Operation *oper = OperationFactory::createOperate(2, 1, '+');
	cout << (*oper).getRes() ;
}


//简单工厂模式，实现超市收费系统
//BTDP P43










int main()
{
//	test_singleton();
	__test_OperationFactory();

	return 0;
}




