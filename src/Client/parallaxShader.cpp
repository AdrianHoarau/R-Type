/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** parallaxShader.cpp
*/

#include "ParallaxShader.hpp"
#include <iostream>

ParallaxShader::ParallaxShader(const std::string& path, const sf::Vector2f& scale) : _offset(0.f), _scale({scale.x, scale.y})
{
    if (!_texture.loadFromFile(path.c_str())) {
        return;
    }
    _texture.setRepeated(true);
    _sprite.setTexture(_texture);
    _sprite.setPosition(0, 0);
    _sprite.setColor(sf::Color(255, 255, 255, 200));
    _sprite.setScale(_scale);
    _parallaxShader.loadFromMemory(
        "uniform float offset;"
        "void main() {"
        "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
        "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
        "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;"
        "    gl_FrontColor = gl_Color;"
        "}", sf::Shader::Vertex);
}

void ParallaxShader::setScale(const sf::Vector2f& scale)
{
    _scale = scale;
    _sprite.setScale(_scale);
}

void ParallaxShader::parallaxShaderDraw(sf::RenderWindow& window)
{
    _parallaxShader.setUniform("offset", _offset += _clock.restart().asSeconds() / 10);
    window.draw(_sprite, &_parallaxShader);
}