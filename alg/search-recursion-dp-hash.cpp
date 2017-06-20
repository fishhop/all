#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <stdio.h>
#include <queue>
#include <stdlib.h>

using namespace std;

typedef struct node  
{  
    int val;  
    struct node  *nex;  
}Node;  
  

#define __SUM__


//*********************               ***********************
//*********************  爬楼梯问题   ***********************
/*LeetCode(70)Climbing Stairs
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
当i = 1时，f(1) = 1,
当i = 2时，f(2) = 2;
当i > 3时，f(i) = f(i-1) + f(i-2)。
*/
//递归解法
long long climb_stairs_digui(size_t n)//注意long long，防止溢出
{
	if(n < 3)
		return n;
	return climb_stairs_digui(n-1) + climb_stairs_digui(n-2);
}


//非递归
long long climb_stairs_for(int n)
{
	if(n < 3)
		return n;
	long long s = 0;
	for(int  i = 3, s1 = 1, s2 = 2; i <= n; ++i)
	{
		s = s1 + s2;
		s1 = s2;
		s2 = s;
	}
	return s;
}


//动态规划
int climb_stairs_dp(int n)
{
	if( n < 3)
		return n;
	int *dp = new int[n+1]();		//注意，是n+1!!!
	dp[1] = 1;
	dp[2] = 2;
	int i = 3;
	for(; i <= n; ++i)
	{
		dp[i] = dp[i-1] + dp[i-2];
	}
	int ret = dp[n];				//条则"自"。即i在上面的循环后已经加一了，所以这里错:ret = dp[n]
	delete []dp;
	return ret;
}
void climb_stairs_test()
{
	long long s;
	s = climb_stairs_digui(5);
	cout << s << endl;

	s = climb_stairs_for(5);
	cout << s << endl;

	s = climb_stairs_dp(5);
	cout << s << endl;
}





#define __RECURSION__

int fabonacci(int n)
{
	if(n == 0)
		return 0;
	if(n == 1)
		return 1;
	return fabonacci(n - 1) + fabonacci(n - 2);
}



int jie_cheng(int n)
{
	if(n == 0)
		return 1;//边界
	return n * jie_cheng(n-1);

}

void jie_cheng_test()
{
	cout << jie_cheng(5) << endl;
}


//*********************               ***********************
//*********************  汉诺塔       ***********************

/*
盘子从上到下编号:1\2\3..

*/
void move(int n, char a, char b)
{
	printf("%d:%c -> %c\n", n, a, b);
}

//注意理解第2、3、4 三个参数含义:
//han_nuo_ta:将2个上的n个盘子移动到第4个参数上，以第3个参数做辅助
//move:将n号从第一个参数移动到第二个参数
//http://wenku.baidu.com/view/b85239f50508763230121225.html
//【理解】:递归函数的理解，按照只有一次来理解:举例:n=2
void han_nuo_ta(int n, char a, char b, char c)
{
	if(n == 1)
		move(1, a, c);
	else								//注意是else，因前面没有return。
	{
		han_nuo_ta(n-1, a, c, b);		//所有n-1个从a移动到b
		move(n, a, c);					//第n个从a移动到c
		han_nuo_ta(n-1, b, a, c);		//所有n-1个从b移动到c	
	}
}

void han_nuo_ta_test(int argv, char **arg)
{
	char a = 'a', b = 'b', c = 'c';

	if(argv != 2)
	{
		printf("pram error!\n");
	}
	//3:三阶汉诺塔
	
	han_nuo_ta(atoi(*(arg + 1)), a, b, c);
	
}





#define __SEARCH__


//*********************               ***********************
//*********************  二分查找    ***********************
//ALG P41
int binary_search(int *a,  int n, int t)
{
	if(!a || n < 1)
		return -1;
	int b = 0, e = n-1, m;
	while(b <= e)
	{
		m = (b + e)/2;
		if(t < a[m])
			e = m - 1;
		else if(t > a[m])
			b = m + 1;
		else				// t == a[m]
			return m;		//放最后，因==出现概率小，这样代码效率更高
	}
	return -1;
}

//递归实现
int binary_search_recursion(int *a, int b, int e, int t)
{
	if(!a || b > e)
		return -1;
	
	int m = (b + e)/2;
	
	if(t == a[m])
		return m;
	if(t < a[m])
		return binary_search_recursion(a, b, m-1, t);
	else
		return binary_search_recursion(a, m+1, e, t);
}


//*********************               ***********************
//*********************  第二大的数     ***********************

//题目：写一个函数找出一个整数数组中，第二大的数。
//初始化最大值为a[0]，次大值为a[1]，遍历一次，每次比较并更新最大值和次大值，最后就可以得到次大值。  
int find_second_max(int *a, int len)  
{
	if(!a || len < 2)
		return 0;
	int max = a[len - 1], sec = a[len - 1];
	for(--len; len >= 0; --len)
	{
		if(sec == max)
		{
			if(max < a[len])
				max = a[len];
			else if(max > a[len])
				sec = a[len];	
		}
		else
		{
			if(a[len] > max)
			{
				sec = max;
				max = a[len];
			}
			else if(a[len] > sec)
			{
				sec = a[len];
			}
		}
	}
	return sec;
}  



//*********************               ***********************
//*********************  找出在序列中出现超过一半以上的数字 ***********************

/*
这题是《剑指offer》上的原题，可惜当时只想记得用快排的方法来做。书上记录了一种更好的方法，
根据数字出现次数与序列个数的关系：超过一半表示相同元素的个数，比其他元素个数至少多1。
可以写出如下算法思路： 
1）定义一个计数器count = 1，并记录当前的元素为key； 
2）遍历序列，如果下一个元素与key不相同则count-；相同则count++； 
3）当count==0时，将当前元素重新赋值为key，并令count=1。 
这样最后的key就是我们要求得元素。 

并不是找到了出现最多的,反例:22341.所以只适合查找出现一半以上的。
*/
int find_appear_than_half(int* arr,int len)
{
    if(!arr || len <= 0) 
		return -1;
	
    int num = 1,key=arr[0];
    for(int i=1; i<len; ++i)
    {
        if(num == 0) 
        {
            key = arr[i];
            num = 1;
        }
        else if(key == arr[i])
			num++;
        else 
			num--;
    }
    //当然最后要验证一下key是不是真的出现了一半以上，上面并不是找到了出现最多的
    num = 0;
    for(int i=0; i<len; ++i)
    {
        if(key == arr[i]) 
			num++;
    }
    if(num < len/2) 
		return -1;
    return key;
}

int find_appear_than_half_multiset(int* arr,int len)
{
	return 0;
}

#define __HASH__

//*********************               ***********************
//*********************  字符串哈希   ***********************
unsigned int SDBM_hash(char *str)
{
    unsigned int hash = 0;
 
    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
 
    return (hash & 0x7FFFFFFF);
}


//详解:<ULK_3，p111>
unsigned long hash_long(unsigned long val, unsigned int bits)   
{   
    unsigned long hash = val * 0x9e370001UL;   
    return hash >> (32 - bits);   
}  
int hash_long_test()  
{  
    // 假设hash table的长度为8(2^3)  
    int bits = 3;  
    int elem_num = 1<<bits;  
    int vec[elem_num];  
                                                                                                                                      
    for (int i=0; i<elem_num; ++i)  
        vec[i] = 0;  
    srand(time(NULL));  
    for(int i=0; i<1000; i++)  
    {     
        int num = rand();  
        int elem_idx = hash_long(num, bits);  
        vec[elem_idx] ++;   
    }     
    cout << "========================\n" << endl;  
    for (int i=0; i<elem_num; ++i)  
    {     
        cout << "vec:" << i << "," << vec[i] << endl;  
    }     
    return 0;  
}  


#define __OTHRES__
/*
Fisher–Yates shuffle洗牌算法
每次随机选取一个数，然后将该数与未抽样数组中最后(或最前)的
元素相交换(如果随机选中的是最后/最前的元素，则相当于没有发生交换)；
然后缩小选取数组的范围，去掉最后的元素,即之前随机抽取出的数。
重复上面的过程，直到剩余数组的大小为1，即只有一个元素时结束：
http://blog.csdn.net/geniusluzh/article/details/8443682
http://blog.csdn.net/robinjwong/article/details/18261393
证明随机:各个元素在j位置出现概率相等，归纳。

时间复杂度:O(n),空间:O(1)
*/
//推广:也就是乱序算法。用处很多
void xi_pai(int *a, int n)
{
	if(!a || n < 2)
		return;
	for(int tmp, i; n > 0; --n)
	{
		i = rand() % n;		//生成0 - n-1之间的随机数
		tmp = a[i];
		a[i] = a[n];
		a[n] = tmp; 
	}

}
void xi_pai_test()
{
	int a[54] = {};
	for(int i = 0; i < 54; ++i)
	{
		a[i] = i;
		cout << a[i] << " " ;
	}
	cout << endl;

	xi_pai(a, sizeof(a)/sizeof(a[0]));

	for(int i = 0; i < 54; ++i)
	{
		cout << a[i] << " " ;
	}
	cout << endl;
	
}


bool is_little_endia()
{
	int val = 1;
	return *((char *)(&val));
}

void is_little_endia_test()
{
	cout << "Your PC is LittleEndia? :\t" << is_little_endia() << endl;
}


int main()
{
//	int a[]={1,27,3,5,2,-22};		//数组必须有序，不然比如这个里找2就找不到,$ g++ 9-medium.cpp ;a:   -1
	int a[]={1,2, 5,6,34,98};		//数组必须有序
	cout << binary_search(a, sizeof(a)/sizeof(a[0]), 2);
//	cout << binary_search_recursion(a, 0, sizeof(a)/sizeof(a[0])-1, 33);


//	cout << count_bit_in_binnary(0b111010) << endl;

//	int a[] = {2, 4, 3, 5};
//	int a[] = {3, 4, 4, 4};
//	int a1[] = {5, 1, 2, 4};
//	int a2[] = {3, 5, 5, 4};
//	cout << find_second_max(a, sizeof(a)/sizeof(a[0])) << endl;
//	cout << find_second_max(a1, sizeof(a1)/sizeof(a1[0])) << endl;
//	cout << find_second_max(a2, sizeof(a2)/sizeof(a2[0])) << endl;


//	is_little_endia_test();

//	hash_long_test();

	return 0;
}
