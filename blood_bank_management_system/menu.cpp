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

#include "Menu.hpp"

std::ostream &operator<<(std::ostream &os, const Menu &menu)
{
    os << menu.data;
    return os;
}

