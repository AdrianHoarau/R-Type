/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** main.cpp
*/

#include "IMonster.hpp"
#include "Error.hpp"
#include <iostream>
#include "pathHandler.hpp"
#include "DLLoader.hpp"
#include "dirReader.hpp"
#include "udpServer.hpp"

int main(int ac, char **av)
{
    try {
        pathHandler hdl(pathType::DIR);
        if (ac > 2)
            throw ErrorNbArgs();
        else if (ac == 2)
            hdl.setPath(av[1]);
        if (hdl.isDirValid() == false)
            throw ErrorDirPath();
        dirReader dir(hdl.getPath());
        dir.findLibraries();
        boost::asio::io_context ioContext;
        std::unique_ptr<INetwork> server = std::make_unique<udpServer>(ioContext, hdl.getPath());
        server->start();
    } catch (Error const &err) {
        std::cerr << err.what() << std::endl;
        return (84);
    }
    return (0);
}