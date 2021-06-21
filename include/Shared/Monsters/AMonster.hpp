/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AMonster.hpp
*/

#ifndef AMONSTER_HPP_
#define AMONSTER_HPP_

#include "IMonster.hpp"
#include "Filter.hpp"

class AMonster : public IMonster
{
    public:
        AMonster();
        AMonster(const AMonster& other) = default;
        AMonster& operator=(const AMonster& other) = default;
        virtual void update(const float dt, ECS::ECSEngine&) = 0;
        virtual ~AMonster() = default;
    protected:
        ECS::Filter _filter;
        Entity _id;
        unsigned int _animation;
    private:
};

#endif /* !AMONSTER_HPP_ */
