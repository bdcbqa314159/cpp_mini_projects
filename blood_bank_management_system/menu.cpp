#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

const char nl = '\n';

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << *ii << nl;
    }

    return os;
}
// cin.ignore(numeric_limits<streamsize>::max(), '\n');

int main()
{
    std::vector<int> u = {1, 2, 3, 4, 5, 6, 7};

    while (true)
    {
        size_t max = u.size();
        size_t input{};
        std::string blank{};
        std::cout << "vector" << nl;
        std::cout << u << nl;

        std::cout << "choose a number: 0 to quit, and max is " << max << " :" << nl;

        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), nl);

        if (input >= 1 && input <= max)
        {
            std::cout << "this is good, you chose: " << input << nl;
        }

        else if (input == 0)
        {
            std::cout << "ok now it is over..." << nl;
            break;
        }
        else
        {
            std::cout << "Bad input" << nl;
        }

        std::cout << "press a key to continue" << nl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), nl);
        std::system("clear");
    }

    return 0;
}