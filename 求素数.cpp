
1.�����Ķ���
  ֻ�ܱ�1�����Լ���������Ȼ����Ϊ�������ر�涨1������������


2.��
(1)���������Ķ��壬�����ԣ����һ����������<==>��������ֻ����1��������
��˿��Ը����б�ĳ���������ӵķ������ж����Ƿ���������   
int isprime(int n)
{
	int i;
	for(i=2;i<=(int)sqrt((double)n);i++)
	{
		if(n%i==0)    //���n������������,��ض���������
		{
			return 0;
		}
	}
	return 1;
}



(2)ɸѡ��������һ����n���������������ô2*n��3*n��4*n���ض�����������
const int MAXN = 500000;
bool is_prime[500001];
int prime[500001];
/*ɸ��������*/
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

