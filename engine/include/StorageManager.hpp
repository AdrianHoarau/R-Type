/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** StorageManager.hpp
*/

#ifndef STORAGEMANAGER_HPP_
#define STORAGEMANAGER_HPP_

#include "Storage.hpp"
#include <unordered_map>
#include <memory>

namespace ECS {
    class StorageManager {
        public:
            StorageManager();
            StorageManager(const StorageManager& other) = default;
            StorageManager& operator=(const StorageManager& other) = default;
            ~StorageManager() = default;
            template <typename T>
            T &findStorage(const componentType& type)
            {
                return (static_cast<T&>(*_storages[type]));
            }
            std::unordered_map<componentType, std::shared_ptr<IStorage>>& getStorages();
            template <typename T>
            void registerStorage(const componentType type)
            {
                _storages.emplace(type, std::make_shared<Storage<T>>(type));
            }

            std::shared_ptr<IStorage>& getStorage(const componentType type);

            template <typename T>
            void addComponent(const Entity entity, const T& component, const componentType type)
            {
                findStorage<Storage<T>>(type).linkEntityToComponent(entity, component);
            }
        protected:
        private:
            std::unordered_map<componentType, std::shared_ptr<IStorage>> _storages;
    };
}
#endif /* !STORAGEMANAGER_HPP_ */
