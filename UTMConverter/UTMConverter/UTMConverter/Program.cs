using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Threading;

namespace UTMConverter
{
    class Program
    {
        const double UTM_FACTOR = 0.9996;
        const double UTM_FALSE_EASTING = 500000;

        const double WGS84_HALF_AXIS = 6378137.000;

        const double WGS84_CLEARING = 3.35281066474748E-03;

        const string UTM_BAND = "CDEFGHJKLMNPQRSTUVWXX";

        const double WGS84_POL = WGS84_HALF_AXIS / (1 - WGS84_CLEARING);

        const double WGS84_EXCENT = ((2 * WGS84_CLEARING) - (WGS84_CLEARING * WGS84_CLEARING));
        const double WGS84_EXCENT2 = ((2 * WGS84_CLEARING) - (WGS84_CLEARING * WGS84_CLEARING)) / ((1 - WGS84_CLEARING) * (1 - WGS84_CLEARING));
        const double WGS84_EXCENT4 = WGS84_EXCENT2 * WGS84_EXCENT2;
        const double WGS84_EXCENT6 = WGS84_EXCENT4 * WGS84_EXCENT2;
        const double WGS84_EXCENT8 = WGS84_EXCENT4 * WGS84_EXCENT4;

        const double MIN_LONGITUDE = -180.0;
        const double MAX_LONGITUDE = +180.0;
        const double MIN_LATITUDE = -80.0;
        const double MAX_LATITUDE = +84.0;
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                WGS84 wgs = ToWGS84(38, "N", 437888.60784181167, 5188481.069527702);
                Console.WriteLine("Longitude : " + wgs.Longitude.ToString());
                Console.WriteLine("Latitude : " + wgs.Latitude.ToString());

                UTM utm = ToUTM(44.18534110153871, 46.84697229537016);
                Console.WriteLine("East : " + utm.East.ToString());
                Console.WriteLine("North : " + utm.North.ToString());
                Console.WriteLine("Zone : " + utm.Zone.ToString());
                Console.WriteLine("Band : " + utm.Band.ToString());
            }
            else if(args.Length == 2)
            {
                RunBenchmark(args);
            }
            else
            {
                Console.WriteLine("Invalid arguments");
            }
        }

        public static void RunBenchmark(string[] args)
        {
            long count = 0;
            Stopwatch stopWatch = new Stopwatch();
            try
            {
                count = Convert.ToInt64(args[1]);
            }
            catch(Exception ex)
            {
                Console.WriteLine("Invalid arguments");
                return;
            }
            
            if(args[0].ToLower() == "utm")
            {
                stopWatch.Start();
                for (long i = 0; i < count; i++)
                {
                    UTM utm = ToUTM(44.18534110153871, 46.84697229537016);
                }
                stopWatch.Stop();
            }
            else if(args[0].ToLower() == "wgs")
            {
                stopWatch.Start();
                for (long i = 0; i < count; i++)
                {
                    WGS84 wgs = ToWGS84(38, "N", 437888.60784181167, 5188481.069527702);
                }
                stopWatch.Stop();
            }
            else
            {
                Console.WriteLine("Invalid arguments");
                return;
            }
            Console.WriteLine("Rows : " + count.ToString());
            Console.WriteLine("Elappsed Time(miliseconds) : " + stopWatch.ElapsedMilliseconds.ToString());


        }
        public static UTM ToUTM(double longitude, double latitude)
        {
            

            if (longitude <= MIN_LONGITUDE || longitude > MAX_LONGITUDE || latitude < MIN_LATITUDE || latitude > MAX_LATITUDE)
            {
                throw new Exception("Inavalid input data");
            }

            double kf0 = WGS84_POL * (Math.PI / 180) * (1 - 3 * WGS84_EXCENT2 / 4 + 45 * WGS84_EXCENT4 / 64 - 175 * WGS84_EXCENT6 / 256 + 11025 * WGS84_EXCENT8 / 16384);
            double kf2 = WGS84_POL * (-3 * WGS84_EXCENT2 / 8 + 15 * WGS84_EXCENT4 / 32 - 525 * WGS84_EXCENT6 / 1024 + 2205 * WGS84_EXCENT8 / 4096);
            double kf4 = WGS84_POL * (15 * WGS84_EXCENT4 / 256 - 105 * WGS84_EXCENT6 / 1024 + 2205 * WGS84_EXCENT8 / 16384);
            double kf6 = WGS84_POL * (-35 * WGS84_EXCENT6 / 3072 + 315 * WGS84_EXCENT8 / 12288);

            
            int zone = (int)((longitude + 180) / 6) + 1;
            
            if ((latitude >= 56d) && (latitude < 64d) && (longitude >= 3d) && (longitude < 12d))
            {
            
                zone = 32;

            }
            else if (latitude >= 72d)
            {
            
                if ((longitude >= 0d) && (longitude < 9d)) zone = 31;
                else if ((longitude >= 9d) && (longitude < 21d)) zone = 33;
                else if ((longitude >= 21d) && (longitude < 33d)) zone = 35;
                else if ((longitude >= 33d) && (longitude < 42d)) zone = 37;
            }

            string sZone = string.Format("00", zone);
            int bandIndex = (int)(1 + (latitude + 80) / 8);
            string band = UTM_BAND.Substring(bandIndex - 1, 1);

            
            double latitudeRad = latitude * Math.PI / 180;

            double tan1 = Math.Tan(latitudeRad);
            double tan2 = Math.Pow(tan1, 2);
            double tan4 = Math.Pow(tan1, 4);
            double cosinus1 = Math.Cos(latitudeRad);
            double cosinus2 = Math.Pow(cosinus1, 2);
            double cosinus3 = Math.Pow(cosinus1, 3);
            double cosinus4 = Math.Pow(cosinus1, 4);
            double cosinus5 = Math.Pow(cosinus1, 5);

            double eta = WGS84_EXCENT2 * cosinus2;

            double tc = WGS84_POL / Math.Sqrt(1 + eta);

            double maLen = (kf0 * latitude) + (kf2 * Math.Sin(2 * latitudeRad)) + (kf4 * Math.Sin(4 * latitudeRad)) + (kf6 * Math.Sin(6 * latitudeRad));

            int merid = (zone - 30) * 6 - 3;

            double dLongitude1 = (longitude - merid) * Math.PI / 180;
            double dLongitude2 = Math.Pow(dLongitude1, 2);
            double dLongitude3 = Math.Pow(dLongitude1, 3);
            double dLongitude4 = Math.Pow(dLongitude1, 4);
            double dLongitude5 = Math.Pow(dLongitude1, 5);

            
            double east, north;
            if (latitude < 0)
            {
                north = 10E+06 + UTM_FACTOR * (maLen + tc * cosinus2 * tan1 * dLongitude2 / 2 + tc * cosinus4 * tan1 * (5 - tan2 + 9 * eta) * dLongitude4 / 24);
            }
            else
            {
                north = UTM_FACTOR * (maLen + tc * cosinus2 * tan1 * dLongitude2 / 2 + tc * cosinus4 * tan1 * (5 - tan2 + 9 * eta) * dLongitude4 / 24);
            }
            east = UTM_FACTOR * (tc * cosinus1 * dLongitude1 + tc * cosinus3 * (1 - tan2 + eta) * dLongitude3 / 6 + tc * cosinus5 * (5 - 18 * tan2 + tan4) * dLongitude5 / 120) + UTM_FALSE_EASTING;

            north = Math.Round(north, 3);
            east = Math.Round(east, 3);

            return new UTM(zone, band, east, north);
        }
        public static WGS84 ToWGS84(int zone, string band, double east, double north)
        {

            double kf0 = WGS84_POL * (Math.PI / 180) * (1 - 3 * WGS84_EXCENT2 / 4 + 45 * WGS84_EXCENT4 / 64 - 175 * WGS84_EXCENT6 / 256 + 11025 * WGS84_EXCENT8 / 16384);
            double kf2 = (180 / Math.PI) * (3 * WGS84_EXCENT2 / 8 - 3 * WGS84_EXCENT4 / 16 + 213 * WGS84_EXCENT6 / 2048 - 255 * WGS84_EXCENT8 / 4096);
            double kf4 = (180 / Math.PI) * (21 * WGS84_EXCENT4 / 256 - 21 * WGS84_EXCENT6 / 256 + 533 * WGS84_EXCENT8 / 8192);
            double kf6 = (180 / Math.PI) * (151 * WGS84_EXCENT6 / 6144 - 453 * WGS84_EXCENT8 / 12288);

            char b = band.ToCharArray()[0];
            if (b < 'N' && band != "")
            {
                north = north - 10E+06;
            }

            double sig = (north / UTM_FACTOR) / kf0;
            double sigRad = sig * Math.PI / 180;
            double fLatitude = sig + kf2 * Math.Sin(2 * sigRad) + kf4 * Math.Sin(4 * sigRad) + kf6 * Math.Sin(6 * sigRad);
            double latitudeRad = fLatitude * Math.PI / 180;

            double tan1 = Math.Tan(latitudeRad);
            double tan2 = tan1 * tan1;
            double tan4 = tan2 * tan2;
            double cosinus1 = Math.Cos(latitudeRad);
            double cosinus2 = cosinus1 * cosinus1;

            double eta = WGS84_EXCENT2 * cosinus2;

            double tc1 = WGS84_POL / Math.Sqrt(1 + eta);
            double tc2 = Math.Pow(tc1, 2);
            double tc3 = Math.Pow(tc1, 3);
            double tc4 = Math.Pow(tc1, 4);
            double tc5 = Math.Pow(tc1, 5);
            double tc6 = Math.Pow(tc1, 6);

            double merid = (zone - 30) * 6 - 3;
            double dLongitude1 = (east - UTM_FALSE_EASTING) / UTM_FACTOR;
            double dLongitude2 = Math.Pow(dLongitude1, 2);
            double dLongitude3 = Math.Pow(dLongitude1, 3);
            double dLongitude4 = Math.Pow(dLongitude1, 4);
            double dLongitude5 = Math.Pow(dLongitude1, 5);
            double dLongitude6 = Math.Pow(dLongitude1, 6);

            double bfakt2 = -tan1 * (1 + eta) / (2 * tc2);
            double bfakt4 = tan1 * (5 + 3 * tan2 + 6 * eta * (1 - tan2)) / (24 * tc4);
            double bfakt6 = -tan1 * (61 + 90 * tan2 + 45 * tan4) / (720 * tc6);

            
            double lfakt1 = 1 / (tc1 * cosinus1);
            double lfakt3 = -(1 + 2 * tan2 + eta) / (6 * tc3 * cosinus1);
            double lfakt5 = (5 + 28 * tan2 + 24 * tan4) / (120 * tc5 * cosinus1);

            
            double latitude = fLatitude + (180 / Math.PI) * (bfakt2 * dLongitude2 + bfakt4 * dLongitude4 + bfakt6 * dLongitude6);
            double longitude = merid + (180 / Math.PI) * (lfakt1 * dLongitude1 + lfakt3 * dLongitude3 + lfakt5 * dLongitude5);

            return new WGS84(longitude, latitude);
            

        }

        public class WGS84
        {
            public double Longitude { get; private set; }
            public double Latitude { get; private set; }

            public WGS84(double longitude, double latitude)
            {
                Longitude = longitude;
                Latitude = latitude;
            }
        }

        public class UTM
        {
            public int Zone { get; private set; }
            public string Band { get; private set; }
            public double East { get; private set; }
            public double North { get; private set; }

            public UTM(int zone, string band, double east, double north)
            {
                Zone = zone;
                Band = band;
                East = east;
                North = north;
            }
        }

        
    }
}
