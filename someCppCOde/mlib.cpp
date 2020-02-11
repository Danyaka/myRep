#include <ostream>
#include "mlib.h"

int square(int val){
    return val * val;
}

float max(float **arr){
    float max_count = arr[0][0];
    for (int i = 0; i < sizeof(arr); i++)
        for (int j = 0; j < sizeof(arr); j++)
        {
            max_count = max_count < arr[i][j] ? arr[i][j] : max_count;
        }
    
}

float min(float **arr){
    float max_count = arr[0][1];
    for (int i = 0; i < sizeof(arr); i++)
        for (int j = 0; j < sizeof(arr); j++)
        {
            max_count = max_count > arr[i][j] ? arr[i][j] : max_count;
        }
    
}

Timer::~Timer(){
    const auto finish = clock_t::now();
    const auto us = std::chrono::duration_cast<microseconds>
    (finish - start_).count();
    std::cout << us << " us" << std::endl << std::endl;

};

void _type_mem_ref(){
     void* ptr = nullptr;
    __SIZE_TYPE__ SZptr = sizeof(ptr);
    std::cout << " ______________________________"    << std::endl;
    std::cout << "|     Memory of type count     |"   << std::endl;
    std::cout << " ------------------------------"    << std::endl;
    std::cout << "|     int: " << sizeof(int)    << " |     wchar_t: "<< sizeof(wchar_t)       << "  |" << std::endl;
    std::cout << "|   short: " << sizeof(short)  << " |   long long: "<< sizeof(long long)     << "  |" << std::endl;
    std::cout << "|   float: " << sizeof(float)  << " | long double: "<< sizeof(long double)   << " | "  << std::endl;
    std::cout << "|  double: " << sizeof(double) << " |   unsg char: "<< sizeof(unsigned char) << "  |" << std::endl;
    std::cout << "|    char: " << sizeof(char)   << " |        bool: "<< sizeof(bool)          << "  |" << std::endl;
    std::cout << "| pointer: " << sizeof(SZptr)  << " |    long int: "<< sizeof(long int)      << "  |" << std::endl;
    std::cout << " ------------------------------"    << std::endl << std::endl;
}