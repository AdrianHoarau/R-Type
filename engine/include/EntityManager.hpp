/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** EntityManager.hpp
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <queue>
#define MAX_ENTITIES 500

typedef size_t Entity;

namespace ECS {
    class EntityManager {
        public:
            EntityManager();
            Entity createEntity();
            void destroyEntity(const Entity entity);
            EntityManager(const EntityManager& other) = default;
            EntityManager& operator=(const EntityManager& other) = default;
            std::vector<Entity>& getEntities();
            ~EntityManager() = default;
        protected:
        private:
            std::queue<Entity> _entities;
            std::vector<Entity> _ids;
            unsigned int _nbEntities;
    };
}

#endif /* !ENTITYMANAGER_HPP_ */
