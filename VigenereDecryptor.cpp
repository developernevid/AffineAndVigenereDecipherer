#include "pch.h"
#include "VigenereDecryptor.h"
#include <cctype>
#include <regex>

decipherer::VigenereDecryptor::VigenereDecryptor()
{
}

decipherer::VigenereDecryptor::~VigenereDecryptor()
{
}

std::string decipherer::VigenereDecryptor::decrypt(const std::string & cipherText)
{
	int keySize = m_key.size();
	std::string decipheredText;

	for (size_t i = 0; i < cipherText.size(); ++i)
	{
		decipheredText += (cipherText[i] - m_key[i % keySize] + 26) % 26 + 'a';  //D i =  (E i - K i + 26) % 26 + offset(97 = a-z, 65 = A-Z)
	}

	return decipheredText;
}

std::string decipherer::VigenereDecryptor::decrypt(const std::string & cipherText, size_t from, size_t to)
{
	int keySize = m_key.size();
	std::string decipheredText;

	for (size_t i = from; i < to; ++i)
	{
		decipheredText += (cipherText[i] - m_key[i % keySize] + 26) % 26 + 'a';  //D i =  (E i - K i + 26) % 26 + offset(97 = a-z, 65 = A-Z)
	}

	return decipheredText;
}

void decipherer::VigenereDecryptor::setKey(const std::string & key)
{
	for (size_t i = 0; i < key.size(); ++i)
	{
		m_key += tolower(key[i]);
	}
}

bool decipherer::VigenereDecryptor::isKeyValid(const std::string & key)
{
	std::regex reg("[a-z]{2,}");
	if (!std::regex_match(key, reg)) {
		return false;
	}
	return true;
}

