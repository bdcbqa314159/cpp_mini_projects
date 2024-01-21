#include <iostream>
#include <fstream>
#include <set>

const char nl = '\n';
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
        else
            return *this;
    }

    friend std::ostream &operator<<(std::ostream &, const ABO &);

private:
    std::string abo_group{};
};

bool check_group(const std::string &input)
{
    const std::set<std::string> groups = {"AB+", "AB-", "O+", "O-", "A+", "A-", "B+", "B-"};
    return groups.find(input) != groups.end();
}

class Menu
{

public:
    void display()
    {
        std::cout << nl << "Menu:" << nl;
        std::cout << "1. Add donor" << nl;
        std::cout << "2. Update donor" << nl;
        std::cout << "3. Add hospital" << nl;
        std::cout << "4. Donate" << nl;
        std::cout << "5. Request blood" << nl;
        std::cout << "6. Display available blood packets" << nl;
        std::cout << "7. Exit" << nl;
    }
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
    Menu myMenu{};

    myMenu.display();

    return 0;
}

std::ostream &operator<<(std::ostream &os, const ABO &group)
{
    os << group.abo_group;
    return os;
}