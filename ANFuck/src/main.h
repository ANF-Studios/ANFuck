#pragma once
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

namespace ANFuck {
	std::string LoadFile(const std::string& filename)
	{
		std::string commands;
		std::ifstream file(filename);

		if (!file.is_open())
			throw std::runtime_error("Failed to open '" + filename + "'.");

		while (file.good()) 
			commands.push_back(file.get());

		return commands;
	}

	void ParseCode(const std::string& commands)
	{
		std::vector<int> data(1, 0);
		std::vector<int>::iterator dataPtr = data.begin();
		std::vector<int>::iterator& defaultDataPtr = dataPtr;

		std::string::const_iterator instructionPtr = commands.begin();
		std::stack<std::string::const_iterator> instructionStack;

		while (instructionPtr != commands.end())
		{
			switch (*instructionPtr)
			{
				// These are basic brainfuck commands
				case '<':
				{
					dataPtr--;
					break;
				}
				case '>':
				{
					dataPtr++;
					if (dataPtr == data.end()) {
						data.push_back(0);
						dataPtr = data.end() - 1;
					}
					break;
				}
				case '+':
				{
					(*dataPtr) += 1;
					break;
				}
				case '-':
				{
					(*dataPtr) -= 1;
					break;
				}
				case '.':
				{
					std::cout << char(*dataPtr);
					break;
				}
				case ',':
				{
					char input;
					std::cin >> input;
					*dataPtr = input;
				}
				case '[':
				{
					instructionStack.push(instructionPtr);

					if (*dataPtr == 0)
					{
						auto startInstructionPtr = instructionPtr;
						while (++instructionPtr != commands.end())
						{
							if (*instructionPtr == '[')
								instructionStack.push(instructionPtr);

							else if (*instructionPtr == ']')
							{
								if (instructionStack.empty())
									throw std::runtime_error("Found a ']' that did not have a matching '['!");

								auto tempInstructionPtr = instructionStack.top();
								instructionStack.pop();

								if (startInstructionPtr == tempInstructionPtr)
									break;
							}
						}
					}
					break;
				}
				case ']':
				{
					if (instructionStack.empty()) 
						throw std::runtime_error("Found a ']' that did not have a matching '['!");

					if (*dataPtr != 0) 
						instructionPtr = instructionStack.top();
					else 
						instructionStack.pop();

					break;
				}
				// From here, starts all added commands
				// which make ANFuck
				case '_':
				{
					// Change the current value's number
					// to something random.
					*dataPtr = rand() % 126 + 1;
					break;
				}
				case '*':
				{
					// Set the dataPtr to what it was at the beggining
					*dataPtr = *defaultDataPtr;
				}
				default:
					break;
			}

			instructionPtr++;
		}


		if (!instructionStack.empty())
			throw std::runtime_error("Found a '[' that did not have a matching ']'!");
	}
}
