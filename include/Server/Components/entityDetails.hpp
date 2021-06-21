/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** entityDetails.hpp
*/

#ifndef ENTITYDETAILS_HPP_
#define ENTITYDETAILS_HPP_

#include "IComponents.hpp"
#include "entityType.hpp"

namespace ECS {
    struct entityDetails : public IComponents {
        entityDetails() = default;
        entityDetails(const entityType type, const animationState state);
        entityDetails(const entityDetails& other) = default;
        entityDetails& operator=(const entityDetails& other) = default;
        ~entityDetails() = default;
        entityType _type;
        animationState _state;
        bool _toUpdate;
    };
}

#endif /* !ENTITYDETAILS_HPP_ */
