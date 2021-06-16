/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Animator
*/

#ifndef ANIMATOR_HPP_
#define ANIMATOR_HPP_

#include "IComponent.hpp"
#include "ModelAnimation.hpp"
#include "AssetManager.hpp"
#include <map>

namespace Component
{

    class Animator : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Animator object
             * @param assetName
             * @param stateName 
             */
            Animator(ECS::Entity& entity, const std::string& assetName, std::string stateName);
            /**
             * @brief Destroy the Animator object
             * 
             */
            ~Animator() = default;
            /**
             * @brief Construct a new Animator object
             * 
             * @param other 
             */
            Animator(const Animator& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return Animator& 
             */
            Animator& operator=(const Animator& other) = default;

            /**
             * @brief Set the State
             * 
             * @param state 
             */
            void SetState(const std::string& state);

            const std::string& GetState(void) const;

            /**
             * @brief Play animation at current state of statemachine
             * 
             * @param model 
             */
            void PlayCurrentState(RayLib::Model& model);

            const std::string &getName() const;

            std::ostream &operator<<(std::ostream &os) override {return os;};
            std::istream &operator>>(std::istream &is) override {return is;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};


        protected:
        private:
            std::string _currentState;
            std::string _name;
            ECS::Entity& _entity;
            Asset& _asset;
    };
}

#endif /* !ANIMATOR_HPP_ */
