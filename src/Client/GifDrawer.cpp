/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** GifDrawer.cpp
*/

#include "GifDrawer.hpp"

GifDrawer::GifDrawer(int nb, const std::string &path, const sf::Vector2f& scale, const sf::Time& frameTime) : _path(path), _index(0), _scale(scale), \
_currentTime(sf::Time::Zero),  _frameTime(frameTime)
{
    std::string pathLoad;

    for (int i = 0; i != nb; i++) {
        pathLoad = _path + std::to_string(i) + ".png";
        loadSprite(pathLoad);
    }
}

void GifDrawer::setScale(const sf::Vector2f& scale)
{
    _scale = scale;
}

void GifDrawer::loadSprite(const std::string& path)
{
    sf::Sprite sprite;

    _textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
    if (!_textures.back()->loadFromFile(path))
        std::cerr << "ERROR: cannot found " << path << "." << std::endl;
    _textures.back()->setSmooth(true);
    sprite.setTexture(*_textures.back());
    _sprites.push_back(sprite);
}

void GifDrawer::update(sf::Time deltaTime, sf::RenderWindow& window)
{
    int size = 0;
    _currentTime += deltaTime;
    if (_currentTime >= _frameTime) {
        _currentTime = sf::microseconds(_currentTime.asMicroseconds() % _frameTime.asMicroseconds());
        size = (static_cast<int>(_sprites.size()));
        if (_index + 1 < size)
            _index++;
        else
            _index = 0;
        _currentTime = sf::Time::Zero;
    }
    _sprites[_index].setScale(_scale);
    window.draw(_sprites[_index]);
}
