//
//  main.cpp
//  DEMO_DAY_01_TIME
//
//  Created by Jingtao Fan on 2021/7/26.
//

#include <iostream>
#include <iomanip>
#include "Time.hpp"

//new an object
//void function(Time t) {
//
//}

int main(int argc, const char * argv[]) {
    if (Time::Is24Format) {
        std::cout << 24 << std::endl;
    }
    else {
        std::cout << 12 << std::endl;
    }
    return 0;
}
