typedef long long LL;
const int MAXN = 3;
LL mod = 20121223;
class Matrix
{
	public:
		//��ž���
		LL m[MAXN][MAXN];
		//�޲ι����ʼ������
		Matrix(){memset(m, 0, sizeof(m));}
		//�вι����ʼ������
		Matrix(LL e[MAXN][MAXN])
		{
			for (int i = 0; i < MAXN; i++)
			{
				for (int j = 0; j < MAXN; j++)
				{
					m[i][j] = e[i][j];
				}
			}
		}
		//���س˷�����
		friend Matrix operator*(Matrix m1 ,Matrix m2)  
		{
			int i,j,k;
			Matrix tmp;
			for(i = 0; i < MAXN; i++)
			{
				for(j = 0; j < MAXN; j++)
				{
					for(k = 0; k < MAXN; k++)
					{
						tmp.m[i][j] += (m1.m[i][k] * m2.m[k][j]) % mod;
						tmp.m[i][j] = tmp.m[i][j] % mod;
					}
				}
			}
			return tmp;
		}
		friend Matrix QuickPow(Matrix M , LL n)  
		{  
			//��ʼ��Ϊ��λ����
			Matrix ans;  
			for(int i = 0 ; i < MAXN ; i++)  
			{  
				for(int j = 0 ; j < MAXN ; j++)  
				{  
					if(i == j)  
						ans.m[i][j] = 1;  
					else  
						ans.m[i][j] = 0;  
				}  
			}  
			//������  
			while( n )  
			{  
				if(n & 1)  
					ans = ans * M;     
				n = n >> 1;
				M = M * M;  
			}  
			return ans;  
		}
};