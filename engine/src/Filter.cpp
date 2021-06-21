/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Filter.cpp
*/

#include "Filter.hpp"

ECS::Filter::Filter()
{
}

std::vector<Entity> ECS::Filter::filterEntities(const std::shared_ptr<ECS::IStorage>& storage, std::vector<Entity>& entities)
{
    std::vector<Entity> validEntities;

    for (auto& ent: entities) {
        if (storage->hasComponent(ent) == true)
            validEntities.push_back(ent);
    }
    return (validEntities);
}