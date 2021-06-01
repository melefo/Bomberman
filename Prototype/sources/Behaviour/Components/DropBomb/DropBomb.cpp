/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** DropBomb
*/

#include "DropBomb.hpp"
#include <iostream>

namespace Prototype
{
    DropBomb::DropBomb(ECS::Entity& attatchedEntity, ECS::Coordinator& coordinator, int bombKey, float dropDelay)
    : _input(), _entity(attatchedEntity), _coordinator(coordinator), _transform(_entity.GetComponent<Transform>()),
      _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype"))
    {
        _bombKey = bombKey;
        _dropDelay = dropDelay;
        _timeToDrop = 0.0f;
        //_window = RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype");
    }

    void DropBomb::Update(float dt)
    {
        (void) dt;
        float windowFrameTime = _window->GetFrameTime();

        if (_timeToDrop > 0.0f) {
            _timeToDrop -= windowFrameTime;
        }
        if (_input.IsKeyDown(_bombKey) && _timeToDrop <= 0.0f) {
            //InstantiateBomb(_transform.position);
            std::cout << "Instantiate bomb" << std::endl;

            _timeToDrop = _dropDelay;
        }
    }

    void DropBomb::InstantiateBomb(RayLib::Vector3 position, Explosion::ExplosionType explosionType, RayLib::Vector3 radius)
    {
        ECS::Entity& entity = _coordinator.CreateEntity();

        entity.AddComponent<Transform>(position, RayLib::Vector3(), RayLib::Vector3(10.0f, 10.0f, 10.0f));
        entity.AddComponent<Renderer>("../assets/bomb/bomb2.fbx", "../assets/bomb/bomb2_text.png");
        entity.AddComponent<Collider, BoxCollider>(entity, _coordinator);
        entity.AddComponent<IBehaviour, Explosion>(radius, explosionType);
    }

}
