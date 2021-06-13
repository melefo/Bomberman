/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** GameConfigurator
*/

#include "GameConfigurator.hpp"

namespace Component
{

    GameConfigurator::GameConfigurator() : _window(RayLib::Window::GetInstance(RayLib::Vector2<int>(), ""))
    {

    }

    void GameConfigurator::Update(double, ECS::Entity&)
    {
        int count = 0;
        // dans le constructeur

        // if drag n drop
        if (_window->IsFileDropped())
        {
            std::vector<std::string> droppedFiles = _window->GetDroppedFiles(&count);
            // open file
            std::ifstream myfile(droppedFiles[0]);

            std::stringstream buffer;
            buffer << myfile.rdbuf();

            std::istringstream iss;
            iss.str(buffer.str());
            myfile.close();

            //std::cout << iss.str() << std::endl;
            std::cout << "Dropped file: " << droppedFiles[0] << std::endl;

            // ! comment trier entity/script ?
                // ! ouvrir, find node script/Entity
            //Serialization::EntityLoader::LoadEntity(iss);
            Serialization::EntityLoader::LoadEntities(iss);

            _window->ClearDroppedFiles();
        }
    }

    void GameConfigurator::FixedUpdate(ECS::Entity&)
    {

    }

    void GameConfigurator::LateUpdate(double, ECS::Entity&)
    {

    }

    void GameConfigurator::SaveMap(void)
    {
        // open a file called map.xml
        std::ofstream file("./map.xml", std::ofstream::trunc | std::ofstream::out);

        // get coordinator
        std::unique_ptr<ECS::Coordinator>& coordinator = ECS::Coordinator::GetInstance();
        // get entities
        const std::list<std::unique_ptr<ECS::Entity>>& entities = coordinator->GetEntities();
        std::ostringstream oss;

        for (auto it = entities.begin(); it != entities.end(); it++) {
            if (it->get()->GetTag() != "Wall" && it->get()->GetTag() != "Box")
                continue;
            std::vector<std::reference_wrapper<std::unique_ptr<IComponent>>> components = it->get()->GetComponents();
            oss << "<Entity>";
            for (auto cmp = components.begin(); cmp != components.end(); cmp++) {
                IXMLSerializable& obj = *cmp->get();
                oss << obj;
            }
            oss << "</Entity>";
        }
        file << "<Entities>";
        file << oss.str();
        file << "</Entities>";
        file.close();
    }
}