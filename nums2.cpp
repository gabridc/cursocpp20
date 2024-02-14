#include <vector>
#include <iostream>
#include <ranges>
// [1,2,3,4,5].filter(v%2===0).map(v=>v*v)

void withoutRanges()
{
    std::vector<int> num{1,2,3,4,5};
    std::vector<int> num2;

    for(auto n : num)
    {
        if(n % 2 == 0)
            num2.emplace_back(n*n);
    }

    for(auto n : num2)
        std::cout << n << std::endl;
}

// [1,2,3,4,5].filter(v%2===0).map(v=>v*v)
void withRanges()
{

    auto even = [](const int n) {return n % 3 == 0; };
    auto square = [](const int n) {return n * n; };

    std::vector<int> input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    auto output = input
        | std::views::filter(even)
        | std::views::transform(square);

    for(auto n : output)
        std::cout << n << std::endl;
}




int main()
{

    withRanges();
}