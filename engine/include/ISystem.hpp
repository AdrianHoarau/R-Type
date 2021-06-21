/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** ISystem.hpp
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

namespace ECS {
class ECSEngine;

class ISystem {
        public:
            virtual ~ISystem() = default;
            virtual void update(const float dt, ECSEngine& engine) = 0;
        protected:
        private:
    };
}

#endif /* !ISYSTEM_HPP_ */