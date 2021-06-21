/*
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Mon Mar 16 11:35:40 AM 2020 arthurbertaud
** Last update Thu Mar 18 6:32:41 PM 2020 arthurbertaud
*/

#include "keyTraducer.hpp"
#include <iostream>

keyTraducer::keyTraducer()
{
    _keys.insert(std::make_pair(sf::Keyboard::A, 'A'));
    _keys.insert(std::make_pair(sf::Keyboard::B, 'B'));
    _keys.insert(std::make_pair(sf::Keyboard::C, 'C'));
    _keys.insert(std::make_pair(sf::Keyboard::D, 'D'));
    _keys.insert(std::make_pair(sf::Keyboard::E, 'E'));
    _keys.insert(std::make_pair(sf::Keyboard::F, 'F'));
    _keys.insert(std::make_pair(sf::Keyboard::G, 'G'));
    _keys.insert(std::make_pair(sf::Keyboard::H, 'H'));
    _keys.insert(std::make_pair(sf::Keyboard::I, 'I'));
    _keys.insert(std::make_pair(sf::Keyboard::J, 'J'));
    _keys.insert(std::make_pair(sf::Keyboard::K, 'K'));
    _keys.insert(std::make_pair(sf::Keyboard::L, 'L'));
    _keys.insert(std::make_pair(sf::Keyboard::M, 'M'));
    _keys.insert(std::make_pair(sf::Keyboard::N, 'N'));
    _keys.insert(std::make_pair(sf::Keyboard::O, 'O'));
    _keys.insert(std::make_pair(sf::Keyboard::P, 'P'));
    _keys.insert(std::make_pair(sf::Keyboard::Q, 'Q'));
    _keys.insert(std::make_pair(sf::Keyboard::R, 'R'));
    _keys.insert(std::make_pair(sf::Keyboard::S, 'S'));
    _keys.insert(std::make_pair(sf::Keyboard::T, 'T'));
    _keys.insert(std::make_pair(sf::Keyboard::U, 'U'));
    _keys.insert(std::make_pair(sf::Keyboard::V, 'V'));
    _keys.insert(std::make_pair(sf::Keyboard::W, 'W'));
    _keys.insert(std::make_pair(sf::Keyboard::X, 'X'));
    _keys.insert(std::make_pair(sf::Keyboard::X, 'X'));
    _keys.insert(std::make_pair(sf::Keyboard::Y, 'Y'));
    _keys.insert(std::make_pair(sf::Keyboard::Z, 'Z'));
    _keys.insert(std::make_pair(sf::Keyboard::Num0, '0'));
    _keys.insert(std::make_pair(sf::Keyboard::Num1, '1'));
    _keys.insert(std::make_pair(sf::Keyboard::Num2, '2'));
    _keys.insert(std::make_pair(sf::Keyboard::Num3, '3'));
    _keys.insert(std::make_pair(sf::Keyboard::Num4, '4'));
    _keys.insert(std::make_pair(sf::Keyboard::Num5, '5'));
    _keys.insert(std::make_pair(sf::Keyboard::Num6, '6'));
    _keys.insert(std::make_pair(sf::Keyboard::Num7, '7'));
    _keys.insert(std::make_pair(sf::Keyboard::Num8, '8'));
    _keys.insert(std::make_pair(sf::Keyboard::Num9, '9'));
    _keys.insert(std::make_pair(sf::Keyboard::Enter, '\n'));
    _inputs.insert(std::make_pair(sf::Keyboard::Q, Graphic::Command::EXIT));
    _inputs.insert(std::make_pair(sf::Keyboard::Down, Graphic::Command::DOWN));
    _inputs.insert(std::make_pair(sf::Keyboard::Right, Graphic::Command::RIGHT));
    _inputs.insert(std::make_pair(sf::Keyboard::Left, Graphic::Command::LEFT));
    _inputs.insert(std::make_pair(sf::Keyboard::Up, Graphic::Command::UP));
    _inputs.insert(std::make_pair(sf::Keyboard::Tab, Graphic::Command::SHOOT));
}

bool keyTraducer::traduceLetter(const sf::Keyboard::Key& key, std::string& c)
{
    if ((c.length() == 8) && (key != sf::Keyboard::Enter) && (key != sf::Keyboard::Backspace))
        return (false);
    for (std::map<sf::Keyboard::Key, char>::iterator it = _keys.begin(); it != _keys.end(); it++)
    {
        if (it->first == key)
        {
            c.push_back(it->second);
            return (true);
        }
    }
    if (key == sf::Keyboard::Backspace)
    {
        c = c.substr(0, c.length() - 1);
        return (true);
    }
    return (false);
}

Graphic::Command keyTraducer::traduceKey(const sf::Keyboard::Key& key)
{
    for (std::map<sf::Keyboard::Key, Graphic::Command>::iterator it = _inputs.begin(); it != _inputs.end(); it++)
    {
        if (it->first == key)
        {
            return (it->second);
        }
    }
    return (Graphic::Command::NOTHING);
}