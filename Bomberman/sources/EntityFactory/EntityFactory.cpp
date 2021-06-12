/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** EntityFactory
*/

#include "UISystem.hpp"
#include "Transform.hpp"
#include "Button.hpp"
#include "ButtonCallbacks.hpp"
#include "BoxCollider.hpp"
#include "Renderer.hpp"
#include "Draggable.hpp"
#include "Destructible.hpp"
#include "Movement.hpp"
#include "DropBomb.hpp"
#include "EntityFactory.hpp"
#include "Scenes.hpp"
#include "Animator.hpp"
#include "SphereCollider.hpp"
#include "Texture.hpp"
#include "Image.hpp"
#include "Text.hpp"
#include "Font.hpp"
#include "PlayerInputs.hpp"
#include "SpeedBoost.hpp"
#include "Explosion.hpp"

EntityFactory::EntityFactory(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
    : _coordinator(coordinator), _camera(camera)
{
}

ECS::Entity& EntityFactory::createButton(const std::string& texturePath)
{
    ECS::Entity &entity = _coordinator.CreateEntity();

    entity.AddComponent<Component::IUIObject, Component::Button>(texturePath);
    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 0.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    entity.AddComponent<Component::IBehaviour, Component::ButtonCallbacks>(entity);

    return (entity);
}

ECS::Entity& EntityFactory::createText(const std::string& content)
{
    ECS::Entity &entity = _coordinator.CreateEntity();

    //entity.AddComponent<Component::IUIObject, Component::Text>();
    entity.AddComponent<Component::Text>(content);
    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 0.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    entity.GetComponent<Component::Text>().font = RayLib::Font("assets/magic_dream.ttf");

    return (entity);
}

ECS::Entity& EntityFactory::createWall()
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("Wall");
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::Renderer>();
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(BOX_SIZE, BOX_SIZE, BOX_SIZE);
    entity.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);
    entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));

    return (entity);
}

ECS::Entity& EntityFactory::createBox(const int, const bool draggable)
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("Box");
    entity.AddComponent<Component::Transform>();
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(BOX_SIZE, BOX_SIZE, BOX_SIZE);
    entity.GetComponent<Component::Transform>().position = RayLib::Vector3(-20.0f, 0.0f, 0.0f);
    entity.AddComponent<Component::Renderer>("Box");
    entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    entity.AddComponent<Component::Destructible>(entity, 1);
    if (draggable)
        entity.AddComponent<Component::IBehaviour, Component::Draggable>(entity, _camera);

    return (entity);
}

ECS::Entity& EntityFactory::createPlayer(const std::string &)
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("Player");
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::PhysicsBody>();
    // entity.AddComponent<Component::Renderer>("assets/Player/" + playerColor + "Player.obj", "assets/Player/" + playerColor + "Player.png");
    entity.AddComponent<Component::Renderer>("Player");
    entity.AddComponent<Component::Animator>("Player", "Idle");
    // entity.AddComponent<Component::Collider, Component::BoxCollider>(entity, RayLib::Vector3(10.0f, 10.0f, 10.0f));
    entity.AddComponent<Component::Collider, Component::SphereCollider>(entity, RayLib::Vector3(), 4.0f);

    entity.AddComponent<Component::IBehaviour, Component::PlayerInputs>(entity);

    entity.GetComponent<Component::Transform>().rotation = RayLib::Vector3(-90.0f, 0.0f, 0.0f);
    //entity.AddComponent<Component::IBehaviour, Component::DropBomb>(entity);
    //entity.AddComponent<Component::Destructible>(entity, 1);

    return (entity);
}

ECS::Entity& EntityFactory::createPickUp(void)
{
    // todo faire un vector de std::function, créer un index random et appeler la fonction correspondante
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("SpeedPickUp");
    entity.AddComponent<Component::Transform>();
    // entity.AddComponent<Component::Renderer>("assets/Player/" + playerColor + "Player.obj", "assets/Player/" + playerColor + "Player.png");
    entity.AddComponent<Component::Renderer>("SpeedPickUp");

    entity.AddComponent<Component::IBehaviour, Component::SpeedBoost>(entity, 5.0f);

    // todo add flashy pickup animation
    //entity.AddComponent<Component::Animator>("../assets/BoxMan/guyanim.iqm", "Idle");
    //entity.AddComponent<Component::Collider, Component::SphereCollider>(entity, RayLib::Vector3(), 2.0f);

    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(5.0f, 5.0f, 5.0f);
    return (entity);
}

ECS::Entity& EntityFactory::createBomb(float radius, Component::Explosion::ExplosionType type)
{
    ECS::Entity& entity = _coordinator.CreateEntity();

    entity.SetTag("Bomb");
    entity.AddComponent<Component::Transform>(RayLib::Vector3(), RayLib::Vector3(), RayLib::Vector3(BOX_SIZE, BOX_SIZE, BOX_SIZE));
    entity.AddComponent<Component::Renderer>("Bomb");
    //! si on spawn une bombe sur le joueur, on est bloqués
    //entity.AddComponent<Collider, BoxCollider>(entity, _coordinator);
    entity.AddComponent<Component::IBehaviour, Component::Explosion>(entity, radius, type);
    return (entity);
}
