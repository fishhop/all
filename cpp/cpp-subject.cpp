#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <queue>
#include <map>
using namespace std;


//此处有误区，见我的doc
void rm_3_times(map<int, int> & m)
{
	map<int, int>::iterator it = m.begin();
	while(it != m.end())
	{
		if(it->second % 3 == 0)
		{
			m.erase(it++);
		}
		else
		{
			++it;
		}
	}
}
void rm_3_times_test()
{
	map<int, int> m;
	m.insert(make_pair(1, 1));
	m.insert(make_pair(2, 3));
	m.insert(make_pair(3, 9));
	m.insert(make_pair(4, 12));

	map<int, int>::iterator it = m.begin();
	while(it != m.end())
	{
		cout << it->second << endl;
		++it;
	}

	rm_3_times(m);
	cout << "size:" << m.size() << endl;

	it = m.begin();
	while(it != m.end())
	{
		cout << it->second << endl;
		++it;
	}
}

void erase_vector()
{
    vector<int> iVec;
    vector<int>::iterator it;
    for(int i=0;i<10;i++)
        iVec.push_back(i);
    for(it=iVec.begin();it!=iVec.end();)
    {
        if(*it ==4 || *it == 9)
        {
            it=iVec.erase(it);		//对于vector 不可以erase(it++)
        }
        else
            ++it;
    }

    for(vector<int>::iterator it = iVec.begin(); it < iVec.end(); ++it)
    {
        cout << * it << " ";
    }
    cout << endl << iVec.size();
    cout << endl;

}

size_t strlen_digui(const char *s)
{
	if(!s || !*s)
		return 0;
	return 1 + strlen_digui(++s);
}


int main()
{
//	erase_vector();
	cout << strlen_digui("123") ;
	return 0;
}

