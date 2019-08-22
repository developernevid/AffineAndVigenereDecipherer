// decipherer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Mediator.h"

int main(int argc, char *argv[])
{
	try
	{
		decipherer::Mediator mediator(argc, argv);
		mediator.mediate();
	}
	catch (const std::exception& er)
	{
		std::cout << er.what() << std::endl;
		return -1;
	}
	return 0;
}
