#include <iostream>
#include "header_v2.h"

extern void print_version();         // from static lib_v2
extern void call_print_from_v1();    // from dynamic libdyn
int call_multiply_from_v1(int,int);  // from dynamic libdyn

int main() {
    std::cout << "Static lib_v2 prints: ";
    print_version();

    std::cout << "Dynamic libdyn->lib_v1 prints: ";
    call_print_from_v1();

#ifndef COMMENT_TEMPLATE_STATIC_CALL // un/comment to magic
    std::cout << "multiply<int>() direct from v2: " << multiply<int>(3,4) << std::endl;
#endif
    std::cout << "call_multiply_from_v1: " << call_multiply_from_v1(3,4) << std::endl;

    return 0;
}