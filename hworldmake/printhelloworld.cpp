#include "printhelloworld.h"

    printRams::printRams(): printRams("Hello Rams")
    {
        
    }

    printRams::printRams(std::string msg): message(msg)
    {

    }

    void printRams::printVector()
    {
        std::vector<std::string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
        
        std::print("**** BEFORE VECTOR **** ");
        for (const std::string& word : msg)
        {
            std::print("{0} ",word);
        }
        std::println(" **** AFTER VECTOR ****");

    }
    void printRams::printcout()
    {
        std::cout << "Goodbye!" << std::endl; 
    }

    void printRams::print()
    {
        std::cout << "@@@ " << message << " @@@" << std::endl;
    }