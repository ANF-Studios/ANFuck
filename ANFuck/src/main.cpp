#ifdef ANFUCK_DEBUG
#include <conio.h>
#endif

#include "main.h"

void ParsePath(const std::string& pathToFile);

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
	if (argc != 2 || (std::string)argv[1] == (std::string)"help") std::cout << HelpMessage << std::endl;
	else if (argv[1] == "version") std::cout << Version << std::endl;
	else if (argv[1] == "path/to/brainfuck/code") std::cout << "You have to enter the actual path of your code";
	else ParsePath((std::string)argv[1]);

#ifdef ANFUCK_DEBUG
	auto _ = _getch();
#endif
}

void ParsePath(const std::string& pathToFile) {
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
