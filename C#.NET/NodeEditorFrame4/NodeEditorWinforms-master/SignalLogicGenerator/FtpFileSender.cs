using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace SignalLogicGenerator
{
    public class FtpFileSender
    {
        public static void SendFiles(List<String> filesPaths, string Uri, string ftpUsername, string ftpPassword)
        {
            string fileName;

            using (WebClient client = new WebClient())
            {
                client.Credentials = new NetworkCredential(ftpUsername, ftpPassword);
                foreach (String path in filesPaths)
                {
                    fileName = path.Substring(path.LastIndexOf("//"));
                    client.UploadFile(Uri + "/" + fileName, WebRequestMethods.Ftp.UploadFile, path);
                }
            }
        }
    }
}
