#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>

const char nl = '\n';

std::ostream &operator<<(std::ostream &, const std::map<size_t, std::string> &);

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v)
{
    for (auto &element : v)
        is >> element;

    return is;
}

class Person
{
protected:
    std::string name{};
    double height{};

public:
    Person() = default;
    Person(const std::string &other_name, double other_height) : name(other_name), height(other_height) {}

    friend std::ostream &operator<<(std::ostream &, const Person &);
    friend std::istream &operator>>(std::istream &is, Person &);
};

class ABO
{
public:
    ABO() = default;
    ABO(const std::string &group) : abo_group(group) {}
    ABO(const std::string &&group) : abo_group(group) {}
    // ABO(const ABO &other) : abo_group(other.abo_group) {}

    ABO &operator=(const ABO &other)
    {
        if (this != &other)
            abo_group = other.abo_group;

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &, const ABO &);
    friend std::istream &operator>>(std::istream &, ABO &);

private:
    std::string abo_group{};
};

class Donor : public Person
{
private:
    std::string contact{};
    bool fit{};
    ABO abo{};

public:
    Donor() = default;
    Donor(const Person &other) : Person(other), contact{}, fit{}, abo{} {}
    void set_contact(const std::string &other_contact)
    {
        contact = other_contact;
        return;
    }

    void set_fit(const bool &other_fit)
    {
        fit = other_fit;
        return;
    }

    void set_abo(const ABO &other_abo)
    {
        abo = other_abo;
        return;
    }

    friend std::ostream &operator<<(std::ostream &, const Donor &);
    friend std::istream &operator>>(std::istream &is, Donor &);
};

class Donors
{
private:
    std::vector<Donor> data{std::vector<Donor>(10)};

public:
    void add(const Donor &donor)
    {
        data.push_back(donor);
        return;
    }

    friend std::ostream &operator<<(std::ostream &, const Donors &);
    friend std::istream &operator>>(std::istream &is, Donors &);
};

void example_for_data_bin()
{

    Person me = {"Bernardo", 1.62};
    Person you = {"Alexia", 1.65};
    Person her = {"Delphine", 1.8};
    std::cout << me << nl;

    std::vector<Person> all = {me, you, her};

    std::vector<Donor> all_1 = {me, you, her};

    for (auto &person : all_1)
    {
        person.set_contact("someone");
        person.set_fit(true);
        person.set_abo({"O+"});
    }

    // for (auto person : all_1)
    //     std::cout << person << nl;

    std::string filename = "test_person";
    std::ofstream output_file{};

    output_file.open(filename);

    if (output_file.is_open())
    {
        for (auto person : all_1)
            output_file << person << nl;
        output_file.close();
    }

    else
    {
        std::cout << "could not open the file" << nl;
        std::abort();
    }

    Donor other{};

    std::ifstream input_file{};

    std::vector<Donor> test{};

    input_file.open(filename);

    if (input_file.is_open())
    {
        while (input_file >> other)
        {
            test.push_back(other);
        }
        input_file.close();
        std::cout << "end of file: " << nl;
        for (auto person : test)
            std::cout << person << nl;
    }

    else
    {
        std::cout << "could not read the file" << nl;
        std::abort();
    }
}

class Checker
{
private:
    std::set<std::string> data{};

public:
    Checker() = default;
    Checker(const std::set<std::string> &other_data) : data(other_data) {}

    bool operator()(const std::string &input)
    {
        return data.find(input) != data.end();
    }
};

struct DataMenu
{
    std::map<size_t, std::string> data{};
    std::map<size_t, std::string> operator()();
};

class Menu
{
private:
    std::map<size_t, std::string> data{};

public:
    Menu() : data(DataMenu()()) {}
    friend std::ostream &operator<<(std::ostream &, const Menu &);
};

// void test_blood_group()
// {
//     std::string name{};

//     int i = 0;
//     while (i < 10)
//     {

//         std::cout << "type>>> ";
//         std::getline(std::cin, name);

//         if (check_group(name))
//             std::cout << "you entered a valid type" << nl;
//         else
//             std::cout << "invalid type" << nl;
//         name = "";
//         i++;
//     }
// }

int main()
{
    Menu menu{};
    Checker check_menu({"1", "2", "3", "4", "5", "6", "7"});
    Checker check_blood({"AB+", "AB-", "O+", "O-", "A+", "A-", "B+", "B-"});
    std::string choice{}, blank{};

    // while (true)
    // {
    //     std::cout << menu << nl;
    //     std::cout << "Please enter a valid choice  >> ";
    //     std::getline(std::cin, choice);

    //     if (check_menu(choice))
    //     {
    //         if (choice == "7")
    //         {
    //             std::cout << "Many thanks and bye" << nl;
    //             std::cout << "press a key to quit" << nl;
    //             break;
    //         }

    //         else
    //         {
    //             std::cout << "you choose " << choice << nl;
    //         }
    //     }
    //     else
    //     {
    //         std::cout << "Sorry the input is invalid" << nl;
    //     }
    //     std::cout << "press a key to continue" << nl;
    //     std::getline(std::cin, blank);
    //     std::system("clear");
    // }

    example_for_data_bin();

    return 0;
}

std::ostream &operator<<(std::ostream &os, const Person &person)
{
    os << person.name << " " << person.height;
    return os;
}

std::istream &operator>>(std::istream &is, Person &person)
{
    is >> person.name >> person.height;
    return is;
}

std::ostream &operator<<(std::ostream &os, const Donor &donor)
{
    os << donor.name << " " << donor.height << " " << donor.contact << " " << donor.fit << " " << donor.abo;
    return os;
}

std::istream &operator>>(std::istream &is, Donor &donor)
{
    is >> donor.name >> donor.height >> donor.contact >> donor.fit >> donor.abo;
    return is;
}

std::ostream &operator<<(std::ostream &os, const ABO &group)
{
    os << group.abo_group;
    return os;
}

std::istream &operator>>(std::istream &is, ABO &group)
{
    is >> group.abo_group;
    return is;
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

std::ostream &operator<<(std::ostream &os, const Donors &donors)
{
    os << donors.data;
    return os;
}

std::istream &operator>>(std::istream &is, Donors &donors)
{
    is >> donors.data;
    return is;
}

std::map<size_t, std::string> DataMenu::operator()()
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