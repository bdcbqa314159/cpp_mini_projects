#include <iostream>
#include <fstream>
#include <map>
#include <utility>

const char nl = '\n';

class Menu
{

public:
    Menu() = default;
    Menu(const std::map<size_t, std::string> &other_data)
    {
        data = other_data;
    }

    std::map<size_t, std::string> data{};

    void add(const std::string &name)
    {
        data.insert(std::make_pair(data.size() + 1, name));
    }

    void save(const std::string &filename)
    {
        std::ofstream output_file{};

        output_file.open(filename, std::ios::binary);

        if (output_file.is_open())
        {
            output_file.write(reinterpret_cast<char *>(this), sizeof(Menu));
            output_file.close();
        }

        else
        {
            std::cout << "could not open the file" << nl;
            std::abort();
        }
        return;
    }
    friend std::ostream &operator<<(std::ostream &, const Menu &);
};

Menu menuLoader(const std::string &filename);

// int main()
// {

//     std::cout << "Hey" << nl;

//     Menu myMenu;

//     myMenu.add("Add option");
//     myMenu.add("Save status");
//     myMenu.add("Quit");
//     std::cout << myMenu << nl;

//     std::string filename = "my_menu_blood_bank";
//     myMenu.save(filename);

//     Menu output = menuLoader(filename);

//     std::cout << output.data.size() << nl;

//     return 0;
// }

std::ostream &operator<<(std::ostream &os, const Menu &menu)
{
    auto it = menu.data.begin();
    for (; it != menu.data.end(); ++it)
    {
        os << it->first << ". " << it->second << nl;
    }

    return os;
}

// void menuSaver(const std::string &filename, Menu &obj)
// {
//     std::ofstream output_file{};

//     output_file.open(filename, std::ios::binary);

//     if (output_file.is_open())
//     {
//         output_file.write(reinterpret_cast<char *>(&obj), sizeof(Menu));
//         output_file.close();
//     }

//     else
//     {
//         std::cout << "could not open the file" << nl;
//         std::abort();
//     }
//     return;
// }

Menu menuLoader(const std::string &filename)
{

    Menu output{};

    std::ifstream input_file{};

    input_file.open(filename, std::ios::binary);

    if (input_file.is_open())
    {
        input_file.read(reinterpret_cast<char *>(&output), sizeof(Menu));
        input_file.close();
    }

    else
    {
        std::cout << "could not read the file" << nl;
        std::abort();
    }

    return output;
}

int main()
{
    std::ofstream MyFile("filename");

    // Write to the file
    MyFile << "Files can be tricky, but it is fun enough!";

    // Close the file
    MyFile.close();

    return 0;
}