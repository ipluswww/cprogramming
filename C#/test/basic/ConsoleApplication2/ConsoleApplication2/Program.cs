using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Text;

namespace ConsoleApplication2
{
    class Program
    {
        public const int file_block_size = 1000000;

        static void Main(string[] args)
        {
            String filename = "";
            filename = Console.ReadLine();
            filename = filename.Trim('\"');


            var filestream = new FileStream(@filename, FileMode.Open);
            var length  = (int)filestream.Length;
            var readable_size = Math.Min(length, file_block_size);
            var bits    = new byte[length];

            filestream.Read(bits, 0, readable_size);

            for(int ix = 0; ix < readable_size; ix++) {
                bits[ix] ^= (byte)0xff;
            }

            filestream.Seek(0, SeekOrigin.Begin);
            filestream.Write(bits, 0, readable_size);

            filestream.Close();
        }
    }
}
