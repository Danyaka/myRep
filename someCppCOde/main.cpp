#include "mlib.h"
#include "numbers.dat"
#include <math.h>
#include <memory>
#include <cstddef>


using func = void(*)(int&, int&);

// 1) solve the problem at least somehow
// even a special case

// 2) better think of returning function types

// 3) think through exceptions

struct Range
{
    public:
    int x;
    int y;
    int sz; 
    Range(){};
    Range(const int& a,const int& b){
        x = a;
        y = b;
        sz = abs(x - y) + 1;
    };
    void setVAL(const int& a,const int& b){
        x = a;
        y = b;
        sz = abs(x - y) + 1;
    };   
};

std::ostream& operator<< (std::ostream& out, const Range& r){
    out << "(" << r.x << " - " << r.y << " " << r.sz << ")" << std::endl;
}

// simplicity check
bool isSimpl_prm(const int& x){
    auto lambda = [=](int k){ return x % k; };
    for (int i = 2; i < int(sqrt(x)); i++)
    {
        if (lambda(i) == 0) return false;     
    }
    return true;
}

// load from numbers.data to the buffer to work with it
std::unique_ptr<int[]> BUFF_LOAD(const Range& rng){
    auto buff_data = std::make_unique<int[]>(rng.sz);
    auto lambda = [rng](){if (rng.x < rng.y) return rng.x; else return rng.y; };
    std::cout << rng.sz << std::endl;
    for (size_t i = 0; i < rng.sz; i++)
    {
        buff_data[i] = Data[lambda() + i];
        // std::cout << buff_data[i] << std::endl;
    }
    return buff_data;
}

// parsing the input array received
std::unique_ptr<Range[]> parsARR(int sz, char const* arr[]){
    size_t n_sz = int((sz - 1) / 2);
    auto r_arr = std::make_unique<Range[]>(n_sz);
    for (size_t i = 1; i < sz; i += 2)
    {
        r_arr[i].setVAL(std::atoi(arr[i]), std::atoi(arr[i+1]));
        // std::cout << r_arr[i] << std::endl;
    }
    return r_arr;
}

// searching for the number of primes in the buffer
std::unique_ptr<int[]> CountSimpl(int imSz, const std::unique_ptr<Range[]> arr){
    size_t sz = int((imSz - 1) / 2);
    auto resaltArr = std::make_unique<int[]>(sz);
    int k = 0;
    for (size_t i = 0; i < sz; i++)
    {
        auto buff_data = std::make_unique<int[]>(arr[i].sz);
        for (size_t j = 0; j < arr[i].sz; j++)
        {
            if (isSimpl_prm(buff_data[j])) k++;
        }
        resaltArr[i] = k;
        k = 0;
    }
    return resaltArr;
}

// float foo(float x){
//     return ((x-2)*(x-3)*(13*x-1) + x*(x-1)*(x-103)*(1/6));
// }

int main(int argc, char const *argv[])
{
    _type_mem_ref();
        
    for (int i = 1; i < argc; i++)
    {
        int v = std::atoi(argv[i]);
        std::cout << v << std::endl;
    }
    
    std::unique_ptr<Range[]> qwe = parsARR(argc, argv);
    // std::unique_ptr<int[]> res = CountSimpl(argc, qwe);

    int* k = (int*) malloc(1024);
    return 0;
}
