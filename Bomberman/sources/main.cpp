/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic [WSL: Ubuntu]
** File description:
** main
*/

#include <iostream>
#include "Coordinator.hpp"
#include "Transform.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"
#include "BehaviourSystem.hpp"
#include "UISystem.hpp"
#include "CollisionSystem.hpp"
#include "Movement.hpp"
#include "DropBomb.hpp"
#include "Button.hpp"
#include "ButtonCallbacks.hpp"
#include "Draggable.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "GameConfigurator.hpp"
#include "Scenes.hpp"
#include "PlayerInputs.hpp"
#include "TerrainGenerator.hpp"
#include "AudioDevice.hpp"
#include "Physics2D.hpp"

#define BOX_SIZE 10

int main(void)
{
    std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();

    //! camera pos and target determined by component
    //! attention le 3e arg: world up est important
    RayLib::Camera3D camera = RayLib::Camera3D(RayLib::Vector3(0.0f, 10.0f, 10.0f), RayLib::Vector3(), RayLib::Vector3(0.0f, 1.0f, 0.0f));
    std::unique_ptr<RayLib::Window>& window = RayLib::Window::GetInstance(RayLib::Vector2<int>(1920, 1000), "Bomberman");

    RayLib::AudioDevice::InitAudioDevice();

    //! game manager for drag and drop


    Engine::GameConfiguration::SetPlayers(3);
    RayLib::Input player1Input(RayLib::Vector2<int>(KEY_RIGHT, KEY_LEFT), RayLib::Vector2<int>(KEY_DOWN, KEY_UP));

    Engine::GameConfiguration::SetPlayerKeys(1, player1Input, KEY_ENTER);

    RayLib::Input player2Input(RayLib::Vector2<int>(KEY_J, KEY_G), RayLib::Vector2<int>(KEY_H, KEY_Y));
    Engine::GameConfiguration::SetPlayerKeys(2, player2Input, KEY_SPACE);

    RayLib::Input player3Input;
    Engine::GameConfiguration::SetPlayerKeys(3, player3Input, KEY_E);

    Engine::GameConfiguration::SetDebugMode(false);

    Engine::GameConfiguration::SetIA(2);

    coordinator->AddSystem<Component::PhysicsSystem>();
    coordinator->AddSystem<Component::UISystem>(camera);
    coordinator->AddSystem<Component::RenderSystem>();
    coordinator->AddSystem<Component::BehaviourSystem>();


    window->SetTargetFPS(60);
    window->SetExitKey(KEY_ESCAPE);
    while (!window->WindowShouldClose() && !coordinator->CloseWindow)
    {
        if (coordinator->GetEntities().size() == 0) {
            Scenes::scenesCtor[coordinator->getCurrentScene()](*coordinator.get(), camera);
        }
        
        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);

        camera.BeginMode();

        //assetManagerRef->lock();
        //bool isLoaded = assetManagerRef->getLoadStatus().isReady;
        //assetManagerRef->unlock();
        //if (isLoaded)
        coordinator->Run();
        //else
        //    Display the loading screen scene

        camera.EndMode();
        window->EndDrawing();
    }
    RayLib::AudioDevice::CloseAudioDevice();
    return (0);
}
