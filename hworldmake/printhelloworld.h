#ifndef _PRINTHELLOWORLD_H
#define _PRINTHELLOWORLD_H

#include <print>
#include <vector>
#include <string>
#include <iostream> 

class printRams
{
public:
    printRams();
    printRams(std::string msg);
    void printVector();
    void printcout();
    void print();
private: 
    std::string message; 
};
#endif 