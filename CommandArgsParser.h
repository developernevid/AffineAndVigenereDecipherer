#pragma once
#include <string>


namespace decipherer {
    class CommandArgsParser
    {
    public:
        CommandArgsParser(int argc, char *argv[]);

		//getters
		std::string inputFileName() const;
		std::string outputFileName() const;
		std::string key() const;
		std::string decipherType() const;

    private:
		bool parseInputFileName(const char* key, const char* value);
		bool parseOutputFileName(const char* key, const char* value);
		bool parseDecipherType(const char* key, const char* value);
		bool parseKey(const char * key, const char * value);

	private:
		std::string m_sInputFileName;
		std::string m_sOutputFileName;
		std::string m_sKey;
		std::string m_sDecipherType;
    };
}
