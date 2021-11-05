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


	static long equalizer(string & num1, string & num2) // зрівнює по кількості символів
	{
		long s = max(num1.size(), num2.size());

		while (num1.size() < s)
			num1.insert(0, "0");
		while (num2.size() < s)
			num2.insert(0, "0");

		return s;
	}


	static string add(string num1, string num2) // для оператора додавання
	{
		long s = equalizer(num1, num2);
		string result;
		int sum;
		int remain = 0;

		for (int j = s - 1; j >= 0; j--)
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


	static string sub(string num1, string num2) // для оператора віднімання
	{
		long s = equalizer(num1, num2);
		string result, x, y;
		int dif;

		if (num1 > num2) // перевіряємо, чи не буде різниця від'ємна
		{
			x = num1;
			y = num2;
		}
		else
		{
			x = num2;
			y = num1;
		}



		for (int j = s - 1; j >= 0; j--)
		{ 
			dif = (x[j] - '0') - (y[j] - '0');

			if (dif >= 0)
				result.insert(0, to_string(dif));
			else
			{
				int next = j - 1;

				while (next >= 0)
				{
					x[next] = (base + (x[next] - '0') - 1) % base + '0';

					if (x[next] != '9')
						break;
					else
						next--;
				}

				result.insert(0, to_string(dif + base));

			}
		}

		return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));

	}


	LongInt & operator=(string x)
	{
		*this = LongInt(move(x));
		return *this;
	}

	LongInt operator+(LongInt x)
	{
		return LongInt(add((*this).value, x.value));
	}

	LongInt operator-(LongInt x)
	{
		return LongInt(sub((*this).value, x.value));
	}



	static string multiply_x10(string & num, long steps) // вирівнює по нулям
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

	static string Karatsuba(LongInt a, LongInt b)
	{
		LongInt result, a1, a2, b1, b2, c1, c2, d1, d2, d1d2, T;
		long n = LongInt::equalizer(a.value, b.value);
		if (n == 1)
		{
			return to_string((a.value[0] - '0') * (b.value[0] - '0'));
		}

		a1 = a.value.substr(0, n/2);
		a2 = a.value.substr(n/2, n - n/2);
		b1 = b.value.substr(0, n/2);
		b2 = b.value.substr(n/2, n - n/2);

		c1 = Karatsuba(a1, b1);
		c2 = Karatsuba(a2, b2);
		d1 = (a1 + a2);
		d2 = (b1 + b2);
		d1d2 = Karatsuba(d1, d2);
		T = d1d2 - c1 - c2;

		LongInt::multiply_x10(c1.value, 2 * (n - n/2));
		LongInt::multiply_x10(T.value, (n - n/2));

		result = c1 + c2 + T;

		return result.value.erase(0, min(result.value.find_first_not_of('0'), result.value.size() - 1));

	}


	static string Toom3(LongInt a, LongInt b)
	{
		LongInt result, a1, a2, a3, b1, b2, b3, c1, c2, c3, d1, d2, d3, T1, T2, T3;

		long m = LongInt::equalizer(a.value, b.value);

		if (m == 1)
		{
			return to_string((a.value[0] - '0') * (b.value[0] - '0'));
		}


		if (m % 3)
		{
			m += 3 - m % 3;

			while (a.value.size() < m)
				a.value.insert(0, "0");
			LongInt::equalizer(a.value, b.value);
		}



		a1 = a.value.substr(0, m / 3);
		a2 = a.value.substr(m / 3, m / 3);
		a3 = a.value.substr(2 * m / 3, m / 3);
		b1 = b.value.substr(0, m / 3);
		b2 = b.value.substr(m / 3, m / 3);
		b3 = b.value.substr(2 * m / 3, m / 3);

		c1 = Toom3(a1, b1);
		c2 = Toom3(a2, b2);
		c3 = Toom3(a3, b3);

		/*
		(a1+a2)*(b1+b2)
		(a1+a3)*(b1+b3)
		(a2+a3)*(b2+b3)
		*/


		d1 = Toom3((a1 + a2), (b1 + b2));
		d2 = Toom3((a1 + a3), (b1 + b3));
		d3 = Toom3((a2 + a3), (b2 + b3));

		/*
		(a1 + a2)*(b1 + b2) - a1 * b1 - a2 * b2
		(a1 + a3)*(b1 + b3) - a1 * b1 - a3 * b3
		(a2 + a3)*(b2 + b3) - a2 * b2 - a3 * b3
		*/


		T1 = d1 - c1 - c2;
		T2 = d2 - c1 - c3;
		T3 = d3 - c2 - c3;

		c1 = LongInt::multiply_x10(c1.value, 4 * m / 3);
		c2 = LongInt::multiply_x10(c2.value, 2 * m / 3);
		T1 = LongInt::multiply_x10(T1.value, 3 * m / 3);
		T2 = LongInt::multiply_x10(T2.value, 2 * m / 3);
		T3 = LongInt::multiply_x10(T3.value, m / 3);


		result = c1 + c2 + c3 + T1 + T2 + T3;

		return result.value.erase(0, min(result.value.find_first_not_of('0'), result.value.size() - 1));

	}


};



int main()
{
	setlocale(LC_CTYPE, "ukr");

	LongInt a, b;

	a = "123456";
	b = "9876543219173";


	cout << "Перелік методів:" << "\n1. Множення Каратсуби" << "\n2. Множення Тоома-Кука" << endl << endl;
	cout << "Введіть номер методу" << endl;


	int input;
	cin >> input;
	 
	switch (input)
	{
	case 1:
		cout << LongInt::Karatsuba(a, b) << endl;
		break;

	case 2:
		cout << LongInt::Toom3(a, b) << endl;
		break;
	default:
		cout << "Хибний формат вводу" << endl;
	}
	


	return 0;
}