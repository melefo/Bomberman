/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Text
*/

#include "Text.hpp"

namespace Prototype
{
    Text::Text(std::string startStr, RayLib::Font startFont, RayLib::Color startColor, unsigned int startSize)
    {
        string = startStr;
        font = startFont;
        color = startColor;
        size = startSize;
    }
}
