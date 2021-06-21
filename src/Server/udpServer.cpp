/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** udpServer.cpp
*/

#include "udpServer.hpp"
#include "Zipper.hpp"
#include <iostream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <sstream>

udpServer::udpServer(boost::asio::io_context& ioContext, const std::string& libPath) : _socket(std::make_shared<boost::asio::ip::udp::socket>(ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), PORT))),
_buffer(std::make_shared<Buffer>()), _libPath(libPath), _sigHandler(), _t(ioContext, boost::asio::chrono::seconds(1))
{
    _parser.insert(std::make_pair(Client::NONE, &udpServer::parserNoneState));
    _parser.insert(std::make_pair(Client::INLOBBY, &udpServer::parserInLobbyState));
    _parser.insert(std::make_pair(Client::READY, &udpServer::parserReadyState));
    _parser.insert(std::make_pair(Client::INGAME, &udpServer::parserInGameState));
    startReceive();
    _t.async_wait(boost::bind(&udpServer::serverEndHandler, this, boost::asio::placeholders::error));
}

void udpServer::startReceive()
{
    _data.fill(0);
    _socket->async_receive_from(boost::asio::buffer(_data), _remoteEndpoint,
    boost::bind(&udpServer::handleReceive, this, boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred));
}

void udpServer::handleReceive(const boost::system::error_code& error, std::size_t bytesTransferred)
{
    (void)bytesTransferred;
    if (doesClientExist() == false) {
        _clients.push_back(std::make_shared<Client>(Client(_remoteEndpoint.address(), _remoteEndpoint.port())));
    }
    if (!error || error == boost::asio::error::message_size) {
        parseData();
        startReceive();
    }
}

void udpServer::parseData()
{
    auto& clt = findClient(_remoteEndpoint.port());
    bool alreadyDone = false;
    BinaryProtocol::Packet p;

    p = _binCodec.unserialize(_data);
    if (_binCodec.check_packet(p) != true) {
        std::cerr << "ERROR: packet not valid" << std::endl;
        return;
    }
    for (auto it = _parser.begin(); it != _parser.end(); ++it)
        if (it->first == clt->getState() && alreadyDone == false) {
            (this->*(it->second))(clt, p._message);
            alreadyDone = true;
        }
    startReceive();
}

void udpServer::handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred)
{
    (void)message;
    (void)error;
    (void)bytesTransferred;
}

void udpServer::start()
{
    _socket->get_io_service().run();
}

bool udpServer::doesClientExist()
{
    for (auto& client: _clients) {
        if (client->getEndpoint().port() == _remoteEndpoint.port())
            return (true);
    }
    return (false);
}

clientPtr& udpServer::findClient(const unsigned short port)
{
    for (auto& client : _clients) {
        if (client->getEndpoint().port() == port)
            return (client);
    }
    return (_clients.front());
}

bool udpServer::doesLobbyExist(const std::string& name)
{
    for (auto& lobby : _lobbies) {
        if (lobby.getName() == name)
            return (true);
    }
    return (false);
}

Lobby& udpServer::findLobby(const std::string& name)
{
    for (auto& lobby : _lobbies) {
        if (lobby.getName() == name)
            return (lobby);
    }
    return (_lobbies.front());
}

void udpServer::parserNoneState(clientPtr& clt, std::string& buffer)
{
    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
    std::size_t start = buffer.find(" ");
    std::size_t second_space = buffer.substr(start + 1, buffer.length()).find(" ");

    std::string command = buffer.substr(0, start);
    std::string firstArg = buffer.substr(start + 1, second_space);

    if (std::strcmp(command.c_str(), "201") == 0) {
        if (isLobbyNameAvailable(firstArg) == true) {
            _lobbies.push_back(Lobby(firstArg));
            _lobbies.back().addClient(clt);
            clt->setState(Client::INLOBBY);
            std::string uuid = "121";
            send(uuid);
        } else {
            send("333");
        }
    } else if (std::strcmp(command.c_str(), "202") == 0) {
        if (doesLobbyExist(firstArg) == true) {
            auto& lobby = findLobby(firstArg);
            if (lobby.isRoomFull() == true || lobby.getState() != Lobby::FREE) {
                send("444");
            } else {
                lobby.addClient(clt);
                clt->setState(Client::INLOBBY);
                send("121");
            }
        } else
            send("777");
    } else if (std::strcmp(command.c_str(), "200") != 0) {
        send("222");
    }
}

void udpServer::parserInLobbyState(clientPtr& clt, std::string& buffer)
{
    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
    std::size_t start = buffer.find(" ");
    std::size_t second_space = buffer.substr(start + 1, buffer.length()).find(" ");

    std::string command = buffer.substr(0, start);
    std::string firstArg = buffer.substr(start + 1, second_space);

    if (std::strcmp(command.c_str(), "203") == 0) {
        send("111");
        clt->setState(Client::READY);
    } else if (std::strcmp(command.c_str(), "204") == 0) {
        send("111");
        findLobby(clt).removeClient(clt);
        clt->setState(Client::NONE);
    } else if (std::strcmp(command.c_str(), "210") == 0) {
        auto& lobby = findLobby(clt);
        routineMenu(lobby.getClients(), lobby.getPlayers(), lobby.getQueuePlayers());
    } else if (std::strcmp(command.c_str(), "200") == 0) {
        findLobby(clt).removeClient(clt);
        clt->setState(Client::NONE);
    } else
        send("222");
}

void udpServer::routineMenu(std::vector<clientPtr>& clients, std::vector<std::shared_ptr<ECS::playerNumber>>& players, std::queue<ECS::playerNumber>& available)
{
    std::string toSend("110 ");
    ECS::playerNumber sample = ECS::SPEC;

    for (auto it : Zipper::zip(clients, players)) {
        toSend += std::to_string(*it.get<1>());
        toSend += ":";
        if (it.get<0>()->getState() == Client::INLOBBY)
            toSend += "0";
        else
            toSend += "2";
        toSend += " ";
    }
    for (unsigned int queueindex = 0; queueindex != available.size(); queueindex++) {
        sample = available.front();
        toSend += std::to_string(sample);
        toSend += ":1";
        available.pop();
        available.push(sample);
        toSend += " ";
    }
    send(toSend);
}

void udpServer::parserReadyState(clientPtr& clt, std::string& buffer)
{
    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
    std::size_t start = buffer.find(" ");
    std::string command = buffer.substr(0, start);

    if (std::strcmp(command.c_str(), "205") == 0) {
        send("111");
        clt->setState(Client::INLOBBY);
    } else if (std::strcmp(command.c_str(), "204") == 0) {
        send("111");
        findLobby(clt).removeClient(clt);
        clt->setState(Client::NONE);
    } else if (std::strcmp(command.c_str(), "206") == 0) {
        auto& lobby = findLobby(clt);
        if (lobby.isReadyToGo() == true) {
            lobby.startGame(_socket, _buffer, _libPath);
        } else
            send("555");
    } else if (std::strcmp(command.c_str(), "210") == 0) {
        auto& lobby = findLobby(clt);
        routineMenu(lobby.getClients(), lobby.getPlayers(), lobby.getQueuePlayers());
    } else if (std::strcmp(command.c_str(), "200") == 0) {
        findLobby(clt).removeClient(clt);
        clt->setState(Client::NONE);
    } else
        send("222");
}

void udpServer::parserInGameState(clientPtr& clt, std::string& buffer)
{
    if (findLobby(clt).getPlayerNumber(clt) == ECS::SPEC) {
        send("666");
        return;
    }
    buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
    std::size_t start = buffer.find(" ");


    std::string command = buffer.substr(0, start);
    if (std::strcmp(command.c_str(), "200") == 0) {
        findLobby(clt).removeClient(clt);
        _buffer->addData(clt->getUuid(), "Off");
    }
    else if (std::strcmp(command.c_str(), "104") == 0) {
        _buffer->addData(clt->getUuid(), "Up");
    }
    else if (std::strcmp(command.c_str(), "103") == 0) {
        _buffer->addData(clt->getUuid(), "Down");
    }
    else if (std::strcmp(command.c_str(), "101") == 0) {
        _buffer->addData(clt->getUuid(), "Right");
    }
    else if (std::strcmp(command.c_str(), "102") == 0) {
        _buffer->addData(clt->getUuid(), "Left");
    }
    else if (std::strcmp(command.c_str(), "105") == 0) {
        _buffer->addData(clt->getUuid(), "Shoot");
    } else
        send("222");
}

void udpServer::removeClient(const boost::uuids::uuid& uuid)
{
    for (auto clt = _clients.begin(); clt != _clients.end(); clt++) {
        if ((*clt)->getUuid() == uuid)
            _clients.erase(clt);
    }
}

void udpServer::send(const std::string& toSend)
{
    _socket->async_send_to(boost::asio::buffer(_binCodec.serialize(_binCodec.createPacket(toSend))), _remoteEndpoint,
    boost::bind(&udpServer::handleSend, this, toSend,
    boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred));
}

Lobby& udpServer::findLobby(const clientPtr& client)
{
    for (auto& lobby : _lobbies) {
        if (lobby.hasClient(client) == true)
            return (lobby);
    }
    return (_lobbies.front());
}

bool udpServer::isLobbyNameAvailable(const std::string& name)
{
    if (name == "")
        return (false);
    for (auto& lobby : _lobbies)
        if (lobby.getName() == name)
            return (false);
    return (true);
}

void udpServer::serverEndHandler(const boost::system::error_code&)
{
    bool canLeave = true;

    if (_sigHandler.isInterrupted() == true) {
        for (auto& lobby : _lobbies) {
            if (lobby.getState() == Lobby::INGAME) {
                std::cerr << "You must wait the end of all games before closing the server." << std::endl;
                canLeave = false;
            }
        }
        if (canLeave == true) {
            std::cerr << "Server's leaving." << std::endl;
            stop();
        }
    }
    _t.expires_at(_t.expires_at() + boost::asio::chrono::seconds(1));
    _t.async_wait(boost::bind(&udpServer::serverEndHandler, this, boost::asio::placeholders::error));
}

void udpServer::stop()
{
    if (_socket->is_open() == true)
        _socket->get_io_service().stop();
}