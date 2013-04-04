const int MAXN = 500000;
bool is_prime[500001];
int prime[500001];
/*É¸·¨ÇóËØÊı*/
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