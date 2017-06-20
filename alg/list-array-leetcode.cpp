#include <iostream>
#include "list-array-leetcode.h"
using namespace std;

void test211()
{
	int a[] = {1,2,2,3,4,4,4,5};
	class s211 s;
	int len = s.rmDuplicate(a, 8);
	for(int i = 0; i < len; ++i)
	{
		cout << a[i] << endl;
	}
}

void test212()
{
	int a[] = {1,2,2,3,4,4,4,4,5,5,5,5};
	class s212 s;
	int len = s.rmDuplicate(a, sizeof(a)/sizeof(a[0]));
	for(int i = 0; i < len; ++i)
	{
		cout << a[i] << endl;
	}
}

void test213()
{
	int a[] = {7};
	class s213 s;
	int i = s.searchRotedArr(a, sizeof(a)/sizeof(a[0]), 7);
	cout << i << endl;
}

void test221()
{
	int a[] = {5,2,6};
	Node *p = new Node;
	Node *head = p;
	for(int i = 0; i < 3; ++i)
	{
		p->nex = new Node;
		p = p->nex;
		
		p->nex = nullptr;
		p->val = a[i];
	}
	s221 s;
	Node *pp = s.add2Num(head->nex, head->nex);
	while(pp)
	{
		std::cout << pp->val << std::endl;
		pp = pp->nex;
	}
}

void test222()
{
	class s222 s;
	Node *p = new Node;
	Node *head = p;
	for(int i = 0; i < 10; ++i)
	{
		p->val = i;
		p->nex = new Node;
		p = p->nex;
	}
	//需注意:p->val在循环结束时没有被赋值
	p->nex = nullptr;//这种方式，只用一处赋值nullptr
	
	p = head;
	for( ; p != nullptr; p = p->nex)
	{
		cout << p->val << " : " << &(p->val)<<endl;
	}
	cout <<endl;
	
	Node *hh = s.reverseBetween(head, 1, 10);
	for( ; hh != nullptr; hh = hh->nex)
	{
		cout << hh->val << " : " << &(hh->val)<<endl;
	}

	//链表内存释放
	while(head != nullptr)
	{
		p = head;
		head = head->nex;
		delete p;
	}

}

void test223()
{
	class s223 s;
	int a[] = {4,2,2,7,5,3,9,6};
	Node *p = new Node;
	Node *head = p;
	for(int i = 0; i < 8; ++i)
	{
		p->nex = new Node;
		p->nex->val = a[i];
		p = p->nex;
	}
	//需注意:p->val在循环结束时没有被赋值
	p->nex = nullptr;//这种方式，只用一处赋值nullptr
	
	p = head->nex;
	for( ; p != nullptr; p = p->nex)
	{
		cout << p->val << " : " << &(p->val)<<endl;
	}
	cout <<endl;
	
	Node *hh = s.Partion(head->nex, 5);
	for( ; hh != nullptr; hh = hh->nex)
	{
		cout << hh->val << " : " << &(hh->val)<<endl;
	}

	//链表内存释放
	while(head != nullptr)
	{
		p = head;
		head = head->nex;
		delete p;
	}
}
/*
4 : 0x20030338
2 : 0x20030348
2 : 0x20030358
7 : 0x20030368
5 : 0x20030378
3 : 0x20030388
9 : 0x20030398
6 : 0x200303a8

4 : 0x20030338
2 : 0x20030348
2 : 0x20030358
3 : 0x20030388
7 : 0x20030368
5 : 0x20030378
9 : 0x20030398
6 : 0x200303a8

*/

void test224()
{
	class s224 s;
	int a[] = {4,2,2,7,5,3,9,6};
	Node *p = new Node;
	Node *head = p;
	for(int i = 0; i < 8; ++i)
	{
		p->nex = new Node;
		p->nex->val = a[i];
		p = p->nex;
	}
	//需注意:p->val在循环结束时没有被赋值
	p->nex = nullptr;//这种方式，只用一处赋值nullptr
	
	p = head->nex;
	for( ; p != nullptr; p = p->nex)
	{
		cout << p->val << " : " << &(p->val)<<endl;
	}
	cout <<endl;
	
	Node *hh = s.rmDuplicate(head->nex);
	for( ; hh != nullptr; hh = hh->nex)
	{
		cout << hh->val << " : " << &(hh->val)<<endl;
	}

	//链表内存释放
	while(head != nullptr)
	{
		p = head;
		head = head->nex;
		delete p;
	}
}

void test225()
{
	class s225 s;
	int a[] = {4,4,2,2,7,5,3,9,6,6};
	Node *p = new Node;
	Node *head = p;
	for(unsigned int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		p->nex = new Node;
		p->nex->val = a[i];
		p = p->nex;
	}
	//需注意:p->val在循环结束时没有被赋值
	p->nex = nullptr;//这种方式，只用一处赋值nullptr
	
	p = head->nex;
	for( ; p != nullptr; p = p->nex)
	{
		cout << p->val << " : " << &(p->val)<<endl;
	}
	cout <<endl;
	
	Node *hh = s.rmDuplicate(head->nex);
	for( ; hh != nullptr; hh = hh->nex)
	{
		cout << hh->val << " : " << &(hh->val)<<endl;
	}

	//链表内存释放
	while(hh != nullptr)
	{
		p = hh;
		hh = hh->nex;
		delete p;
	}
}
void test226()
{
	class s226 s;
	int a[] = {4,9,2,8,7,5,3,9,6,11};
	Node *p = new Node;
	Node *head = p;
	for(unsigned int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		p->nex = new Node;
		p->nex->val = a[i];
		p = p->nex;
	}
	//需注意:p->val在循环结束时没有被赋值
	p->nex = nullptr;//这种方式，只用一处赋值nullptr
	
	p = head->nex;
	for( ; p != nullptr; p = p->nex)
	{
		cout << p->val << " : " << &(p->val)<<endl;
	}
	cout <<endl;
	
	Node *hh = s.rotate(head->nex, 2);
	for( ; hh != nullptr; hh = hh->nex)
	{
		cout << hh->val << " : " << &(hh->val)<<endl;
	}

	//链表内存释放
	while(hh != nullptr)
	{
		p = hh;
		hh = hh->nex;
		delete p;
	}
}

//链表从后往前数转变为从前往后数
void test227()
{
	class s227 s;
	int a[] = {1};
//	int a[] = {1,2,3,4,5,6,7,8};
	Node *p = new Node;
	Node *head = p;
	for(unsigned int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		p->nex = new Node;
		p->nex->val = a[i];
		p = p->nex;
	}
	//需注意:p->val在循环结束时没有被赋值
	p->nex = nullptr;//这种方式，只用一处赋值nullptr
	
	p = head->nex;
	cout << "origin list:" << endl;
	for( ; p != nullptr; p = p->nex)
	{
		cout << p->val << " : " << &(p->val)<<endl;
	}
	cout <<endl;
	
//	Node *hh = s.rmNthNodeFromEnd(head->nex, sizeof(a)/sizeof(a[0]));
//	Node *hh = s.rmNthNodeFromEnd(head->nex, sizeof(a)/sizeof(a[0]) + 1);
//	Node *hh = s.rmNthNodeFromEnd(head->nex, 1);
	Node *hh = s.rmNthNodeFromEnd(head->nex, 1);

	cout << "after del:" << endl;
	for( ; hh != nullptr; hh = hh->nex)
	{
		cout << hh->val << " : " << &(hh->val)<<endl;
	}

	//链表内存释放
	while(hh != nullptr)
	{
		p = hh;
		hh = hh->nex;
		delete p;
	}
}


void test_s61_less_var_less_code()
{
//	int a[10] = {2,4,7};		//要有10!!，这样这个数组才有足够的空间容纳b!!!!
//	int b[] = {1,5,8};

//	int a[10] = {2};		//要有10!!，这样这个数组才有足够的空间容纳b!!!!
//	int b[] = {1,3,4};

	int a[10] = {2};		//要有10!!，这样这个数组才有足够的空间容纳b!!!!
	int b[] = {1};


	s61_less_var_less_code s;
	s.mergeSortedArr(a, 1,b ,sizeof(b)/sizeof(b[0]));
	for(int i = 0; i < 1 + sizeof(b)/sizeof(b[0]); ++i)
		cout << i << ":" << a[i] << endl;
}



void test_s61_less_var()
{
//	int a[10] = {2,4,7};		//要有10!!，这样这个数组才有足够的空间容纳b!!!!
//	int b[] = {1,5,8};

//	int a[10] = {2};		//要有10!!，这样这个数组才有足够的空间容纳b!!!!
//	int b[] = {1,3,4};

	int a[10] = {2};		//要有10!!，这样这个数组才有足够的空间容纳b!!!!
	int b[] = {1};


	s61_less_var s;
	s.mergeSortedArr(a, 1,b ,sizeof(b)/sizeof(b[0]));
	for(int i = 0; i < 1 + sizeof(b)/sizeof(b[0]); ++i)
		cout << i << ":" << a[i] << endl;
}



void test_s61()
{
	int a[10] = {2,4,7};
	int b[3] = {1,5,8};
	s61 s;
	s.mergeSortedArr(a, 3, b, 3);
	for(int i = 0; i < 6; ++i)
		cout << a[i] << endl;
}

void test_s66()
{
	int a[5] = {3,4,-1,1};
	s66 s;
	cout << s.findFirstMissingInt(a, 4) << endl;
}

void test_s72()
{
	int a[4] = {1,2,4,5};
	s72 s;
	cout << s.searchInsertPosition(a, 4, 3) << endl;
}



void test_revOutput()
{
	int a[] = {4,2,2,7,5,3,9,6};
	Node *p = new Node;
	Node *head = p;
	for(int i = 0; i < 8; ++i)
	{
		p->nex = new Node;
		p->nex->val = a[i];
		p = p->nex;
	}
	//需注意:p->val在循环结束时没有被赋值
	p->nex = nullptr;//这种方式，只用一处赋值nullptr
	
	p = head->nex;
	for( ; p != nullptr; p = p->nex)
	{
		cout << p->val << " : " << &(p->val)<<endl;
	}
	cout <<endl;

	revOutput s2;
	s2.reverseOutput2(head->nex);
		

	//链表内存释放
	while(head != nullptr)
	{
		p = head;
		head = head->nex;
		delete p;
	}
}


int main()
{
//	test211();
//	test212();
//	test213();	
//	test221();
//	test222();
//	test223();
//	test224();
//	test225();
//	test226();	
//	test227();	
//	test_revOutput();

	test_s61_less_var_less_code();
	return 0;
}
