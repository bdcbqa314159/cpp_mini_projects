#pragma once

#include <map>
#include <string>
#include <vector>

struct DataMenu
{
    std::map<std::string, std::string> data{};
    std::map<std::string, std::string> operator()(const std::vector<std::string> &);
};
