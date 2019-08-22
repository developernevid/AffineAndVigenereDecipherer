#include "pch.h"
#include "CommandArgsParser.h"
#include <iostream>

decipherer::CommandArgsParser::CommandArgsParser(int argc, char *argv[])
{
	if (argc > 1 
		&& ((argc - 1) % 2) == 0) {
		int index = 1;
		while (argc - 1 > 0) {
			if (parseInputFileName(argv[index], argv[index + 1])) {}
			else if (parseOutputFileName(argv[index], argv[index + 1])) {}
			else if (parseDecipherType(argv[index], argv[index + 1])) {}
			else if (parseKey(argv[index], argv[index + 1])) {}
			else {
				throw(std::invalid_argument("Incorrect arguments of command line.\n"\
					"Example of correct arguments: \n"\
					"decipherer.exe -input_file_name sss.txt -output_file_name decipheredByVigenere.txt -decipher_type [vigener / affine] -key [myvigenerekey / 12_21]"));
			}

			index += 2;
			argc -= 2;
		}

		if (m_sDecipherType.empty()
			|| m_sInputFileName.empty()
			|| m_sKey.empty()
			|| m_sOutputFileName.empty()) 
		{
			throw(std::invalid_argument("Not completed list of arguments. Enter full list.\n"\
				"Example of correct arguments: \n"\
				"decipherer.exe -input_file_name sss.txt -output_file_name decipheredByVigenere.txt -decipher_type [vigener / affine] -key [myvigenerekey / 12_21]"));
		}
	}
	else {
		throw(std::invalid_argument("Please enter correct arguments.\n"\
			"Example of correct arguments: \n"\
			"decipherer.exe -input_file_name sss.txt -output_file_name decipheredByVigenere.txt -decipher_type [vigener / affine] -key [myvigenerekey / 12_21]"));
	}
}

std::string decipherer::CommandArgsParser::inputFileName() const
{
	return m_sInputFileName;
}

std::string decipherer::CommandArgsParser::outputFileName() const
{
	return m_sOutputFileName;
}

std::string decipherer::CommandArgsParser::key() const
{
	return m_sKey;
}

std::string decipherer::CommandArgsParser::decipherType() const
{
	return m_sDecipherType;
}

bool decipherer::CommandArgsParser::parseInputFileName(const char * key, const char * value)
{
	if (strcmp(key, "-input_file_name") != 0) {
		return false;
	}
	m_sInputFileName = value;
	return true;
}

bool decipherer::CommandArgsParser::parseOutputFileName(const char * key, const char * value)
{
	if (strcmp(key, "-output_file_name") != 0) {
		return false;
	}
	m_sOutputFileName = value;
	return true;
}

bool decipherer::CommandArgsParser::parseDecipherType(const char * key, const char * value)
{
	if (strcmp(key, "-decipher_type") != 0) {
		return false;
	}
	m_sDecipherType = value;
	return true;
}

bool decipherer::CommandArgsParser::parseKey(const char * key, const char * value)
{
	if (strcmp(key, "-key") != 0) {
		return false;
	}
	m_sKey = value;
	return true;
}