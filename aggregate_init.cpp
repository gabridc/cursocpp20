#include <string>


struct Info
{
    std::string fullname = name + surname1 + surname2;
    std::string name;
    std::string surname1;
    std::string surname2;


};

int main()
{
    Info{.name = "pepe", .phone ="555"};
}