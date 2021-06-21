/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** IMonster.hpp
*/

#ifndef IMONSTER_HPP_
#define IMONSTER_HPP_

#include "ECSEngine.hpp"

class IMonster {
    public:
        virtual ~IMonster() = default;
        virtual void init(ECS::ECSEngine&) = 0;
        virtual void update(const float dt, ECS::ECSEngine&) = 0;
    protected:
    private:
};

#endif /* !IMONSTER_HPP_ */
