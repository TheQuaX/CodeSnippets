using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hanoi
{
    class Program
    {
        static void hanoi(char source, char middle, char dest, int n)
        {
            if (n == 1) {
                Console.WriteLine(source + " -> " + dest);
            } else {
                hanoi(source, dest, middle, n - 1);
                Console.WriteLine(source + " -> " + dest);
                hanoi(middle, source, dest, n - 1);
            }
        }

        static void Main(string[] args)
        {
            hanoi('A', 'B', 'C', 5);
        }
    }
}
