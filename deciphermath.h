#pragma once

namespace decipherer {
	// greatest common divisor - calculation by Evklid alghoritm
	int gcd(int a, int b);

	// finds modular multiplicative inverse of ‘a’ under modulo ‘m’
	// preconditions: The multiplicative inverse of “a modulo m” exists if and only if a and m are relatively prime (i.e., if gcd(a, m) = 1).
	int multiplicativeInversion(int a, int m);

	//3 mod - 10 = -7 -3 mod 10 = 7 
	int modulo(int a, int m);
};