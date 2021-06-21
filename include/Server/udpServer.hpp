/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** udpServer.hpp
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include "INetwork.hpp"
#include "Buffer.hpp"
#include "Lobby.hpp"
#include "BinaryProtocol.hpp"
#include "SignalHandler.hpp"
#include <map>
#include <boost/array.hpp>

constexpr unsigned int BUFFSIZE = 1024;
constexpr unsigned int PORT = 1666;

class udpServer : public INetwork {
public:
    udpServer(boost::asio::io_context&, const std::string& libPath);
    void start();
    void stop();
    udpServer(const udpServer& other) = default;
    udpServer& operator=(const udpServer& other) = default;
    ~udpServer() = default;
    typedef void(udpServer::*parsingFunction)(clientPtr&, std::string&);
private:
    clientPtr& findClient(const unsigned short);
    bool doesClientExist();
    void send(const std::string& toSend);
    void startReceive();
    void parseData();
    void acceptConnection();
    Lobby& findLobby(const std::string& name);
    Lobby& findLobby(const clientPtr& client);
    bool doesLobbyExist(const std::string& name);
    void parserNoneState(clientPtr&, std::string&);
    void parserInLobbyState(clientPtr& clt, std::string&);
    void parserReadyState(clientPtr& clt, std::string&);
    void parserInGameState(clientPtr& clt, std::string&);
    void removeClient(const boost::uuids::uuid& uuid);
    void handleReceive(const boost::system::error_code& error, std::size_t);
    void handleSend(const std::string&, const boost::system::error_code&, std::size_t);
    bool isLobbyNameAvailable(const std::string& name);
    void routineMenu(std::vector<clientPtr>& clients, std::vector<std::shared_ptr<ECS::playerNumber>>& players, std::queue<ECS::playerNumber>& available);
    void serverEndHandler(const boost::system::error_code& /*e*/);
    std::shared_ptr<boost::asio::ip::udp::socket> _socket;
    boost::asio::ip::udp::endpoint _remoteEndpoint;
    BinaryProtocol::Codec _binCodec;
    boost::array<uint8_t, BUFFSIZE> _data;
    std::vector<clientPtr> _clients;
    std::vector<Lobby> _lobbies;
    std::shared_ptr<Buffer> _buffer;
    std::map<Client::clientState, parsingFunction> _parser;
    std::string _libPath;
    SignalHandler _sigHandler;
    boost::asio::steady_timer _t;
};

#endif /* !UDPSERVER_HPP_ */
