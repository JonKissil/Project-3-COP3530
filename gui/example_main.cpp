#include "gui.h"
#include <string>
#include <vector>
#include <iostream>



struct Algo{
    std::string *inputPtr;
    std::vector<std::string> *outputPtr;

    void algoFunction(){
        std::cout << "Running Data Funciton\n";
        std::cout << "Inputted String: \"" << *(inputPtr) << "\"\n";
        generate_random_strings(1000, 10);

    }

    Algo(){
        inputPtr = new std::string("");
        outputPtr = new std::vector<std::string>;

    }

    std::string generate_random_string(size_t length) {
        const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::string result;
        for (size_t i = 0; i < length; ++i) {
            result += charset[rand() % charset.size()];
        }
        return result;
    }

// Function to generate a vector of random strings
    void generate_random_strings(size_t num_strings, size_t string_length) {
        (*outputPtr).clear();
        for (size_t i = 0; i < num_strings; ++i) {
            (outputPtr)->push_back(generate_random_string(string_length));
        }
    }
};




int main(){
    GUI& gui = GUI::getInstance();
    Algo *test_algo = new Algo();


    // this is where the gui will write what the user has inputted
    // this can then be used for what ever algo is needed
    gui.setInputPtr(test_algo->inputPtr);

    // this is what the gui will run when the user hits "search"
    // basically what algo needs to be ran
    gui.setSearchButtonFunction([&]() {
        test_algo->algoFunction();
    });

    //REMEBER!!!
    // the output ptr must always be set even when data changes
    // make sure to update this so that the gui knows where the new data is.
    // errors due to memory accessing are usually because the pointer has changed
    // so long as this points to something other than nullptr itll work
    // must point to a std::vector<std::string>
    gui.setOutputListPtr(test_algo->outputPtr);


    return gui.run();
}