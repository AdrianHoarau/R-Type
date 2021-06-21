/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** SystemManager.hpp
*/

#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include "ISystem.hpp"
#include <vector>
#include <memory>

namespace ECS {
    class ISystem;

    class SystemManager {
    public:
        SystemManager();
        SystemManager(const SystemManager& other) = default;
        SystemManager& operator=(const SystemManager& other) = default;
        std::vector<std::shared_ptr<ISystem>>& getSystems();
        void addSystem(const std::shared_ptr<ISystem>& system);
        ~SystemManager() = default;
    private:
        std::vector<std::shared_ptr<ISystem>> _systems;
    };
}

#endif /*!SYSTEMMANAGER_HPP*/