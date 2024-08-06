#include "head/get_code.h"
#include <iostream>

std::string str;

int main(void) {
    std::getline(std::cin,str);
    std::cout << getcode(str) << std::endl;
    return 0;
}