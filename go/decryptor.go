package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

func findStartIndex(data []byte, startIndex int) int {
	return strings.Index(data[startIndex:], "\x89PNG")
}

func findEndIndex(data []byte, startIndex int) int {
	return strings.Index(data[startIndex:], "\x49\x45\x4E\x44\xAE\x42\x60\x82") + startIndex + 8
}

func findAllPNGData(filePath string) [][]byte {
	data, err := ioutil.ReadFile(filePath)
	if err != nil {
		fmt.Printf("Error reading file: %v\n", err)
		return nil
	}

	startIndex := 0
	pngDataList := [][]byte{}

	for {
		startIndex = findStartIndex(data, startIndex)
		if startIndex == -1 {
			break
		}

		endIndex := findEndIndex(data, startIndex+1)
		if endIndex == -1 {
			fmt.Printf("End of PNG data not found in the file: %s\n", filePath)
			return nil
		}

		pngData := data[startIndex:endIndex]
		pngDataList = append(pngDataList, pngData)

		startIndex = endIndex + 1
	}

	return pngDataList
}

func buildPNGFiles(pngDataList [][]byte, outputDir string) {
	if _, err := os.Stat(outputDir); os.IsNotExist(err) {
		os.MkdirAll(outputDir, os.ModePerm)
	}

	for i, pngData := range pngDataList {
		outputPath := fmt.Sprintf("%s/output_file_%d.png", outputDir, i+1)
		err := ioutil.WriteFile(outputPath, pngData, os.ModePerm)
		if err != nil {
			fmt.Printf("Error writing PNG data to file: %v\n", err)
		} else {
			fmt.Printf("PNG data extracted and saved to: %s\n", outputPath)
		}
	}
}

func main() {
	filePaths := []string{"c1", "c2", "c7", "c8", "c9", "mi", "nm1", "nm3", "nm4", "oi"}

	for _, inputFile := range filePaths {
		outputDir := fmt.Sprintf("%s_output", strings.TrimSuffix(inputFile, ".txt"))
		pngDataList := findAllPNGData(inputFile)
		if pngDataList != nil {
			buildPNGFiles(pngDataList, outputDir)
		} else {
			fmt.Printf("No PNG data found in the file: %s\n", inputFile)
		}
	}
}
