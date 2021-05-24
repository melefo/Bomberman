/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** Entity
*/

#include <algorithm>
#include "Exceptions.hpp"
#include "Entity.hpp"

namespace ECS
{
    Entity::Entity(uint32_t id) :
    _id(id), _components()
    {
    }

    template<typename T>
    std::unique_ptr<T> &Entity::GetComponent()
    {
        std::string name(typeid(T).name());

        const auto &it = this->_components.find(name);
        if (it == this->_components.end())
            throw new Exception::EntityException("Entity doesn't contains this Component");
        return *it;
    }

    template<typename T>
    void Entity::AddComponent()
    {
        std::string name(typeid(T).name());

        if (this->HasComponent<T>())
            throw new Exception::EntityException("Entity already contains this Component");
        this->_components.insert(name, std::make_unique<T>());
    }

    template<typename T>
    bool Entity::HasComponent() const
    {
        std::string name(typeid(T).name());

        return this->_components.find(name) != this->_components.end();
    }

    bool Entity::HasComponent(std::string &name) const
    {
        return this->_components.find(name) != this->_components.end();
    }

    uint32_t Entity::GetId() const
    {
        return this->_id;
    }
}