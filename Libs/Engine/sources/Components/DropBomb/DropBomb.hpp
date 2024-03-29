/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** DropBomb
*/

#ifndef DROPBOMB_HPP_
#define DROPBOMB_HPP_

#include "IBehaviour.hpp"
#include "Input.hpp"
#include "PhysicsBody.hpp"
#include "Entity.hpp"
#include "Collider.hpp"
#include "Explosion.hpp"
#include "SquareCollider.hpp"
#include "Transform.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Destructible.hpp"

namespace Component
{
    /**
     * @brief Behaviour for players or AI allowing to drop a bomb upon pressing a key
     * 
     */
    class DropBomb : public ECS::IComponent {
        public:
            /**
             * @brief Construct a new Drop Bomb object
             * 
             * @param attatchedEntity 
             * @param coordinator 
             * @param dropBombKey Key to press
             * @param dropDelay Cooldown for bomb-dropping
             */
            DropBomb(ECS::Entity& self, float dropDelay=2.5f, float minDelay = 1.0f, float maxBombs = 5.0f);
            /**
             * @brief Destroy the Drop Bomb object
             * 
             */
            ~DropBomb() override = default;
            /**
             * @brief Construct a new Drop Bomb object
             * 
             * @param other 
             */
            DropBomb(const DropBomb& other) = default;
            /**
             * @brief 
             * 
             * @param other 
             * @return DropBomb& 
             */
            DropBomb& operator=(const DropBomb& other) = default;

            /**
             * @brief Function to create a bomb, belongs in an entity factory
             * 
             * @param position 
             * @param explosionType 
             * @param radius 
             */
            void InstantiateBomb(RayLib::Vector3 position,
                                 Explosion::ExplosionType explosionType=Explosion::ExplosionType::CIRCLE);

            /**
             * @brief Create a bomb
             * 
             */
            ECS::Entity& CreateBomb(ECS::Coordinator& coordinator, float radius, Explosion::ExplosionType type);

            /**
             * @brief Get the cross size
             * 
             * @return int 
             */
            int GetBombNumber();

            /**
             * @brief Get the time of the range bonus
             * 
             * @return float&
             * 
             */
            float &GetBonusTimeRange();

            /**
             * @brief Get the time of the cooldown bonus
             * 
             * @return float&
             * 
             */
            float &GetBonusTimeCoolDown();

            /**
             * @brief Add bonusBombs to be dropped, for duration seconds
             * 
             * @param bonusBombs 
             * @param duration 
             */
            void BoostBombNumber(int bonusBombs, float duration);
            /**
             * @brief SetBombCooldown to bonusTime, for duration seconds
             * 
             * @param bonusTime 
             * @param duration 
             */
            void BoostBombCooldown(float bonusTime, float duration);

            /**
             * @brief Get the Drop Delay object
             * 
             * @return float 
             */
            float GetDropDelay(void);

            std::ostream &operator<<(std::ostream &os) override {return os;};
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override {return ptree;};

            /**
             * @brief Called to regulate bonus time
             * 
             */
            void Update();

            /**
             * @brief Round a float to a multiple of 10
             * 
             * @param num 
             * @return int 
             */
            int RoundToNearest10(float num);

            /**
             * @brief Cooldown timer
             * 
             */
            float timeToDrop;
        protected:
        private:

            /**
             * @brief Singleton coordinator reference (instantiation)
             * 
             */
            std::unique_ptr<ECS::Coordinator>& _coordinator;

            /**
             * @brief Reference to window singleton to get frametime
             * 
             */
            std::unique_ptr<RayLib::Window>& _window;

            int _bombNumber;
            int _defaultBombNumber;
            // ! appliqué aux deux bonus possibles...
            float _bonusTimeRange;
            float _bonusTimeCoolDown;
            float _defaultDropDelay;
            /**
             * @brief Bomb cooldown
             * 
             */
            float _dropDelay;

            float _minDelay;
            float _maxBombs;

            ECS::Entity& _self;
    };
}

#endif /* !DROPBOMB_HPP_ */
