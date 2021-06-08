/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** BehaviourSystem
*/

#ifndef BEHAVIOURSYSTEM_HPP_
#define BEHAVIOURSYSTEM_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"
#include "IBehaviour.hpp"

namespace Component
{
    class BehaviourSystem : public ECS::ASystem {
        public:
            BehaviourSystem();
            ~BehaviourSystem() override = default;

            void Update(double dt, ECS::Entity &entity) override;
            void FixedUpdate(ECS::Entity &entity) override;
            void LateUpdate(double dt, ECS::Entity &entity) override;

        protected:
        private:
    };
}

#endif /* !BEHAVIOURSYSTEM_HPP_ */
