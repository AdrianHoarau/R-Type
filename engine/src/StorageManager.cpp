/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** StorageManager.cpp
*/

#include "StorageManager.hpp"

ECS::StorageManager::StorageManager()
{
}

std::unordered_map<ECS::componentType, std::shared_ptr<ECS::IStorage>>& ECS::StorageManager::getStorages()
{
    return (_storages);
}

std::shared_ptr<ECS::IStorage>& ECS::StorageManager::getStorage(const ECS::componentType type)
{
    return (_storages[type]);
}