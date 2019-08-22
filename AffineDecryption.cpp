#include "pch.h"
#include "AffineDecryption.h"
#include <regex>
#include <exception>
#include "deciphermath.h"

decipherer::AffineDecryption::AffineDecryption()
{
}


decipherer::AffineDecryption::~AffineDecryption()
{
}

std::string decipherer::AffineDecryption::decrypt(const std::string & cipherText)
{
	std::string decipherText = "";
	int inverse = decipherer::multiplicativeInversion(m_iA, 26);

	for (size_t i = 0; i < cipherText.size(); i++)
	{
		decipherText += char(decipherer::modulo((cipherText[i] - 'a' - m_iB) * inverse, 26) + 'a');
	}
	return decipherText;
}

std::string decipherer::AffineDecryption::decrypt(const std::string & cipherText, size_t from, size_t to)
{
	std::string decipherText = "";
	int inverse = decipherer::multiplicativeInversion(m_iA, 26);

	for (size_t i = from; i < to; i++)
	{
		decipherText += char(decipherer::modulo((cipherText[i] - 'a' - m_iB) * inverse, 26) + 'a');
	}
	return decipherText;
}

bool decipherer::AffineDecryption::isKeyValid(const std::string & key)
{
	std::regex reg("(\\d{1,5})_(\\d{1,5})");
	if (!std::regex_match(key, reg)) {
		return false;
	}
	std::smatch match;
	std::regex_search(key, match, reg);
	int a = std::stoi(match.str(1));
	int b = std::stoi(match.str(2));

	return gcd(a, 26) == 1 && b > 0; //Coprime integers a and 26(count of symbols in latin alphabet)
}

void decipherer::AffineDecryption::setKey(const std::string & key)
{
	std::regex reg("(\\d{1,5})_(\\d{1,5})");
	std::smatch match;
	std::regex_search(key, match, reg);
	m_iA = std::stoi(match.str(1));
	m_iB = std::stoi(match.str(2));
}
