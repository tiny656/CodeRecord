#include <iostream> 
#include <cstdio> 
#include <cstring>
#include <string>
using namespace std;  
  
int const MAXN = 800;  
  
class BigNumber  
{  
public:  
	int s[MAXN];  
	int len;  

	void cleanLeadZero()	  // 去除前导零  
	{ 
		while (len > 1 && !s[len - 1]) len--;  
	}  
	
	void multiplyTen(int n)   // 乘以10的n次方  
	{  
		int i;  
		if (n > len) 
		{  
			while (len >= 1) s[len--] = 0;  
 		} 
		else 
		{  
			for (i = 0; i < len - n; i++)   
			{  
				s[i] = s[i + n];  
			}  
			len -= n;  
		}  
	}	  
	
	void divisionTen(int n)   // 除以10的n次方  
	{  
		if (n > 0) 
		{  
			int i;  
			for (i = len - 1; i >= 0; i--)   
			{  
				s[i + n] = s[i];  
			}  
			for (i = 0; i < n; i++) 
			{  
				s[i] = 0;  
			}  
			len += n;  
		}  
	} 
		
	string str() const		// 将结果转换成字符串  
	{  
		string res = "";  // 每个位的数逆序添加到str末尾。  
		for (int i = 0;  i < len; i++) 
		{  
			res = (char)(s[i] + '0') + res;  
		}  
		if (res == "") res = "0";  
		return res;  
	}
			
	BigNumber()   // 构造函数  
	{  
		memset(s, 0, sizeof(s));  
		len = 1;  
	}  
		
	BigNumber(int num) 
	{  
		*this = num;  
	}		
		
	BigNumber(const char *num)  
	{  
		*this = num;  
	}  
		
	BigNumber getSub(int n) const   // 截取整数的前n位数（例如1234434 调用 getSub(3)的话得到的结果是123）  
	{  
		BigNumber c;  
		c.len = 0;  
		for (int i = 0; i < n; i++) 
		{  
			c.s[c.len++] = s[len - n + i];  
		}  
		return c;  
	}		
		
	BigNumber operator = (const char *num)   // 重载赋值运算符  
	{  
		len = strlen(num);  
 								 // 整数在s数组中是逆序存放的（如："456" 在s 数组中是s[0] = 6, s[1] = 5, s[2] = 4）  
		for (int i = 0; i < len; i++) 
		{  
			s[i] = num[len - i - 1] - '0';  
		}  
		return *this;  
	}  
		
	BigNumber operator = (int num)
	{  
		char s[MAXN];  
		sprintf(s, "%d", num);  
		*this = s;  
		return *this;  
	}   
	
	// 重载加减乘除  
	BigNumber operator + (const BigNumber &) const;  
	BigNumber operator - (const BigNumber &) const;  
	BigNumber operator * (const BigNumber &) const;  
	BigNumber operator / (const BigNumber &) const;  
	BigNumber operator % (const BigNumber &) const;  
	BigNumber operator -= (const BigNumber &);  
	BigNumber operator += (const BigNumber &);  
	BigNumber operator *= (const BigNumber &);  
	BigNumber operator /= (const BigNumber &);  
	// 重载比较运算符  
	bool operator < (const BigNumber &) const;  
	bool operator > (const BigNumber &) const;  
	bool operator <= (const BigNumber &) const;  
	bool operator >= (const BigNumber &) const;  
	bool operator == (const BigNumber &) const;  
	// 重载输入输出流  
	friend istream & operator >> (istream &, BigNumber &);  
	friend ostream & operator << (ostream &, BigNumber &);		
};  //类结束


  
BigNumber BigNumber::operator + (const BigNumber & x) const  // ++++++++++++++++++++++++++++++++
{  
	BigNumber r;  
	r.len = 0;  
	// up 是用来保持进位的  
	int i, up;  
	int maxLen = max(len, x.len);  
	for (i = 0, up = 0; up || i < maxLen; i++) 
	{  
		int temp = up;  
		if (i < len) temp += s[i];  
		if (i < x.len) temp += x.s[i];  
		up = temp / 10;  
		r.s[r.len++] = temp % 10;  
	}  
	// 去除前导零  
	r.cleanLeadZero();  
	return r;  
}  
  
// 减法在使用时要注意在计算a - b时要确保a >= b;  
// 如果a < b 则计算 先输出一个'-' 再输出 b - a 的结果  
BigNumber BigNumber::operator - (const BigNumber & b) const   // -------------------------------
{  
	BigNumber c;  
	c.len = 0;  
	int i;  
	// 用来保存退位  
	int down;  
	for (i = 0, down = 0; i < len; i++)   
	{  
		int temp = s[i] - down;  
		if (i < b.len) temp  -= b.s[i];  
		if (temp >= 0) down = 0;  
		else 
		{  
			down = 1;  
			temp += 10;  
		}  
		c.s[c.len++] = temp;  
	}  
	c.cleanLeadZero();  
	return c;  
}  
  
BigNumber BigNumber::operator * (const BigNumber & b) const  // *************************
{  
	int i, j;  
	BigNumber c;  
	c.len = len + b.len;  
	for (i = 0; i < len; i++) 
	{  
		for (j = 0; j < b.len; j++) 
		{  
			c.s[i + j] += s[i] * b.s[j];  
		}  
	}  
	  
	for (i = 0; i < c.len - 1; i++) 
	{  
		c.s[i + 1] += c.s[i] / 10;  
		c.s[i] %= 10;  
	}  
	c.cleanLeadZero();  
	return c;  
}  
  
BigNumber BigNumber::operator / (const BigNumber & b) const  // //////////////////////////////////////////
{  
	int i, j;  
	BigNumber r;  
	r.len = 0;  
	// 模拟除法的过程  
	// 先取blen - 1位  
	BigNumber temp = this->getSub(b.len - 1);  
	// 一位一位的除从而取得完整的答案  
	for (i = len - b.len; i >= 0; i--)   
	{  
		// temp用来存储被除数的前blen位。  
		temp = temp * 10 + s[i];  
		// 如果temp < b则再在该位的结果为0  
		if (temp < b) 
		{  
			r.s[r.len++] = 0;  
		} 
		else 
		{  
			// 否则找到第一个j使得b * j的结果大于 temp  
			for (j = 1; j <= 10; j++) 
			{  
					if (b * j > temp) break;  
			}  
			// 因为此时（j - 1） * b小于等于 temp，所有j - 1就是在该位除的结果  
			r.s[r.len++] = j - 1;  
			// temp 减去被减去部分为下一次迭代做准备  
			temp = temp - (b * (j - 1));  
		}  
	}  
	// 逆序（因为结果是要逆序存储的，而在求解过程中结果是顺序存储的）  
	for (i = 0; i < r.len / 2; i++) 
	{  
		int temp = r.s[i];  
		r.s[i] = r.s[r.len - 1 - i];  
		r.s[r.len - 1 - i] = temp;  
	}  
	r.cleanLeadZero();  
	return r;  
}  
  
BigNumber BigNumber::operator % (const BigNumber & b) const   //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
{  
	BigNumber r;  
	r = *this / b;		  
	r = *this - r * b;  
	return r;  
}  
  
BigNumber BigNumber::operator += (const BigNumber & b)   
{  
	*this = *this + b;  
	return *this;  
}  
  
BigNumber BigNumber::operator -= (const BigNumber & b)  
{  
	*this = *this - b;  
	return *this;  
}  
  
BigNumber BigNumber::operator *= (const BigNumber & b)  
{  
	*this = *this * b;  
	return *this;  
}  
  
BigNumber BigNumber::operator /= (const BigNumber & b)   
{  
	*this = *this / b;  
	return *this;  
}  
  
bool BigNumber::operator < (const BigNumber & b) const  
{  
	if (len != b.len) return len < b.len;  
	else 
	{  
		for (int i = len - 1; i >= 0; i--) 
		{  
			if (s[i] != b.s[i]) return s[i] < b.s[i];  
		}  
	}  
	return false;  
}  
  
bool BigNumber::operator > (const BigNumber & b) const  
{  
	return b < *this;  
}  
  
bool BigNumber::operator <= (const BigNumber & b) const  
{  
	return !(b > *this);  
}  
  
bool BigNumber::operator >= (const BigNumber & b) const  
{  
	return !(*this < b);  
}  
  
bool BigNumber::operator == (const BigNumber & b) const  
{  
	return !(b < *this) && !(b > *this);  
}  
  
istream & operator >> (istream & in, BigNumber & x)  
{  
	string s;  
	in >> s;  
	x = s.c_str();  
	return in;  
}  
  
ostream & operator << (ostream & out, BigNumber & x)  
{  
	out << x.str();  
	return out;  
}  
  
char a[905], b[905];
  
int main()  
{
	while (scanf("%s %s", a,b) != EOF) 
	{  
		BigNumber num1(a);  
		BigNumber num2(b);
		cout << (num1/num2).str() << endl;  
	}  
	return 0;  
}