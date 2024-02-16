#include <string>


struct Info
{
    std::string name;
    std::string phone;

};

int main()
{
    Info{.name = "pepe", .phone ="555"};
}