#include <iostream>

#include "say-hello.hpp"

int main(int argc, char* argv[]) {
    if(argc < 2){
        return 0;
    }
    SayHello(argv[1]);
    return 0;
};