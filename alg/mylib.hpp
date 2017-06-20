//http://www.cnblogs.com/gylei/archive/2013/03/16/2963546.html
//http://blog.csdn.net/tengxiaoming/article/details/5626975
//<<数据结构与算法分析:C语言描述.pdf>>

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <cstring>
#include <map>
#include <stack>
#include <iostream>

typedef struct node
{
	int val;
	struct node *next; 
}Node;

Node * arrToList(int *a, int n)
{
	if(!a || n < 1)
		return NULL;
	
	Node *h = new Node();
	Node *head = h;
	h->next = NULL;
	h->val = a[0];
	for(int i = 1; i < n; ++i)
	{
		h->next = new Node();
		h = h->next;
		h->val = a[i];
		h->next = NULL;
	}
	return head;
}

void printList(Node *h)
{
	if(!h)
		return;
	while(h)
	{
		std::cout << h->val << std::endl;
		h = h->next;
	}
}

typedef struct dNode
{
	int val;
	struct dNode *pre;
	struct dNode *next;
}DNode;
DNode * arrToDList(int *a, int n)
{
	if(!a || n < 1)
		return NULL;
	
	DNode *h = new DNode();
	DNode *head = h;
	h->next = NULL;
	h->pre = NULL;
	h->val = a[0];

	DNode *pre = NULL;
	for(int i = 1; i < n; ++i)
	{
		pre = h;
		h->next = new DNode();
		h = h->next;
		
		h->val = a[i];
		h->next = NULL;
		h->pre = pre;
	}
	return head;
}

void printDList(DNode *h)
{
	if(!h)
		return;
	while(h)
	{
		if(h->pre)
			std::cout << "pre:" <<  h->pre->val << " , ";		
		std::cout << h->val << std::endl;
		h = h->next;
	}
}


typedef struct treeNode
{
	int val;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode;

TreeNode * arrToBSTTreeDo(int a[], int b, int e)
{
	if(b > e)
		return nullptr;
	int m = (b + e)/2;					//按照有序数组转换为BST(二叉排序树)

	TreeNode *p = new TreeNode;
	p->val = a[m];

	p->left =  arrToBSTTreeDo( a, b, m-1);//m已经用了，当然要排除
	p->right = arrToBSTTreeDo( a, m+1, e);

	return p;
}
//CIG P150
//根据中序遍历结果[或有序数组]重建BST
TreeNode *arrToBSTTree(int *a, int n)
{
	if(!a || n < 1)
		return NULL;
	return arrToBSTTreeDo(a, 0, n);	
}

void arrToStack(int *a, int n, std::stack<int> &st)
{
	if(!a || n < 1)
		return;
	for(int i = 0; i < n; ++i)
	{
		st.push(a[i]);
	}
}

void printStack(std::stack<int> &st)
{
	std::cout << "printStack:"  << std::endl;
	while(!st.empty())
	{
		std::cout << st.top() << std::endl;
		st.pop();
	}
}


