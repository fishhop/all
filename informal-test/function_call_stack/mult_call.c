int foo1(int m, int n)
{
    int p=m*n;
    return p;
}

int foo(int a, int b)
{
    int c=a+1;
    int d=b+1;
    int e=foo1(c,d);
    return e;
}
 
int main()
{
    int result=foo(3,4);
    return 0;
}
