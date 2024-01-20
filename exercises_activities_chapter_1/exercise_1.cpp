#include <iostream>

constexpr int test(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    std::cout << "Hello Universe" << std::endl;
    int x = 1, y = 2;

    constexpr int a = 1, b = 4;

    constexpr int u = test(x, y);
    constexpr int v = test(a, b);
    return 0;
}