#pragma once
#include "AbstractDecryption.h"

namespace decipherer {
	class AffineDecryption :
		public AbstractDecryption
	{
	public:
		AffineDecryption();
		~AffineDecryption();

		// Inherited via AbstractDecryption
		virtual std::string decrypt(const std::string & cipherText) override;
		virtual std::string decrypt(const std::string & cipherText, size_t from, size_t to) override;
		virtual void setKey(const std::string & key) override;
		virtual bool isKeyValid(const std::string& key) override;


	private:
		int m_iA, m_iB; 
	};
	
};