/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Client
*/

#include "Client.hpp"
#include <memory>
#include "Background.hpp"
#include "Wall.hpp"
#include "Obstacle.hpp"
#include "PlayerShoot.hpp"
#include "Alien.hpp"
#include "AlienShoot.hpp"
#include "Ufo.hpp"
#include "UfoShoot.hpp"
#include "Spaceship.hpp"
#include "SpaceshipShoot.hpp"
#include "Pirate.hpp"
#include "PirateShoot.hpp"
#include "Bomb.hpp"
#include "ItemSpeed.hpp"

Client::Client(const std::string& ip, unsigned short port, const std::string& configFile)
: _sigHandler(), _binCodec(), _ioService(), _clientSocket(_ioService), _sfmlModule(configFile), _state(NONE), _connexion(), _currentTime(sf::Time::Zero)
{
    boost::system::error_code err;

    _clientSocket.open(boost::asio::ip::udp::v4(), err);
    if (err)
        std::cerr << "Error while opening socket" << std::endl;
    _remoteEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);
    std::fill(_recvBuff.begin(), _recvBuff.end(), -1);
    _serverResponse.insert(std::make_pair(100, &Client::handleUpdateGame));
    _serverResponse.insert(std::make_pair(110, &Client::handleUpdateMenu));
    _serverResponse.insert(std::make_pair(111, &Client::handleFine));
    _serverResponse.insert(std::make_pair(135, &Client::handleEnd));
    _serverResponse.insert(std::make_pair(222, &Client::handleInvalidCommand));
    _serverResponse.insert(std::make_pair(333, &Client::handleGhostRoom));
    _serverResponse.insert(std::make_pair(444, &Client::handleFullRoom));
    _serverResponse.insert(std::make_pair(555, &Client::handleTooFast));
    _serverResponse.insert(std::make_pair(121, &Client::handleJoinLobby));
    _serverResponse.insert(std::make_pair(131, &Client::handleStartGame));
    _serverResponse.insert(std::make_pair(666, &Client::handleBusy));

    _players.push_back(std::shared_ptr<Players>(new Players(P1)));
    _players.push_back(std::shared_ptr<Players>(new Players(P2)));
    _players.push_back(std::shared_ptr<Players>(new Players(P3)));
    _players.push_back(std::shared_ptr<Players>(new Players(P4)));
}

void Client::start()
{
    std::cout << "Welcome to the client !" << std::endl;
    startReceive();
    _thread = boost::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
    _sfmlModule.init(sf::Vector2f(1, 1));
    #ifndef _WIN32 
        _sfmlModule.getMenuDrawer().getAudio().playSound(Audio::MENU);
    #endif
    _clientName = _sfmlModule.getPlayerName();
    if (_clientName.size() > 8) {
        _sfmlModule.stop();
        return;
    }
    #ifndef _WIN32 
        _sfmlModule.getAudio().playSound(Audio::PLAYERNAME);
    #endif
    loop();
}

void Client::stop()
{
    send("200");
    send("200");
    _sfmlModule.stop();
    _thread.detach();
    _ioService.stop();
    _clientSocket.close();
    std::cout << "Bye bye !" << std::endl;
}

void Client::setState(const ClientState& state)
{
    _state = state;
}

void Client::changeState()
{
    if (_state == INLOBBY || _state == NONE)
        _state = READY;
    else
        _state = INLOBBY;
}

int Client::checkGameState(const Graphic::Command& com)
{
    if (com == Graphic::EXIT)
        return -1;
    if (com == Graphic::RIGHT)
        send("101");
    if (com == Graphic::LEFT)
        send("102");
    if (com == Graphic::UP)
        send("103");
    if (com == Graphic::DOWN)
        send("104");
    if (com == Graphic::SHOOT)
        send("105");
    return 0;
}

void Client::loop()
{
    MenuDrawer::State stateMenu = MenuDrawer::State::UNREADY;
    static timeType start = std::chrono::system_clock::now();
    timeType end;
    std::chrono::seconds time;
    Graphic::Command check = Graphic::Command::NOTHING;
    sf::Clock frameClock;
    sf::Time checkTime(sf::seconds(1));

    _entities.push_back(std::shared_ptr<Graphic::Player>(new Graphic::Player(0, P1, false, {100,100}, animationState::ANIMATION_2)));
    while (_sigHandler.isInterrupted() != true) {
        end = std::chrono::system_clock::now();
        time = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        if (_state == INLOBBY || _state == READY || _state == NONE) {
            stateMenu = _sfmlModule.Menu(_clientName, _players, _state, frameClock);
            if (checkMenuState(stateMenu) == -1)
                break;
        } else if (_state == INGAME) {
            check = _sfmlModule.game(_entities);
            if (checkGameState(check) == -1)
                break;
        }
        if (_state == INLOBBY || _state == READY) {
            if (time >= std::chrono::seconds(1)) {
                send("210");
                start = std::chrono::system_clock::now();
            }
        }
        _currentTime += _connexion.restart();
        if (_currentTime >= checkTime && _state == INGAME) {
            _state = NONE;
            #ifndef _WIN32 
                _sfmlModule.getAudio().stopSound(Audio::GAME);
                _sfmlModule.getMenuDrawer().getAudio().playSound(Audio::MENU);
            #endif
            _sfmlModule.setState(MenuDrawer::State::HOME);

        }
    }
    if (_sigHandler.isInterrupted()) {
        send("200");
        send("200");
    }
}

int Client::checkMenuState(const MenuDrawer::State& stateMenu)
{
    if (stateMenu == MenuDrawer::State::QUIT)
        return (-1);
    if (stateMenu == MenuDrawer::State::BIG) {
        _sfmlModule.init(sf::Vector2f((static_cast<float>(1.3)), static_cast<float>(1.3)));
        _sfmlModule.setState(MenuDrawer::State::SETTINGS);
    }
    if (stateMenu == MenuDrawer::State::NORMAL) {
        _sfmlModule.init(sf::Vector2f((static_cast<float>(1)), static_cast<float>(1)));
        _sfmlModule.setState(MenuDrawer::State::SETTINGS);
    }
    if (stateMenu == MenuDrawer::State::GAME) {
        if (_state == READY)
            send("206");
        else
           _sfmlModule.setState(MenuDrawer::State::ROOM);
    }
    if (stateMenu == MenuDrawer::State::CREATE) {
        send("201 "+_sfmlModule.getRoomName());
        _sfmlModule.setState(MenuDrawer::State::WAITING);
    }
    if (stateMenu == MenuDrawer::State::ROOM_JOIN) {
        send("202 "+_sfmlModule.getRoomName());
        _sfmlModule.setState(MenuDrawer::State::WAITING);
    }
    if (stateMenu == MenuDrawer::State::HOME && (_state == READY || _state == INLOBBY)) {
        send("204");
        _state = NONE;
    }
    if (stateMenu == MenuDrawer::State::READY || stateMenu == MenuDrawer::State::UNREADY) {
        changeState();
        if (_state == READY)
            send("203");
        else
            send("205");
        _sfmlModule.setState(MenuDrawer::State::ROOM);
    }
    return (0);
}

void Client::startReceive()
{
    _recvBuff.fill(0);
    _clientSocket.async_receive(boost::asio::buffer(_recvBuff), boost::bind(&Client::handleReceive, this, boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred));
}

void Client::handleReceive(const boost::system::error_code& ec, std::size_t bytesTransferred)
{
    BinaryProtocol::Packet p;

    _connexion.restart();
    _currentTime = sf::Time::Zero;
    if (ec) {
        std::cerr << "ERROR while reading " << bytesTransferred << " bytes on socket" << std::endl;
        return;
    }
    p = _binCodec.unserialize(_recvBuff);
    if (_binCodec.check_packet(p) != true) {
        std::cerr << "ERROR: packet not valid" << std::endl;
        startReceive();
        return;
    }
    handleServerMessage(p._message);
    startReceive();
}

void Client::handleServerMessage(const std::string& update)
{
    int code = std::atoi(update.c_str());

    for (auto it = _serverResponse.begin(); it != _serverResponse.end(); ++it)
        if (it->first == code)
            (this->*(it->second))(update);
}

void Client::handleUpdateMenu(const std::string& update)
{
    Players::State state1(static_cast<Players::State>(std::atoi(update.substr(6, 1).c_str())));
    Players::State state2(static_cast<Players::State>(std::atoi(update.substr(10, 1).c_str())));
    Players::State state3(static_cast<Players::State>(std::atoi(update.substr(14, 1).c_str())));
    Players::State state4(static_cast<Players::State>(std::atoi(update.substr(18, 1).c_str())));

    for (auto obj = _players.begin(); obj != _players.end(); obj++) {
        if ((obj->get()->getType() == P1))
            obj->get()->setState(state1);
        if ((obj->get()->getType() == P2))
            obj->get()->setState(state2);
        if ((obj->get()->getType() == P3))
            obj->get()->setState(state3);
        if ((obj->get()->getType() == P4))
            obj->get()->setState(state4);
    }
}


void Client::handleUpdateGame(const std::string& updateRoutine)
{
    std::string update(updateRoutine);

    entityType type = (static_cast<entityType>(std::atoi(update.substr(update.find_first_of(" ") + 1, update.find_last_of(" ") - update.find_first_of(" ")).c_str())));
    int id = std::atoi(update.substr(update.find_last_of(" ") + 1, update.find_first_of("|") + 1 - update.find_last_of(" ")).c_str());
    animationState animation = (static_cast<animationState>(std::atoi(update.substr(update.find_first_of("|") + 1, update.find_last_of("|") - update.find_first_of("|")).c_str())));
    bool state = std::atoi(update.substr(update.find_last_of("|") + 1, update.find_first_of(".") + 1 - update.find_last_of("|")).c_str());
    float x = std::atof(update.substr(update.find_first_of(".") + 1, update.find_last_of(".") + 1 - update.find_first_of(".")).c_str());
    float y = std::atof(update.substr(update.find_last_of(".") + 1).c_str());

    if (state == true) {
        for (auto obj = _entities.begin(); obj != _entities.end(); obj++) {
            if ((obj->get()->getId() == id)) {
                updateEntity(id, sf::Vector2f{x, y}, animation);
                return;
            }
        }
        createEntity(id, type, false, sf::Vector2f{x, y}, animation);
    }
    else
       destroyEntity(id);
}

void Client::handleFine(const std::string& update)
{
    (void)update;
}

void Client::handleInvalidCommand(const std::string& update)
{
    (void)update;
    std::cout << "Error: Invalid command." << std::endl;
}

void Client::handleGhostRoom(const std::string& update)
{
    (void)update;
    _sfmlModule.setState(MenuDrawer::State::HOME);
}

void Client::handleFullRoom(const std::string& update)
{
    (void)update;
    _sfmlModule.setState(MenuDrawer::State::HOME);
}

void Client::handleTooFast(const std::string& update)
{
    (void)update;
    std::cout << "Error: Please wait." << std::endl;
    _sfmlModule.setState(MenuDrawer::State::ROOM);
}


void Client::handleJoinLobby(const std::string& update)
{
    (void)update;
    std::cout << "Lobby joined." << std::endl;
    _state = INLOBBY;
    _sfmlModule.setState(MenuDrawer::State::ROOM);
}

void Client::handleStartGame(const std::string& update)
{
    (void)update;
    std::cout << "Game started: Good luck !" << std::endl;
    _state = INGAME;
    #ifndef _WIN32 
        _sfmlModule.getMenuDrawer().getAudio().stopSound(Audio::MENU);
        _sfmlModule.getAudio().playSound(Audio::STARTGAME);
        _sfmlModule.getAudio().playSound(Audio::GAME);
    #endif
    _sfmlModule.setState(MenuDrawer::State::GAME);
}

void Client::handleBusy(const std::string& update)
{
    (void)update;
    std::cout << "Error: Please wait." << std::endl;
}

void Client::handleEnd(const std::string& update)
{
    (void)update;
    #ifndef _WIN32 
        _sfmlModule.getAudio().stopSound(Audio::GAME);
        _sfmlModule.getMenuDrawer().getAudio().playSound(Audio::MENU);
    #endif
    _sfmlModule.setState(MenuDrawer::State::GAME);
    _state = INLOBBY;
    _sfmlModule.setState(MenuDrawer::State::ROOM);
    _entities.clear();
    std::cout << "Finished." << std::endl;
}

void Client::send(const std::string& str)
{
    boost::system::error_code err;
    std::size_t bytes = 0;

    bytes = _clientSocket.send_to(boost::asio::buffer(_binCodec.serialize(_binCodec.createPacket(str))), _remoteEndpoint, 0, err);
    if (err) {
        std::cerr << "ERROR while sending " << bytes << " bytes of data" << std::endl;
        return;
    }
}

void Client::createEntity(int entityId, const entityType& entityType, bool bonus, const sf::Vector2f& entityPos, const animationState& animation)
{
    if (entityType == BACKGROUND)
    _entities.push_back(std::make_shared<Graphic::Background>(Graphic::Background(entityId, bonus, entityPos, animation)));
    else if (entityType == P1 || entityType == P2 || entityType == P3 ||  entityType == P4)
    _entities.push_back(std::make_shared<Graphic::Player>(Graphic::Player(entityId, entityType, bonus, entityPos, animation)));
    else if (entityType == WALL)
    _entities.push_back(std::make_shared<Graphic::Wall>(Graphic::Wall(entityId, bonus, entityPos, animation)));
    else if (entityType == OBSTACLE)
    _entities.push_back(std::make_shared<Graphic::Obstacle>(Graphic::Obstacle(entityId, bonus, entityPos, animation)));
    else if (entityType == PLAYER_SHOOT) {
        _entities.push_back(std::make_shared<Graphic::PlayerShoot>(Graphic::PlayerShoot(entityId, bonus, entityPos, animation)));
        #ifndef _WIN32 
            _sfmlModule.getAudio().playSound(Audio::SHOOT);
        #endif
    } else if (entityType == ALIEN)
    _entities.push_back(std::make_shared<Graphic::Alien>(Graphic::Alien(entityId, bonus, entityPos, animation)));
    else if (entityType == ALIEN_SHOOT)
    _entities.push_back(std::make_shared<Graphic::AlienShoot>(Graphic::AlienShoot(entityId, bonus, entityPos, animation)));
    else if (entityType == UFO)
    _entities.push_back(std::make_shared<Graphic::Ufo>(Graphic::Ufo(entityId, bonus, entityPos, animation)));
    else if (entityType == UFO_SHOOT)
    _entities.push_back(std::make_shared<Graphic::UfoShoot>(Graphic::UfoShoot(entityId, bonus, entityPos, animation)));
    else if (entityType == SPACESHIP)
    _entities.push_back(std::make_shared<Graphic::Spaceship>(Graphic::Spaceship(entityId, bonus, entityPos, animation)));
    else if (entityType == SPACESHIP_SHOOT)
    _entities.push_back(std::make_shared<Graphic::SpaceshipShoot>(Graphic::SpaceshipShoot(entityId, bonus, entityPos, animation)));
    else if (entityType == PIRATE)
    _entities.push_back(std::make_shared<Graphic::Pirate>(Graphic::Pirate(entityId, bonus, entityPos, animation)));
    else if (entityType == PIRATE_SHOOT)
    _entities.push_back(std::make_shared<Graphic::PirateShoot>(Graphic::PirateShoot(entityId, bonus, entityPos, animation)));
    else if (entityType == BOMB)
    _entities.push_back(std::make_shared<Graphic::Bomb>(Graphic::Bomb(entityId, bonus, entityPos, animation)));
    else if (entityType == ITEMSPEED)
    _entities.push_back(std::make_shared<Graphic::ItemSpeed>(Graphic::ItemSpeed(entityId, bonus, entityPos, animation)));
}

void Client::updateEntity(int entityId, const sf::Vector2f& entityPos, const animationState &anime) const
{
    for (size_t index = 0; index != _entities.size(); index++) {
        if ((_entities[index].get()->getId() == entityId)) {
            _entities.at(index).get()->update((static_cast<int>(entityPos.x)), (static_cast<int>(entityPos.y)));
            _entities.at(index).get()->setAnimation(anime);
        }
    }
}

void Client::destroyEntity(int entityId)
{
    for (size_t index = 0; index != _entities.size(); index++) {
        if ((_entities[index].get()->getId() == entityId)) {
            _entities.erase(_entities.begin() + index);
            index--;
        }
    }
}