/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** IStorage.hpp
*/

#ifndef ISTORAGE_HPP_
#define ISTORAGE_HPP_

#include "Components.hpp"
#include <array>

namespace ECS {
    class IStorage {
        public:
            virtual ~IStorage() = default;
            virtual bool destroyEntity(std::size_t entityID) = 0;
            virtual bool hasComponent(std::size_t entityID) = 0;
            virtual componentType getType() const = 0;
        protected:
        private:
    };
}
#endif /* !ISTORAGE_HPP_ */
