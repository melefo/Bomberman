/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** ModelShader
*/

#ifndef CUSTOMSHADER_HPP_
#define CUSTOMSHADER_HPP_

#include "IComponent.hpp"

namespace Component {
    class ModelShader : public ECS::IComponent {
        public:
            ModelShader(const std::string shaderPath);
            ~ModelShader() = default;

            virtual void Update() = 0;

            std::ostream &operator<<(std::ostream &os) override;
            std::istream &operator>>(std::istream &is) override;
            boost::property_tree::ptree& operator<<(boost::property_tree::ptree &ptree) override;

        protected:
        private:
    };
}

#endif /* !CUSTOMSHADER_HPP_ */