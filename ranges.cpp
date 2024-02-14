#include <iostream>
#include <vector>
#include <ranges>

struct Point
{

    int x;
    int y;
};


int main()
{

    std::vector<Point> points{{-1,8}, {0,1}, {548, 2365}};

    auto result = points | std::views::filter([](const Point& p){ return p.x > 0;});

    for(auto [x,y] : result)
        std::cout << x << " " << y << std::endl;


}