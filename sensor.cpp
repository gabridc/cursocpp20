#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <generator>
#include <ranges>
#include <cmath>
#include <limits>
#include <algorithm>
#include <numeric>

template <typename T>
std::generator<T> gMax(const T& value)
{
    T max = std::numeric_limits<int>::min();
    while(true)
    {
        max = std::max(value, max);
        co_yield max;
    }
}

template <typename T>
std::generator<T> gMin(const T& value)
{
    T min = std::numeric_limits<int>::max();
    while(true)
    {
        min = std::min(value, min);
        co_yield min;
    }
}

template <size_t S=10, typename R = double, typename T>
std::generator<R> gMean(const T& value)
{
    std::array<T,S> mean{};

    for(size_t i = 0; i < S; ++i)
    {
        mean[i] = value;
        co_yield std::accumulate(std::begin(mean), std::begin(mean)+i+1, 0) / (i+1);
    }

    int idx = 0;
    while(true)
    {
        mean[idx] = value;
        idx = idx % S;
        co_yield std::accumulate(std::begin(mean), std::end(mean), 0)/S;
    }
}

std::generator<int> sensor() {
    int range = 10;
    int mean = 50;
    while(true) {
        co_yield mean + rand()%range - range/2;
    }
}

struct SensorData {
    int min;
    int max;
    double avg;
};

std::ostream& operator<<(std::ostream& os, const SensorData& data) {
    return os
        << " min: " << data.min
        << " max: " << data.max
        << " avg: " << data.avg
    ;
}

std::generator<SensorData> filteredSensor() {
    int shared_value{};
    auto genMax  = gMax(shared_value);
    auto genMin  = gMin(shared_value);
    auto genMean = gMean(shared_value);
    for(int value : sensor()) {
        shared_value = value;
        co_yield SensorData{
            .min = *genMin.cbegin(),
            .max = *genMax.cbegin(),
            .avg = *genMean.cbegin()
        };
    }
}



int main() {
    for(auto value : filteredSensor() | std::views::take(10)) {
        std::cout << "nice_value: " << value << std::endl;
    }
}


