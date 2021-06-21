/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** testECSEngine.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ECSEngine.hpp"
#include "movementSystem.hpp"
#include "entityDetails.hpp"
#include "entityType.hpp"
#include "Error.hpp"
#include "Player.hpp"

Test(testECSEngineSimpleUsage, ECSEngine)
{
    ECS::ECSEngine engine;

    engine.registerComponent<ECS::Position>(ECS::POSITION);
    engine.registerComponent<ECS::Velocity>(ECS::VELOCITY);
    engine.registerComponent<ECS::entityDetails>(ECS::ENTITY_DETAILS);
    engine.registerComponent<ECS::Player>(ECS::PLAYER);

    engine.registerSystem<ECS::movementSystem>();

    auto ent = engine.getNewEntity();
    engine.addComponent(ent, ECS::Position(0, 0), ECS::POSITION);
    engine.addComponent(ent, ECS::Velocity(1, 1), ECS::VELOCITY);
    engine.addComponent(ent, ECS::entityDetails(entityType::PLAYER_SHOOT, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
    engine.update(1);
    cr_assert_eq(engine.getComponent<ECS::Position>(ent, ECS::POSITION)._x, 1);
}

Test(testECSEngineSecondSimpleUsage, ECSEngine)
{
    ECS::ECSEngine engine;

    engine.registerComponent<ECS::Position>(ECS::POSITION);
    engine.registerComponent<ECS::Velocity>(ECS::VELOCITY);
    engine.registerComponent<ECS::entityDetails>(ECS::ENTITY_DETAILS);
    engine.registerComponent<ECS::Player>(ECS::PLAYER);

    engine.registerSystem<ECS::movementSystem>();

    auto ent = engine.getNewEntity();
    engine.addComponent(ent, ECS::Position(0, 0), ECS::POSITION);
    engine.addComponent(ent, ECS::Velocity(1, 2), ECS::VELOCITY);
    engine.addComponent(ent, ECS::entityDetails(entityType::PLAYER_SHOOT, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
    engine.update(1);
    cr_assert_eq(engine.getComponent<ECS::Position>(ent, ECS::POSITION)._y, 2);
}

Test(testECSEngineEntity, ECSEngine)
{
    ECS::ECSEngine engine;

    engine.getNewEntity();
    cr_assert_eq(engine.getEntites().front(), 0);
}

Test(testECSRemoveEntity, ECSEngine)
{
    ECS::ECSEngine engine;

    engine.getNewEntity();
    engine.removeEntity(engine.getNewEntity());
    cr_assert_eq(engine.getEntites().front(), 0);
}

Test(testECSErrorNbEntities, ECSEngine)
{
    ECS::ECSEngine engine;

    try {
        for (int i = 0; i != 505; i++)
            engine.removeEntity(engine.getNewEntity());
    } catch (Error &err) {
        cr_assert_eq(std::strcmp(err.what(), "Error: invalid number of entities has been reached."), 0);
    }
}