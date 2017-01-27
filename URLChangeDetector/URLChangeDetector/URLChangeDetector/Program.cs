using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;
using System.IO;
using NDesk.Options;


namespace URLChangeDetector
{
    class Program
    {
        static string ParentDirectory = string.Empty;
        static int Threads = 1;
        static string ReplaceDomain = string.Empty;
        static int KeepOldRuns = 2;
        static string RunFolder = string.Empty;
        static string RecentFolder = string.Empty;
        static string LogFile = string.Empty;
        static string AllStatsLogFile = string.Empty;
        static int totalSuccess = 0;
        static int totalFail = 0;
        static void Main(string[] args)
        {
            bool show_help = false;
            
            var p = new OptionSet() 
            {
                { "d|directory=", "the directory to run in.",
                  v => ParentDirectory = v },
                { "t|threads=", 
                    "the number of threads to use while running.\n" + 
                        "this must be an integer.",
                  (int v) => Threads = v },
                { "r|replacedomain=", "the domain to replace.",
                  v => ReplaceDomain = v },
                { "o|keepoldruns=", 
                "the number of Current Run folders to retain.\n" + 
                    "this must be an integer.",
                (int v) => KeepOldRuns = v },
                { "h|help",  "show this message and exit", 
                  v => show_help = v != null },
            };

            List<string> extra;
            try
            {
                extra = p.Parse(args);
            }
            catch (OptionException e)
            {
                Console.Write("URLChangeDetector: ");
                Console.WriteLine(e.Message);
                Console.WriteLine("Try `URLChangeDetector --help' for more information.");
                return;
            }

            if (show_help)
            {
                ShowHelp(p);
                return;
            }

            Run();

            return;
            
        }

        static void Run()
        {
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();

            RunFolder = string.IsNullOrEmpty(ParentDirectory) ? string.Empty : ParentDirectory + "\\";
            RunFolder += DateTime.Now.ToString("yyyy_MM_dd-hhmm-ss");
            RecentFolder = GetRecentFolder(ParentDirectory);
            Directory.CreateDirectory(RunFolder);
            var reader = new StreamReader(File.OpenRead(ParentDirectory + "\\InputURLs.txt"));
            List<UrlFormat> urls = new List<UrlFormat>();
            while (!reader.EndOfStream)
            {
                var line = reader.ReadLine();
                var values = line.Split('\t');
                if(values.Length < 2)
                    continue;
                UrlFormat url = new UrlFormat();
                url.Url = Replace(values[0]);
                url.Method = values[1].ToLower() == "get" ? 0 : 1;
                if (url.Method == 1 && values.Length > 2)
                {
                    url.Content = values[2];
                }
                urls.Add(url);

            }
            LogFile = RunFolder + "\\" + "URL_Results.txt";
            using (StreamWriter sw = File.CreateText(LogFile))
            {
                sw.WriteLine("Url\tTime(Milliseconds)\tResult\tMessage\tComparison\tDifferentLineNumber\tDifferentValue(Old)\tDifferentValue(New)");
                
            }
            
            Parallel.ForEach(
                urls,
                new ParallelOptions { MaxDegreeOfParallelism = Threads },
                url => {
                    if (url.Method == 0)
                    {
                        DownloadWithGet(url);
                    }
                    else
                    {
                        DownloadWithPost(url);
                    }
                }
            );

            AllStatsLogFile = RunFolder + "\\" + "OverAllStats.txt";

            stopWatch.Stop();

            using (StreamWriter sw = File.CreateText(AllStatsLogFile))
            {
                sw.WriteLine("Total Run Time(Milisecond) : " + stopWatch.ElapsedMilliseconds.ToString());
                sw.WriteLine("Total Success Count : " + totalSuccess.ToString());
                sw.WriteLine("Total Fail Count : " + totalFail.ToString());

            }
            Console.WriteLine("Total Run Time(Milisecond) : " + stopWatch.ElapsedMilliseconds.ToString());
            Console.WriteLine("Total Success Count : " + totalSuccess.ToString());
            Console.WriteLine("Total Fail Count : " + totalFail.ToString());

            RemoveOldData();
        }

        static string Replace(string url)
        {
            if (string.IsNullOrEmpty(ReplaceDomain))
                return url;
            var doubleSlashesIndex = url.IndexOf("://");
            var start = doubleSlashesIndex != -1 ? doubleSlashesIndex + "://".Length : 0;
            var end = url.IndexOf("/", start);
            if (end == -1)
                end = url.Length;

            string trimmed = url.Substring(start, end - start);
            //if (trimmed.StartsWith("www."))
            //    trimmed = trimmed.Substring("www.".Length);
            //if(ReplaceDomain.StartsWith("www."))
            //    ReplaceDomain = ReplaceDomain.Substring("www.".Length);
            string newURL = url.Replace(trimmed, ReplaceDomain);
            return trimmed;
        }
        static void RemoveOldData()
        {
            string[] dirs = Directory.GetDirectories(ParentDirectory);
            List<DateTime> lstDirs = new List<DateTime>();
            foreach(string dir in dirs)
            {
                lstDirs.Add(DateTime.ParseExact(dir.Replace(ParentDirectory + "\\", ""), "yyyy_MM_dd-hhmm-ss", null));
            }
            lstDirs.Sort();
            lstDirs.Reverse();
            for (int i = 0; i < lstDirs.Count; i++)
            {
                if(i >= KeepOldRuns)
                {
                    string path = ParentDirectory + "\\" + lstDirs[i].ToString("yyyy_MM_dd-hhmm-ss");
                    Directory.Delete(path, true);
                    Console.WriteLine("Removed {0} Folder", lstDirs[i].ToString("yyyy_MM_dd-hhmm-ss"));
                }
            }
        }
        static string GetRecentFolder(string root)
        {
            string[] dirs = Directory.GetDirectories(root);
            DateTime recentDate = DateTime.MinValue;
            string result = string.Empty;
            foreach(string dir in dirs)
            {
                try
                {
                    DateTime dt = DateTime.ParseExact(dir.Replace(root + "\\", ""), "yyyy_MM_dd-hhmm-ss", null);
                    if (dt > recentDate)
                    {
                        recentDate = dt;
                        result = dir;
                    }
                }
                catch(Exception ex)
                {
                    continue;
                }
            }
            return result;
        }
        static void DownloadWithGet(UrlFormat url)
        {
            WebRequest request = WebRequest.Create(url.Url);
            request.Credentials = CredentialCache.DefaultCredentials;
            string responseContent = null;
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            string errorMessage = string.Empty;
            int status = 0;
            try
            {
                using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
                {
                    using (Stream stream = response.GetResponseStream())
                    {
                        using (StreamReader reader = new StreamReader(stream))
                        {
                            responseContent = reader.ReadToEnd();
                            string resultFileName = RunFolder + "\\" + url.Url.GetHashCode().ToString();
                            File.WriteAllText(resultFileName, responseContent);
                        }
                    }
                }
            }
            catch(WebException ex)
            {
                errorMessage = ex.Message;
                status = 1;
            }

            
            stopWatch.Stop();

            if (!File.Exists(RecentFolder + "\\" + url.Url.GetHashCode().ToString()))
            {
                status = 2;
                errorMessage = "no prior for comparison";
            }

            WriteLogFile(url, stopWatch.ElapsedMilliseconds, status, errorMessage);            
        }
        
        static void DownloadWithPost(UrlFormat url)
        {
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            string errorMessage = string.Empty;
            int status = 0;

            byte[] data = Encoding.ASCII.GetBytes(url.Content);

            WebRequest request = WebRequest.Create(url.Url);
            request.Method = "POST";
            request.ContentType = "application/x-www-form-urlencoded";
            request.ContentLength = data.Length;
            
            using (Stream stream = request.GetRequestStream())
            {
                stream.Write(data, 0, data.Length);
            }

            string responseContent = null;
            try
            {
                using (WebResponse response = request.GetResponse())
                {
                    using (Stream stream = response.GetResponseStream())
                    {
                        using (StreamReader reader = new StreamReader(stream))
                        {
                            responseContent = reader.ReadToEnd();
                            string resultFileName = RunFolder + "\\" + url.Url.GetHashCode().ToString();
                            File.WriteAllText(resultFileName, responseContent);
                        }
                    }
                }
            }
            catch (WebException ex)
            {
                errorMessage = ex.Message;
                status = 1;
            }


            stopWatch.Stop();

            if ((status == 0) && (!File.Exists(RecentFolder + "\\" + url.Url.GetHashCode().ToString())))
            {
                status = 2;
                errorMessage = "no prior for comparison";
            }

            WriteLogFile(url, stopWatch.ElapsedMilliseconds, status, errorMessage);    
        }

        static void WriteLogFile(UrlFormat url, long miliseconds, int status, string errorMessage)
        {
            
            if(status == 0)
            {
                totalSuccess++;
            }
            else
            {
                totalFail++;
            }

            string log = url.Url + "\t";
            log += miliseconds.ToString() + "\t";
            
            log += (status == 0 ? "Success" : "Failure") + "\t";
            
            log += errorMessage + "\t";

            if (status == 0)
            {
                string oldValue = System.IO.File.ReadAllText(RecentFolder + "\\" + url.Url.GetHashCode().ToString());
                string newValue = System.IO.File.ReadAllText(RunFolder + "\\" + url.Url.GetHashCode().ToString());
                if(oldValue.Equals(newValue, StringComparison.Ordinal))
                {
                    log += "Identical\t";
                }
                else
                {
                    log += "Different\t";
                    string[] oldLines = oldValue.Split(new string[] { Environment.NewLine }, StringSplitOptions.None);
                    string[] newLines = newValue.Split(new string[] { Environment.NewLine }, StringSplitOptions.None);
                    int length = Math.Min(oldLines.Length, newLines.Length);
                    int i = 0;
                    for (i = 0; i < length; i++)
                    {
                        if (!(oldLines[i].Equals(newLines[i], StringComparison.Ordinal)))
                            break;
                    }
                    if(i < length)
                    {
                        log += (i + 1).ToString() + "\t";

                        int dIndex = DiffersAtIndex(oldLines[i], newLines[i]);
                        if (dIndex < 0)
                        {
                            log += "\t\t";
                        }
                        else
                        {
                            if(dIndex < oldLines[i].Length)
                            {
                                log += oldLines[i].Substring(dIndex, 100);
                            }
                            log += "\t";

                            if (dIndex < newLines[i].Length)
                            {
                                log += newLines[i].Substring(dIndex, 100);
                            }
                            log += "\t";
                        }

                    }
                    else
                    {
                        log += "\t\t\t";
                    }
                }
            }
            else
            {
                log += "\t\t\t\t";
            }

            using (StreamWriter sw = File.AppendText(LogFile))
            {
                sw.WriteLine(log);
                
            }
        }
        static int DiffersAtIndex(string s1, string s2)
        {
            int index = 0;
            int min = Math.Min(s1.Length, s2.Length);
            while (index < min && s1[index] == s2[index])
                index++;

            return (index == min && s1.Length == s2.Length) ? -1 : index;
        }
        static void ShowHelp(OptionSet p)
        {
            Console.WriteLine("Usage: URLChangeDetector [OPTIONS]=[VALUE]");
            Console.WriteLine();
            Console.WriteLine("Options:");
            p.WriteOptionDescriptions(Console.Out);
        }

        
    }
    class UrlFormat
    {
        public string Url { get; set; }
        public int Method { get; set; }
        public string Content { get; set; }

    }
}
