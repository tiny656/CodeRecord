#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

/*从start到end位置，翻转数组elem*/
void reverse(int *elem, int start , int end)
{
	int i;
	for(i = 0; i <= (end-start)>>1; i++)
	{
		int tmp = elem[start+i];
		elem[start+i] = elem[end-i];
		elem[end-i] = tmp;
	}
}

/*
	Target:将elem向右循环移动dis的距离
	设数组为T = ab组成，b是需要向右移动的个数
	如果移动的dis大于数组的长度n，则dis = dis % n 
	对于T = ab， 需要变成 T' = ba
	则T' = ba = (a'b')'
	即对a翻转，对b翻转，在对整体数组elem翻转
	算法复杂度：O(n)
	空间复杂度：O(1)
*/ 
void move(int *elem, int n, int dis)
{
	dis = dis % n;
	reverse(elem, 0, n-dis-1);
	reverse(elem, n-dis,n-1);
	reverse(elem, 0, n-1);
}

int a[105];
int main()
{
	int n, dis,i;
	scanf("%d %d", &n, &dis);
	for(i = 0; i < n; i++)	scanf("%d", &a[i]);
	move(a, n, dis);
	printf("%d", a[0]);
	for(i = 1; i < n; i++)	printf(" %d", a[i]);
	printf("\n");
	return 0;
}