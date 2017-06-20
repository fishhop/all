//http://www.cnblogs.com/gylei/archive/2013/03/16/2963546.html
//http://blog.csdn.net/tengxiaoming/article/details/5626975
//<<数据结构与算法分析:C语言描述.pdf>>

#include <stdio.h>
#include <stdlib.h>

typedef int DType;

typedef void (*printFun)(DType);

typedef struct node
{
	DType val;
	struct node *nex; //在这里不可以用:Node *, Node 还没生效呢!
}Node;


Node *create()
{
	Node *p = malloc(sizeof(*p));

	if(!p)return NULL;

	//表头，数据域不必处理，存储时从下一个开始
	p->nex = NULL;

	return p;
}

Node *findPrev(Node *h, DType val)
{
	//有局部副本，对H的修改不改变源值

	if(!h)
		return NULL;
	for(; h->nex; h = h->nex)
	{
		if(h->nex->val == val)		
			return h;
	}
	return NULL;	
}

Node *ins(Node *H, DType val)
{
	if(!H)
		return NULL;

	Node *p = malloc(sizeof(*p));//要在堆里申请内存
	
	if(!p)
		return NULL;

	p->val = val;
	p->nex = H->nex;
	H->nex = p;

	return H;
}


void del(Node *H, DType val)
{
	if(!H)
		return;
	Node *tmp;
	
	while( H->nex )
	{
		if(H->nex->val == val)
		{
			tmp = H->nex;
			H->nex = H->nex->nex;
			free(tmp);
			tmp = NULL			//置NULL，以防外边其他地方有记录此地址，还会用到
		}
		else
			H = H->nex;			//只有没有删除时，才跳变H的指向。
	}
}


// 下面错误，可以删除相连的两个6中的第一个，跳过了第二个
#if 0
void del(Node *H, DType val)
{
	if(!H)
		return;
	Node *tmp;
	for(; H->nex; H = H->nex)
	{
		if(H->nex->val == val)
		{
			tmp = H->nex;
			H->nex = H->nex->nex;
			free(tmp);
		}
	}
}
#endif


#if 0
Node * del_no_head(Node *h, int val)
{
	if(!h)	
		return NULL;
	Node *tmp;
	for(; h->nex; h = h->nex)
	{
		if(h->nex->val == val)
		{
			tmp = h->nex;
			h->nex = h->nex->nex;
			free(tmp);
		}
	}
	if(h->val == val)
	{
		tmp = h;
		h = h->nex;
		free(tmp);
	}
	return h;
}
#endif

void delList(Node *H)
{
	Node *p = H->nex, *tmp = NULL;

	while(p)
	{
		tmp = p;
		p = p->nex;//这句要在free之上执行，free tmp时 p也被free掉了。		
		free(tmp);
	}

	H->nex = NULL;
	
}

void display(Node *H, printFun print)//注意函数指针用法
{
	if(H == NULL)
	{
		printf("Head is NULL\n");
		return;
	}
	while(H->nex)
	{
		print(H->nex->val);//函数指针掉用
		printf(":%p ]\n",H->nex);
		H = H->nex;
	}
}


void display_2(Node *h, printFun print)//注意函数指针用法
{
	if(!h)
	{
		printf("Head is NULL\n");
		return;
	}
	while(h)
	{
		printf("[%d - :%p ]\n",h->val,h);
		h = h->nex;
	}
}


void printInt(int v)
{
	printf("[%d - ", v);
}


size_t size_2(Node *H)
{
	if(!H)
		return 0;
	int n = 0;
	for(; H->nex; H = H->nex)
	{
		++n;
	}
	return n;

}

size_t size(Node *H)
{
	int i = 0;
	while((H = H->nex))//注意加括号，不加括号会编译警告
		++i;
	return i;
}
/*
	while(H = H->nex)

	警告：建议在用作真值的赋值语句前后加上括号 [-Wparentheses]

*/



//*********************               ***********************
//*********************  单链表的环   ***********************
//http://www.cnblogs.com/xudong-bupt/p/3667729.html

//判断是否有环，尾端是一个环(也只能是这种形式吧，不然链表岂不是有分叉，不满足单链表)  
bool isLoop(Node * pHead)  
{  
	if(!pHead)
		return true;
	
    Node * fast = pHead;  
    Node * slow = pHead;  
    //如果无环，则fast先走到终点  
    //当链表长度为奇数时，fast->Next为空  
    //当链表长度为偶数时，fast为空  
    while( fast != NULL && fast->nex != NULL)  
    {  
  
        fast = fast->nex->nex;  
        slow = slow->nex;  
        //如果有环，则fast会超过slow一圈
        if(fast == slow)  
            break;  
    }  
  
    if(fast == NULL || fast->nex == NULL  )  
        return false;  
    else  
        return true;  
}  
  
//计算环的长度 
/*
在环上相遇后，记录第一次相遇点为Pos，之后指针slow继续每次走1步，fast每次走2步。在下次相遇的时候fast比slow正好又多走了一圈，也就是多走的距离等于环长。
设从第一次相遇到第二次相遇，设slow走了len步，则fast走了2*len步，相遇时多走了一圈：
环长=2*len-len。
*/
int loopLength(Node * pHead)  
{
	if(!pHead)
		return true;	
	
    if(isLoop(pHead) == false)  
        return 0;  
    Node * fast = pHead;  
    Node * slow = pHead;  
    int length = 0;  
    bool begin = false;  
    bool agian = false;  
    while( fast != NULL && fast->nex != NULL)  
    {  
        fast = fast->nex->nex;  
        slow = slow->nex;  
        //超两圈后停止计数，挑出循环  
        if(fast == slow && agian == true)  
            break;  
        //超一圈后开始计数  
        if(fast == slow && agian == false)  
        {             
            begin = true;  
            agian = true;  
        }  
  
        //计数  
        if(begin == true)  
            ++length;  
          
    }  
    return length;  
}  
  
  
//求出环的入口点  
/*
第一次碰撞点Pos到连接点Join的距离=头指针到连接点Join的距离，因此，分别从第一次碰撞点Pos、头指针head开始走，相遇的那个点就是连接点。
*/
Node* findLoopEntrance(Node * pHead)  
{  
	if(!pHead)
		return nullptr;	
    Node * fast = pHead;  
    Node * slow = pHead;  
    while( fast != NULL && fast->nex != NULL)  
    {  
  
        fast = fast->nex->nex;  
        slow = slow->nex;  
        //如果有环，则fast会超过slow一圈  
        if(fast == slow)  
        {  
            break;  
        }  
    }  
    if(fast == NULL || fast->nex == NULL)  
        return NULL;  
    slow = pHead;  
    while(slow != fast)  
    {  
        slow = slow->nex;  
        fast = fast->nex;  
    }  
  
    return slow;  
}  



//*********************               ***********************
//*********************  两个链表相交    ***********************
//在末尾相交或者从中间某个地方相交，都符合下面的判断
bool isCross(node *h1, node *h2)
{
	if(!h1 || !h2)
		return 0;
	for(; h1->nex && h2->nex; h1 = h1->nex,h2 = h2->nex)
		;
	return h1 == h2 ? true : false; 
}

void _test_above_all()
{
	//表头 pHead; 第一个节点:pHead->nex
	
	Node *pHead = NULL;
	Node *newL = NULL;
	
	pHead = create();

	printf("size:%d\n", (unsigned int)size(pHead));
	for(int i = 5; i < 10; ++i)
	{
		ins(pHead, i);
	}
	printf("size:%d\n", (unsigned int)size(pHead));


	Node *findRes = findPrev(pHead, 6);
	printf("\nfindPrev:%d\n",  findRes->val);
	display(pHead, printInt);

	printf("\ins:%d\n",  6);
//	ins(pHead->nex, 6);
	ins(pHead, 6);
	ins(pHead, 6);
	display(pHead, printInt);

	printf("\ndel:%d\n",  6);
	del(pHead, 6);
	display(pHead, printInt);

//	newL = reverseList_withHead(pHead);
//	printf("\n\nafter reverse(return):\n");
//	display(newL, printInt);


//	newL = reverseList(pHead->nex);
//	printf("\n\nafter reverseList:\n");
//	display_2(newL, printInt);


//	printf("\n\ndelete 6:\n");
//	del(pHead, 6);
//	display(pHead, printInt);

	printf("\n\nclear the list:\n");
	delList(pHead);
	display(pHead, printInt);
	printf("\nsize:%d\n", (unsigned int)size(pHead));	
}

int main()
{

	return 0;
	
}	


#define __NO__SEE__
#define __NO__SEE__
#define __NO__SEE__



//pre:要处理节点的前一个,第一次时处理cur会影响pre,所以pre初始为NULL，不可以被初始化为H，
//cur:表示要处理的节点,第一个节点是H->nex,所以cur当然要初始化为它；
//链表反转--有哑节点版
Node *reverseList_withHead(Node *H)
{
	if(!H || !(H->nex))
		return H;
	
	Node *pre = NULL, *cur = H->nex, *nex = NULL;
	while(cur)
	{
		nex = cur->nex;			//想要处理cur,当然要先暂存cur
		cur->nex = pre;			//第一次时,pre为null,从而使未来的list尾部指向了null
		pre = cur;				//pre第一次本对应H，但没有，所以最后要H->nex = pre;
		cur = nex;
	}
	H->nex = pre;				//表头不参与逆转，不动，其他成员逆转完，表头重新指到新位置即可。
	return H;					//返回不返回均可，函数中通过->号已经对调用函数中的值进行了修改。源list已改变
}								//注意:H = H->nex;并不改变原H; 而, H->nex = p;则改变了原H。


