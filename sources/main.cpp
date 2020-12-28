//
// Created by lizer on 27.12.2020.
//
#include "Analysis.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    std::string path;
    if (argc == 0)
    {
        path = ".";
        Analysis exp(path);
        exp.Analyze();
        std::cout << exp;
    }

    else if (argc == 2)
    {
        path = argv[1];
        Analysis exp(path);
        exp.Analyze();
        std::cout << exp;
    }
    return 0;
}
