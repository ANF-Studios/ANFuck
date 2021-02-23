#ifdef ANFUCK_DEBUG
#include <conio.h>
#endif

#include "main.h"

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
	const std::string helpType = (std::string)argv[1];
	if (argc != 2 || helpType == (std::string)"help") std::cout << HelpMessage;
	else if (helpType == (std::string)"version") std::cout << Version;
	else if (helpType == (std::string)"path/to/brainfuck/code") std::cout << "You have to enter the actual path of your code";
	else GetAndRunCode((std::string)argv[1]);

#ifdef ANFUCK_DEBUG
	auto _ = _getch();
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
