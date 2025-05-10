#include "header_v1.h"
#include <iostream>

extern void print_version();

void call_print_from_v1() { 
    std::cout << "Call to v1: ";
    print_version(); 
}

int call_multiply_from_v1(int a, int b) {
    std::cout << "Call to v1: ";
    return multiply<int>(a, b);
}