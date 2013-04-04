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

	void cleanLeadZero()	  // ȥ��ǰ����  
	{ 
		while (len > 1 && !s[len - 1]) len--;  
	}  
	
	void multiplyTen(int n)   // ����10��n�η�  
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
	
	void divisionTen(int n)   // ����10��n�η�  
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
		
	string str() const		// �����ת�����ַ���  
	{  
		string res = "";  // ÿ��λ����������ӵ�strĩβ��  
		for (int i = 0;  i < len; i++) 
		{  
			res = (char)(s[i] + '0') + res;  
		}  
		if (res == "") res = "0";  
		return res;  
	}
			
	BigNumber()   // ���캯��  
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
		
	BigNumber getSub(int n) const   // ��ȡ������ǰnλ��������1234434 ���� getSub(3)�Ļ��õ��Ľ����123��  
	{  
		BigNumber c;  
		c.len = 0;  
		for (int i = 0; i < n; i++) 
		{  
			c.s[c.len++] = s[len - n + i];  
		}  
		return c;  
	}		
		
	BigNumber operator = (const char *num)   // ���ظ�ֵ�����  
	{  
		len = strlen(num);  
 								 // ������s�������������ŵģ��磺"456" ��s ��������s[0] = 6, s[1] = 5, s[2] = 4��  
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
	
	// ���ؼӼ��˳�  
	BigNumber operator + (const BigNumber &) const;  
	BigNumber operator - (const BigNumber &) const;  
	BigNumber operator * (const BigNumber &) const;  
	BigNumber operator / (const BigNumber &) const;  
	BigNumber operator % (const BigNumber &) const;  
	BigNumber operator -= (const BigNumber &);  
	BigNumber operator += (const BigNumber &);  
	BigNumber operator *= (const BigNumber &);  
	BigNumber operator /= (const BigNumber &);  
	// ���رȽ������  
	bool operator < (const BigNumber &) const;  
	bool operator > (const BigNumber &) const;  
	bool operator <= (const BigNumber &) const;  
	bool operator >= (const BigNumber &) const;  
	bool operator == (const BigNumber &) const;  
	// �������������  
	friend istream & operator >> (istream &, BigNumber &);  
	friend ostream & operator << (ostream &, BigNumber &);		
};  //�����


  
BigNumber BigNumber::operator + (const BigNumber & x) const  // ++++++++++++++++++++++++++++++++
{  
	BigNumber r;  
	r.len = 0;  
	// up ���������ֽ�λ��  
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
	// ȥ��ǰ����  
	r.cleanLeadZero();  
	return r;  
}  
  
// ������ʹ��ʱҪע���ڼ���a - bʱҪȷ��a >= b;  
// ���a < b ����� �����һ��'-' ����� b - a �Ľ��  
BigNumber BigNumber::operator - (const BigNumber & b) const   // -------------------------------
{  
	BigNumber c;  
	c.len = 0;  
	int i;  
	// ����������λ  
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
	// ģ������Ĺ���  
	// ��ȡblen - 1λ  
	BigNumber temp = this->getSub(b.len - 1);  
	// һλһλ�ĳ��Ӷ�ȡ�������Ĵ�  
	for (i = len - b.len; i >= 0; i--)   
	{  
		// temp�����洢��������ǰblenλ��  
		temp = temp * 10 + s[i];  
		// ���temp < b�����ڸ�λ�Ľ��Ϊ0  
		if (temp < b) 
		{  
			r.s[r.len++] = 0;  
		} 
		else 
		{  
			// �����ҵ���һ��jʹ��b * j�Ľ������ temp  
			for (j = 1; j <= 10; j++) 
			{  
					if (b * j > temp) break;  
			}  
			// ��Ϊ��ʱ��j - 1�� * bС�ڵ��� temp������j - 1�����ڸ�λ���Ľ��  
			r.s[r.len++] = j - 1;  
			// temp ��ȥ����ȥ����Ϊ��һ�ε�����׼��  
			temp = temp - (b * (j - 1));  
		}  
	}  
	// ������Ϊ�����Ҫ����洢�ģ������������н����˳��洢�ģ�  
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