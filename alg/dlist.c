//http://www.open-open.com/lib/view/open1410699307711.html
//百度文库:一个完整的双向链表程序(C语言版)
//http://www.jb51.net/article/51962.htm
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
这样编译不过:
typedef enum Status
{
	OK = 0,
	ERR,
};

*/
typedef enum
{
	OK = 0,
	ERR,
}Status;

typedef int DType;

typedef struct node
{
	DType val;
	struct node *pre, *nex;
}Node;

typedef struct dList
{
	Node *head, *tail;
	int len;
}DList;

/*分配值为i的节点，并返回节点地址*/ 
Node *CreateNode(DType i); 
   
/*构造一个空的双向链表*/ 
DList *CreateList(); 
   
/*删除一个双向链表*/ 
void DestroyList(DList **L); 
   
/*将一个链表置为空表，释放原链表节点空间*/ 
void ClearList(DList *L); 
 
/*将pnode所指节点插入第一个节点之前*/ 
Node *InsFirst(DList *L, Node *node); 
   
/*将链表第一个节点删除并返回其地址*/ 
Node *DelFirst(DList *L); 
         
/*删除链表中的尾节点并返回其地址，改变链表的尾指针指向新的尾节点*/ 
Node *DelLast(DList *L); 
   
/*在链表中p位置之前插入新节点S*/ 
Node *InsBefore(DList *L, Node *node, Node *s); 
   
/*在链表中p位置之后插入新节点s*/ 
Node *InsAfter(DList *L, Node *node, Node *s); 
   
/*返回在链表中第i个节点的位置*/ 
Node *LocatePos(DList *L, int i); 
   
/*打印data*/
void print(DType val);  







#define __FUNCTION__

/*分配值为i的节点，并返回节点地址*/ 
Node *CreateNode(DType i)
{
	Node *p = malloc(sizeof(*p));
	if(p == NULL)
	{
		return NULL;
	}
	p->val = i;
	p->pre = p->nex = NULL;
	return p;
}
   
/*构造一个空的双向链表*/ 
DList *CreateList()
{
	DList *L = malloc(sizeof(*L));
	Node *head = CreateNode(0);
	if(L == NULL || head == NULL)
	{
		return NULL;
	}
	
	L->head = L->tail = head;
	L->len = 0;
	return L;
}
   
/*删除一个双向链表*/ 
void DestroyList(DList **L)
{
	ClearList(*L);
	free((*L)->head);
	free(*L);
	*L = NULL;
	
}
   
/*将一个链表置为空表，释放原链表节点空间*/ 
void ClearList(DList *L)
{
	Node *tmp = L->tail;
	while(L->head != L->tail)
	{
		L->tail = tmp->pre;
		tmp->pre->nex = NULL;//忽略此步之后导致display时死循环
		free(tmp);
		tmp = L->tail;
	}
	L->len = 0;
}


/*将node所指节点插入第一个节点之前*/ 
Node *InsFirst(DList *L, Node *node)
{
	if(!L || !L->head )
		return NULL;
	if(L->head == L->tail)
	{
		node->nex = NULL;			//攘外必先安内，先确定对外影响最小的部分:node
		node->pre = L->head;
		L->head->nex = node;
		L->tail = node;
	}
	else
	{
		node->nex = L->head->nex;
		node->pre = L->head;
		L->head->nex->pre = node;
		L->head->nex = node;
	}
	++L->len;
	return node;
}


//链接一串
void Append(DList *L, Node *node)
{
	if(!L || !L->head  || !node)
		return;
	L->tail->nex = node;
	node->pre = L->tail;
	while(node->nex)
	{
		node = node->nex;
		++L->len;
	}
	L->tail = node;
	++L->len;//所链接链表的尾节点
}


/*将链表第一个节点删除并返回其地址*/ 
Node *DelFirst(DList *L)
{
	if(!L || !L->head || L->head == L->tail)
		return;
	if(!L->head->nex->nex)
	{
		L->tail = L->head;
		free(L->head->nex);
		L->head->nex = NULL;
	}
	else
	{
		Node *tmp = L->head->nex;
		L->head->nex->nex->pre = L->head;
		L->head->nex = L->head->nex->nex;
		free(tmp);
	}
	return L->head->nex;
}
   
/*删除链表中的尾节点并返回其地址，改变链表的尾指针指向新的尾节点*/ 
Node *DelLast(DList * L)
{
	if(!L || !L->head || L->head == L->tail)
		return;
	Node *tmp;
	if(!L->head->nex)
	{
		tmp = L->head->nex;
		L->head->nex = NULL;
		L->tail = L->head;
		free(tmp);
	}
	else
	{
		tmp = L->tail;
		L->tail->pre->nex = NULL;
		L->tail = L->tail->pre;
		free(tmp);
	}
	return L->tail;
}


//删除第n个节点
Node *Del_nth(DList *L, int n)
{
	if(!L || !L->head || n < 1)
		return NULL;
	Node *tmp = L->head;
	for(; n >0 && tmp; --n)
	{
		tmp = tmp->nex;
	}
	if(n > 0)
		return NULL;
	if(L->tail == tmp)
	{
		tmp->pre->nex = NULL;
		L->tail = tmp->pre;
	}
	else
	{
		tmp->pre->nex = tmp->nex;
		tmp->nex->pre = tmp->pre;		
	}
	free(tmp);

	return L->head;
}


/*在链表中p位置之前插入新节点S*/ 
Node *InsBefore(DList *L, Node *p, Node *s)
{
	if(!L || !L->head)
		return NULL;
	if(!p || !s)
		return L->head;	

	s->pre = p->pre;
	s->nex = p;
	p->pre->nex = s;
	p->pre = s;
	++L->len;
	return p;
}



/*在链表中p位置之后插入新节点s*/ 
Node *InsAfter(DList *L, Node *p, Node *s)
{
	if(!L || !L->head)
		return NULL;
	if(!p || !s)
		return L->head;	

	
	if(p->nex == L->tail)
		L->tail = s;
	else
		p->nex->pre = s;
	s->pre = p;
	s->nex = p->nex;
	p->nex = s;
	++L->len;
	return p;
	
}



//逆转双链表用途较少吧，因为双链表有前驱信息



/*返回在链表中第i个节点的位置*/ 
Node *LocatePos(DList *L, int i) 
{
	Node *p = L->head;
	
	if(i < 1 && i >= L->len);
		return NULL;
		
	int j = 0;
	while(j != i)
	{
		p = p->nex;
		++j;
	}
	return p;
	//链表内存空间并不连续，故p+i指向的地方并不一定是链表空间
//	return p+i;
}
   
/*打印data*/
void print(const DType val)
{
//	总结:此处打印data的地址,总是同一个地址，并不能得到链表中原节点的地址
//	After Ins:4:0x28cc40 - 3:0x28cc40 - 2:0x28cc40 - 1:0x28cc40 - 0:0x28cc40 -
//	printf("%d:%p - ", val, &val);
	printf("%d - ", val);

}

void display(const DList *L)
{
	if(L == NULL)
	{
		printf("List is NULL!\n");
		return;
	}
	Node *H = L->head;
	while(H != NULL && H->nex != NULL)
	{
		H = H->nex;
		print(H->val);
		printf("(%p) ",H);
	}
}

int main()
{
	DList *L = CreateList();
	Node *p = NULL, *s = NULL;
	printf("\nBefore Ins:\n");
	display(L);

//	for(int i = 1; i != 1; ++i)
	for(int i = 1; i != 4; ++i)
	{
		p = CreateNode(i);
		InsFirst(L, p);	
	}
	printf("\nAfter Ins:\n");
	display(L);
	
//	printf("\nAfter rev:\n");
//	Node *pr = reverse(L);
//	display(L);


//	p = LocatePos(L, 3);
//	printf("\nLocatePos:%d\n", p->val);
//	fflush(stdout);
//	s = CreateNode(100);
//	InsBefore(L, p, s);
//	printf("\nAfter InsBefore:\n");
//	display(L);

//	p = LocatePos(L, 5);
//	s = CreateNode(200);
//	InsAfter(L, p, s);
//	printf("\nAfter InsAfter:\n");
//	display(L);



//	L->head = NULL;
//	DelFirst(L);
//	printf("\nAfter DelFirst:\n");
//	display(L);



//	//检验是否free成功,如果成功，会重新申请到原来释放的内存
//	p = LocatePos(L, 3);	
//	s = CreateNode(300);
//	InsBefore(L, p, s);
//	printf("\nAfter InsBefore:\n");
//	display(L);


	Del_nth(L, 1);
	printf("\nAfter Del_nth:\n");
	display(L);


//	DelLast(L);
//	printf("\nAfter DelLast:\n");
//	display(L);

//	p = LocatePos(L, 3);
//	s = CreateNode(100);
//	InsBefore(L, p, s);
//	printf("\nAfter InsBefore:\n");
//	display(L);

//	fflush(stdout);
//	p = CreateNode(500);
//	printf("\nLen:%d\n", L->len);
//	Append(L, p);
//	printf("\nAfter Append:\n");
//	display(L);
//	printf("\nLen:%d\n", L->len);


//	DestroyList(&L);
//	printf("\nAfter DestroyList:\n");
//	display(L);

//	//检验是否free成功
//	L = CreateList();
//	for(int i = 1; i != 10; ++i)
//	{
//		p = CreateNode(i);
//		InsFirst(L, p);	
//	}
//	printf("\nAfter Ins:\n");
//	display(L);


	return 0;
}
//OUT:
/*
$ ./a.exe

Before Ins:

After Ins:
9 - (0x20048330) 8 - (0x20048320) 7 - (0x20048310) 6 - (0x20048300) 5 - (0x200482f0) 4 - (0x200482e0) 3 - (0x200482d0) 2 - (0x200482c0) 1 - (0x200482b0)
LocatePos:7

After InsBefore:
9 - (0x20048330) 8 - (0x20048320) 100 - (0x20048340) 7 - (0x20048310) 6 - (0x20048300) 5 - (0x200482f0) 4 - (0x200482e0) 3 - (0x200482d0) 2 - (0x200482c0) 1 - (0x200482b0)
After InsAfter:
9 - (0x20048330) 8 - (0x20048320) 100 - (0x20048340) 7 - (0x20048310) 6 - (0x20048300) 200 - (0x20048350) 5 - (0x200482f0) 4 - (0x200482e0) 3 - (0x200482d0) 2 - (0x200482c0) 1 - (0x200482b0)
After DelFirst:
8 - (0x20048320) 100 - (0x20048340) 7 - (0x20048310) 6 - (0x20048300) 200 - (0x20048350) 5 - (0x200482f0) 4 - (0x200482e0) 3 - (0x200482d0) 2 - (0x200482c0) 1 - (0x200482b0)
After InsBefore:
8 - (0x20048320) 100 - (0x20048340) 300 - (0x20048330) 7 - (0x20048310) 6 - (0x20048300) 200 - (0x20048350) 5 - (0x200482f0) 4 - (0x200482e0) 3 - (0x200482d0) 2 - (0x200482c0) 1 - (0x200482b0)
After DelLast:
8 - (0x20048320) 100 - (0x20048340) 300 - (0x20048330) 7 - (0x20048310) 6 - (0x20048300) 200 - (0x20048350) 5 - (0x200482f0) 4 - (0x200482e0) 3 - (0x200482d0) 2 - (0x200482c0)
After InsBefore:
8 - (0x20048320) 100 - (0x20048340) 100 - (0x200482b0) 300 - (0x20048330) 7 - (0x20048310) 6 - (0x20048300) 200 - (0x20048350) 5 - (0x200482f0) 4 - (0x200482e0) 3 - (0x200482d0) 2 - (0x200482c0)
After DestroyList:
List is NULL!

After Ins:
9 - (0x20048330) 8 - (0x20048320) 7 - (0x20048310) 6 - (0x20048300) 5 - (0x200482f0) 4 - (0x200482e0) 3 - (0x200482d0) 2 - (0x200482c0) 1 - (0x200482b0)
*/


//GDB
/*
(gdb) x /4w 0x80049b00
0x80049b00:     0x00000003      0x80049b10      0x80049af0      0x00000013
(gdb) n
211                     H = H->nex;
(gdb)
212                     print(H->val);
(gdb)
213                     printf("(%p) ",H);
(gdb)
209             while(H->nex != NULL)
(gdb) p H->nex
$12 = (struct node *) 0x80049af0
(gdb) x /4w 0x80049af0
0x80049af0:     0x00000002      0x80049b00      0x80049ae0      0x00000013
(gdb) n
211                     H = H->nex;
(gdb)
212                     print(H->val);
(gdb)
[New Thread 6576.0x1464]
213                     printf("(%p) ",H);
(gdb)
209             while(H->nex != NULL)
(gdb) p H->nex
$13 = (struct node *) 0x80049ae0
(gdb) x /4w 0x80049ae0
0x80049ae0:     0x00000001      0x80049af0      0x80049ad0      0x00000013
(gdb)

*/
