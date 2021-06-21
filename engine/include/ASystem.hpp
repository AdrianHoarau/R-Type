/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** ASystem.hpp
*/

#ifndef ASYSTEM_HPP_
#define ASYSTEM_HPP_

#include "ISystem.hpp"
#include "Filter.hpp"

namespace ECS {
    class ASystem : public ISystem {
        public:
            ASystem();
            ~ASystem() = default;
            ASystem(const ASystem& other) = default;
            ASystem& operator=(const ASystem& other) = default;
        protected:
            Filter _filter;
        private:
    };
}

#endif /* !ASYSTEM_HPP_ */
