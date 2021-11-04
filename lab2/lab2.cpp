#include <iostream>
#include <string>
#include <utility>

using namespace std;

int base = 10;


class LongInt
{
public:

	string value;

	LongInt(string x) // ����� ������ �, �� ����� ������, ����� ����������� :(
	{
		value = move(x);
	}

	LongInt()
	{
		value = "0";
	}


	static int equalizer(string num1, string num2) // ������ �� ������� �������
	{
		int s = max(num1.size(), num2.size());

		while (num1.size() < s)
			num1.insert(0, "0");
		while (num2.size() < s)
			num2.insert(0, "0");

		return 0;
	}


	static string add(string num1, string num2) // ��� ��������� ���������
	{
		long n = equalizer(num1, num2);
		string result;
		int sum;
		int remain = 0;

		for (int j = n - 1; j >= 0; j--)
		{
			sum = (num1[j] - '0') + (num2[j] - '0') + remain;
			result.insert(0, to_string(sum % base));
			remain = sum / base;
		}

		if (remain)
		{
			result.insert(0, to_string(remain));
		}

		return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
	}


	static string sub(string num1, string num2) // ��� ��������� ��������
	{
		long n = equalizer(num1, num2);
		string result, x, y;
		int differ;

		if (num1 > num2) // ����������, �� �� ���� ������ ��'����
		{
			x = num1;
			y = num2;
		}
		else
		{
			x = num2;
			y = num1;
		}

		for (int j = n - 1; j >= 0; --j)
		{
			if (differ >= 0)
				result.insert(0, to_string(differ));
			else
			{
				int next = j - 1;
				while (next >= 0)
				{
					x[next] = (base + (x[next] - '0') - 1) % base + '0';

					if (x[next] != 9)
						break;
					else
						--next;
				}

				result.insert(0, to_string(differ + base));

			}
		}

		return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));

	}


	LongInt operator + (LongInt x)
	{
		return LongInt(add((*this).value, x.value));
	}

	LongInt operator - (LongInt x)
	{
		return LongInt(sub((*this).value, x.value));
	}


	static string multiply_x10(string num, long steps) // ������� �� �����
	{
		for (int i = 0; i < steps; i++)
			num.append("0");

		return num;
	}


	// NOTES: Karatsuba
	// x = aT + b
	// y = cT + d 
	// x*y = acT^2 + (ad + bc)T + bd
	// x*y = acT^2 + ((a+b)(c+d) - ac - bd)T + bd

	static string Karatsuba(LongInt num1, LongInt num2)
	{
		LongInt result, a1, a2, b1, b2, c1, c2, d1, d2, d1d2, T;
		long s = LongInt::equalizer(num1.value, num2.value);
		if (s == 1)
		{
			return to_string((num1.value[0] - '0') * (num2.value[0] - '0'));
		}

		a1 = num1.value.substr(0, s/2);
		a2 = num1.value.substr(s/2, s - s/2);
		b1 = num2.value.substr(0, s/2);
		b2 = num2.value.substr(s/2, s - s/2);
		c1 = Karatsuba(a1, b1);
		c2 = Karatsuba(a2, b2);
		d1 = a1 + a2;
		d2 = b1 + b2;
		d1d2 = Karatsuba(d1, d2);
		T = d1d2 - c1 - c2;

		LongInt::multiply_x10(c1.value, 2 * (s - s / 2));
		LongInt::multiply_x10(T.value, 2 * (s / 2));

		result = c1 + c2 + T;

		return result.value.erase(0, min(result.value.find_first_not_of('0'), result.value.size() - 1));

	}


};



int main()
{
	return 0;
}