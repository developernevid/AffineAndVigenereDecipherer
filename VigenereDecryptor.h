#pragma once
#include "AbstractDecryption.h"
#include <vector>

namespace decipherer {
	class VigenereDecryptor :
		public AbstractDecryption
	{
	public:
		VigenereDecryptor();
		~VigenereDecryptor();

		// Inherited via AbstractDecryption
		//precondition - all encryptedText must be in lowercase and without special symbols like spaces, dots and etc.
		virtual std::string decrypt(const std::string & cipherText) override;
		virtual std::string decrypt(const std::string & cipherText, size_t from, size_t to) override;
		virtual void setKey(const std::string & key) override;
		virtual bool isKeyValid(const std::string & key) override;

	private:
		std::string m_sOnlyWithLowerCaseLetters;
		std::string m_key;

	};
};
