
1.��
(1)���������Ķ��壬�����ԣ����һ����������<==>��������ֻ����1��������
��˿��Ը����б�ĳ���������ӵķ������ж����Ƿ���������   
int isPrime(int n) {
	int i;
	for(i = 2; i <= (int)sqrt((double)n); ++i) {
		//���n������������,��ض���������
		if (n % i == 0) return 0; 
	}
	return 1;
}


(2). ��������� 1-maxn������.
����һ����n�����n����������ô2*n��3*n��4*n���ض�����������
const int maxn = xxxxx;
int prime[maxn/5];
bool isPrime[maxn + 5];


int i, j, cnt;
void init() {
	isPrime[1] = isPrime[1] = 1;
	for (i = 2; i <= maxn; ++i) {
	    if (!isPrime[i]) {
	        for (j = i + i; j <= maxn; j+=i) { //�ӷ�����
	            isPrime[j] = 1;
	        }
	    }
	}

	cnt = 0;
	for (i = 2; i <= maxn; i++) {
	    if (!isPrime[i])
	        prime[cnt++] = i;
	}
}



2. �����1-maxn�����Ӹ���
int d[maxn + 5];
for (i = 1; i <= maxn; i++) { //���Ϊi+=2������1,3,5...�������Ӹ�����ż����������
    for (j = i; j <= maxn; j+=i) {
        d[j]++;
    }
}
