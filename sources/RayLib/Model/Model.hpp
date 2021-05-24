/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Model
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <raylib.h>
#include <string>
#include "Vector3.hpp"
#include "Color.hpp"

namespace RayLib
{
    class Model {
        public:
            Model(const std::string& fileName);
            ~Model();

            void DrawModel(Vector3 position, float scale, Color tint);
            void DrawModelEx(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);

        protected:
        private:
            ::Model _model;
    };
}

#endif /* !MODEL_HPP_ */
