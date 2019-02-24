/**
 * \file math/vector.hpp
 *
 * \author Simon Struthers <snstruthers@gmail.com>
 * \version pre_dev v0.1.0
 *
 * \section LICENSE
 * GenEx (short for General Executor) - window manager and runtime environment.
 * Copyright (C) 2019 | The GenEx Project
 *
 * This file is part of GenEx.
 *
 * GenEx is free software: you can redistribute it and/or modify it under the terms of the GNU
 * General Public License version 2 as published by the Free Software Foundation.
 *
 * GenEx is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at https://www.gnu.org/copyleft/gpl.html
 *
 * You should have received a copy of the GNU General Public License version 2 along with GenEx.
 * If not, see http://www.gnu.org/licenses.
 *
 * \section DESCRIPTION
 * The header file defining a mathematical N-dimensional Vector class.
 *
 */

#ifndef MATH_VECTOR_HPP
#define MATH_VECTOR_HPP

#include "base.hpp"

namespace GenEx {
    namespace Math {

// --- VECTOR CLASS -------------------------------------------------------------------------------

        /** \brief A class representing a mathematical vector
         *
         * \param unsigned int <u>N</u>: number of elements in this vector
         * \param typename <u>T</u>: numerical class to be used by the vector internally
         *
         */
        template <unsigned int N, typename T>
        class Vector {
        private:
            T items[N];

            /** \brief Returns a copy of the data stored in this Vector
             *
             * \return T[] copy of the array storing this vector's data
             *
             */
            T *get_data() const;

            bool valid_size() const;

            T get_item(const unsigned int index) const;
        public:
            /** \brief Creates a new vector initialized with a specific value.
             *
             * \param T <u>init</u>: The value with which the vector's elements are to
             *       be initialized
             *
             */
            Vector(T init);

            /** \brief Creates a new empty vector.
             */
            Vector();

            /** \brief Creates a new vector from a list of values.
             *
             * \param <u>initlist</u>: an initializer list containing values to populate
             * this vector with
             *
             */
            Vector(std::initializer_list<T> initlist);

            /** \brief Copy constructor for Vector.
             *
             * \param Vector <u>other</u>: another vector
             *
             */
            Vector(const Vector<N,T> &other);

            /** \brief Copy constructor for Vector.
             *
             * \param Vector <u>other</u>: another vector
             *
             */
            Vector(Vector<N,T> &&other);

// ------ OPERATORS -------------------------------------------------------------------------------

            /** \brief Assignment operator for Vector.
             * \param Vector <u>other</u>: another vector
             *
             */
            Vector<N,T> &operator= (const Vector<N,T> &other);

            /** \brief Assignment operator for Vector.
             * \param Vector <u>other</u>: another Vector
             *
             */
            Vector<N,T> &operator= (Vector<N,T> &&other);

            /** \brief Assignment operator for Vector.
             * \param <u>initlist</u>: new values for to put in the Vector
             *
             */
            Vector<N,T> &operator= (std::initializer_list<T> initlist);

            /** \brief Equality operator with another Vector
             *
             * \param Vector <u>other</u>: another Vector
             * \return bool TRUE if all values in both Vectors are equivalent
             *
             */
            bool operator== (const Vector<N,T> &other) const;

            /** \brief Equality operator with another Vector
             *
             * \param Vector <u>other</u>: another Vector
             * \return bool TRUE if all values in both Vectors are equivalent
             *
             */
            bool operator== (Vector<N,T> &&other);

            /** \brief Non-equality operator with another Vector
             *
             * \param Vector <u>other</u>: another Vector
             * \return bool FALSE if all values in both Vectors are equivalent
             *
             */
            bool operator!= (const Vector<N,T> &other) const;

            /** \brief Non-equality operator with another Vector
             *
             * \param Vector <u>other</u>: another Vector
             * \return bool FALSE if all values in both Vectors are equivalent
             *
             */
            bool operator!= (Vector<N,T> &&other);

            /** \brief Vector cast.
             *
             * \return Vector M-dimensional Vector using type U for values
             *
             */
            template <unsigned int M, typename U> operator Vector<M,U> ();

            /** \brief Cast Vector to SDL_Point
             *
             * \return SDL_Point Point where {x, y} = {*this[0], *this[1]}
             *
             */
            operator SDL_Point ();

            /** \brief In-place vector addition.
             *
             * \param Vector <u>other</u>: Other vector to use for addition; Must be of the
             *       same size and type as this vector
             *
             */
            Vector<N,T> &operator+= (const Vector<N,T> &other);

            /** \brief In-place vector addition.
             *
             * \param Vector <u>other</u>: Other vector to use for addition; Must be of the
             *       same size and type as this vector
             *
             */
            Vector<N,T> &operator+= (Vector<N,T> &&other);

            /** \brief In-place vector subtraction.
             *
             * \param Vector <u>other</u>: Other vector to use for subtraction; Must be of
             *       the same size and type as this vector
             *
             */
            Vector<N,T> &operator-= (const Vector<N,T> &other);

            /** \brief In-place vector subtraction.
             *
             * \param Vector <u>other</u>: Other vector to use for subtraction; Must be of
             *       the same size and type as this vector
             *
             */
            Vector<N,T> &operator-= (Vector<N,T> &&other);

            /** \brief In-place scalar vector multiplication.
             *
             * \param T <u>scalar</u>: Value to use to scale the items in the vector
             *
             */
            Vector<N,T> &operator*= (T scalar);

            /** \brief In-place scalar vector division.
             *
             * \param T <u>scalar</u>: Value to use to scale the items in the vector
             *
             */
            Vector<N,T> &operator/= (T scalar);

            /** \brief Vector dot product.
             *
             * \param Vector <u>other</u>: Vector to calculate dot-product with
             *
             */
            T operator* (const Vector<N,T> &other);

            /** \brief Vector dot product.
             *
             * \param Vector <u>other</u>: Vector to calculate dot-product with
             *
             */
            T operator* (Vector<N,T> &&other);

            /** \brief Vector addition. Adds two vectors together into a new vector.
             *
             * \param Vector <u>other</u>: Another vector to add into this one;
             * \return Vector A new vector of the same size & type of this and the other
             *        vector containing the sums of the values of each
             *
             */
            Vector<N,T> operator+ (const Vector<N,T> &other) const;

            /** \brief Vector addition. Adds two vectors together into a new vector.
             *
             * \param Vector <u>other</u>: Another vector to add into this one;
             * \return Vector A new vector of the same size & type of this and the other
             *        vector containing the sums of the values of each
             *
             */
            Vector<N,T> operator+ (Vector<N,T> &&other);

            /** \brief Vector subtraction. Subtracts two vectors together into a new vector.
             *
             * \param Vector <u>other</u>: Another vector to subtract from this one;
             * \return Vector A new vector of the same size & type of this and the
             *        other vector containing the differences of the values of each
             *
             */
            Vector<N,T> operator- (const Vector<N,T> &other) const;

            /** \brief Vector subtraction. Subtracts two vectors together into a new vector.
             *
             * \param Vector <u>other</u>: Another vector to subtract from this one;
             * \return Vector A new vector of the same size & type of this and the
             *        other vector containing the differences of the values of each
             *
             */
            Vector<N,T> operator- (Vector<N,T> &&other);

            /** \brief Scalar vector division. Divides the values of this vector by a
             * constant scalar.
             *
             * \param T <u>scalar</u>: Value from which scale the values of this vector
             * \return Vector A new vector of the same size & type of this one
             *        containing the each value in this one divided by the scalar
             *
             */
            Vector<N,T> operator/ (T scalar);

            /** \brief Returns the item at the given index
             *
             * \param unsigned int <u>index</u>: Index into this vector
             * \return T& Reference to the item in the vector
             * \throw GenEx::Error if index is invalid
             *
             */
            T &operator[] (unsigned int index);

            /** \brief Vector negation. Flips the signs of the values in this vector.
             */
            Vector<N,T> operator- ();

// ------ FUNCTIONS -------------------------------------------------------------------------------

            /** \brief Returns the square of the values in this vector.
             *
             * \return T Square of the values in this vector
             *
             */
            T square();

            /** \brief Returns the magnitude of this vector.
             *
             * \return T Magnitude of this vector
             *
             */
            T magnitude();

            /** \brief Normalizes this vector.
             */
            Vector<N,T> &normalize();

            /** \brief Returns the distance between two vectors.
             *
             * \param Vector <u>other</u>: the vector you're trying to find the distance to
             * \return T Distance between this vector and the other
             *
             */
            T distance(const Vector<N,T> &other);

            /** \brief Returns the distance between two vectors.
             *
             * \param Vector <u>other</u>: the vector you're trying to find the distance to
             * \return T Distance between this vector and the other
             *
             */
            T distance(Vector<N,T> &&other);

            /** \brief Gets the size of the vector.
             *
             * \return unsigned int Size of the vector
             *
             */
            unsigned int size() const;
        };

// --- VECTOR L/R OPERATORS -----------------------------------------------------------------------

        /** \brief Scalar vector multiplication. Multiplies the values of this vector
         *       by a constant scalar.
         *
         * \param Vector <u>vec</u>: The vector to multiply
         * \param T <u>scalar</u>: Value from which scale the values of this vector
         * \return Vector A new vector of the same size & type of this one
         *        containing the each value in this one multiplied by the scalar
         *
         */
        template <unsigned int N, typename T>
        Vector<N,T> operator* (const Vector<N,T> &vec, T scalar) {
            Vector<N, T> ret_val(vec);
            return ret_val *= scalar;
        }

        /** \brief Scalar vector multiplication. Multiplies the values of this vector
         *       by a constant scalar.
         *
         * \param Vector <u>vec</u>: The vector to multiply
         * \param T <u>scalar</u>: Value from which scale the values of this vector
         * \return Vector A new vector of the same size & type of this one
         *        containing the each value in this one multiplied by the scalar
         *
         */
        template <unsigned int N, typename T>
        Vector<N,T> operator* (T scalar, const Vector<N,T> &vec) {
            return vec * scalar;
        }

// --- VECTOR HELPER FUNCTIONS --------------------------------------------------------------------

        /** \brief Returns the vector cross product of two 3D vectors.
         *
         * \param Vector <u>v1</u>: A 3D vector
         * \param Vector <u>v2</u>: A 3D vector
         * \return Vector The cross product of <i>v1</i> and <i>v2</i>
         *
         */
        template<typename T>
        Vector<3,T> CrossProduct3D(Vector<3,T> &v1, Vector<3,T> &v2);

        /** \brief Returns the vector cross product of two 2D vectors.
         *
         * \param Vector <u>v1</u>: A 2D vector
         * \param Vector <u>v2</u>: A 2D vector
         * \return T The cross product of <i>v1</i> and <i>v2</i>
         *
         */
        template<typename T>
        T CrossProduct2D(Vector<2,T> &v1, Vector<2,T> &v2);

        /** \brief Returns the orthogonal vector of a given 2D vector.
         *
         * \param Vector <u>vec</u>: A 2D vector
         * \return Vector The orthogonal vector of <i>vec</i>
         *
         */
        template<typename T>
        Vector<2,T> OrthoVector2D(Vector<2,T> &vec);

        /** \brief Rotates the vector by <i>angle</i> degrees.
         *
         * \param Vector <u>vec</u>: The vector you want to rotate
         * \param double <u>angle</u>: The angle in degrees
         * \return Vector The rotated vector
         *
         */
        template<typename T>
        Vector<2,T> RotateVector2D(Vector<2,T> &vec, double angle);

        /** \brief Gets the midpoint between two 2D Vectors
         *
         * \param Vector <u>v1</u>: First 2D Vector
         * \param Vector <u>v2</u>: Second 2D Vector
         * \param T <u><i>t</i></u>: place on the line segment; defaults to 0.5 for midpoint;
         *        can be between 0.0 for start point, 1.0 for end point
         * \return Vector Point on the line between the two vectors
         *
         */
        template<typename T>
        Vector<2,T> GetMidpoint2D(Vector<2,T> &v1, Vector<2,T> &v2, T t);

// --- VECTOR ALIASES -----------------------------------------------------------------------------

        /** \brief 2D Vector using floats
         */
        typedef Vector<2, float> Vector2F;

        /** \brief 2D Vector using doubles
         */
        typedef Vector<2, double> Vector2;

        /** \brief 2D Vector using long doubles
         */
        typedef Vector<2, long double> Vector2L;

        /** \brief 3D Vector using floats
         */
        typedef Vector<3, float> Vector3F;

        /** \brief 3D Vector using doubles
         */
        typedef Vector<3, double> Vector3;

        /** \brief 3D Vector using long doubles
         */
        typedef Vector<3, long double> Vector3L;
    }
}

namespace std {
    template<unsigned int N, typename T>
    std::string to_string(GenEx::Math::Vector<N,T> &_vec);
}

#endif // MATH_VECTOR_HPP
