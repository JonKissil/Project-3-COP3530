#include "readresults.h"

std::vector<std::string> readResults() {
    std::ifstream f("results.txt");
    std::string line;
    std::vector<std::string> outputVector;

    while(std::getline(f, line)) {
        outputVector.push_back(line);
    }

    f.close();

    return outputVector;
}


void runscript(std::string artist, std::string song) {
    artist = '"'+artist+'"';
    song = '"'+song+'"';
    std::string command = "launchscript.sh " + artist + ' ' + song;
    std::system(command.c_str());
}