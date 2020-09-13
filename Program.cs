using System;

namespace BrainFuckInterpreter
{
    class Program
    {
        private static void Main()
        {
            Initialize();
            MainCode();
        }

        private static void Initialize()
        {
            Console.Title = "BrainFuck Interpreter";
        }

        private static void MainCode()
        {
            Console.WriteLine("Enter Command Buffer: ");
            string commandBuffer = Console.ReadLine();

            int[] memory = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            int memoryPointer = 0;
            Console.ForegroundColor = ConsoleColor.Blue;

            for (int i = 0; i < commandBuffer.Length; ++i)
            {
                switch (commandBuffer[i])
                {
                    case ',':
                        try
                        {
                            Console.Clear();
                            Console.Write("Provide input (int): ");
                            string input = Console.ReadLine();
                            memory[memoryPointer] = System.Convert.ToInt32(input);
                        }

                        catch (Exception ex)
                        {
                            Console.Beep();
                            Console.Clear();
                            Console.ForegroundColor = ConsoleColor.White;
                            Console.Write("An exception has occured and this step is skipped!\n" + ex.Message);
                            Console.ForegroundColor = ConsoleColor.Blue;
                            Console.ReadKey(true);
                        }
                        break;

                    case '.':
                        Console.WriteLine(memory[memoryPointer]);
                        break;

                    case '<':
                        try
                        {
                            memoryPointer--;
                        }

                        catch (Exception ex)
                        {
                            Console.Beep();
                            Console.Clear();
                            Console.ForegroundColor = ConsoleColor.White;
                            Console.Write("An exception has occured and this step is skipped!\n" + ex.Message);
                            Console.ForegroundColor = ConsoleColor.Blue;
                            Console.ReadKey(true);
                        }

                        break;

                    case '>':
                        memoryPointer++;
                        break;

                    case '+':
                        memory[memoryPointer] += 1;
                        break;

                    case '-':
                        memory[memoryPointer] -= 1;
                        break;

                    case '[':
                        if (memory[memoryPointer] == 0)
                        {
                            int skip = 0;
                            int ptr = i + 1;
                            while (commandBuffer[ptr] != ']' || skip > 0)
                            {
                                if (commandBuffer[ptr] == '[')
                                {
                                    skip += 1;
                                }
                                else if (commandBuffer[ptr] == ']')
                                {
                                    skip -= 1;
                                }
                                ptr += 1;
                                i = ptr;
                            }
                        }
                        break;

                    case ']':
                        if (memory[memoryPointer] != 0)
                        {
                            int skip = 0;
                            int ptr = i - 1;
                            while (commandBuffer[ptr] != '[' || skip > 0)
                            {
                                if (commandBuffer[ptr] == ']')
                                {
                                    skip += 1;
                                }
                                else if (commandBuffer[ptr] == '[')
                                {
                                    skip -= 1;
                                }
                                ptr -= 1;
                                i = ptr;
                            }
                        }
                        break;
                }

                Console.Clear();

                for (int j = 0; j < memory.Length; ++j)
                {
                    if (j == memoryPointer)
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                    }
                    else
                    {
                        Console.ForegroundColor = ConsoleColor.Blue;
                    }
                    Console.Write(memory[j] + " ");
                }
                Console.WriteLine("\n");

                for (int j = 0; j < commandBuffer.Length; ++j)
                {
                    if (j == i)
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                    }
                    else
                    {
                        Console.ForegroundColor = ConsoleColor.Blue;
                    }
                    Console.Write(commandBuffer[j] + " ");
                }

                System.Threading.Thread.Sleep(1000);
            }

            Console.ForegroundColor = ConsoleColor.White;
            Console.Write("\nPress any key to continue or q to close...");
            var Input = Console.ReadKey();
            if (Input.Key == ConsoleKey.Q) Environment.Exit(0);
            else
            {
                Console.Clear();
                MainCode();
            }
        }
    }
}
