#include <vector>
#include <iostream>
#include <algorithm>
#include <ranges>
// [1,2,3,4,5].slice(0,3).reverse()
using namespace std;

vector<int> slicing(vector<int>& arr,
                    int X, int Y)
{
    // Starting and Ending iterators
    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;
    // To store the sliced vector
    vector<int> result(Y - X + 1);
    // Copy vector using copy function()
    copy(start, end, result.begin());
    // Return the final sliced vector
    return result;
}

void withoutRanges()
{
    std::vector<int> num{1,2,3,4,5};
    std::vector<int> num2;

    num2 = slicing(num, 0, 2);
    std::reverse(num2.begin(), num2.end());

    for(auto n : num2)
        std::cout << n << std::endl;
}

// [1,2,3,4,5].slice(0,3).reverse()
void withRanges()
{
    std::vector<int> v{1,2,3,4,5};
    auto even_numbers = v | std::views::take(3) | std::views::reverse;

    for(auto n : even_numbers)
        std::cout << n << std::endl;
}

int main()
{

withRanges();

}

