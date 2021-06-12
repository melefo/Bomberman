/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** UISystem
*/

#include "UISystem.hpp"
#include "Transform.hpp"
#include <iostream>

namespace Component
{
    UISystem::UISystem(RayLib::Camera3D& camera) : _camera(camera)
    {
        // ! obsolète ?
        AddDependency<IUIObject>();

        AddDependency<Renderer>();
        AddDependency<Transform>();
    }

    void UISystem::Update(double, ECS::Entity& entity)
    {
        /*
        std::vector<std::reference_wrapper<IUIObject>> uiObjects = entity.OfType<IUIObject>();
        Transform& transform = entity.GetComponent<Transform>();

        RayLib::Vector2<float> position = RayLib::Vector2<float>(transform.position.x, transform.position.y);

        _camera.EndMode();
        for (IUIObject& uiObject : uiObjects) {
            // ! ajouter dans vector3 un .magnitude pour récup un float
            uiObject.Draw(position, RayLib::Vector2<float>(transform.scale.x, transform.scale.y));
        }
        _camera.BeginMode();*/

        std::unique_ptr<AssetManager> &assetManagerRef = AssetManager::GetInstance();
        Transform& transform = entity.GetComponent<Transform>();
        Renderer& renderer = entity.GetComponent<Renderer>();

        //RayLib::Texture& texture = assetManagerRef->getAssetFromName(renderer.getName()).getTexture();
        std::vector<std::reference_wrapper<IUIObject>> uiObjects = entity.OfType<IUIObject>();
        RayLib::Vector2<float> position = RayLib::Vector2<float>(transform.position.x, transform.position.y);
        RayLib::Vector2<float> scale = RayLib::Vector2<float>(transform.scale.x, transform.scale.y);

        _camera.EndMode();
        for (IUIObject& uiObject : uiObjects) {
            uiObject.Draw(position, assetManagerRef->getAssetFromName(renderer.getName()), scale);
        }
        _camera.BeginMode();
    }
}
