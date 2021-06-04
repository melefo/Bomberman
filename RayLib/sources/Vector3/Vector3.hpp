/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Vector3
*/

#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <raylib.h>

namespace RayLib
{
    /**
     * @brief Vector3 encapsulation
     * 
     */
    class Vector3
    {
        public:
            /**
             * @brief Construct a new Vector 3
             * Initialize values to zero
             */
            Vector3();

            /**
             * @brief Construct a new Vector 3 object
             * 
             * @param x initialize x parameter
             */
            Vector3(float x);

            /**
             * @brief Construct a new Vector 3 object
             * 
             * @param x initialize x parameter
             * @param y initialize y parameter
             */
            Vector3(float x, float y);

            /**
             * @brief Construct a new Vector 3 object
             * 
             * @param x initialize x parameter
             * @param y initialize y parameter
             * @param z initialize z parameter
             */
            Vector3(float x, float y, float z);

            /**
             * @brief Construct a new Vector 3 object
             * 
             * @param vec 
             */
            Vector3(const Vector3 &vec);

            /**
             * @brief Construct a new Vector 3 object
             * 
             * @param vec 
             */
            Vector3(const ::Vector3 &vec);

            ~Vector3() = default;

            /**
             * @brief Get the Vector3 as a raylib structure
             * 
             * @return ::Vector3
             */
            ::Vector3 getVector3(void);

            /**
             * @brief Assignment operator
             * 
             * @param vector3 
             * @return Vector3& 
             */
            Vector3 &operator=(const Vector3& vector3);

            /**
             * @brief Multiply vector by factor
             * 
             * @param factor 
             * @return Vector3& 
             */
            Vector3 &operator*=(const float factor);

            /**
             * @brief Add two vectors
             * 
             * @param vector3 
             * @return Vector3& 
             */
            Vector3 &operator+=(const Vector3& vector3);

            /**
             * @brief Add two vectors
             * 
             * @param vec 
             * @return Vector3 
             */
            Vector3 operator+(const Vector3& vec);

            /**
             * @brief Subtract vector
             * 
             * @param vec 
             * @return Vector3 
             */
            Vector3 operator-(const Vector3& vec);

            /**
             * @brief Multiply each parameter by other corresponding parameters
             * 
             * @param vec 
             * @return Vector3 
             */
            Vector3 operator*(const Vector3& vec);

            /**
             * @brief Multiply vector parameters by factor
             * 
             * @param factor 
             * @return Vector3 
             */
            Vector3 operator*(const float factor);

            /**
             * @brief Return the distance to other vector
             * 
             * @param other 
             * @return float 
             */
            float Distance(const Vector3 other);

            float x;
            float y;
            float z;
        protected:
        private:
    };
}

#endif /* !VECTOR3_HPP_ */
