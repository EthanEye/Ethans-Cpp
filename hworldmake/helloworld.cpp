#include <print>
#include <vector>
#include <string>
#include <iostream> 
#include "printhelloworld.h"

//using namespace std;

int main()
{
    printRams * pRams = new printRams();
    pRams->printVector();
    pRams->printcout();
    pRams->print();
    delete pRams; 
  

    printRams pCSU(std::string("Go CSU")); 
    pCSU.print();
    pCSU.printcout(); 
    pCSU.printVector();


    return 0;
}
