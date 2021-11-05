
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