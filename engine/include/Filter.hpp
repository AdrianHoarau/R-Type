/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Filter.hpp
*/

#ifndef FILTER_HPP_
#define FILTER_HPP_

#include "EntityManager.hpp"
#include "StorageManager.hpp"

namespace ECS {
    class Filter {
        public:
            Filter();
            ~Filter() = default;
            Filter(const Filter& other) = default;
            Filter& operator=(const Filter& other) = default;
            std::vector<Entity> filterEntities(const std::shared_ptr<IStorage>& storage, std::vector<Entity>& entities);
            template <typename T>
            T& findComponent(const componentType& type, std::unordered_map<componentType, std::shared_ptr<IStorage>>& components)
            {
                return (static_cast<T&>(*components[type]));
            }
        protected:
        private:
    };
}

#endif /* !FILTER_HPP_ */
