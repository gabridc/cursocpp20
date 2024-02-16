#include <set>
#include <iostream>
#include <compare>
struct Entity
{
    int id;

    friend bool operator<(const Entity& l, const Entity& r)
    {
        return l.id < r.id;
    }

};

class ValueObject
{
    public:
    auto operator<=>(const ValueObject&) const = default;  

};

class Phone
{
    private:
    std::string phone = "15";
};

 
class Address : public ValueObject
{
    public:
    Address(int s, int c) : street(s), city(c) {};

    private:
    int street;
    int city;

};

struct Info
{
    std::string name;
    std::string phone;

    auto operator<=>(const Info& r) const = default;
};


int main()
{
    std::set<Entity> entities = {Entity{3}, Entity{5}};
    std::set<Address> valueObjects{{1, 1}, {1, 1}};
    std::set<Info> valueObjects2{{"1", "1"}, {"1", "1"}};
    std::set<Info> valueObjects3{{"1", "2"}, {"2", "1"}};

    std::cout << entities.size() << std::endl;
    std::cout << valueObjects.size() << std::endl;
    std::cout << valueObjects2.size() << std::endl;
    std::cout << valueObjects3.size() << std::endl;

    std::cout << (Info{"1", "1"} == Info{"1", "1"}) << std::endl;
    std::cout << (Info{"2", "1"} == Info{"1", "1"}) << std::endl;

    std::cout << std::is_eq(std::string("hola") <=> std::string("hola")) << std::endl;
}