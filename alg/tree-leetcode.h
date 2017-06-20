#ifndef PART2_H
#define PART2_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

typedef struct treeNode
{
	int val;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode;


/*
知识点:

1.二叉树的深度优先遍历一般采用栈,广度优先遍历一般采用队列。
2.二叉树的深度优先遍历:前序、中序、后序遍历

*/



/*
二叉树遍历:递归实现
理解:按照只有三个节点的二叉树来理解就很好理解了
*/
void visit(int val)
{
	std::cout << val << std::endl;
}


//前序遍历
class s511_digui
{
	public:
		void tra(TreeNode *r)
		{
			if(!r)
				return;
			visit(r->val);
			tra(r->left);
			tra(r->right);
		}		
};

//中序遍历
class s512_digui
{
	public:
		void tra(TreeNode *r)
		{
			if(!r)
				return;
			tra(r->left);
			visit(r->val);
			tra(r->right);
		}	
};

//后序遍历
class s513_digui
{
	public:
		void tra(TreeNode *r)
		{
			if(!r)
				return;
			tra(r->left);
			tra(r->right);
			visit(r->val);
		}	
};
/*
以后序遍历
举例:(数字代表null)
   a
 b   c
1 2 3 4

step:
tra(a)
	tra(b)
		tra(1)//返回
		tra(2)//返回
		visit(b)
	tra(c)
		tra(3)//返回
		tra(4)//返回
		visit(c)
	visit(a)
*/



#define __C__PP__



//前序遍历:栈方法
class s511
{
	public:
		vector<int> preTraverse(TreeNode *r)
		{
			vector<int> res;
			if(!r)
				return res;		
			
			stack<TreeNode *> st;
			st.push(r);//先push
			
			while(!st.empty())
			{
				r = st.top();
				st.pop();//再pop
				res.push_back(r->val);//这个在p->right和p->left之前,即访问在前，则为前序遍历，下同。

				if(r->right)	//这里先压入right，则right后出来
					st.push(r->right);
				if(r->left)
					st.push(r->left);
			}
			return res;
		}
};



//时间复杂度 O(n), 空间复杂度O(n)
//http://blog.csdn.net/doc_sgl/article/details/14436785
/*
注意体会:
1.虽是左、中、右遍历，但在实际中，"中"其实是左或者右,所以无需考虑"中"
2.就像有吸铁在左下角吸引，总是会有往左路偏航的力,所以，跑完之后需要人力手动纠正到右边去
*/
class s512
{
	public:
		vector<int> inTraverse(TreeNode *r)
		{
			vector<int> res;
			if(!r)
				return res;	
			
			stack<TreeNode *> ss;
			                                //没有紧接着的pop,这里无push
			while(!ss.empty() || r)//下面要给r赋值循环，这里要额外多一个r判断
			{
				while(r)//跑完左路
				{
					ss.push(r);
					r = r->left;
				}
				r = ss.top();
				ss.pop();//push和pop个数总数1:1				
				res.push_back(r->val);	
				
				r = r->right;//跑到右路去
			}
			return res;
		}
};


/*
为什么用这种方法?
逻辑清晰明了，再者比其他方法判断少,实现未必慢
*/
class s513_postTra_by_reverse
{
	public:
		vector<int> postTraverse(TreeNode * r)
		{

			vector<int> res;
			if(!r)
				return res;	
			
			stack<TreeNode *> ss;
			ss.push(r);
			
			while(!ss.empty())
			{
				r = ss.top();//这里间接将p转换到下一个，所以下文中，只要push进去了，就不必p=p->left了
				ss.pop();

				res.push_back(r->val);

				if(r->left)
					ss.push(r->left);
				if(r->right)
					ss.push(r->right);
			}
			reverse(res.begin(), res.end());//#include <algorithm>
			return res;
		}
};

/*
知识点:
1. vector等容器用clear来重置!
*/

//level order 层次遍历。 即BF traversal（广度优先遍历)
/*
知识点:
1.利用队列先进先出的特性。

*/
//http://blog.csdn.net/sunao2002002/article/details/46280539
class s514
{
	public:
		vector<vector<int> > levelTraverse(TreeNode *r)
		{
			vector<vector<int> > res ;
			if(!r)
				return res;		
			
			queue<TreeNode *> q;
			q.push(r);
			
			while(!q.empty())			//外循环承接一层的遍历结果，内循环遍历具体的一层、并压入下一层
			{
				vector<int> tmp_res;
				queue<TreeNode *> tmp_q;//每次重新定义，以便清空 
				while(!q.empty())
				{
					r = q.front();
					q.pop();
					tmp_res.push_back(r->val);
					
					if(r->left)
						tmp_q.push(r->left);	//先进先出
					if(r->right)
						tmp_q.push(r->right);
					
				}
				q = tmp_q; 					//错:q.push(tmp_q);
				res.push_back(tmp_res);
			}
			return res;
		}
};



//利用层序遍历求深度(高度)
class s501
{
	public:
		int getTreeDepth(TreeNode *r)
		{
			if(!r)
				return 0;
			
			int depth = 0;
			TreeNode *p;
			queue<TreeNode *> q;
			
			q.push(r);
			while(!q.empty())
			{
				queue<TreeNode *> tmp_q;
				while(!q.empty())
				{
					p = q.front();
					q.pop();
					if(p->left)tmp_q.push(p->left);
					if(p->right)tmp_q.push(p->right);
				}
				q = tmp_q;
				++depth;
			}
			return depth;
		}
};




class s518
{
	public:
		bool isSameTree(TreeNode *p, TreeNode *q)
		{
			stack<TreeNode *> s;
			s.push(p);
			s.push(q);
			while(!s.empty())
			{
				p = s.top();
				s.pop();
				q = s.top();
				s.pop();
				
				if(!p && !q)
					continue;
				if((!p || !q) || (p->val != q->val))
					return false;
				
				s.push(p->left);//这里不管p->left是不是null,都push进去,和遍历不同
				s.push(q->left);
				
				s.push(p->right);
				s.push(q->right);
			}
			return true;
		}

		//FDS P183
		bool isSameTree_digui(TreeNode *p, TreeNode *q)
		{
			stack<TreeNode *> s;
			s.push(p);
			s.push(q);
			while(!s.empty())
			{
				p = s.top();
				s.pop();
				q = s.top();
				s.pop();
				
				if(!p && !q)
					continue;
				if((!p || !q) || (p->val != q->val))
					return false;
				
				s.push(p->left);//这里不管p->left是不是null,都push进去,和遍历不同
				s.push(q->left);
				
				s.push(p->right);
				s.push(q->right);
			}
			return true;
		}		
};

class s519
{
	public:
		bool isMirrorTree(TreeNode *r)
		{
			if(!r)
				return true;
			
			stack<TreeNode *> s;
			TreeNode *p, *q;
			
			s.push(r->left);
			s.push(r->right);
			while(!s.empty())
			{
				p = s.top();
				s.pop();
				q = s.top();
				s.pop();
				
				if(!p && !q)//这里已经排除同位null的情况，所以下面的||很妙
					continue;
				if((!p || !q) || (p->val != q->val))
					return false;
				
				s.push(p->left);
				s.push(q->right);
				
				s.push(p->right);
				s.push(q->left);
			}
			return true;
		}

};




//二叉树的构建
//http://www.tuicool.com/articles/Fbqea2e
//http://www.cnblogs.com/Romi/archive/2012/08/30/2663455.html
//http://blog.163.com/almerzhimin@126/blog/static/15525631020103112347782/

/*
知识点:
1.注意体会递归
*/
/*
BST:二叉排序树又叫二叉查找树,英文名称是:Binary Sort Tree
将有序数组转换为BST

*/
class s500
{
	public:
		TreeNode *doCreateBTree()
		{
			int a[] = {1,2,3,4,5};
			return createBTree(a, 0, sizeof(a)/sizeof(a[0])-1);		//sizeof(a)/sizeof(a[0])错写为sizeof(a)而错误!!
		}
	private:
		TreeNode * createBTree(int a[], int b, int e)
		{
			if(b >= e)
				return nullptr;
			int m = (b + e)/2;					//按照有序数组转换为BST(二叉排序树)
		
			TreeNode *p = new TreeNode;
			p->val = a[m];

			p->left =  createBTree( a, b, m-1);//m已经用了，当然要排除
			p->right = createBTree( a, m+1, e);

			return p;
		}

};
/*
注意!!!!
有序数组转换为二叉树后的结果并不是唯一的!!!!
只要按照中序遍历，大小关系和原数组一样就OK
例:a[] = {1,2,3,4,5};
按上面转换后是:
   3 
 1   4 
  2    5
  
但是实际下面也是满足的:
   3
  2  4
1      5

*/

/*
将有序数组转换为二叉树
例如 4,6,8,10,12,14,16

转换为二叉树为

             10

              / \

            6    14

           / \    /  \ 

         4   8 12   16

*/










#define __NO__SEE__
#define __NO__SEE__
#define __NO__SEE__

//----------------------------以下暂时忽略-----------------------------------


/*
思路
这道题是要求恢复一颗有两个元素调换错了的二叉查找树。中序遍历BST 然后找到逆序。有两种情况需要考虑:
两个错位的节点是相邻的父子树关系, 那么找到第一个先序遍历逆序的两个节点
两个错位的节点不是父子树关系, 这就是发生两次逆序的情况，那么这时候需要调换的元素应该是第一次逆序前面的元素，和第二次逆序后面的元素。

http://segmentfault.com/a/1190000004284255
http://blog.csdn.net/ljiabin/article/details/44514651

1.二叉查找树判断:中序遍历
*/
//BST中有两个逆序，反转之
class s517
{
	public:
		void reverse(TreeNode *r)
		{
			if(!r)
				return;
			pre = first = second = nullptr;

			inTraverse(r);
			if(!first && !second)
				return;
			
			int tmp = first->val;//只调换val 不是node
			first->val = second->val;
			second->val = tmp;
		}
	private:
		TreeNode *pre, *first, *second;
		void inTraverse(TreeNode *r)		//递归
		{
			if(!r)
				return;
			
			inTraverse(r->left);
			
			if(pre != nullptr && pre->val > r->val)
			{
				if(!first)
					first = pre;	//第一个逆序点
				second = r;			//如果相邻第一次就找全， 如果不相邻则遍历完后找到第二个逆序点,会自动更新
			}
			pre = r;//给pre赋值,保存上一个节点
			
			inTraverse(r->right);
		}
};





class s500_by_ptr2ptr
{
	public:
		void createBTree(TreeNode **p)
		{
			cout << "input the val:" << endl;
			int val;
			cin >> val;
			if(val == 0)
				return;
			else
			{
				*p = new TreeNode;
				(*p)->val = val;
				createBTree(&((*p)->left));
				createBTree(&((*p)->right));
			}
		}
};


#endif
