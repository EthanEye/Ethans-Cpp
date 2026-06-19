#include <iostream>
#include <string>
#include "utility.h"
#include "block.h"
#include <vector>

using std::cout;
using std::endl;
using std::string;

const char* INVALID_USAGE = "Invalid arguments";
const char* CIPHER_TYPE_ERROR = "Invalid Function Type";
const char* CIPHER_MODE_ERROR = "Invalid Mode Type";

char checkArguments(int argc, char* argv[]);
std::string checkOperationMode(const string& mode);
std::vector<std::string> startCipher(char type, const string& mode);

// COMMANDS
// ./cipher B input.txt output.txt key.txt E
// ./cipher B output.txt input.txt key.txt D


int main(int argc, char* argv[])
{
    if (argc != 6) {
        cout << INVALID_USAGE << endl;
        return 1;
    }

    char type = checkArguments(argc, argv);
    std::string mode = checkOperationMode(argv[5]);

    FileUtils::setPaths(argv[2], argv[3], argv[4]);

    //cout << "Mode of operation: " << mode << endl;

    std::vector<std::string> result = startCipher(type, mode);

    std::string fullResult;
    for (const auto& block : result) {
        fullResult += block;
    }

    //cout << "Result: " << fullResult << endl;
    //cout << "Press Enter to exit...";
    return 0;
}


char checkArguments(int argc, char* argv[])
{
    if (argv[1][0] != 'B' && argv[1][0] != 'S') {
        cout << CIPHER_TYPE_ERROR << endl;
        exit(1);
    }
    return argv[1][0];
}


std::string checkOperationMode(const string& mode)
{
    if (mode != "E" && mode != "D") {
        cout << CIPHER_MODE_ERROR << endl;
        exit(1);
    }
    return mode;
}


std::vector<std::string> startCipher(char type, const string& mode)
{
    std::vector<std::string> result;

    if (type == 'B') {
        BlockCipher cipher;

        if (mode == "E") {
            result = cipher.encrypt();
        }
        else { 
            result = cipher.decrypt();
        }

    }
    else if (type == 'S') {
        cout << "Stream cipher not implemented" << endl;
    }

    return result;
}
