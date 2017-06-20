#!/usr/bin/awk -f
BEGIN{
a[0]="a";
a[1]="b";
for(i=0; i < 3; ++i)
{
print a[i];
}
}
{exit;}
END{exit;}