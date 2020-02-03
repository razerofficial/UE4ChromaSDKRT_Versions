using System;
using System.IO;

namespace UnrealEngineVersionChanger
{
    class Program
    {
        public enum Versions
        {
            UNKNOWN = -1,
            UE4_5 = 5,
            UE4_6 = 6,
            UE4_7 = 7,
            UE4_8 = 8,
            UE4_9 = 9,
            UE4_10 = 10,
            UE4_11 = 11,
            UE4_12 = 12,
            UE4_13 = 13,
            UE4_14 = 14,
            UE4_15 = 15,
            UE4_16 = 16,
            UE4_17 = 17,
            UE4_18 = 18,
            UE4_19 = 19,
            UE4_20 = 20,
            UE4_21 = 21,
            UE4_22 = 22,
            UE4_23 = 23,
            UE4_24 = 24,
        };

        private static Versions _sVersion = Versions.UNKNOWN;

        const string TOKEN_VERSION_4_8_OR_LESS = "___HACK_UE4_VERSION_4_8_OR_LESS";
        const string TOKEN_VERSION_4_9_OR_GREATER = "___HACK_UE4_VERSION_4_9_OR_GREATER";
        const string TOKEN_VERSION_4_9_TO_4_15 = "___HACK_UE4_VERSION_4_9_TO_VERSION_4_15";
        const string TOKEN_VERSION_4_15_OR_LESS = "___HACK_UE4_VERSION_4_15_OR_LESS";
        const string TOKEN_VERSION_4_16_OR_GREATER = "___HACK_UE4_VERSION_4_16_OR_GREATER";
        const string TOKEN_VERSION_4_17_OR_LESS = "___HACK_UE4_VERSION_4_17_OR_LESS";
        const string TOKEN_VERSION_4_18_OR_GREATER = "___HACK_UE4_VERSION_4_18_OR_GREATER";
        const string TOKEN_COMMENTS = "//";

        static bool EditLine(ref string contents, ref int i, int lastNewline, string token, bool enable)
        {
            bool hasChange = false;
            if (contents.Substring(i).StartsWith(token))
            {
                string firstPart = contents.Substring(0, lastNewline + 1);
                string nextPart = contents.Substring(lastNewline + 1);
                if (enable)
                {
                    if (nextPart.StartsWith(TOKEN_COMMENTS))
                    {
                        //remove comments
                        contents = firstPart + nextPart.Substring(TOKEN_COMMENTS.Length);
                        hasChange = true;
                        i = i - TOKEN_COMMENTS.Length + token.Length;
                    }
                }
                else
                {
                    if (!nextPart.StartsWith(TOKEN_COMMENTS))
                    {
                        //add comments
                        contents = firstPart + TOKEN_COMMENTS + nextPart;
                        hasChange = true;
                        i = i + TOKEN_COMMENTS.Length + token.Length;
                    }
                }
            }
            return hasChange;
        }

        static void EditFile(FileInfo fi)
        {
            try
            {
                Console.WriteLine("Process: {0}", fi.Name);
                string contents = string.Empty;
                using (FileStream fs = File.Open(fi.FullName, FileMode.Open, FileAccess.Read, FileShare.ReadWrite))
                {
                    using (StreamReader sr = new StreamReader(fs))
                    {
                        contents = sr.ReadToEnd();
                    }
                }
                bool hasChange = false;

                // switch line endings
                contents = contents.Replace("\r\n", "\n").Replace("\n", "\r\n");

                int lastNewline = 0;
                for (int i = 0; i < contents.Length; ++i)
                {
                    switch (contents[i])
                    {
                        case '\n':
                        case '\r':
                            lastNewline = i;
                            break;
                    }
                    if (EditLine(ref contents, ref i, lastNewline, TOKEN_VERSION_4_8_OR_LESS, _sVersion <= Versions.UE4_8))
                    {
                        hasChange = true;
                        continue;
                    }
                    if (EditLine(ref contents, ref i, lastNewline, TOKEN_VERSION_4_9_OR_GREATER, _sVersion >= Versions.UE4_9))
                    {
                        hasChange = true;
                        continue;
                    }
                    if (EditLine(ref contents, ref i, lastNewline, TOKEN_VERSION_4_9_TO_4_15, _sVersion >= Versions.UE4_9 && _sVersion <= Versions.UE4_15))
                    {
                        hasChange = true;
                        continue;
                    }
                    if (EditLine(ref contents, ref i, lastNewline, TOKEN_VERSION_4_15_OR_LESS, _sVersion <= Versions.UE4_15))
                    {
                        hasChange = true;
                        continue;
                    }
                    if (EditLine(ref contents, ref i, lastNewline, TOKEN_VERSION_4_16_OR_GREATER, _sVersion >= Versions.UE4_16))
                    {
                        hasChange = true;
                        continue;
                    }
                    if (EditLine(ref contents, ref i, lastNewline, TOKEN_VERSION_4_17_OR_LESS, _sVersion <= Versions.UE4_17))
                    {
                        hasChange = true;
                        continue;
                    }
                    if (EditLine(ref contents, ref i, lastNewline, TOKEN_VERSION_4_18_OR_GREATER, _sVersion >= Versions.UE4_18))
                    {
                        hasChange = true;
                        continue;
                    }
                }

                if (!hasChange)
                {
                    return;
                }
                if (fi.Exists)
                {
                    fi.Delete();
                }
                using (FileStream fs = File.Open(fi.FullName, FileMode.CreateNew, FileAccess.Write, FileShare.ReadWrite))
                {
                    using (StreamWriter sw = new StreamWriter(fs))
                    {
                        sw.Write(contents);
                        sw.Flush();
                    }
                }
                if (true)
                {
                    //good place to stop
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Failed to process file: {0} exception={1}", fi.FullName, e);
            }
        }

        static void ProcessFiles(DirectoryInfo di)
        {
            foreach (FileInfo fi in di.GetFiles())
            {
                switch (fi.Extension)
                {
                    case ".h":
                    case ".cpp":
                    case ".cs":
                        EditFile(fi);
                        break;
                }
            }
        }

        static void ProcessFolder(DirectoryInfo di)
        {
            if (di.Name == "Intermediate")
            {
                return;
            }
            //Console.WriteLine("*Process: {0}", di.FullName);

            if (!di.Exists)
            {
                return;
            }

            ProcessFiles(di);

            foreach (DirectoryInfo child in di.GetDirectories())
            {
                if (child == di)
                {
                    continue;
                }
                ProcessFolder(child);
            }
        }
        static void UnitTest()
        {
            // unit test
            EditFile(new FileInfo(@"C:\Public\UE4ChromaSDK\Source\UE4ChromaSDK\UE4ChromaSDKGameModeBase.h"));
        }
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.Error.WriteLine("Missing argument!");
                return;
            }

            switch (args[0])
            {
                case "4.5":
                    _sVersion = Versions.UE4_5;
                    break;
                case "4.6":
                    _sVersion = Versions.UE4_6;
                    break;
                case "4.7":
                    _sVersion = Versions.UE4_7;
                    break;
                case "4.8":
                    _sVersion = Versions.UE4_8;
                    break;
                case "4.9":
                    _sVersion = Versions.UE4_9;
                    break;
                case "4.10":
                    _sVersion = Versions.UE4_10;
                    break;
                case "4.11":
                    _sVersion = Versions.UE4_11;
                    break;
                case "4.12":
                    _sVersion = Versions.UE4_12;
                    break;
                case "4.13":
                    _sVersion = Versions.UE4_13;
                    break;
                case "4.14":
                    _sVersion = Versions.UE4_14;
                    break;
                case "4.15":
                    _sVersion = Versions.UE4_15;
                    break;
                case "4.16":
                    _sVersion = Versions.UE4_16;
                    break;
                case "4.17":
                    _sVersion = Versions.UE4_17;
                    break;
                case "4.18":
                    _sVersion = Versions.UE4_18;
                    break;
                case "4.19":
                    _sVersion = Versions.UE4_19;
                    break;
                case "4.20":
                    _sVersion = Versions.UE4_20;
                    break;
                case "4.21":
                    _sVersion = Versions.UE4_21;
                    break;
                case "4.22":
                    _sVersion = Versions.UE4_22;
                    break;
                case "4.23":
                    _sVersion = Versions.UE4_23;
                    break;
                case "4.24":
                    _sVersion = Versions.UE4_24;
                    break;
                default:
                    Console.Error.WriteLine("Unsupported version!");
                    return;
            }

            //UnitTest();

            DirectoryInfo di = new DirectoryInfo(Directory.GetCurrentDirectory());
            string targetDir = string.Format("{0}\\Source", di.FullName);
            Console.WriteLine("Processing for {0}... {1}", _sVersion, targetDir);
            ProcessFolder(new DirectoryInfo(targetDir));
            targetDir = string.Format("{0}\\Plugins", di.FullName);
            ProcessFolder(new DirectoryInfo(targetDir));
        }
    }
}
