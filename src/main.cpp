#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Usage: " << av[0] << " <argument>" << std::endl;
        return 1;
    }
    std::cout << "Argument provided: " << av[1] << std::endl;
    return 0;
}

// proteçãodedados@wizink.pt