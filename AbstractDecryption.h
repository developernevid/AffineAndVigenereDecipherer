#pragma once
#include <string>

namespace decipherer {
	class AbstractDecryption
	{
	public:
		//precondition - all encryptedText must be in lowercase and without special symbols like spaces, dots and etc.
		virtual std::string decrypt(const std::string& cipherText) = 0;
		virtual std::string decrypt(const std::string& cipherText, size_t from, size_t to) = 0;
		virtual void setKey(const std::string& key) = 0;
		virtual bool isKeyValid(const std::string& key) = 0;

		AbstractDecryption();
		virtual ~AbstractDecryption();
	};
};

