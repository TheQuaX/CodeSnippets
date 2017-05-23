using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

    class Program
    {
        static Dictionary<char, string> charToMorse = new Dictionary<char, string>()
        {
            {'a', ".-"},
            {'b', "-..."},
            {'c', "-.-."},
            {'d', "-.."},
            {'e', "."},
            {'f', "..-."},
            {'g', "--."},
            {'h', "...."},
            {'i', ".."},
            {'j', ".---"},
            {'k', "-.-"},
            {'l', ".-.."},
            {'m', "--"},
            {'n', "-."},
            {'o', "---"},
            {'p', ".--."},
            {'q', "--.-"},
            {'r', ".-."},
            {'s', "..."},
            {'t', "-"},
            {'u', "..-"},
            {'v', "...-"},
            {'w', ".--"},
            {'x', "-..-"},
            {'y', "-.--"},
            {'z', "--.."},
            
            {'0', "-----"},
            {'1', ".----"},
            {'2', "..---"},
            {'3', "...--"},
            {'4', "....-"},
            {'5', "....."},
            {'6', "-...."},
            {'7', "--..."},
            {'8', "---.."},
            {'9', "----."},
            
            {' ', "/"},
            {'.', ".-.-.-"},
            {',', "--..--"},
            {':', "---..."},
            {'?', "..--.."},
            {'!', "..--."},
            {'\'', ".----."},
            {'-', "-....-"},
            {'/', "-..-."},
            {'"', ".-..-."},
            {'@', ".--.-."},
            {'=', "-...-"}
        };
        
        static void Main(string[] args)
        {
            string input = Console.ReadLine().ToLower().Trim();
            StringBuilder output = new StringBuilder();
            foreach(char c in input)
                if(charToMorse.ContainsKey(c))
                    output.Append(charToMorse[c] + " ");
            Console.WriteLine(output);
        }
    }
