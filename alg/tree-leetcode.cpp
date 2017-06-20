#include <iostream>
#include "tree-leetcode.h"
using namespace std;

void test_s511()
{
	s500 st;
 	TreeNode *root = st.doCreateBTree();
	s511 s;
	vector<int> vec = s.preTraverse(root);
	cout << "result:" << endl;
	for(vector<int>::size_type i = 0; i != vec.size(); ++i)
	{
		cout << vec[i] << endl;
	}
	
}

void test_s512()
{
	s500 st;
 	TreeNode *root = st.doCreateBTree();
	s512 s;
	vector<int> vec = s.inTraverse(root);
	cout << "result:" << endl;
	for(vector<int>::size_type i = 0; i != vec.size(); ++i)
	{
		cout << vec[i] << endl;
	}
	
}

void test_s513()
{
	s500 st;
 	TreeNode *root = st.doCreateBTree();
	s513_postTra_by_reverse s;
	vector<int> vec = s.postTraverse(root);
	cout << "result:" << endl;
	for(vector<int>::size_type i = 0; i != vec.size(); ++i)
	{
		cout << vec[i] << endl;
	}
	
}

void test_s514()
{
	s500 st;
 	TreeNode *root = st.doCreateBTree();
	s514 s;
	vector<vector<int> > vec = s.levelTraverse(root);//知识点:二维数组
	cout << "result:" << endl;
	for(vector<int>::size_type i = 0; i != vec.size(); ++i)
	{
		for(vector<int>::size_type j = 0; j != vec[i].size(); ++j)//注意vec[i].size()
		{
			cout << vec[i][j] << ",";
		}
		cout <<  ";" << endl;
	}
}

void test_s500_by_ptr2ptr()
{
	s500_by_ptr2ptr st;
 	TreeNode *root = nullptr;
	st.createBTree(&root);
	s514 s;
	vector<vector<int> > vec = s.levelTraverse(root);//知识点:二维数组
	cout << "result:" << endl;
	for(vector<int>::size_type i = 0; i != vec.size(); ++i)
	{
		for(vector<int>::size_type j = 0; j != vec[i].size(); ++j)//注意vec[i].size()
		{
			cout << vec[i][j] << ",";
		}
		cout <<  ";" << endl;
	}
}


void test_s501()
{
	s500_by_ptr2ptr st;
 	TreeNode *root = nullptr;
	st.createBTree(&root);
	s501 s;
	cout << s.getTreeDepth(root) << endl;
}

void test_s517()
{
	s500_by_ptr2ptr st;
 	TreeNode *root = nullptr;
	st.createBTree(&root);
	s514 s;
	s517 reverse_c;
	reverse_c.reverse(root);
	vector<vector<int> > vec = s.levelTraverse(root);//知识点:二维数组
	cout << "result:" << endl;
	for(vector<int>::size_type i = 0; i != vec.size(); ++i)
	{
		for(vector<int>::size_type j = 0; j != vec[i].size(); ++j)//注意vec[i].size()
		{
			cout << vec[i][j] << ",";
		}
		cout <<  ";" << endl;
	}
}

void test_digui()
{

	s500 st;
 	TreeNode *root = st.doCreateBTree();
	s511_digui s;
	s.tra(root);

}

int main()
{
//	test_s511();
//	test_s512();
//	test_s513();
//	test_s514();
//	test_s500_by_ptr2ptr();
//	test_s517();
//	test_s501();
	test_digui();
	return 0;
}
