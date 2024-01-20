#include <iostream>
#include <fstream>

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

int main()
{

    return 0;
}