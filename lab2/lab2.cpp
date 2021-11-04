#include <iostream>
#include <string>
#include <utility>

using namespace std;

int base = 10;


class LongInt
{
public:

	string value;

	LongInt(string x)
	{
		value = move(x);
	}

	LongInt()
	{
		value = "0";
	}

	static int equalizer(string num1, string num2)
	{
		int s = max(num1.size(), num2.size());

		while (num1.size() < s)
			num1.insert(0, "0");
		while (num2.size() < s)
			num2.insert(0, "0");

		return 0;
	}


	static string add(string num1, string num2)
	{

	}


	static string sub(string num1, string num2)
	{

	}


	LongInt operator + (LongInt x)
	{
		return LongInt(add((*this).value, x.value));
	}

	LongInt operator - (LongInt x)
	{
		return LongInt(sub((*this).value, x.value));
	}

	LongInt operator * (LongInt x)
	{
		return 
	}


	static string multiply_x10(string num, long steps)
	{
		for (int i = 0; i < steps; i++)
			num.append("0");

		return num;
	}


	static string Karatsuba(LongInt num1, LongInt num2)
	{
		LongInt result, a1, a2, b1, b2, c1, c2, T1;
		long n = LongInt::equalizer(num1.value, num2.value);
		if (n == 1)
		{
			
		}

		a1 = num1.value.substr(0, n/2);
		a2 = num1.value.substr(n/2, n - n/2);
		b1 = num2.value.substr(0, n/2);
		b2 = num2.value.substr(n/2, n - n/2);

		c1 = a1*b1;
		c2 = a2*b2;

		T1 = (a1 + a2) * (b1 + b2) - c1 - c2;

		result = c1 + c2 + T1
		
			
		return ();

	}


};

// karatsuba:
// x = aT + b
// y = cT + d 
// x*y = acT^2 + (ad + bc)T + bd
// x*y = acT^2 + ((a+b)(c+d) - ac - bd)T + bd


int main()
{
	return 0;
}