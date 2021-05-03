#ifdef ANFUCK_DEBUG
	#ifdef _WIN32
		#include <conio.h>
	#else
		#include <iostream>
	#endif
#endif

#include "main.h"

template<typename T>
void PrintMessage(const T& msg);
void GetAndRunCode(const std::string& pathToFile);

const char Version[6] = "0.1.0";
const char* HelpMessage = R"(Usage: anfuck [version] [help] [path/to/brainfuck/code]
version                        Prints the current interpreter version
help                           Displays this message
path/to/brainfuck/code         Gets the location of the code to be interpreted)";

int main(int argc, char* argv[]) {
#ifdef ANFUCK_DEBUG
	std::cout
		<< "argv[1]: "
		<< typeid(argv[1]).name()
		<< std::endl
		<< "help: "
		<< typeid("help").name()
		<< std::endl;
#endif
	if (argv[1] != nullptr)
	{
		const std::string helpType = (std::string)argv[1];
		if (argc != 2 || helpType == (std::string)"help") PrintMessage(HelpMessage);
		else if (helpType == (std::string)"version") PrintMessage((std::string)"ANFuck v" + Version);
		else if (helpType == (std::string)"path/to/brainfuck/code") std::cout << "You have to enter the actual path of your code";
		else GetAndRunCode((std::string)argv[1]);
	} else PrintMessage(HelpMessage);

#ifdef ANFUCK_DEBUG
	#ifdef _WIN32
		auto _ = _getch();
	#else
		std::cin.get();
	#endif
#endif
}

void GetAndRunCode(const std::string& pathToFile) {
    try
	{
		std::string commands = ANFuck::LoadFile(pathToFile);
		ANFuck::ParseCode(commands);
	}
	catch (const std::exception& e)
	{
		std::cout << std::endl << e.what() << std::endl;
	}
}

template<typename T>
void PrintMessage(const T& msg) { std::cout << msg; }
