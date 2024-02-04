#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <utility>

#include "Checker.hpp"
#include "DataMenu.hpp"
#include "io_utility.hpp"
#include "data.hpp"

class Menu
{
private:
    std::map<std::string, std::string> data{};
    Checker myChecker{};

public:
    Menu() = default;
    Menu(const std::vector<std::string> &choice_data) : data(DataMenu()(choice_data))
    {
        std::set<std::string> myset{};
        for (size_t i = 1; i <= choice_data.size(); ++i)
            myset.insert(std::to_string(i));
        myChecker.set_data(myset);
    }

    bool check(const std::string &input)
    {
        return myChecker(input);
    }

    std::string operator()(const std::string &input)
    {
        return data[input];
    }

    friend std::ostream &operator<<(std::ostream &, const Menu &);
};

int main()
{
    Menu menu(choices);

    std::cout << menu << nl;

    return 0;
}

std::ostream &operator<<(std::ostream &os, const Menu &menu)
{
    os << menu.data;
    return os;
}