/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** GifDrawer.hpp
*/

#ifndef GIFDRAWER_HPP_
#define GIFDRAWER_HPP_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

class GifDrawer {
    private:
        std::string _path;
        int _index;
        sf::Vector2f _scale;
        sf::Time _currentTime;
        sf::Time _frameTime;
        std::vector<std::shared_ptr<sf::Texture>> _textures;
        std::vector<sf::Sprite> _sprites;

        void loadSprite(const std::string& path);
    public:
        GifDrawer(int nb, const std::string &path, const sf::Vector2f& scale, const sf::Time& frameTime);
        GifDrawer(const GifDrawer& other) = default;
        GifDrawer& operator=(const GifDrawer& other) = default;
        ~GifDrawer() = default;
        void update(sf::Time deltaTime, sf::RenderWindow& window);
        void setScale(const sf::Vector2f& scale);
};

#endif