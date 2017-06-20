#ifndef PART2_H
#define PART2_H

#include <iostream>
using namespace std;
typedef struct node
{
	int val;
	struct node *nex;
}Node;

//前后脚摸石头过河,前脚每次一步往前走,
//若值一样，后脚不动；若不一样，则后脚先迈一步，再接值
class s211
{
	public:
		int rmDuplicate(int *a, int n)
		{
			if(!a)
				return 0;
			if(n < 2)
				return n;
			
			int pre = 0;
			for(int cur = 1; cur < n; ++cur)
			{
				if(a[pre] != a[cur])
					a[++pre] = a[cur];	//以2个相等的元素为例，这里pre=i
			}
			return pre + 1;			//返回新数组长度
		}
};

//按照自己的思路来
class s212
{
	public:
		int rmDuplicate(int *a, int n)
		{
			if(!a)
				return 0;			
 			if(n < 3)		 
 				return n;
			
			int pre = 0;
			for(int cur = 1; cur < n; ++cur)
			{
				if(a[pre] == a[cur])
				{
					++pre;
					++cur;
					while(cur < n && a[pre] == a[cur])//吸星大法
						++cur;
					if(cur == n)
						break;		//跳出for循环
				}
				a[++pre] = a[cur];	//在if外，因为上面211题是!=
			}
			return pre + 1;
		}
};

//一半一半地缩小搜索范围
class s213
{
	public:
		int searchRotedArr(int *a, int len, int t)
		{
			if(!a || !len)
				return -1;
			if(len == 1)
				return a[0]==t ? 0 : -1;
			
			int b = 0, e = len-1, m;
			while(b < e)
			{
				m = (e + b) / 2;
				if(t == a[m])		//此处等于，下面不可能=
					return m;
				if(a[b] < a[m])		//转折点在右边部分，这样左边部分是升序排列的
				{
					if(a[b] <= t && t < a[m])//满足这个条件就进入了没有转折点、全部都是升序的序列
						e = m - 1;
					else
						b = m + 1; //此处 +1，因为上面的if有 =
				}
				else		//这里表示转折点在左边,右边是纯升序
				{
					if(a[m] < t && t <= a[e])
						b = m + 1;
					else
						e = m - 1;
				}
			}
			return -1;
		}
};

//?号表达式简化代码
class s221
{
	public:
		Node *add2Num(Node *a, Node *b)
		{
			if(!a )
				return b;
			if(!b)
				return a;
			
			Node *head = new Node;//new是运算符，不需要头文件
			Node *p = head;
			int up = 0, x, y;
			while(a || b)
			{
				p->nex = new Node;		//new是运算符，不需要头文件
				p = p->nex;				//先申请下一跳空间，再跳到那里接招。

				x = a == nullptr ? 0 : a->val;
				y = b == nullptr ? 0 : b->val;
				
				p->val = (x + y + up) % 10;
				up = (x + y + up) / 10;
				
				if(a)a = a->nex;
				if(b)b = b->nex;
			}
			if(up > 0)
			{
				p->nex = new Node;		//new是运算符，不需要头文件
				p = p->nex;
				p->val = up;
			}
			p->nex = nullptr;
			return head->nex;	
		}
};

//这个版本不用申请多余的head节点，节省了空间，
//但是导致每次计算多了判断，牺牲了时间
class s221_no_head_node
{
	public:
		Node *add2Num(Node *a, Node *b)
		{
			if(!a )
				return b;
			if(!b)
				return a;
			
			Node *head = NULL, *p, *pre;
			int up = 0, x, y;
			while(a || b)
			{
				p = new Node;//new是运算符，不需要头文件
				p->nex  = nullptr;
				
				x = a == nullptr ? 0 : a->val;
				y = b == nullptr ? 0 : b->val;
				
				p->val = (x + y + up) % 10;
				up = (x + y + up) / 10;
				
				if(a)a = a->nex;
				if(b)b = b->nex;

				if(!head)
				{
					pre = head = p;
				}
				else
				{
					pre->nex = p;
					pre = pre->nex;
				}
				p = p->nex;
			}
			
			if(up > 0)
			{
				p = new Node;//new是运算符，不需要头文件
				pre->nex = p;
				p->nex = nullptr;	
				p->val = up;
			}
			
			return head;	
		}
};



//中间某一部分转180度
class s222
{
	public:
		Node *reverseBetween(Node *h, int m, int n)
		{
			if(!h)
				return NULL;
			if(!(m < n && m > 0))
				return h;
				
			Node dum;				//如果从头节点开始反转，这样有利。
			dum.nex = h;
			Node *pre = &dum;
			int i = 0;				//另一个for也要用，这里定义i,另外可以考虑利用 --m, --n，这样便不用i
			for(; i < m-1; ++i)
				pre = pre->nex;

			Node *cur = pre->nex;			//指向m(第m个)
			Node *nex = cur->nex;	//指向m+1
			for(; i < n; ++i)
			{
				cur->nex = nex->nex;
				nex->nex = pre->nex;
				pre->nex = nex;
				nex = cur->nex;
			}
			return dum.nex;
		}
};

//因为是大于等于5,所以结果中7在5前面
class s223
{
	public:
		Node *Partion(Node *head, int val)
		{
			if(!head)
				return NULL;
			
			Node h1, h2;					//以空间换时间和逻辑简洁性
			Node *p1 = &h1, *p2 = &h2;		//勿漏p2前的*
			for(; head; head = head->nex)
			{
				if(head->val < val)
				{
					p1->nex = head;
					p1 = p1->nex;
				}
				else
				{
					p2->nex = head;
					p2 = p2->nex;
				}
			}
			p2->nex = nullptr;
			p1->nex = h2.nex;
			return h1.nex;
		}
};

class s224
{
	public:
		Node *rmDuplicate(Node *h)//test中传入的参数是h->nex
		{
			if(!h)
				return nullptr;	
			
			Node *head = h, *tmp;
			for(; h->nex; h = h->nex)
			{
				if(h->val == h->nex->val)
				{
					tmp = h->nex;
					h->nex = h->nex->nex;
					delete tmp;
				}
			}
			return head;
		}
};
/*
注意体会:
h = h->nex;跳到下一个; 
h->nex = cur;改变当前指针的下一跳地址
*/


//s225_B 的改进版，定义一个哑节点，这样便可以轻松处理第一个、第二个遗漏的问题
//重复节点要全部删除，不是像上面要保留一个
class s225
{
	public:
		Node *rmDuplicate(Node *h)
		{
			if(!h || !(h->nex))
				return h;	
			
			Node head;
			Node *pre = &head, *cur = h, *tmp;
			pre->nex = cur;

			while(cur && cur->nex)
			{
				if(cur->val != cur->nex->val)
				{
					pre = cur;	//没有重复,pre则要走一步
					cur = cur->nex;
				}
				else
				{
					while(cur->nex && cur->val == cur->nex->val)
					{
						tmp = cur->nex;
						cur->nex = cur->nex->nex;
						delete tmp;		//先删重复节点之后的节点，之后再删脚踩的的这个节点cur
					}
					
					tmp = cur;
					cur = cur->nex;//在delete之上,因为下面会delete cur
					delete tmp;	
					
					pre->nex = cur;//有重复时，pre不变
				}
			}	
			return head.nex;
		}
};
/*
错误:

如果
tmp = pHead->nex;
cur = cur->nex;
pHead->nex = cur;
delete tmp; 
改为:
tmp = pHead->nex;
pHead->nex = cur->nex;
delete tmp;	
cur = cur->nex;
会运行错误,

在delete tmp后，cur = cur->nex;中会cur为非法地址
因为第一步中,tmp、pHead->next实际均还是cur,所以delete时便把cur释放了!!!
*/

class s226
{
	public:
		Node *rotate(Node *h, int k)
		{
			if(!h || !k)
				return h;	
			
			Node *tmp;
			int len = 1;
			for(tmp = h ; tmp->nex; tmp = tmp->nex)
				++len;
			tmp->nex = h;			//闭环
			k = k % len;
			tmp = h;
			for(int i = 0; i < k; tmp = tmp->nex, ++i)
			{
			}						//技巧，不用在{}里if(i == k)
			h = tmp->nex;
			tmp->nex = nullptr;	//断开环. tmp  (h)tmp->nex
			//【知识点】这里修改的是tmp，而上面赋值给h,却用的是tmp的下一个节点。

			return h;
		}
};
//错误:int i = 0, tmp = h;相当于定义了一个tmp
//所以不要将变量赋值和定义放在一起!!!!
//for(int i = 0, tmp = h; i < k; tmp = tmp->nex, ++i)
/*
注意:
h = tmp->nex; //tmp的下一个节点
和
tmp->nex = nullptr;	//修改tmp的值

注意体会
*/


//拓展:另见剑指Or 输出倒数第K个节点
/*
极:
一个成员；
删除最后、开头节点；
n超出开头；
已在testcase中体现
*/
class s227
{
	public:
		Node *rmNthNodeFromEnd(Node *h, int n)	//传入的第一个节点不是哑节点
		{
			if(!h || n < 1)
				return h;
			
			Node *pre = h, *end = h, *tmp;
			for(;end->nex && n > 0; end = end->nex)
				--n;								//end:我先出发啦，走到第n个节点(从1数)//这时,pre在第0节点，可以推出end在倒数第1时，pre在倒数第n+1(即要删除节点的前一个)
			if(n > 0)								//倒数 n 等于 或 超过链表长度，则只删除开头节点。或只有一个节点。			
			{
				tmp = h;
				h = h->nex;
				delete tmp;
			}
			else
			{
				for(;end->nex; end = end->nex)
				{
					pre = pre->nex;
				}								//pre走到倒数第n+1个节点，即n的前一个节点
				tmp = pre->nex;
				pre->nex = pre->nex->nex;
				delete tmp;
			}
			return h;							//返回哑节点的下一个节点
		}
};
//注意:下面的int在前和在后面都不对!
//	for(p = h, int i = 0; i < n; ++i)


//因为是merge到a里,所以a的高空间是空的，所以要先往高处填充
/*
Given two sorted integer arrays A and B, merge B into A as one sorted array.
Note: You may assume that A has enough space to hold additional elements from B. The number of
elements initialized in A and B are m and n respectively.
*/


class s61_less_var
{
	public:
		void mergeSortedArr(int a[], size_t m, int b[], size_t n)
		{	
			if(!a || !b || !m)
				return;
			for(; m > 0 && n > 0 ; )
			{
				if(a[m-1] > b[n-1])
				{
					a[m+n-1] = a[m-1];
					m--;
				}
				else
				{
					a[m+n-1] = b[n-1];
					n--;				
				}
			}
			for(; n > 0 ; n--)
				a[m+n-1] = b[n-1];
		}
};


//注意下面的编译错误
#if 0 
class s61_less_var
{
	public:
		void mergeSortedArr(int a[], size_t m, int b[], size_t n)
		{	
			if(!a || !b || !m)
				return;
//			while(m > 0 && n > 0)
//				a[m+n-1] = a[m-1] > b[n-1] ? a[(m--)-1] : b[(n--)-1];	
				//‘m’上的运算结果可能是未定义的 [-Wsequence-point]
			while(n > 0)
				a[m+n-1] = b[(n--)-1];
		}
};
/
*
同样下面也会警告:
		a[m+n+1] = a[m] > b[n] ? a[m--] : b[n--];	//短路求值
	while(n >= 0)
		a[m+n+1] = b[n--];	//这里m是-1;
警告：‘m’上的运算结果可能是未定义的 [-Wsequence-point]
		 a[m+n+1] = a[m] > b[n] ? a[m--] : b[n--]; 

*
/

#endif


class s61
{
	public:
		void mergeSortedArr(int a[], size_t m, int b[], size_t n)
		{	
//			if(m < 1 || n < 1 || !b || !a)	//1.不要滥用assert; 2.如果上面m和n是int ，m < 1不可以用!m代替，还有负值
											//2.如果上面m和n是int ，m < 1不可以用!m代替，还有负值

			if(!m || !n || !b || !a)		//1.上面是size_t，则m和n只可能>=0, 即便是传入例如-3(被转换为unsigned int)，也会在这里变为>0的，见我的OS_计算机原理.doc
				return;				

			int ia = m - 1, ib = n - 1, icur = m + n - 1;
			while(ia >= 0 && ib >= 0)//类似与冒泡思想				
			{
				if(a[ia] > b[ib])
					a[icur--] = a[ia--];//ia和ib不是同时-- !!
				else
					a[icur--] = b[ib--];
			}
			while(ib >= 0)//目的是把b全搬过去,所以ia>=0也无所谓，留着就行了
				a[icur--] = b[ib--];
		}
};


class s62
{
	public:
		Node *mergeSorteList(Node *p, Node *q)
		{
			if(!p)
				return q;
			if(!q)
				return p;
			
			Node head;
			Node *cur = &head;
			for( ; p && q; cur = cur->nex)
			{
				if(p->val < q->val)
				{
					cur->nex = p;	//取小者
					p = p->nex;		
				}
				else
				{
					cur->nex = q;
					q = q->nex;
				}
			}
			if(p)
				cur->nex = p;
			if(q)
				cur->nex = q;
			return head.nex;
		}
};


//http://www.tuicool.com/articles/veErm2M
class s72
{
	public:
		int searchInsertPosition(int a[], int n, int t)
		{
			if(!a || n < 0)
				return 0;			
			int b = 0, e = n-1, m;
			while(b <= e)	//用<就行，别矫情用!=,导致下面越界死循环
			{
				m = (b + e)/2;
				if(t == a[m])
					return m;
				if(t < a[m])
					e = m - 1;
				else
					b = m + 1;
			}
			if(t > a[b])
				return b + 1;
			else
				return b;
		}
};


//变种:从尾到头打印字符串
class revOutput
{
	public:
		/* 方法1:先逆序，再遍历*/

		/* 方法2: 栈 */
		
		/* 方法3: 递归调用 */  
		void reverseOutput2(Node* h)   
		{  
			if(h) 
			{	
				reverseOutput2(h->nex);	
				cout << h->val << endl;   
			}  
		}  
};









#define __NO__SEE__
#define __NO__SEE__
#define __NO__SEE__

//----------------------------以下暂时忽略-----------------------------------


//下面处理的思路不正确，第一个、第二个会遗漏
class s225_B
{
	public:
		Node *rmDuplicate(Node *h)
		{
			Node *head = h, *tmp, *cur = h->nex;
			if(!h)
				return nullptr;
			
			while(cur && cur->nex)
			{
				if(cur->val != cur->nex->val)
				{
						h = cur;//或者h = h->nex; 即:h跳到下一个; h本质是指针，存放一个地址
						cur = cur->nex;					
				}
				else
				{
					while(cur->nex && cur->val == cur->nex->val)
					{
						tmp = cur->nex;
						cur->nex = cur->nex->nex;
						delete tmp;
					}
					
					tmp = h->nex;
					cur = cur->nex;
					h->nex = cur;//h->nex = cur;改变当前指针的下一跳地址,因为下一跳被delete，当然要更换
					delete tmp;				
				}
				
			}
			if(head->val == head->nex->val)
			{
				tmp = head;
				head = head->nex->nex;
				delete tmp->nex;
				delete tmp;
			}
			return head;
		}
};



//http://www.2cto.com/kf/201406/312304.html
class s64
{
	public:
		Node *insertSortList(Node *h)
		{
			if(!h || !h->nex)
				return h;
			Node dum;
			dum.nex = h;
			Node *cur = h, *pre, *tmp;
			while(cur->nex)
			{
				if(cur->nex->val < cur->val)
				{
					pre = &dum;
					while(pre->nex->val < cur->nex->val)
						pre = pre->nex;	//循环后找到cur->enxt不大于的点pre->nex,下面交换两者
					tmp = cur->nex;
					cur->nex = tmp->nex;
					tmp->nex = pre->nex;
					pre->nex = tmp;
				}
				else
					cur = cur->nex;
			}
			return dum.nex;
		}
};


//http://blog.csdn.net/suwei19870312/article/details/12512207
class s66
{
	public:
		int findFirstMissingInt(int a[], int n)
		{
			for(int i = 0; i < n; ++i)
			{
				if(a[i] <= n && a[i] >=1 
					&& a[i] != i + 1 && a[i] != a[a[i] - 1])
				{
					swap(a[i], a[a[i] - 1]);
					--i;//交换了,i要停在原位,继续检验
				}
			}
			for(int i = 0; i < n; ++i)
			{
				if(a[i] != i+1)
					return i+1;
			}
			return n+1;
		}
};


#endif
