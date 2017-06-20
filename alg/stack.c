#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	OK = 0,
	ERR,
}Status;

typedef long long DType;

typedef struct
{
	DType *top, *base;
	int size;
}Stack; //这里要有Stack, 而struct后可有可无

const int INIT_SIZE = 10;
const int INC_SIZE = 10;

Status init(Stack *s)
{
	s->base = (DType *)malloc(INIT_SIZE * sizeof(*(s->base))); 
	
	s->top = s->base;
	s->size = INIT_SIZE;

	return OK;
}


//不提倡防御式编程，下面realloc不必检查是否成功
Status Push(Stack *s, DType d)
{
	if(!s)
		return;
	if((s->top - s->base) >= s->size)
	{
		s->base = (DType *)realloc(s->base, 
			(s->size + INC_SIZE) * sizeof(*(s->top)));

		s->top = s->base + s->size;
		s->size += INC_SIZE;
	}
	*s->top++ = d;

	return OK;
}


Status Pop(Stack *s, DType *d)
{
	if(s->base == s->top)
		return ERR;
	--s->size;
	*d = *(--s->top);//先减指针,再从减后的地址取值,因为 top此时指向空的地方
	return OK;
}


void Clear(Stack *s)
{
	s->top = s->base;
}

void Destroy(Stack *s)
{
	//因为申请时malloc返回指针给了s->base,所以free(s->base)即可，不必考虑其后的****
	free(s->base);
	s->top = NULL;
	s->base = NULL;
	s->size = 0;
	
}

Status GetTop(Stack *s, DType *d)
{
	if(s->top == s->base)
	{
		return ERR;
	}
	*d = *(s->top - 1);
	return OK;
}

void visit(DType d)
{
	printf("%lld,",d);
}

Status Traverse(Stack *s, void (*visit)(DType d))//1.注意函数指针用法
{
	DType *tmp = s->base;
	while(s->top != tmp)
	{
		visit(*(tmp));//2.函数指针调用
		printf(" - %p ; ",tmp);
		++tmp;
	}
	printf("\n");
	return OK;
}

void test()
{
	Stack s;

	init(&s);
	printf("before push:\n");
	Traverse(&s, visit);
	
	for(int i = 5; i != 10; ++i)
	{
		Push(&s, i);
	}
	printf("after push:\n");
	Traverse(&s, visit);


	//下面这样做无力吐槽...给NULL赋值...
//	DType *d = NULL;
	DType d = 0;
	Pop(&s, &d);
	printf("Pop:%lld\n", d);
	printf("after Pop:\n");
	Traverse(&s, visit);//3.函数指针调用

	GetTop(&s, &d);
	printf("GetTop:%lld\n", d);
	printf("after GetTop:\n");
	Traverse(&s, visit);

	Clear(&s);
	printf("after Clear:\n");
	Traverse(&s, visit);

	//test realloc
	for(int i = 1; i != 20; ++i)
	{
		Push(&s, i);
	}
	printf("after push:\n");
	Traverse(&s, visit);
	for(int i = 30; i != 32; ++i)
	{
		Push(&s, i);
	}
	printf("after push:\n");
	Traverse(&s, visit);

	Destroy(&s);
	printf("after Destroy:\n");
	Traverse(&s, visit);

}
int main()
{
	test();
	return 0;
}
