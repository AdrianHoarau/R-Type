/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** MenuDrawer.cpp
*/
#include "MenuDrawer.hpp"
#include <iostream>

MenuDrawer::MenuDrawer(const sf::Vector2f& scale) : _state(HOME), _winpos({1116, 797}), _scale(scale), _text(TextDrawer()),
_key(keyTraducer()), _roomName(""), _parallaxShader("../../ressources/sprites/background_final.png", _scale), _gifDrawer(45, "../../ressources/sprites/gif/frame_", _scale, sf::seconds(0.04f))
#ifndef _WIN32 
,_audio()
#endif
{
    setButton();
    initPosButton();
    _back.loadFromFile("../../ressources/sprites/spaceship_final.png");
    _back.setSmooth(true);
    _background.setTexture(_back);
    _background.setScale(_scale.x, _scale.y);
    #ifndef _WIN32 
        _audio.addSound("../../ressources/sounds/button.ogg", false, Audio::BUTTON);
        _audio.addSound("../../ressources/sounds/rtype.ogg", true, Audio::MENU);
        _audio.addSound("../../ressources/sounds/ready.wav", false, Audio::READY);
    #endif
}

void MenuDrawer::setButton()
{
    loadSpriteSize("../../ressources/sprites/rectangle.png", WALL, sf::IntRect(0, 0, 28, 19), {2, 2});
    loadSpriteSize("../../ressources/sprites/spaceship_o.png", P1, sf::IntRect(0, 0, 28, 19), {0.35, 0.35});
    loadSpriteSize("../../ressources/sprites/spaceship_t.png", P2, sf::IntRect(0, 0, 28, 19), {0.35, 0.35});
    loadSpriteSize("../../ressources/sprites/spaceship_tr.png", P3, sf::IntRect(0, 0, 28, 19), {0.25, 0.25});
    loadSpriteSize("../../ressources/sprites/spaceship_f.png", P4, sf::IntRect(0, 0, 28, 19), {0.25, 0.25});
    loadSprite("../../ressources/sprites/New_Button.png", NEW, sf::IntRect(0, 0, 28, 19), {0.5f, 0.5f});
    loadSprite("../../ressources/sprites/Load_Button.png", JOIN, sf::IntRect(0, 0, 28, 19), {0.5f, 0.5f});
    loadSprite("../../ressources/sprites/Settings_Button.png", SETTINGS, sf::IntRect(0, 0, 28, 19), {0.5f, 0.5f});
    loadSprite("../../ressources/sprites/Quit_Button.png", QUIT, sf::IntRect(0, 0, 28, 19), {0.5f, 0.5f});
    loadSprite("../../ressources/sprites/ready.png", READY, sf::IntRect(0, 0, 28, 19), {0.2f, 0.2f});
    loadSprite("../../ressources/sprites/unready.png", UNREADY, sf::IntRect(0, 0, 28, 19), {0.2f, 0.2f});
    loadSprite("../../ressources/sprites/Home_Square_Button.png", HOME, sf::IntRect(0, 0, 28, 19), {0.35f, 0.35f});
    loadSprite("../../ressources/sprites/play_button.png", GAME, sf::IntRect(0, 0, 28, 19), {0.2f, 0.2f});
    loadSprite("../../ressources/sprites/big_button.png", BIG, sf::IntRect(0, 0, 28, 19), {0.2f, 0.2f});
    loadSprite("../../ressources/sprites/small_button.png", NORMAL, sf::IntRect(0, 0, 28, 19), {0.2f, 0.2f});
    loadSprite("../../ressources/sprites/jumelles.png", VIEW, sf::IntRect(0, 0, 28, 19), {0.35f, 0.35f});
}

void MenuDrawer::setScale(const sf::Vector2f& scale)
{
    _scale = scale;
}

void MenuDrawer::reSize()
{
    _background.setScale(_scale);
    _parallaxShader.setScale(_scale);
    _gifDrawer.setScale(_scale);
}

sf::Vector2f MenuDrawer::getPosButton(const State& obj)
{
    sf::Vector2f error(-1, -1);

    for (std::map<State, sf::Vector2f>::iterator it = _posButtons.begin(); it != _posButtons.end(); it++) {
        if ((it)->first == obj)
            return (it)->second;
    }
    return error;
}

void MenuDrawer::initPosButton()
{
    float x = (((_winpos.x / 2) - 150) * _scale.x);
    float y = ((_winpos.y / 3) * _scale.y);
    float x_settings = (((_winpos.x / 2) - 320) * _scale.x);
    float y_settings = ((_winpos.y / 3) * _scale.y);
    float x_room = (_winpos.x - 307) * _scale.x;
    float y_room = (_winpos.y / 6 + 8) * _scale.y;
    sf::Vector2f posBack((_winpos.x - 100) * _scale.x, (_winpos.y - 135) * _scale.y);
    sf::Vector2f pos(x, y);
    sf::Vector2f posRoom(x_room, y_room);
    sf::Vector2f posSet(x_settings, y_settings);

    _posButtons.insert(std::make_pair(HOME, posBack));
    _posButtons.insert(std::make_pair(VIEW, posBack));
    _posButtons.insert(std::make_pair(NEW, pos));
    pos.y += 130 * _scale.y;
    _posButtons.insert(std::make_pair(JOIN, pos));
    pos.y += 130 * _scale.y;
    _posButtons.insert(std::make_pair(SETTINGS, pos));
    pos.y += 130 * _scale.y;
    _posButtons.insert(std::make_pair(QUIT, pos));
    _posButtons.insert(std::make_pair(READY, posRoom));
    _posButtons.insert(std::make_pair(UNREADY, posRoom));
    _posButtons.insert(std::make_pair(GAME, posRoom));
    _posButtons.insert(std::make_pair(NORMAL, posSet));
    posSet.x += 350 * _scale.x;
    _posButtons.insert(std::make_pair(BIG, posSet));

}

void MenuDrawer::loadSpriteSize(const std::string& path, const entityType& obj, sf::IntRect rect, const posVector& scale)
{
    sf::Sprite sprite;

    _textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    if (!_textures.back()->loadFromFile(path))
        std::cerr << "ERROR: cannot found " << path << "." << std::endl;
    (void)rect;
    _textures.back()->setSmooth(true);
    sprite.setTexture(*_textures.back());
    sprite.setScale(scale.x * _scale.x, scale.y *_scale.y);
    _players.insert(std::make_pair(obj, sprite));
}


void MenuDrawer::loadSprite(const std::string& path, const State& obj, sf::IntRect rect,  const posVector& scale)
{
    sf::Sprite sprite;

    _textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    if (!_textures.back()->loadFromFile(path))
        std::cerr << "ERROR: cannot found " << path << "." << std::endl;
    (void)rect;
    _textures.back()->setSmooth(true);
    sprite.setTexture(*_textures.back());
    sprite.setScale(scale.x, scale.y);
    _buttons.insert(std::make_pair(obj, sprite));
}

MenuDrawer::State MenuDrawer::clickButton(sf::RenderWindow& window, sf::Event& event)
{
    for (std::map<State, sf::Sprite>::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
        if ((it)->second.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
            if (checkRoom((it)->first) == true && _state == ROOM)
                return (it)->first;
            #ifndef _WIN32 
                _audio.playSound(Audio::BUTTON);
            #endif
            if (checkView((it)->first) == true && _state == VIEW)
                return (it)->first;
            if (checkHome((it)->first) == true && _state == HOME)
                return (it)->first;
            if (checkSettings((it)->first) == true && _state == SETTINGS)
                return (it)->first;
            if ((it)->first == HOME && _state == WAITING)
                return (it)->first;
            }
    }
    return _state;
}

MenuDrawer::State MenuDrawer::handleMenu(sf::RenderWindow& window, sf::Event& event)
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f translated_pos = window.mapPixelToCoords(mouse_pos);
    sf::Color color(128, 128, 128);

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _state = QUIT;
        if (event.type == sf::Event::MouseButtonPressed)
            _state = clickButton(window, event);
        for (std::map<State, sf::Sprite>::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
            if ((it)->second.getGlobalBounds().contains(translated_pos))
               (it)->second.setColor(color);
            else
               (it)->second.setColor(sf::Color::White);
        }
    }
    return _state;
}

MenuDrawer::State MenuDrawer::getState() const
{
    return _state;
}

bool MenuDrawer::checkView(const State& state)
{
    if (state == HOME)
        return true;
    return false;
}

bool MenuDrawer::checkSettings(const State& state)
{
    if (state == BIG)
        return true;
    if (state == NORMAL)
        return true;
    if (state == HOME)
        return true;
    return false;
}

bool MenuDrawer::checkRoom(const State& state)
{
    if (state == READY) {
        #ifndef _WIN32 
            _audio.playSound(Audio::READY);
        #endif
        return true;
    }
    if (state == UNREADY) {
        #ifndef _WIN32 
                _audio.playSound(Audio::READY);
        #endif
        return true;
    }
    if (state == HOME || state == GAME) {
        #ifndef _WIN32 
                _audio.playSound(Audio::BUTTON);
        #endif
        return true;
    }
    return false;
}

bool MenuDrawer::checkHome(const State& state)
{
    if (state == NEW)
        return true;
    if (state == SETTINGS)
        return true;
    if (state == JOIN)
        return true;
    if (state == QUIT)
        return true;
    if (state == VIEW)
        return true;
    return false;
}

void MenuDrawer::drawHome(sf::RenderWindow& window, const std::string& playerName)
{
    sf::Vector2f pos;
    sf::Vector2f defaultVal(-1, -1);
    std::string wel = "Welcome Capitain " + playerName + " !";

    window.clear();
  _parallaxShader.parallaxShaderDraw(window);
  window.draw(_background);
    for (std::map<State, sf::Sprite>::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
        if (checkHome((it)->first) == true) {
            pos = getPosButton((it)->first);
            pos.x *= _scale.x;
            if ((it)->first == VIEW)
                pos.y *= _scale.y;
            (it)->second.setPosition(pos);
            window.draw((it)->second);
        }
    }
    pos = getPosButton(NEW);
    pos.x -= 80;
    pos.y -= 150;
    _text.drawPos(pos, wel, window, 45, _scale);
    window.display();
}

std::string MenuDrawer::getRoomName()const
{
    return (_roomName);
}

void MenuDrawer::draw(sf::RenderWindow& window, const std::string& playerName, sf::Event& event, const std::vector<std::shared_ptr<Players>>&entities, const ClientState& clientS, sf::Time &frameTime)
{
    sf::Vector2f defaultVal(-1, -1);

    if (_state == WAITING) {
        window.clear();
        _parallaxShader.parallaxShaderDraw(window);
        window.draw(_background);
        drawButton(HOME, defaultVal, window);
        window.display();
    }
    if (_state == VIEW) {
        window.clear();
        _parallaxShader.parallaxShaderDraw(window);
        window.draw(_background);
        drawButton(HOME, defaultVal, window);
        window.display();
    }
    if (_state == HOME)
        drawHome(window, playerName);
    if (_state == SETTINGS)
        drawSettings(window);
    if (_state == NEW) {
        _roomName = enterScene(window, event, CREATE);
        return;
    }
    if (_state == JOIN) {
        _roomName = enterScene(window, event, ROOM_JOIN);
        return;
    }
    if (_state == ROOM || _state == READY || _state == UNREADY)
        drawRoom(window, entities, clientS, frameTime);
}

void MenuDrawer::drawSettings(sf::RenderWindow& window)
{
    sf::Vector2f defaultVal(-1, -1);

    window.clear();
    _parallaxShader.parallaxShaderDraw(window);
    window.draw(_background);
    drawButton(BIG, defaultVal, window);
    drawButton(NORMAL, defaultVal, window);
    drawButton(HOME, defaultVal, window);
    window.display();
}

std::string MenuDrawer::getPlayerName(const entityType& type)
{
    if (type == P1)
        return std::string("player 1");
    if (type == P2)
        return std::string("player 2");
    if (type == P3)
        return std::string("player 3");
    if (type == P4)
        return std::string("player 4");
    return std::string("");
}

void MenuDrawer::drawPlayerRoom(const std::shared_ptr<Players>& player, sf::RenderWindow& window)
{
    float x = (_winpos.x / 6 - 20) * _scale.x;
    float y = (_winpos.y / 6) * _scale.y;
    float x_icon = x + 33* _scale.x;
    float y_icon = y + 30* _scale.y;
    float x_text = x + 150* _scale.x;
    float y_text = y + 25 * _scale.y;
    std::string name;
    sf::Vector2f pos(x, y);
    sf::Vector2f posIcon(x_icon, y_icon);
    sf::Vector2f posText(x_text, y_text);
    for (std::map<entityType, sf::Sprite>::iterator it = _players.begin(); it != _players.end(); it++) {
        if ((it)->first == player->getType() && player->getState() != Players::OFF) {
            drawRect(pos, window);
            name = getPlayerName((it)->first);
            (it)->second.setPosition(posIcon);
            window.draw((it)->second);
            _text.drawSize(posText, name, window, 30);
            if (player->getState() == Players::READY)
                drawIconStat(READY, window, pos);
            else
                drawIconStat(UNREADY, window, pos);
        }
        posText.y += 120;
        pos.y += 120;
        posIcon.y += 120;
    }
}

void MenuDrawer::drawRect(const sf::Vector2f& pos, sf::RenderWindow& window)
{
    for (std::map<entityType, sf::Sprite>::iterator it = _players.begin(); it != _players.end(); it++) {
        if ((it)->first == WALL) {
            (it)->second.setPosition(pos);
            window.draw((it)->second);
        }
    }
}

void MenuDrawer::drawIconStat(const State& state, sf::RenderWindow& window, sf::Vector2f pos)
{
    sf::Texture texture;
    sf::Sprite go;

    pos.x += (500* _scale.x);
    pos.y += (22 * _scale.y);
    go.setPosition(pos);
    go.setScale(sf::Vector2f(0.3f, 0.3f));
    if (state == State::READY)
        texture.loadFromFile("../../ressources/sprites/V_Button.png");
    else
        texture.loadFromFile("../../ressources/sprites/X_Button.png");
    texture.setSmooth(true);
    go.setTexture(texture);
    window.draw(go);
}

void MenuDrawer::drawState(const State& state, sf::RenderWindow& window, const sf::Vector2f& pos)
{
    for (std::map<State, sf::Sprite>::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
        if ((it)->first == state) {
            (it)->second.setPosition(pos);
            window.draw((it)->second);
        }
    }
}

void MenuDrawer::setState(const State& state)
{
    _state = state;
}

void MenuDrawer::drawButton(const State& state, const sf::Vector2f& pos, sf::RenderWindow& window)
{
    sf::Vector2f defaultVal(-1, -1);
    sf::Vector2f set;

    for (std::map<State, sf::Sprite>::iterator it = _buttons.begin(); it != _buttons.end(); it++) {
        if ((it)->first == state) {
            if (defaultVal.x == pos.x && defaultVal.y == pos.y)
                set = getPosButton(state);
            else
                set = pos;
            set.x *= _scale.x;
            set.y *= _scale.y;
            (it)->second.setPosition(set);
            window.draw((it)->second);
        }
    }
}

void MenuDrawer::drawRoom(sf::RenderWindow& window, const std::vector<std::shared_ptr<Players>>&Players, const ClientState& clientS, sf::Time &frameTime)
{
    float x = (_winpos.x / 2 + 250) * _scale.x;
    float y = (_winpos.y / 6 - 100) * _scale.y;
    sf::Vector2f pos(x, y);
    sf::Vector2f defaultVal(-1, -1);

    window.clear();
    _gifDrawer.update(frameTime , window);
    drawButton(HOME, defaultVal, window);
    drawButton(GAME, defaultVal, window);
    for (auto it = Players.begin(); it != Players.end(); it++) {
       drawPlayerRoom((*it), window);
    }
    if (clientS != ClientState::READY)
        drawState(READY, window, pos);
    else
        drawState(UNREADY, window, pos);
    window.display();
}

const std::string MenuDrawer::enterScene(sf::RenderWindow& window, sf::Event& event, const State& state)
{
    std::string port = "";
    sf::Vector2f posConditions((50* _scale.x), (_winpos.y /4 - 50)* _scale.y);
    sf::Vector2f posName((_winpos.x /3 + 60) * _scale.x, (_winpos.y /2)* _scale.y);
    sf::Vector2f posEnter(50 * _scale.x, (_winpos.y - 100) * _scale.y);
    sf::Vector2f posBack((_winpos.x - 100) * _scale.x, (_winpos.y - 135) * _scale.y);
    sf::RectangleShape zone(createRectangleShape(sf::Vector2f(340, 70), sf::Vector2f((_winpos.x /3)  * _scale.x, (_winpos.y /2)  * _scale.y), sf::Color(255, 255, 255, 50)));
    sf::Texture texture;
    sf::Sprite back;
    sf::Vector2i mouse_pos;
    sf::Vector2f translated_pos;
    sf::Color color(128, 128, 128);

    window.clear();
    back.setPosition(posBack);
    back.setScale(sf::Vector2f(0.35f, 0.35f));
    texture.loadFromFile("../../ressources/sprites/Home_Square_Button.png");
    texture.setSmooth(true);
    back.setTexture(texture);
    displayJoinScene(posConditions, posName, zone, posEnter, port, window, back);
    while (port.find("\n") == std::string::npos) {
        while (window.pollEvent(event)) {
            mouse_pos = sf::Mouse::getPosition(window);
            translated_pos = window.mapPixelToCoords(mouse_pos);
            if (event.type == sf::Event::KeyPressed)
                _key.traduceLetter(event.key.code, port);
            if (event.type == sf::Event::Closed) {
                _state = QUIT;
                return ("closssssssse");
            }
            if (back.getGlobalBounds().contains(translated_pos))
               back.setColor(color);
            else
               back.setColor(sf::Color::White);
            if (event.type == sf::Event::MouseButtonPressed) {
                if (back.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
                    _state = HOME;
                    return ("");
                }
            }
            event.key.code = sf::Keyboard::Escape;
        }
        displayJoinScene(posConditions, posName, zone, posEnter, port, window, back);
        window.draw(back);
    }
    port = port.substr(0, port.length() - 1);
    _state = state;
    return (port);
}

#ifndef _WIN32 
    Audio &MenuDrawer::getAudio()
    {
        return _audio;
    }
#endif

sf::RectangleShape MenuDrawer::createRectangleShape(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& color)
{
    sf::RectangleShape rect(size);

    rect.setPosition(pos);
    rect.setFillColor(color);
    return (rect);
}

void MenuDrawer::displayJoinScene(const sf::Vector2f& posConditions, const sf::Vector2f& posName, \
const sf::RectangleShape& rect, const sf::Vector2f& posEnter, const std::string& port, sf::RenderWindow& window, const sf::Sprite& back)
{
    window.clear();
    _parallaxShader.parallaxShaderDraw(window);
    window.draw(_background);
    window.draw(rect);
    _text.draw(posConditions, "Enter the name of the room.", window);
    _text.draw(posName, port, window, sf::Color::Black);
    _text.draw(posEnter, "Press enter to confirm.", window);
    window.draw(back);
    window.display();
}