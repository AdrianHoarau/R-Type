/*
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Mon Mar 16 11:35:07 AM 2020 arthurbertaud
** Last update Thu Mar 18 5:16:05 PM 2020 arthurbertaud
*/

#ifndef KEYTRADUCER_HPP_
#define KEYTRADUCER_HPP_

#include <map>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "IGraphicLibrary.hpp"

class keyTraducer
{
public:
    keyTraducer();
    keyTraducer(const keyTraducer& other) = default;
    keyTraducer& operator=(const keyTraducer& other) = default;
    ~keyTraducer() = default;
    bool traduceLetter(const sf::Keyboard::Key& key, std::string& );
    Graphic::Command traduceKey(const sf::Keyboard::Key& key);

private:
    std::map<sf::Keyboard::Key, char> _keys;
    std::map<sf::Keyboard::Key, Graphic::Command> _inputs;
};

#endif /* !KEYTRADUCER_HPP_ */
