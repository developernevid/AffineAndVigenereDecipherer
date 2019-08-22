#include "pch.h"
#include "deciphermath.h"


int decipherer::gcd(int a, int b)
{
	int x;
	while (b)
	{
		x = a % b;
		a = b;
		b = x;
	}
	return a;
}

int decipherer::multiplicativeInversion(int a, int m)
{
	a = a % m;
	for (int x = 1; x < m; x++)
		if ((a * x) % m == 1)
			return x;
}

int decipherer::modulo(int a, int m)
{
	return (m + (a % m)) % m;
}