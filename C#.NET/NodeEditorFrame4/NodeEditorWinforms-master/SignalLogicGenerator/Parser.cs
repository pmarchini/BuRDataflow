using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SampleCommon;


namespace SignalLogicGenerator
{
    public class Parser
    {

        public static int _MAX_NR_ELEMENTS = 25;
        public static int _MAX_NR_DEPTH = 5;

        protected int[,] ParserMatrix;


        /// <summary>
        /// Get type of the value ref
        /// 0  = Node 
        /// 1  = Var
        /// 2  = Const val
        /// 3  = Const bool
        /// -1 = default
        /// </summary>
        public static int GetPointerType(int type)
        {
            //TODO -> Controllare
            switch (type)
            {
                case 1:
                    return 0;
                case 2:
                    return 0;
                case 3:
                    return 0;
                case 4:
                    return 0;
                case 5:
                    return 0;
                case 6:
                    return 0;
                case 7:
                    return 1;
                case 8:
                    return 1;
                case 9:
                    return 2;
                case 10:
                    return 3;
                default:
                    return -1;

            }
        }

        /// <summary>
        /// Parse dictionaryExport into array struct
        /// </summary>
        public static int[,] Parse(Dictionary<string,List<String>> dictionaryRappresentation)
        {
            Dictionary<string, int> matchNodes = new Dictionary<string, int>();
            int i = 0;
            int j = 0;

            if (dictionaryRappresentation.Count > _MAX_NR_ELEMENTS)
                return null;

            int[,] ParserMatrix = new int[_MAX_NR_ELEMENTS, _MAX_NR_DEPTH];

            //creo dizionario GUID - numero nodo
            foreach( KeyValuePair<string, List<String>> pair in dictionaryRappresentation)
            {
                matchNodes.Add(pair.Key, i);
                i++;
            }

            i = 0;
            //a dizionario creato genero la logica
            foreach(KeyValuePair<string, List<String>> pair in dictionaryRappresentation)
            {
                j = 0;
                foreach (string s in pair.Value)
                {
                    if(j == 0)
                    {
                        ParserMatrix[i, j] = int.Parse(s);
                    }
                    else
                    {
                        if (j % 2 != 0)
                            ParserMatrix[i, j] = GetPointerType(ParserMatrix[i, 0]);
                        else
                        {
                            switch(ParserMatrix[i, j - 1])
                            {
                                case 0://Nodo
                                    matchNodes.TryGetValue(s, out ParserMatrix[i, j]);
                                    break;
                                case 1://Variabile
                                    ParserMatrix[i, j] = int.Parse(s) - 1;
                                    break;
                                case 3:
                                    ParserMatrix[i, j] = int.Parse(s);
                                    break;
                                default:
                                    break;
                            }
                        }
                            
                    }
                    j++;
                }
                i++;
            }
            return ParserMatrix;
        }

        public static void PrintMatrixFile(int[ , ] Matrix)
        {
            if (File.Exists("MatrixFile.mx"))
                File.Delete("MatrixFile.mx");

            FileStream fs = File.OpenWrite("MatrixFile.mx");

            using (StreamWriter bw = new StreamWriter(fs))
            {
                for (int i = 0; i < _MAX_NR_ELEMENTS; i++)
                {
                    for (int j = 0; j < _MAX_NR_DEPTH; j++)
                    {
                        bw.Write(Matrix[i, j]);
                        bw.Write(" ");
                    }
                    bw.Write("\n");
                }
            }
            fs.Close();
        }
    }
}
