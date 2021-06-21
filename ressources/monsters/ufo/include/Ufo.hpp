/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** ufo.hpp
*/

#ifndef UFO_HPP_
#define UFO_HPP_

#include "AMonster.hpp"

class Ufo : public AMonster
{
    public:
        Ufo();
        Ufo(const Ufo& other) = default;
        Ufo& operator=(const Ufo& other) = default;
        void init(ECS::ECSEngine&);
        void update(const float dt, ECS::ECSEngine&);
        ~Ufo() = default;
    private:
    int _time;
    int _speed;
    int _zone;
    bool _way;
};

#endif /* !UFO_HPP_ */
