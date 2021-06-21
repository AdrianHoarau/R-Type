/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** main.cpp
*/

#include "pathHandler.hpp"
#include "Client.hpp"

int main(int ac, char **av)
{
    if (ac < 3) {
        std::cout << "./client <host> <port> <config_file>" << std::endl;
        return (1);
    }
    try {
        std::unique_ptr<INetwork> cli;
        if (av[3] != NULL)
            cli = std::make_unique<Client>(av[1], std::atoi(av[2]), av[3]);
        else
            cli = std::make_unique<Client>(av[1], std::atoi(av[2]));
        cli->start();
        cli->stop();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}