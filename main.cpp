//
// Created by Maddie on 12/3/2024.
//

#include "readresults.h"
#include "./gui/gui.h"

// struct for handling basic structure of algorithm parts
struct Algo{
    std::string *artistPtr;
    std::string *songPtr;
    std::vector<std::string> *outputPtr;

    void algoFunction(){
        std::cout << "Running Analysis\n";
        std::cout << "Inputted String: \"" << *(artistPtr) << " : " << (*songPtr) << "\"\n";

        runscript((*artistPtr), (*songPtr));
        (*outputPtr) = readResults();
    }

    Algo(){
        artistPtr = new std::string("");
        songPtr = new std::string("");
        outputPtr = new std::vector<std::string>;
    }
};



int main() {

    GUI &gui = GUI::getInstance();
    Algo *algo = new Algo();

    // where the gui should write the user inputs
    gui.setInputPtrs(algo->artistPtr, algo->songPtr);

    // what the search button does
    gui.setSearchButtonFunction([&]() {
        algo->algoFunction();
    });

    // where the gui should get its output contents from
    gui.setOutputListPtr(algo->outputPtr);

    // gui will return exit codes
    int status = gui.run();
    return status;
}