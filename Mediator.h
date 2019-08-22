#pragma once
#include <memory>
#include <thread>
#include <map>
#include <vector>

#include "CommandArgsParser.h"
#include "AbstractDecryption.h"

namespace decipherer {
	class Mediator
	{
	public:
		Mediator(int argc, char *argv[]);
		~Mediator();

		//reads text from filepath and converts ciphered text to lowercase symbols
		inline void mediate()
		{
			readCipheredTextFromFile();
			distributeTasksForThreads();
			saveDecipheredTextToFile();
		}

	private:
		void readCipheredTextFromFile();
		void distributeTasksForThreads();
		void saveDecipheredTextToFile();

	private:
		std::string m_sCipheredText;
		//key equals to number of thread just for ordering result string
		std::map<int, std::string> m_mapDecipheredText;
		std::vector<std::thread> m_threadPool;
		std::unique_ptr<AbstractDecryption> m_unPtrDecipherer;
		std::unique_ptr<CommandArgsParser> m_unPtrParser;
	};
};

