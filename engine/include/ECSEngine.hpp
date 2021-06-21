/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** ECSEngine.hpp
*/

#ifndef ECSENGINE_HPP_
#define ECSENGINE_HPP_

#include "StorageManager.hpp"
#include "SystemManager.hpp"

namespace ECS {
    class ECSEngine {
        public:
            ECSEngine();
            ECSEngine(const ECSEngine& other) = default;
            ECSEngine& operator=(const ECSEngine& other) = default;
            void update(float dt);
            Entity getNewEntity() const;
            void removeEntity(const Entity entity);
            template<typename T>
            void registerComponent(const componentType type)
            {
                _storageM->registerStorage<T>(type);
            }

            template<typename T,typename... Args>
            void registerSystem(Args&&... args)
            {
                _systemM->addSystem(std::make_shared<T>(std::forward<Args>(args)...));
            }

            template<typename T>
            void addComponent(const Entity entity, const T& component, const componentType type)
            {
                _storageM->addComponent<T>(entity, component, type);
            }

            template<typename T>
            T& getComponent(const Entity entity, const componentType type)
            {
                Storage<T>& storage = _storageM->findStorage<Storage<T>>(type);
                return (storage.getComponent(entity));
            }
            std::shared_ptr<IStorage>& getStorage(const componentType type);
            std::vector<Entity>& getEntites();
            std::vector<std::shared_ptr<ISystem>>& getSystems();
            ~ECSEngine() = default;
        protected:
        private:
            std::unique_ptr<StorageManager> _storageM;
            std::unique_ptr<EntityManager> _entityM;
            std::unique_ptr<SystemManager> _systemM;
    };
}

#endif /* !ECSENGINE_HPP_ */
