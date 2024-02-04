#include "DataMenu.hpp"

std::map<std::string, std::string> DataMenu::operator()(const std::vector<std::string> &choices)
{

    std::map<std::string, std::string> map{};
    for (size_t i = 0; i < choices.size(); i++)
        map.insert(std::make_pair(std::to_string(i + 1), choices.at(i)));

    return map;
}
