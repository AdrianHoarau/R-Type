/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Audio.hpp
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <SFML/Audio.hpp>
#include <memory>
#include <map>
#include <iostream>

class Audio {
    public:
    enum audioType {
        MENU,
        GAME,
        SHOOT,
        DAMAGE,
        BUTTON,
        BOMB,
        STARTGAME,
        PLAYERNAME,
        READY,
        UNREADY,
    };
    private:
        std::vector<std::shared_ptr<sf::SoundBuffer>> _soundBuffer;
        std::map<audioType, sf::Sound> _sounds;
    public:
        Audio();
        Audio(const Audio& other) = default;
        Audio& operator=(const Audio& other) = default;
        ~Audio() = default;
        void addSound(const std::string& path, bool loop, const audioType &type);
        void playSound(const audioType& type);
        void stopSound(const audioType& type);
};

#endif