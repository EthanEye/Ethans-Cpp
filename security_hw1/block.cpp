#include "block.h"
#include "utility.h"
#include <iostream>
#include <vector>


void BlockCipher::setKey(const std::string& keyValue) {

}


std::string BlockCipher::pad(const std::string& input) {
	const int BLOCK_SIZE = 16;
    std::string padded = input;
	int size = input.size();
	int paddingNeeded = BLOCK_SIZE - (size % BLOCK_SIZE);
    for (int i = 0; i < paddingNeeded; i++) {
        padded += static_cast<char>(0x81); 
    }
    return padded; 
}


std::vector<std::string> BlockCipher::encryptBlock(const std::string& plaintextBlock) {
    std::vector<std::string> blocks;
    
    return blocks;
}


std::vector<std::string> BlockCipher::decryptBlock(const std::string& cipherBlock) {
    std::vector<std::string> blocks;
    
    return blocks;
}


std::vector<std::string> BlockCipher::encrypt() {
    //std::cout << "Cipher: Block" << std::endl;
    std::vector<std::string> result;
    std::string text = FileUtils::readFile(FileUtils::inputPath);
    std::vector<std::string> blockVector = convertToBlocks(text);
	std::vector<std::string> keyVector = convertToBlocks(FileUtils::readFile(FileUtils::keyPath));
	if (keyVector.size() < blockVector.size()){
        std::cerr << "Error: Key is too short for the plaintext." << std::endl;
        exit(1);
    }
	std::vector<std::string> xorVector = FileUtils::xorVector(blockVector, keyVector);
    std::vector<std::string> swapVector = FileUtils::swapVector(keyVector,xorVector);
    for (size_t i = 0; i < swapVector.size(); ++i) {
        const std::string& block = swapVector[i];
        FileUtils::writeFile(2, block);
        result.push_back(block);
    }
    return result;
}


std::vector<std::string> BlockCipher::decrypt() {
    //std::cout << "Cipher: Block" << std::endl;

    
    std::string cipherText = FileUtils::readFile(FileUtils::inputPath);
    std::vector<std::string> cipherBlocks = convertToBlocks(cipherText);
    std::string keyText = FileUtils::readFile(FileUtils::keyPath);
    std::vector<std::string> keyBlocks;
    for (size_t i = 0; i < keyText.size(); i += 16) {
        keyBlocks.push_back(keyText.substr(i, 16));
    }

    
    if (keyBlocks.size() < cipherBlocks.size()) {
        //std::cerr << "Error: Key is too short for the ciphertext." << std::endl;
        exit(1);
    }

 
    std::vector<std::string> unswappedBlocks = FileUtils::unswapVector(keyBlocks, cipherBlocks);

 
    std::vector<std::string> paddedPlainBlocks = FileUtils::xorVector(unswappedBlocks, keyBlocks);

  
    std::vector<std::string> plainBlocks;
    for (auto& block : paddedPlainBlocks) {
        std::string cleanBlock = block;
       
        while (!cleanBlock.empty() && static_cast<unsigned char>(cleanBlock.back()) == 0x81) {
            cleanBlock.pop_back();
        }
        plainBlocks.push_back(cleanBlock);

       
        FileUtils::writeFile(2, cleanBlock);
    }

    return plainBlocks;
}




std::vector<std::string> BlockCipher::convertToBlocks(const std::string& text) {
    std::vector<std::string> result;
    const size_t BLOCK_SIZE = 16;

    for (size_t i = 0; i < text.size(); i += BLOCK_SIZE) {
        size_t remaining = text.size() - i;
        size_t chunkSize = (remaining >= BLOCK_SIZE) ? BLOCK_SIZE : remaining;
        std::string block = text.substr(i, chunkSize);


        if (block.size() < 16) {
            block = pad(block);
        }
        result.push_back(block);
        
    }
    
	return result;
}