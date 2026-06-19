#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <iostream>
#include <vector>

class BlockCipher {
private:
    std::string key;           
    size_t blockSize = 16;     

    
    std::string pad(const std::string& input);

public:
	BlockCipher() = default;
 
    void setKey(const std::string& keyValue);

    std::vector<std::string> encryptBlock(const std::string& plaintextBlock);
    std::vector<std::string> decryptBlock(const std::string& cipherBlock);
    std::vector<std::string> encrypt();
    std::vector<std::string> decrypt();
	std::vector<std::string> convertToBlocks(const std::string& text);
};

#endif
