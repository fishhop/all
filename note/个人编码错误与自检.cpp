
【检查-索引】
空匹专头终，极域自正名，分内快

【检查-完整】
空值		【*str == '\0' 和 str == NULL 是两种情况注意区分】【p && p->next 用时记得先判p的有效性】
			【栈pop时看是否size已为0】
类型匹配	【return值、指针赋值时的类型(const char * ——> char*; char * ——> void *；void ——> char *；long long ——> (int)res)】
			【赋值时要判断两个数不相等】【找不到，返回-1】
专业		【参数const（const char *）、函数成员后const】【inline】【size_t】【::size_type】
头尾		【链表操作的头尾处理】【 最后记得给头赋值（*pHead = preHead.next;）】
终			【字符串末尾添加'\0'】【链表末尾p2->nex = nullptr】

极值		【0，“”，null，数组0个、1个元素】
有效域		【{}之外变量】【返回了局部变量的引用】【std】【delete之前p已变】
自增		【没有++或--导致死循环】【++后值已变（return中判断时）】
非负（0正）	【size_t】【unsigned int】
变量名		【是否定义，与定义的是否一致，如: a和arr。】

分内死		【分成多个函数，步步为营】
内			【内循环别一直while忘了外循环的界限，如：while(s != h && *s != ' ')--s；】
快			【手写就别讲究变量命名了！快准第一】


【注意】
先写出可能遇到的坑，再继续写;
逻辑简单就好，不要图花哨；

while(n > len)中没有n++或s++，或p1 = p1->nex;导致死循环。

//1.是否返回局部作用域变量
TreeNode *createBTree()
{
	...
	else
	{
		TreeNode *p = new TreeNode;
		p->val = val;
		.....
	}
	return p;//错
}

//2.
memPool = (ADDR_LIST_NODE *)calloc(getIpAddrNum(), sizeof(ADDR_LIST_NODE));
if (NULL == memPool)
	return;
for (i=0; i<getMaxIpAddrNum(); ++i)
{
	lstAdd(&AddrMemPoolFreeList, (NODE*)&(memPool[i]));//calloc之后强制转换，好处：mempool可以按数组访问。
}

//3.命名空间
using namespace std；
或
std::string mystr("hah");
std::count(v.begin(), v.end(), *it);

//4.返回值
return *this;

//5.const 引用，对于能定义const的地方就定义为const
read(std::istream &in, const cla &c)
std::string get_book() const
{}

//6.new，新的链表节点等，记得申请内存。

/*
7.考虑极限情况，如出队，假如删除的节点到了rear节点（单独用rear和front指针来标记头尾，内容变化时指针要相应变化）
	链表：删除头、尾特殊考虑。
*/

//8.检查程序时，举例举出几个典型的例子，在程序中模拟走一遍看看。

/*
9.for循环，与vec.size()等比较时，变量i 要定义为如 vector<int>::size_type ix = 0;
否则，会有编译警告:有符号和无符号数之间不可以进行比较
*/

/*
10.多用size_t啊，在c或c++都是，
情况：
数组下标，memcpy等size参数，
*/

//数组的引用，下面中[10]中的10不能少，不然编译错误
TreeNode *createBTree(TreeNode *p, int (&a)[10], int n)

//排序等算法中，简写字母以减少工作量，如:beg -> b; end -> e;


总结：几种容器中，对于vector，不能从头部插入、删除，所以如pop_front之类的操作都不支持。

