#ifdef ANFUCK_DEBUG
	#include <conio.h>
#endif

#include "main.h"

static struct Interpreter {
	const char Version[6] = "0.1.0";
	const char* HelpMessage =
R"(Usage: anfuck [version] [help] [path/to/brainfuck/code]
version      Prints the current interpreter version
help         Displays this message
[path/to/brainfuck/code] Gets the location of the code to be interpreted)";
};

int main(int argc, char* argv[]) {
	Interpreter interpreter;
	if (argc != 2 || argv[1] == "help") std::cout << interpreter.HelpMessage << std::endl;
	else if (argv[1] == "version") std::cout << interpreter.Version << std::endl;
	else if (argv[1] == "path/to/brainfuck/code") std::cout << "You have to enter the actual path of your code" << std::endl;
	else ParsePath((std::string)argv[1]);

#ifdef ANFUCK_DEBUG
	auto _ = _getch();
#endif
}

void ParsePath(std::string& pathToFile) {
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
