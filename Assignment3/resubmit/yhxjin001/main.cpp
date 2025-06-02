#include <string>
#include <iostream>
#include "PGMimageProcessor.h"
using namespace std;
int main(int argc, char* argv[])
{
    // check command line args: note a basic check - should be more robust, assumes all args are correct
    int minValidSize=2; unsigned char threashold = 35;
    int minFilterSize=2; int maxFilterSize=8000; bool printData=false; bool writeOut = false ;std::string output;

    for (int i = 1; i < argc - 1 ; i++){
        std::string arg = argv[i];
        if (arg == "-m" && i + 1 < argc){
            minValidSize = atoi(argv[i + 1]);
        }
        else if (arg == "-f" && i + 2 < argc){
            minFilterSize = atoi(argv[i + 1]);
            maxFilterSize = atoi(argv[i + 2]);
        }

        else if (arg == "-t" && i + 1 < argc){
            threashold = atoi(argv[i+1]);
        }
        else if (arg == "-p"){
            printData = true;
        }
        else if (arg == "-w"){
            writeOut = true;
            output = argv[i+1];
        }
    }
    std::string input = argv[argc - 1];
    yhxjin001::PGMimageProcessor processor;

    // Reading input image
    processor.read(input);
    // Processing pgm image
    std::cout << "Extracting components..." << std::endl ;
    processor.extractComponents(threashold, minValidSize);
    std::cout << "Filtering components..." << std::endl;
    processor.filterComponentsBySize(minFilterSize, maxFilterSize);

    if (printData){
        std::cout<<"Printing data" << std::endl;
        for (const yhxjin001::ConnectedComponentPtr & componentPtr : processor.getComponentPtrs()){
            processor.printComponentData(*componentPtr);
        }
    }

    if (writeOut){
        processor.writeComponents(output);
    }


}