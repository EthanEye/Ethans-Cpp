#include "utility.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::string FileUtils::inputPath = "";
std::string FileUtils::outputPath = "";
std::string FileUtils::keyPath = "";


void FileUtils::setPaths(const std::string& input, const std::string& output, const std::string& key) {
    
	inputPath = checkPath(input);
    outputPath = checkPath(output);
    keyPath = checkPath(key);
}


std::string FileUtils::checkPath(const std::string& path) {
    
    std::ifstream file(path);  

    if (!file) {
        std::cerr << "Error: cannot open file: " << path << std::endl;
        exit(1);
    }

    //std::cout << "File exists: " << path << std::endl;

    return path; 
}

std::string FileUtils::readFile(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);  

    if (!file) {
        std::cerr << "Error opening file: " << path << std::endl;
        exit(1);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

void FileUtils::writeFile(int pathIdent, const std::string& data)
{
    std::string selectedPath = "";

    if (pathIdent == 1) {
        selectedPath = FileUtils::inputPath;
    }
    else if (pathIdent == 2) {
        selectedPath = FileUtils::outputPath;
    }
    else if (pathIdent == 3) {
        selectedPath = FileUtils::keyPath;
    }
    else {
        std::cerr << "Invalid path: " << pathIdent << std::endl;
        exit(1);
    }

    std::ofstream file(selectedPath, std::ios::binary | std::ios::app);
    if (!file) {
        std::cerr << "Error opening file: " << selectedPath << std::endl;
        exit(1);
    }

    file.write(data.c_str(), data.size());
    file.close();  
}

std::string FileUtils::xorString(const std::string& data, const std::string& key) {
    std::string result = data;
    size_t keyLen = key.size();
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i % keyLen];
    }
    return result;
}

std::vector<std::string> FileUtils::xorVector(
    const std::vector<std::string>& block1,
    const std::vector<std::string>& block2
) {
    std::vector<std::string> result;
    size_t len = block1.size();
    for (size_t i = 0; i < len; ++i) {
        result.push_back(xorString(block1[i], block2[i % block2.size()]));
    }
    return result;
}
std::vector<std::string> FileUtils::swapVector(
    const std::vector<std::string>& keyVector,
    const std::vector<std::string>& xorVector
) {
    std::vector<std::string> result;

   
    for (size_t b = 0; b < xorVector.size(); ++b) {
        std::string block = xorVector[b];      
        const std::string& key = keyVector[b]; 

        size_t start = 0;
        size_t end = block.size() - 1;

        while (start < end) {
            unsigned char keyByte = static_cast<unsigned char>(key[start]);

            
            if (keyByte % 2 != 0) {
                std::swap(block[start], block[end]);
                --end; 
            }
            ++start; 
        }

        result.push_back(block);
    }

    return result;
}

std::vector<std::string> FileUtils::unswapVector(
    const std::vector<std::string>& keyVector,
    const std::vector<std::string>& swappedVector
) {
    std::vector<std::string> result;

    for (size_t b = 0; b < swappedVector.size(); ++b) {
        std::string block = swappedVector[b];
        const std::string& key = keyVector[b];

        // Record indices of swaps in original swapVector
        size_t start = 0;
        size_t end = block.size() - 1;
        std::vector<std::pair<size_t, size_t>> swaps;

        // Build swap pairs
        while (start < end) {
            unsigned char keyByte = static_cast<unsigned char>(key[start]);
            if (keyByte % 2 != 0) {
                swaps.push_back({ start, end });
                --end;
            }
            ++start;
        }

        // Reverse the swaps in reverse order
        for (auto it = swaps.rbegin(); it != swaps.rend(); ++it) {
            std::swap(block[it->first], block[it->second]);
        }

        result.push_back(block);
    }

    return result;
}




