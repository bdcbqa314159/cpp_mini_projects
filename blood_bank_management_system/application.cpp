#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>

const char nl = '\n';

std::ostream &operator<<(std::ostream &, const std::map<size_t, std::string> &);

struct Person
{
    std::string name{};
    double height{};
};

std::ostream &operator<<(std::ostream &os, const Person &person)
{
    os << person.name << " " << person.height;
    return os;
}

void example_for_data_bin()
{

    Person me = {"Bernardo", 1.62};
    std::cout << me << nl;

    std::string filename = "test_person";
    std::ofstream output_file{};

    output_file.open(filename, std::ios::binary);

    if (output_file.is_open())
    {
        output_file.write(reinterpret_cast<char *>(&me), sizeof(Person));
        output_file.close();
    }

    else
    {
        std::cout << "could not open the file" << nl;
        std::abort();
    }

    Person other{};

    std::ifstream input_file{};

    input_file.open(filename, std::ios::binary);

    if (input_file.is_open())
    {
        input_file.read(reinterpret_cast<char *>(&other), sizeof(Person));
        input_file.close();
    }

    else
    {
        std::cout << "could not read the file" << nl;
        std::abort();
    }

    std::cout << "success?" << nl << other << nl;
}

class ABO
{
public:
    ABO() = default;
    ABO(const std::string &group) : abo_group(group) {}

    ABO(const ABO &other) : abo_group(other.abo_group) {}

    ABO &operator=(const ABO &other)
    {
        if (this != &other)
            abo_group = other.abo_group;

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &, const ABO &);

private:
    std::string abo_group{};
};

class Checker
{
private:
    std::set<std::string> data{};

public:
    Checker() = default;
    Checker(const std::set<std::string> &other_data) : data(other_data) {}
    // Checker(const std::set<std::string> &&other_data) : data(other_data) {}

    bool operator()(const std::string &input)
    {
        return data.find(input) != data.end();
    }
};

bool check_group(const std::string &input)
{
    const std::set<std::string> groups = {"AB+", "AB-", "O+", "O-", "A+", "A-", "B+", "B-"};
    return groups.find(input) != groups.end();
}

bool check_menu_choice(const std::string &input)
{
    const std::set<std::string> choice = {"1", "2", "3", "4", "5", "6", "7"};
    return choice.find(input) != choice.end();
}

struct DataMenu
{
    std::map<size_t, std::string> data{};

    std::map<size_t, std::string> operator()()
    {
        std::vector<std::string> choices = {
            "Add donor",
            "Update donor",
            "Add hospital",
            "Donate",
            "Request blood",
            "Display available blood packets",
            "Exit",
        };
        std::map<size_t, std::string> map{};
        for (size_t i = 0; i < choices.size(); i++)
            map.insert(std::make_pair(i + 1, choices.at(i)));

        return map;
    }
};

class Menu
{
private:
    std::map<size_t, std::string> data{};

public:
    Menu() : data(DataMenu()()) {}
    friend std::ostream &operator<<(std::ostream &, const Menu &);
};

void test_blood_group()
{
    std::string name{};

    int i = 0;
    while (i < 10)
    {

        std::cout << "type>>> ";
        std::getline(std::cin, name);

        if (check_group(name))
            std::cout << "you entered a valid type" << nl;
        else
            std::cout << "invalid type" << nl;
        name = "";
        i++;
    }
}

int main()
{
    Menu menu{};
    Checker check_menu({"1", "2", "3", "4", "5", "6", "7"});
    Checker check_blood({"AB+", "AB-", "O+", "O-", "A+", "A-", "B+", "B-"});
    std::string choice{};

    while (true)
    {
        std::cout << menu << nl;
        std::cout << "Please enter a valid choice  >> ";
        std::getline(std::cin, choice);

        if (check_menu(choice))
        {
            if (choice == "7")
            {
                std::cout << "Many thanks and bye" << nl;
                std::cout << "press a key to quit" << nl;
                break;
            }

            else
            {
                std::cout << "you choose " << choice << nl;
            }
        }
        else
        {
            std::cout << "Sorry the input is invalid" << nl;
        }
        std::cout << "press a key to continue" << nl;
        std::getc(stdin);
        std::system("clear");
    }

    return 0;
}

std::ostream &operator<<(std::ostream &os, const ABO &group)
{
    os << group.abo_group;
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::map<size_t, std::string> &map)
{
    for (auto it = map.begin(); it != map.end(); it++)
        os << it->first << " " << it->second << nl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Menu &menu)
{
    os << menu.data;
    return os;
}