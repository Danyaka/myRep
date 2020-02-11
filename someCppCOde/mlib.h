#include <chrono>
#include <iostream>

int square(int val);
float max(float **arr);
float min(float **arr);
void _type_mem_ref();

class Timer
{
using clock_t = std::chrono::high_resolution_clock;
using microseconds = std::chrono::microseconds;

private:
    const clock_t::time_point start_;
public:
    Timer(): start_(clock_t::now()){};
    ~Timer();
};

