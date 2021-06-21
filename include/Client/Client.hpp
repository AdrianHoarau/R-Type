/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <map>
#include "Player.hpp"
#include "SFMLModule.hpp"
#include "SignalHandler.hpp"
#include "BinaryProtocol.hpp"
#include "INetwork.hpp"

#include <chrono>

using timeType = std::chrono::time_point<std::chrono::system_clock>;
class Client : public INetwork
{
    public:
        Client(const std::string& ip, unsigned short port, const std::string& configFile = "../../ressources/config_file.txt");
        Client(const Client& other) = default;
        Client& operator=(const Client& other) = default;
        ~Client() = default;
        void start();
        void stop();
        typedef void(Client::*hsmFunction)(const std::string&);
    private:
        void send(const std::string& str);
        void startReceive();
        void loop();
        int checkMenuState(const MenuDrawer::State& state);
        int checkGameState(const Graphic::Command& com);
        void handleReceive(const boost::system::error_code&, std::size_t);
        void handleServerMessage(const std::string&);
        void handleUpdateMenu(const std::string&);
        void handleUpdateGame(const std::string&);
        void handleFine(const std::string&);
        void handleInvalidCommand(const std::string&);
        void handleGhostRoom(const std::string&);
        void handleFullRoom(const std::string&);
        void handleTooFast(const std::string&);
        void handleJoinLobby(const std::string&);
        void handleStartGame(const std::string&);
        void handleBusy(const std::string&);
        void handleEnd(const std::string&);
        void setState(const ClientState&);
        void createEntity(int entityId, const entityType& entityType, bool bonus, const sf::Vector2f& entityPos, const animationState& animation);
        void updateEntity(int entityId, const sf::Vector2f& entityPos, const animationState &) const;
        void destroyEntity(int entityId);
        void changeState();
    private:
        SignalHandler _sigHandler;
        BinaryProtocol::Codec _binCodec;
        boost::asio::io_service _ioService;
        boost::asio::ip::udp::socket _clientSocket;
        SFMLModule _sfmlModule;
        ClientState _state;
        sf::Clock _connexion;
        sf::Time _currentTime;
        boost::thread _thread;
        boost::array<uint8_t, 1024> _recvBuff;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        std::string _clientName;
        std::vector<std::shared_ptr<Graphic::Entity>> _entities;
        std::vector<std::shared_ptr<Players>> _players;
        std::map<int, hsmFunction> _serverResponse;
};

#endif /* !CLIENT_HPP_ */
