#include <iostream>
#include <concepts>

class Foo
{
    public:
    Foo operator+(const Foo& rhs)
    {
        return Foo{};
    }
};

class Foo2
{
    public:
    Foo2 operator-(const Foo2& rhs)
    {
        return Foo2{};
    }
};

template<typename T>
concept CanSum = std::integral<T> || std::floating_point<T>;

concept isFoo = Foo;


template<typename T>
requires CanSum<T>
T sum(T a, T b)
{
    return a + b;
}


int main()
{
    std::cout << sum(5, 3) << std::endl;
    sum(Foo{}, Foo{});
    // sum(Foo2{}, Foo2{}); does not work because Foo2 type is not valid in templated function sum

}