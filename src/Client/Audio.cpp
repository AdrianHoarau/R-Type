/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Audio.cpp
*/

#include "Audio.hpp"

Audio::Audio()
{
}

void Audio::addSound(const std::string& path, bool loop, const audioType &type)
{
    sf::Sound sound;

    _soundBuffer.push_back(std::shared_ptr<sf::SoundBuffer>(new sf::SoundBuffer));
    if (!_soundBuffer.back()->loadFromFile(path))
        std::cerr << "ERROR: cannot found " << path << "." << std::endl;
    if (loop == true)
        sound.setLoop(true);
    sound.setBuffer(*_soundBuffer.back());
    _sounds.insert(std::make_pair(type, sound));
}

void Audio::playSound(const audioType& type)
{
    for (std::map<audioType, sf::Sound>::iterator it = _sounds.begin(); it != _sounds.end(); it++) {
        if (type == (it)->first)
            (it)->second.play();
    }
}

void Audio::stopSound(const audioType& type)
{
    for (std::map<audioType, sf::Sound>::iterator it = _sounds.begin(); it != _sounds.end(); it++) {
        if (type == (it)->first)
            (it)->second.stop();
    }
}