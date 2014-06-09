
1.求法
(1)根据素数的定义，很明显，如果一个数是素数<==>它的因子只包含1和它本身。
因此可以根据判别某个数的因子的方法来判断其是否是素数。   
int isPrime(int n) {
	int i;
	for(i = 2; i <= (int)sqrt((double)n); ++i) {
		//如果n存在其它因子,则必定不是素数
		if (n % i == 0) return 0; 
	}
	return 1;
}


(2). 打表求素数 1-maxn的素数.
对于一个数n，如果n是素数，那么2*n，3*n，4*n，必定不是素数。
const int maxn = xxxxx;
int prime[maxn/5];
bool isPrime[maxn + 5];


int i, j, cnt;
void init() {
	isPrime[1] = isPrime[1] = 1;
	for (i = 2; i <= maxn; ++i) {
	    if (!isPrime[i]) {
	        for (j = i + i; j <= maxn; j+=i) { //加法运算
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



2. 打表求1-maxn的因子个数
int d[maxn + 5];
for (i = 1; i <= maxn; i++) { //如果为i+=2，就是1,3,5...奇数因子个数，偶数因子类似
    for (j = i; j <= maxn; j+=i) {
        d[j]++;
    }
}
