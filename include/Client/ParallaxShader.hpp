/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** ParallaxShader.hpp
*/

#include <SFML/Graphics.hpp>
#include <string>

class ParallaxShader {
    private:
        float _offset;
        sf::Vector2f _scale;
        sf::Clock _clock;
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Shader _parallaxShader;
    public:
        ParallaxShader(const std::string& , const sf::Vector2f& scale);
        ParallaxShader(const ParallaxShader& other) = default;
        ParallaxShader& operator=(const ParallaxShader& other) = default;
        ~ParallaxShader() = default;
        void setScale(const sf::Vector2f& );
        void parallaxShaderDraw(sf::RenderWindow& window);
};