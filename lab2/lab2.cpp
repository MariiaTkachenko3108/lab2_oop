#include <iostream>
#include <string>


using namespace std;

int base = 10;


class LongInt
{
public:



	static int equalizer(string num1, string num2)
	{
		int s = max(num1.size(), num2.size());

		while (num1.size() < s)
			num1.insert(0, "0");
		while (num2.size() < s)
			num2.insert(0, "0");

		return 0;
	}


};

// ���������:
// x = aT + b
// y = cT + d 
// x*y = acT^2 + (ad + bc)T + bd
// x*y = acT^2 + ((a+b)(c+d) - ac - bd)T + bd


int main()
{
	return 0;
}