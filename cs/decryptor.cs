using System;
using System.IO;
using System.Collections.Generic;

class Program
{
    static List FindAllPngData(string filePath)
    {
        List pngDataList = new List();

        using (FileStream file = new FileStream(filePath, FileMode.Open, FileAccess.Read))
        {
            byte[] data = new byte[file.Length];
            file.Read(data, 0, data.Length);

            int startIdx = 0;
            while (true)
            {
                startIdx = Array.IndexOf(data, (byte)0x89, startIdx);
                if (startIdx == -1)
                {
                    break;
                }

                int endIdx = Array.IndexOf(data, (byte)0x82, startIdx + 8); // Finding the end of PNG data marker
                if (endIdx == -1)
                {
                    Console.WriteLine($"End of PNG data not found in the file: {filePath}");
                    return null;
                }

                byte[] pngData = new byte[endIdx - startIdx + 8];
                Array.Copy(data, startIdx, pngData, 0, pngData.Length);
                pngDataList.Add(pngData);

                startIdx = endIdx + 8;
            }
        }

        return pngDataList;
    }

    static void BuildPngFiles(List pngDataList, string outputDir)
    {
        if (!Directory.Exists(outputDir))
        {
            Directory.CreateDirectory(outputDir);
        }

        for (int i = 0; i < pngDataList.Count; i++)
        {
            string outputFilePath = Path.Combine(outputDir, $"output_file_{i + 1}.png");
            using (FileStream outputFile = new FileStream(outputFilePath, FileMode.Create, FileAccess.Write))
            {
                outputFile.Write(pngDataList[i], 0, pngDataList[i].Length);
            }

            Console.WriteLine($"PNG data extracted and saved to: {outputFilePath}");
        }
    }

    static void Main(string[] args)
    {
        string[] filePaths = { "c1", "c2", "c7", "c8", "c9", "mi", "nm1", "nm3", "nm4", "oi" };

        foreach (string inputFilePath in filePaths)
        {
            string outputDir = $"{Path.GetFileNameWithoutExtension(inputFilePath)}_output";
            List pngDataList = FindAllPngData(inputFilePath);
            if (pngDataList != null)
            {
                BuildPngFiles(pngDataList, outputDir);
            }
            else
            {
                Console.WriteLine($"No PNG data found in the file: {inputFilePath}");
            }
        }
    }
}
