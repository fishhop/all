#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
	if(!a || !b)
		return;
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void swap_5(int *a, int *b)
{
	if(!a || !b)
		return;
	*a = *a + *b - (*b = *a);//注意:这里存在溢出可能
}



void swap_2(int *a, int *b)
{
	if(!a || !b)
		return;	
	*a = *a + *b;//注意:这里存在溢出可能
	*b = *a - *b;
	*a = *a - *b;
}


void test_swap()
{
	int a = 1, b = 2;
	printf("\n%d,%d\n",a, b);

//	swap_2(&a, &b);
//	printf("%d,%d\n",a, b);

	swap(NULL, &b);
	printf("%d,%d\n",a, b);

//	swap_3(&a, &b);
//	printf("%d,%d\n",a, b);

//	swap_4(&a, &b);
//	printf("%d,%d\n",a, b);

//	swap_5(&a, &b);
//	printf("%d,%d\n",a, b);	
}

void Traverse(int *a, int len)
{
	for(int i=0; i<len; ++i)
	{
		printf("%d,",a[i]);
	}
	printf("\n");
}



/*
时间复杂度:O(n2)
空间复杂度:O(1)
*/
// 1.插入排序
//从第二个开始，依次往左边串，每次都到头
void InsertSort(int *a, int len)
{
	if(!a || len < 2)
		return;
	int i, j, tmp;											//【注意】此类双循环，确定外循环i的起点:i是j的最大范围
	for(i = 1; i < len; ++i)					//注意j必须要在这里定义!!因为在下面的for循环之外有用到
	{
		tmp = a[i];								//下面,tmp < a[j],如何确定是<，就看什么条件下可以继续执行循环，例数组:1，2
		for(j = i-1; j>=0 && tmp < a[j]; --j)	//tmp < a[j]放在这里和在下面用if(tmp < a[j])，效果不同，这里可以让循环提前终止!!!不必浪费时间，下面则需要break
		{
			a[j+1] = a[j];
		}
		a[j+1] = tmp;							//tmp比a[j]大，要插在a[j]后，即a+1
	}
}



// 2.希尔排序
//插入排序中的1全部换成gap, --j中也隐藏了1,也要换
void ShellInsert(int *a, int gap, int len)
{
	if(!a || len < 2)
		return;
	int i, j, tmp;
	for(i = gap; i < len; ++i)		//这里++i不变,不然岂不漏掉一些元素了。
	{
		tmp = a[i];
		for(j = i-gap; j>=0 && tmp < a[j]; j -= gap)
		{
			a[j+gap] = a[j];
		}
		a[j+gap] = tmp;						//for完时-gap，这里+gap，相当于a[j]
	}	
}
void ShellSort(int *a, int len)	
{
	for(int gap = len/2; gap > 0; gap /= 2)
	{
		ShellInsert(a, gap, len);
	}
}

void ShellSort_2(int *a, int len)	
{
	int dlta[] = {5, 3, 1};
	for(int i = 0; i<3; ++i)
	{
		ShellInsert(a, dlta[i], len);
	}
}

/*void ShellInsert(int *a, int gap, int len)
Before sort:
5,3,7,8,9,66,1,7,6,33,4,
i=5,tmp=66      5,3,7,8,9,66,1,7,6,33,4,
i=6,tmp=1       5,3,7,8,9,66,1,7,6,33,4,
                5,3,7,8,9,66,[3],7,6,33,4,
i=7,tmp=7       5,[1],7,8,9,66,3,7,6,33,4,
i=8,tmp=6       5,1,7,8,9,66,3,7,6,33,4,
                5,1,7,8,9,66,3,7,8,33,4,
i=9,tmp=33      5,1,7,6,9,66,3,7,8,33,4,
i=10,tmp=4      5,1,7,6,9,66,3,7,8,33,4,
                5,1,7,6,9,66,3,7,8,33,[66],
                5,1,7,6,9,[5],3,7,8,33,66,
i=3,tmp=6       [4],1,7,6,9,5,3,7,8,33,66,
i=4,tmp=9       4,1,7,6,9,5,3,7,8,33,66,
i=5,tmp=5       4,1,7,6,9,5,3,7,8,33,66,
                4,1,7,6,9,7,3,7,8,33,66,
i=6,tmp=3       4,1,5,6,9,7,3,7,8,33,66,
                4,1,5,6,9,7,[6],7,8,33,66,
                4,1,5,[4],9,7,6,7,8,33,66,
i=7,tmp=7       [3],1,5,4,9,7,6,7,8,33,66,
                3,1,5,4,9,7,6,9,8,33,66,
。。。。。
After sort:
1,3,4,5,6,7,7,8,9,33,66,
*/


//3. 冒泡排序
//每次都从头开始，往后前进，俩俩比较，一轮后至少确保较小的数都有往前挪了一步。
void BubbleSort(int *a, int len)
{
	if(!a || len < 2)
		return;
	for(int i = len-1, chg = 1; chg && i > 0; --i)	//因为第一轮中，最后两个已比较，所以下一轮跳过
	{
		chg = 0;				// 交换标志，如果这一趟没有交换，说明排序已经完成。
		for(int j = 0; j < i; ++j)  //change不可以放在这里!!不然相当于定义新的change
		{
			if(a[j] > a[j+1])
			{
				swap(&a[j], &a[j+1]);
				chg = 1;
			}
		}
	}
}

/*
仅前面len个无序，那么在第一趟遍历后,
最后发生交换的位置必定小于len，
记录下这位置，第二次只要从数组头部遍历到这个位置就可以了
*/
void BubbleSort_2(int *a, int len)
{
	if(!a || len < 2)
		return;	

	int j, chg;
	chg = len;
	while(chg > 0)
	{
		len = chg;
		chg = 0;
		
		for(j = 0; j < len-1; ++j)//原生态的冒泡排序中，外层for循环起到改变下面的len的作用，注意体会
		{
			if(a[j] > a[j+1])
			{
				swap(&a[j], &a[j+1]);
				chg = j;//这里change = j;相当于将下一次while循环里的 for循环中的len减1(或更多)，
			}			//至于change，考虑=0的情况便于推倒
		}
	}
}



//4.快速排序
//原理:http://developer.51cto.com/art/201403/430986.htm
/*
1.为什么要右边先出发?
http://blog.csdn.net/w282529350/article/details/50982650

因为,选择最左边的为基准，要从基准的对面右边出发，

当然，选择最右边的为基准也是可以的，反之...


2.体会下面程序中"Z"字形走位,tmp = a[low];a[low] = a[high];a[high] = a[low];a[low] = tmp;

*/
//据说非递归实现要慢，纳尼?
//http://developer.51cto.com/art/201403/430986.htm
//http://www.cnblogs.com/foreverking/articles/2234225.html
/*
原理:
一次可以确保一个元素位置是最终位置:即，其左边都比他小，右边都比他大。
然后递归重复。左边作为标志，右边先开始扫描，再左边开始扫描
*/
int part(int *a, int b, int e)
{
	int tmp = a[b];						//基准处于悬空状态
	while(b < e)
	{
		while(b < e && tmp <= a[e])		//无忽略"="，是:>=，//a[e] >= tmp,如何确定是<，就看什么条件下可以继续执行循环，显然是
			--e;
										//从高往低找小的，以消除逆序，所以这里只管把小的移到前边去，
										//因为a[low]在之前已经储存了,腾出空位了，所以这里可以改变a[low]，同时将a[high]腾出了一个空位
		a[b] = a[e];
		while(b < e && tmp >= a[b])
			++b;
		a[e] = a[b];					//b给了e，b空出来了，下一轮又填上
	}
	a[b] = tmp;							//基数归位,因为最开始处储存了a[low]，提取出来了，所以这里要还原给通过循环实际找到的low
	return b;
}
void qSort(int *a, int b, int e)
{
	if(!a || b >= e)	//因为low >= high的话，下面依然会执行一系列操作，没用的!当然要禁止
		return;			//所以无需参与排序

	int m = part(a, b, e);	//通过次函数可以体会到:也是一种交换排序
	qSort(a, b, m-1);	//注意和归并排序区分,这里要排除m
	qSort(a, m+1, e);	//无丢 +1,因为mid的位置是合适的，前面的都比它小，后面的都比它大
}



//5.选择排序
void SelectSort_2(int *a, int n)
{
	if(!a || n < 2)
		return;		
	for(int i = 0, ix; i < n-1; ++i)
	{
		ix = i;
		for(int j = i+1; j < n; ++j)	//这里无条件循环，所以，时间复杂度最好最坏均是O(n2)
		{
			if(a[ix] > a[j])
				ix = j;
		}
		if(ix != i)						
			swap(&a[i], &a[ix]);
	}
}


//6. 堆排序
//http://blog.csdn.net/morewindows/article/details/6709644/
// 从0开始计算 i节点的子节点为 2*i+1, 2*i+2 
/* 已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数 */
/* 调整H.r[s]的关键字,使H.r[s..m]成为一个大顶堆(对其中记录的关键字而言) */
void shift(int *a, int b, int e)
{
	int tmp = a[b];
	int i = 2 * b + 1;				//i = 2*beg + 1 左孩子
	while(i <= e)					//i = e时，也要和子节点比较调整，所以勿漏=
	{
		if(i+1 <= e && a[i] < a[i+1])  //在左右孩子中找最大的; i+1 < end,这个用来确保i+1节点存在
			++i;                      //变相地将最大者下标获取
		if(tmp >= a[i])          	//父节点比两个子节点都大
			break;               	//因每次都是只将大顶堆中的顶节点和最后一个节点交换,故交换后第一个节点后面的节点是满足堆的性质的
		else
			a[b] = a[i];         	//把较大的子结点往上移动,替换i的父结点  
		b = i;           			//暂存子节点的下标作为下一轮父节点，以方便最后交换父子节点的值
		i = 2 * i + 1;   			//上两步将传进来的beg的子节点i的值赋给了beg,所以这里要进入节点i的子节点，以便找出两个子节点中较大的一个给i
	}
	a[b] = tmp;          			//将旧堆顶赋给后面的节点,这里不是Z字走位，因为上面 b = i;
}
void HeapSort(int *a, int len)
{
	if(!a || len < 2)
		return;	
											//心里有堆即有堆，下面进行堆的初始化，即:调整堆
	for(int i = len/2 - 1; i >= 0; --i)		//由堆的性质:a[len/2 - 1]为堆的最后一个非叶子节点
		shift(a, i, len-1);					//从下往上一圈一圈逐渐变大
	for(int i = len-1; i > 0; --i)			//>0
	{
		swap(&a[0], &a[i]);					//交换要在先，因为上面已经建好了大顶堆/* 将堆顶记录和当前未经排序子序列H.r[0..i]中最后一个记录相互交换 */
		shift(a, 0, i-1);					//注意:i-1 ,因为上面交换后，i已经是在有序序列里，将H.r[0..i-1]重新调整为大顶堆 */
	}
}


//7.归并排序
//http://blog.csdn.net/morewindows/article/details/6678165
//程序在易读性、空间消耗之间取得平衡即可，若实在要求性能，这里可以少申请一个i，直接用b
void Merge(int *a, int *tmp, int b, int m, int e)
{
	int i = b, k = b, j = m+1;	//i, j, k三个游离标尺
	while(i <= m && j <= e)
	{
		if(a[i] < a[j])			//选择小的
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}
	while(i <= m)
		tmp[k++] = a[i++];
	while(j <= e)
		tmp[k++] = a[j++];
	for(int i = b; i <= e; ++i)		//将tmp拷贝到a中去
		a[i] = tmp[i];             
}
//b:begin, m:middle, e:end
void doMsort(int *a, int *tmp, int b, int e)
{
	if(b < e)
	{
		int m = (b + e)/2; 			
		doMsort(a, tmp, b, m);	//这里是m，不然m漏掉了，区分于二分查找等。
		doMsort(a, tmp, m+1, e);
		Merge(a, tmp, b, m, e);	//按照一次来看来理解,上面两步先sort两半边，这步合并两半边
	}
}
void mSort(int *a, int len)
{
	if(!a || len < 2)
		return;		
	int *tmp = (int *)malloc(len * sizeof(a[0]));	//所以,空间复杂度O(N)
	doMsort(a, tmp, 0, len-1);
	free(tmp);
	
}



#define __NO__SEE__
/*
当两个指针变量指向同一个地址的数据时，只有传统写法可以工作。
究其原因传统写法把地址上的值取了出来，而异或写法直接在原地址上进行值运算，一次异或之后值就成了0，两个指针都指向这个地址，后面再怎么异或也只能是0了。可以画个图来试试。
a ⊕ b ⊕ a = b.
*/
void swap_3(int* a, int* b)
{
	if(!a || !b)
		return;
	*a ^= *b;  
	*b ^= *a;  
	*a ^= *b;  
}  

void swap_4(int *a, int *b)
{
	if(!a || !b)
		return;
	*a ^= *b ^= *a ^= *b;
}

void InsertSort_2(int *a, int n)
{
	if(!a || n < 2)
		return ;
	for(int i = 1, j, tmp; i < n; ++i)
	{
		tmp = a[i];
		for(j = i-1; j >= 0; --j)
		{
			if(a[j] > tmp)
				a[j+1] = a[j];
			else
				break;			
		}
		a[j+1] = tmp;
	}
}


int main()
{
	int a[] = {5,3,7,8,9,2,1,7,6,6,6,19,20,13};
//	printf("Before sort:\n");
//	Traverse(a, sizeof(a)/sizeof(a[0]));
	
	InsertSort(a, sizeof(a)/sizeof(a[0]));
//	InsertSort_2(a, sizeof(a)/sizeof(a[0]));

//	ShellSort(a, sizeof(a)/sizeof(a[0]));	
//	ShellSort_2(a, sizeof(a)/sizeof(a[0]));

//	BubbleSort(a, sizeof(a)/sizeof(a[0]));
//	BubbleSort_2(a, sizeof(a)/sizeof(a[0]));

//	qSort(a, 0, sizeof(a)/sizeof(a[0]));
//	SelectSort(a, sizeof(a)/sizeof(a[0]));
//	SelectSort_2(a, sizeof(a)/sizeof(a[0]));

//	HeapSort(a, sizeof(a)/sizeof(a[0]));
//	mSort(a, sizeof(a)/sizeof(a[0]));
//	printf("After sort:\n");
	Traverse(a, sizeof(a)/sizeof(a[0]));

//	test_swap();

	return 0;
}
