#include "io_utility.hpp"
#include "data.hpp"

std::ostream &operator<<(std::ostream &os, const std::map<std::string, std::string> &map)
{
    for (typename std::map<std::string, std::string>::const_iterator ii = map.begin(); ii != map.end(); ++ii)
    {
        os << ii->first << " " << ii->second << nl;
    }

    return os;
}