/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Explosion
*/

#include "Explosion.hpp"
#include <iostream>

namespace Component
{
    Explosion::Explosion(ECS::Entity& entity, float radius, Explosion::ExplosionType startType, unsigned int startPower, float timer) :
    _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(800, 450), "Prototype")), _myEntity(entity), _transform(_myEntity.GetComponent<Transform>()),
    _coordinator(ECS::Coordinator::GetInstance())
    {
        _radius = radius;
        type = startType;
        power = startPower;
        _explosionTimer = timer;
    }

    void Explosion::Update(double)
    {
        _explosionTimer -= _window->GetFrameTime();

        // ! draw wire sphere on the window to see/debug radius!
        _window->DrawSphereWires(_transform.position, _radius);

        if (_explosionTimer <= 0.0f) {
            std::cout << "BOOM" << std::endl;
            std::vector<std::reference_wrapper<ECS::Entity>> entities = CollisionSystem::OverlapSphere(*_coordinator.get(), _transform.position, _radius);

            for (auto it = entities.begin(); it != entities.end(); it++) {
                if (it->get().HasComponent<Destructible>()) {
                    Destructible& destructible = it->get().GetComponent<Destructible>();
                    destructible.TakeDamage(power);
                }
            }
            _myEntity.Dispose();
        }
    }

    void Explosion::FixedUpdate(ECS::Entity& entity)
    {
        (void) entity;
    }

    std::ostream& Explosion::operator<<(std::ostream& stream)
    {
        // save radius
        // explosion type
        // power
        return (stream);
    }

}