
1.素数的定义
  只能被1和它自己整除的自然数称为素数，特别规定1不属于素数。


2.求法
(1)根据素数的定义，很明显，如果一个数是素数<==>它的因子只包含1和它本身。
因此可以根据判别某个数的因子的方法来判断其是否是素数。   
int isprime(int n)
{
	int i;
	for(i=2;i<=(int)sqrt((double)n);i++)
	{
		if(n%i==0)    //如果n存在其它因子,则必定不是素数
		{
			return 0;
		}
	}
	return 1;
}



(2)筛选法：对于一个数n，如果是素数，那么2*n，3*n，4*n，必定不是素数。
const int MAXN = 500000;
bool is_prime[500001];
int prime[500001];
/*筛法求素数*/
int len = 0;
void init()
{
	int i,j;
	memset(is_prime, 0, sizeof(int)*(n+2));
	is_prime[0] = 1; is_prime[1] = 1;
	for(i = 2; i * i <= MAXN; i++)
	{
		if(is_prime[i])	continue;
		for(j = i * i; j <= MAXN; j += i)	is_prime[j] = 1;
	}
	for(i = 1; i <= MAXN; i++)
	{
		if(!is_prime[i])	prime[len++] = i;
	}
}

