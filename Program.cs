using System;
using System.IO;
using System.Text;
using System.Collections.Generic;

namespace BFI
{
    sealed class Program
    {
        public static string code;
        public static short[] memory;
        public static int ptr;
        public static int codePos;
        public static Stack<int> stack;
        public static Dictionary<int, int> branchTable;
        public const int MEMORY_CELLS = 65536;

        private static void Main()
        {
            Initialize();
            Program p = new Program();
            p.Run();
            Console.ReadKey(true);
        }

        private static void Initialize()
        {
            Console.OutputEncoding = Encoding.ASCII;
            Console.Title = "BrainFuck Interpreter";
        }
        
        public void Run()
        {
            var source = new FileInfo("Program.bf");
            if (!source.Exists)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("[ERROR] This file doesn't exists");
            }
            Parse(source);
        }
        
        static void Parse(FileInfo f)
        {
            memory = new short[MEMORY_CELLS];
            ptr = 0;
            codePos = 0;
            stack = new Stack<int>();
            branchTable = new Dictionary<int, int>();

            try
            {
                using (StreamReader r = f.OpenText())
                    code = r.ReadToEnd();
            }
            catch (Exception e)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine(e);
            }
            
            for (int i = 0; i < code.Length; i++)
            {
                switch (code[i])
                {
                    case '[':
                        stack.Push(i);
                        break;
                    case ']':
                        if (stack.Count == 0)
                        {
                            Console.ForegroundColor = ConsoleColor.Red;
                            Console.WriteLine("[ERROR] Missing opening chevron \"[\"");
                            Console.ResetColor();
                        }
                        else
                        {
                            var openingBracketPosition = stack.Pop();
                            branchTable.Add(openingBracketPosition, i + 1);
                            branchTable.Add(i, openingBracketPosition + 1);
                        }
                        break;
                    default:
                        break;

                }
            }
            
            if (stack.Count > 0)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("[ERROR] Missing closing chevron \"]\"");
                return;
            }
            while (codePos < code.Length)
            {
                switch (code[codePos])
                {
                    case '+':
                        memory[ptr]++;
                        codePos++;
                        break;
                    case '-':
                        memory[ptr]--;
                        codePos++;
                        break;
                    case '>':
                        ptr++;
                        if (ptr == MEMORY_CELLS)
                            ptr = 0;
                        codePos++;
                        break;
                    case '<':
                        ptr--;
                        if (ptr == -1)
                            ptr = MEMORY_CELLS - 1;
                        codePos++;
                        break;
                    case '.':
                        Console.Write(Convert.ToChar(memory[ptr]));
                        codePos++;
                        break;
                    case ',':
                        var r = (short)Console.Read();
                        if (r != 13)
                        {
                            if (r != -1)
                                memory[ptr] = r;
                            codePos++;
                        }
                        break;
                    case '[':
                        if (memory[ptr] == 0)
                            codePos = branchTable[codePos];
                        else
                            codePos++;
                        break;
                    case ']':
                        if (memory[ptr] == 0)
                            codePos++;
                        else
                            codePos = branchTable[codePos];
                        break;
                    default:
                        codePos++;
                        break;
                }
            }
        }
    }
}
