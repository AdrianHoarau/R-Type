/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** MenuDrawer.hpp
*/

#ifndef MenuDrawer_HPP_
#define MenuDrawer_HPP_

#include <memory>
#include <map>
#include "TextDrawer.hpp"
#include "Vector.hpp"
#include "keyTraducer.hpp"
#include <utility>
#include "Players.hpp"
#include "ClientState.hpp"
#include "ParallaxShader.hpp"
#include "GifDrawer.hpp"
#include "Audio.hpp"

class MenuDrawer {
public:
    enum State
    {
        HOME = 1,
        NEW = 2,
        JOIN = 3,
        SETTINGS = 4,
        QUIT = 5,
        NORMAL = 6,
        BIG = 7,
        CREATE = 8,
        ROOM_JOIN = 9,
        ROOM = 10,
        READY = 11,
        UNREADY = 12,
        GAME = 13,
        WAITING = 14,
        VIEW = 15,
    };
public:
    MenuDrawer(const sf::Vector2f& scale);
    MenuDrawer(const MenuDrawer&) = default;
    MenuDrawer& operator=(const MenuDrawer&) = default;
    ~MenuDrawer() = default;
    void draw(sf::RenderWindow& window, const std::string& playerName, sf::Event& event, const std::vector<std::shared_ptr<Players>>& players, const ClientState& clientS, sf::Time &frameTime);
    State handleMenu(sf::RenderWindow& window, sf::Event& event);
    void setScale(const sf::Vector2f& );
    std::string getRoomName()const;
    void setState(const State& );
    void reSize();
    State getState() const;
    #ifndef _WIN32 
        Audio &getAudio();
    #endif

protected:
private:
    State _state;
    posVector _winpos;
    sf::Vector2f _scale;
    TextDrawer _text;
    keyTraducer _key;
    std::string _roomName;
    ParallaxShader _parallaxShader;
    GifDrawer _gifDrawer;
    #ifndef _WIN32 
        Audio _audio;
    #endif
    sf::Sprite _background;
    sf::Texture _back;
    std::map<State, sf::Sprite> _buttons;
    std::map<State, sf::Vector2f> _posButtons;
    std::map<entityType, sf::Sprite> _players;
    std::vector<std::shared_ptr<sf::Texture>> _textures;

    void setButton();
    void drawButton(const State& state, const sf::Vector2f& pos, sf::RenderWindow& window);
    void loadSprite(const std::string& path, const State& obj, sf::IntRect,  const posVector& scale);
    void drawHome(sf::RenderWindow& window, const std::string& playerName);
    bool checkHome(const State& );
    State clickButton(sf::RenderWindow& window, sf::Event& event);
    sf::Vector2f getPosButton(const State& obj);
    void initPosButton();
    std::string getPlayerName(const entityType& type);
    void displayJoinScene(const sf::Vector2f& posConditions, const sf::Vector2f& posName, const sf::RectangleShape& rect, \
    const sf::Vector2f& posEnter, const std::string& port, sf::RenderWindow& window,  const sf::Sprite& back);
    const std::string enterScene(sf::RenderWindow& window, sf::Event& event, const State& state);
    sf::RectangleShape createRectangleShape(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& color);
    void drawRoom(sf::RenderWindow& window, const std::vector<std::shared_ptr<Players>>&players, const ClientState& clientS, sf::Time &frameTime);
    void drawPlayerRoom(const std::shared_ptr<Players>& player, sf::RenderWindow& window);
    void loadSpriteSize(const std::string& path, const entityType& obj, sf::IntRect, const posVector& scale);
    void drawRect(const sf::Vector2f& , sf::RenderWindow& window);
    void drawState(const State& state, sf::RenderWindow& window, const sf::Vector2f& pos);
    void drawIconStat(const State& state, sf::RenderWindow& window, sf::Vector2f pos);
    bool checkRoom(const State& state);
    bool checkSettings(const State& state);
    void drawSettings(sf::RenderWindow& window);
    bool checkView(const State& state);
};

#endif /* !MenuDrawer_HPP_ */