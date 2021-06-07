/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Vector3
*/

#include "Vector3.hpp"

namespace RayLib
{

    Vector3::Vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3::Vector3(float newX)
    {
        x = newX;
        y = 0;
        z = 0;
    }

    Vector3::Vector3(float newX, float newY)
    {
        x = newX;
        y = newY;
        z = 0;
    }

    Vector3::Vector3(float newX, float newY, float newZ)
    {
        x = newX;
        y = newY;
        z = newZ;
    }

    Vector3::Vector3(const Vector3 &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    Vector3::Vector3(const ::Vector3 &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    ::Vector3 Vector3::getVector3(void)
    {
        ::Vector3 vec3 = {x, y, z};

        return (vec3);
    }

    Vector3& Vector3::operator=(const Vector3& vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return (*this);
    }

    Vector3& Vector3::operator+=(const Vector3& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return (*this);
    }

    Vector3 Vector3::operator+(const Vector3& vec)
    {
        Vector3 newVec = Vector3(x + vec.x, y + vec.y, z + vec.z);

        return (newVec);
    }

    Vector3 Vector3::operator-(const Vector3& vec)
    {
        Vector3 newVec = Vector3(x - vec.x, y - vec.y, z - vec.z);

        return (newVec);
    }


    Vector3 Vector3::operator*(const Vector3& vec)
    {
        Vector3 newVec = Vector3(x * vec.x, y * vec.y, z * vec.z);

        return (newVec);
    }

    Vector3 Vector3::operator*(const float factor)
    {
        Vector3 newVec = Vector3(x * factor, y * factor, z * factor);

        return (newVec);
    }

    Vector3& Vector3::operator*=(const float factor)
    {
        x *= factor;
        y *= factor;
        z *= factor;
        return (*this);
    }

    // todo smoothdamp
    // cf https://github.com/Unity-Technologies/UnityCsReference/blob/master/Runtime/Export/Math/Vector3.cs
    void Vector3::SmoothDamp(Vector3, float, float)
    {

    }

    void Vector3::Lerp(Vector3 target, float t)
    {
        if (t < 0)
            t = 0;
        if (t > 1)
            t = 1;
        x = x + (target.x - x) * t;
        y = y + (target.y - y) * t;
        z = z + (target.z - z) * t;
    }

    float Vector3::Distance(const Vector3 other)
    {
        float distance = sqrt(pow(static_cast<double>(x - other.x), 2.0) +
                              pow(static_cast<double>(y - other.y), 2.0) +
                              pow(static_cast<double>(z - other.z), 2.0));

        return (distance);
    }

}