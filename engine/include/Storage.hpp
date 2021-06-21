/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Storage.hpp
*/

#ifndef STORAGE_HPP_
#define STORAGE_HPP_

#include "IStorage.hpp"
#include "EntityManager.hpp"
#include <unordered_map>
#include <memory>
#include <iostream>

namespace ECS {
    template <typename T>
    class Storage : public IStorage
    {
    public:
        Storage(const componentType& type) : _size(0), _type(type){};
        ~Storage() = default;
        Storage(const Storage& other) = default;
        Storage& operator=(const Storage& other) = default;
        void linkEntityToComponent(Entity entityID, const T& component)
        {
            Entity newIndex = _size;
            _entityToIndex[entityID] = newIndex;
            _indexToEntity[newIndex] = entityID;
            _componentArray[newIndex] = component;
            _size++;
        }

        T &getComponent(Entity entityID)
        {
            return (_componentArray[_entityToIndex[entityID]]);
        }
        bool destroyEntity(Entity entityID)
        {
            if (_entityToIndex.find(entityID) != _entityToIndex.end())  {
                removeEntity(entityID);
                return (true);
            }
            return (false);
        }
        bool hasComponent(Entity entityID)
        {
            if (_entityToIndex.find(entityID) != _entityToIndex.end())
                return (true);
            return (false);
        }

        componentType getType() const
        {
            return (_type);
        }
    private:
        std::array<T, 5000> _componentArray;
        std::unordered_map<Entity, size_t> _entityToIndex;
        std::unordered_map<size_t, Entity> _indexToEntity;
        size_t _size;
        componentType _type;
        void removeEntity(size_t entityID)
        {
            size_t indexOfRemovedEntity = _entityToIndex[entityID];
            size_t indexOfLastElement = _size - 1;
            size_t entityOfLastElement = _indexToEntity[indexOfLastElement];

            _componentArray[indexOfRemovedEntity] = _componentArray[indexOfLastElement];
            _entityToIndex[entityOfLastElement] = indexOfRemovedEntity;
            _indexToEntity[indexOfRemovedEntity] = entityOfLastElement;
            _entityToIndex.erase(entityID);
            _indexToEntity.erase(indexOfLastElement);
            --_size;
        }
    };
}

#endif /*!STORAGE_HPP_*/