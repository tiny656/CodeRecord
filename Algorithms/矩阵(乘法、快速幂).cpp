#include <iostream>
using namespace std;

#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef unsigned __int64 uint64;
typedef signed __int64 int64;
#else
typedef unsigned long long uint64;
typedef signed long long int64;
#endif

/*---------------矩阵的快速幂BEGIN---------------*/
//这里更改矩阵大小
const int MAXN = 2;
const int MOD = 20121223;

//矩阵
typedef  struct{
	int  m[MAXN][MAXN];
}  Matrix;

//预置单位矩阵
Matrix I2 = { 1, 0 , 0, 1 };
//Matrix I3 = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

//矩阵乘法
Matrix MatrixMul(const Matrix &a, const Matrix &b) {
	int i, j, k;
	Matrix c;
	for (i = 0; i < MAXN; i++)
	for (j = 0; j < MAXN; j++) {
		c.m[i][j] = 0;
		for (k = 0; k < MAXN; k++)
			c.m[i][j] += (a.m[i][k] * b.m[k][j]) % MOD;
		c.m[i][j] %= MOD;
	}
	return c;
}

//矩阵快速幂求解 m^n % MOD
Matrix QuickPow(Matrix m, int64 n)
{
	Matrix ans = I2;
	//快速幂
	assert(n >= 0);
	while (n >= 1) {
		if (n & 1) ans = MatrixMul(ans, m);
		n = n >> 1;
		m = MatrixMul(m, m);
	}
	return ans;
}

//打印矩阵
void Print(const Matrix &m) {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			printf("%d ", m.m[i][j]);
		}
		printf("\n");
	}
}
/*---------------矩阵快速幂END---------------*/

/*---------------整数快速幂BEGIN---------------*/
// m^n % k
int QuickPow(int64 m, int64 n, const int64 &k) {
	int64 ans = 1;
	while (n > 0) {
		if (n & 1LL) ans = (ans * m) % k;
		n = n >> 1LL;
		m = (m * m) % k;
	}
	return ans;
}
/*---------------整数快速幂END---------------*/



int main() {
	
	/*----Test Begin----*/
	Matrix P = { 1,1,1,0};
	for (int i = 0; i < 10; i++){
		Print(QuickPow(P, i));
		cout << endl;
	}

	cout << QuickPow(2, 3, 3) << endl;
	/*----Test End----*/
	return 0;
}