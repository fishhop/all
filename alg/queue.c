#include <stdio.h>

//malloc需要，勿漏
#include <stdlib.h>

/*
实现思路:
单独用一个完整的节点来记录 front;
采用尾插法的链表，这样插入和删除都很方便，不用遍历链表。

队列的链表表示:
		rear              front   
		  5    4   3   2   1
链表: NULL                 head
【尾插法】
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
	struct node *nex;
}Node;

typedef struct queue
{
	Node *front, *rear;
}Queue;


Status Init(Queue *Q)
{
	//不需要检查malloc返回值
	Q->front = Q->rear = malloc(sizeof(Node));
	if(!Q->front)
		return ERR;
	Q->front->nex = NULL;
	return OK;
}

Status Destroy(Queue *Q)
{
	Node *nex = Q->front;//其实，可以用Q->rear 代替tmp，但是可读性也很重要
	while(Q->front)
	{
		nex = Q->front->nex;
		free(Q->front);
		Q->front = nex;
	}
	return OK;
}

Status Clear(Queue *Q)
{
	Node *p = Q->front->nex;
	while(p)
	{
		Q->rear = p->nex;
		free(p);
		p = Q->rear;
	}
	//前面只是free,free后并没有自动变为NULL，记得这一点
	Q->front->nex = NULL;
	Q->rear = Q->front;
	return OK;	
}

Status EnQ(Queue *Q, DType d)
{
	Q->rear->nex = malloc(sizeof(Node));
	Q->rear->nex->val = d; 
	Q->rear->nex->nex = NULL; 
	Q->rear = Q->rear->nex;

	return OK;
}


Status DeQ(Queue *Q, int* d)
{
	if(!Q || !Q->front || !Q->front->nex)
		return;
	*d = Q->front->nex->val;
	Node *tmp = Q->front->nex;
	if(tmp == Q->rear)
		Q->rear = Q->front;
	Q->front->nex = Q->front->nex->nex;
	free(tmp);
}


//此函数原先实现有误
Status DeQ(Queue *Q, DType *d)
{
	if(!Q || !Q->front || !Q->front->nex)
		return;
	*d = Q->front->nex->val;			
	Node *tmp = Q->front->nex;				//注意:从Q->front->next开始出队，Q->front只是哑节点,Q->front始终固定	
	if(tmp == Q->rear)
		Q->rear = Q->front;
	Q->front->nex = Q->front->nex->nex;
	
	free(tmp);

	return OK;
}

void Traverse(Queue *Q)
{
	//要判断传进来的指针非空
	if(Q->front == NULL)
		return;
	//要从->next开始，因为第一个节点为头指针，不存值
	//如严蔚敏书p61
	Node *p = Q->front->nex;

	//此条件不行while(p != Q->rear)	
	while(p != NULL)	
	{
		
		printf("%d-%p; ", p->val, &(p->val));
		p = p->nex;
	}
	printf("\n");
}

void test()
{
	Queue Q;
	Init(&Q);
	printf("Init:\n");
	Traverse(&Q);
	
	for(int i = 1; i != 10; ++i)
	{
		EnQ(&Q, i);
	}
	printf("EnQ:\n");
	Traverse(&Q);

	int d = 0;
	DeQ(&Q, &d);
	printf("DeQ:%d\n", d);
	Traverse(&Q);

	Clear(&Q);
	printf("Clear:\n");
	Traverse(&Q);

	EnQ(&Q, 20);
	printf("EnQ:\n");
	Traverse(&Q);

	Destroy(&Q);
	printf("Destroy:\n");
	Traverse(&Q);
	
	Init(&Q);
	printf("Init:\n");
	Traverse(&Q);

	for(int i = 1; i != 10; ++i)
	{
		EnQ(&Q, i);
	}
	printf("EnQ:\n");
	Traverse(&Q);

	
}

int main()
{
	test();
	return 0;
}
