#include "pch.h"
#include "Mediator.h"
#include <fstream>
#include <algorithm>

#include "VigenereDecryptor.h"
#include "AffineDecryption.h"


decipherer::Mediator::Mediator(int argc, char *argv[])
	: m_unPtrParser(std::make_unique<CommandArgsParser>(CommandArgsParser(argc, argv)))
{
	if (m_unPtrParser->decipherType() == "vigener") {
		m_unPtrDecipherer = std::make_unique<decipherer::VigenereDecryptor>(VigenereDecryptor());
	}
	else if (m_unPtrParser->decipherType() == "affine") {
		m_unPtrDecipherer = std::make_unique<decipherer::AffineDecryption>(AffineDecryption());
	}
	else {
		throw(std::invalid_argument("Invalid decipher type " + m_unPtrParser->decipherType()));
	}
	if (!m_unPtrDecipherer->isKeyValid(m_unPtrParser->key())) {
		throw(std::invalid_argument("Invalid key. \nVigener key format is two and more latin alphabet letters.\nAffine key format is two numbers A and B, where both A and 26 must be coprime."));
	}
	m_unPtrDecipherer->setKey(m_unPtrParser->key());
}


decipherer::Mediator::~Mediator()
{
}

void decipherer::Mediator::readCipheredTextFromFile()
{
	try
	{
		std::ifstream inputFile(m_unPtrParser->inputFileName());
		if (!inputFile.is_open()) {
			throw(std::exception(std::string("cannot open file " + m_unPtrParser->inputFileName()).c_str()));
		}

		std::string tempStr((std::istreambuf_iterator<char>(inputFile)),
			std::istreambuf_iterator<char>());

		for (size_t i = 0; i < tempStr.size(); ++i) {
			if (isalpha(tempStr[i])) {
				m_sCipheredText += tolower(tempStr[i]);
			}
		}

		if (m_sCipheredText.size() == 0) {
			inputFile.close();
			throw(std::invalid_argument("nothing to decrypt in file " + m_unPtrParser->inputFileName()));
		}
		inputFile.close();
	}
	catch (const std::exception& er)
	{
		throw er;
	}
}

void decipherer::Mediator::distributeTasksForThreads()
{
	const size_t minBlockPerThread = 500;
	const size_t maxThreads = m_sCipheredText.size() / minBlockPerThread;
	if (maxThreads < 2) {
		//so thread is one
		m_mapDecipheredText[0] = move(m_unPtrDecipherer->decrypt(m_sCipheredText));
	}
	else {
		try
		{
			const size_t hardwareThreads = std::thread::hardware_concurrency() == 0 ? 2 : std::thread::hardware_concurrency();
			const size_t countOfThreads = std::min(hardwareThreads, maxThreads);

			size_t blockPerThread = m_sCipheredText.size() / countOfThreads;
			size_t remainderForLastThread = m_sCipheredText.size() % countOfThreads;
			size_t fromIndex = 0;
			for (size_t i = 0; i < countOfThreads; ++i, fromIndex += blockPerThread) {

				if (i == countOfThreads - 1) {
					std::thread t([=]() {
						m_mapDecipheredText[i] = move(m_unPtrDecipherer->decrypt(m_sCipheredText, fromIndex, fromIndex + blockPerThread + remainderForLastThread));
					});
					m_threadPool.push_back(move(t));
				}
				else {
					std::thread t([=]() {
						m_mapDecipheredText[i] = move(m_unPtrDecipherer->decrypt(m_sCipheredText, fromIndex, fromIndex + blockPerThread));
					});
					m_threadPool.push_back(move(t));
				}
			}
			for (auto it = m_threadPool.begin(); it != m_threadPool.end(); ++it) {
				if (it->joinable()) {
					it->join();
				}
				else {
					throw(std::exception("thread is unjoinable"));
				}
			}
		}
		catch (const std::exception& er)
		{
			throw(er);
		}

	}
}

void decipherer::Mediator::saveDecipheredTextToFile()
{
	std::ofstream outputFile(m_unPtrParser->outputFileName());
	if (!outputFile.is_open()) {
		throw(std::exception(std::string("cannot open file " + m_unPtrParser->outputFileName()).c_str()));
	}
	for (auto it = m_mapDecipheredText.begin(); it != m_mapDecipheredText.end(); ++it) {
		outputFile << it->second;
	}
	outputFile.close();
}
