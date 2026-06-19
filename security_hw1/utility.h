#ifndef UTILITY_H
#define UTILITY_H
#include <vector>

#include <string>
class FileUtils {
public:
    static std::string inputPath;
    static std::string outputPath;
    static std::string keyPath;

    static void setPaths(const std::string& input, const std::string& output, const std::string& key);
    static std::string checkPath(const std::string& path);
    static std::string readFile(const std::string& path);
    static void writeFile(int path, const std::string& data);
	static std::vector<std::string> xorVector(const std::vector<std::string>& block1, const std::vector<std::string>& block2);  
    static std::string xorString(const std::string& data, const std::string& key);
    static std::vector<std::string> swapVector(const std::vector<std::string>& keyVector, const std::vector<std::string>& xorVector);
    static std::vector<std::string> unswapVector(const std::vector<std::string>& keyVector, const std::vector<std::string>& xorVector);
};

#endif
