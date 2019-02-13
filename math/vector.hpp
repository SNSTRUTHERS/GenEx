#ifndef MATH_VECTOR_HPP
#define MATH_VECTOR_HPP

#include "base.hpp"

namespace GenEx {
    namespace Math {

// --- VECTOR CLASS -------------------------------------------------------------------------------

        /** \brief A struct representing a mathematical vector
         *
         * \param unsigned int <u>N</u>: number of elements in this vector
         * \param typename <u>T</u>: numerical class to be used by the vector internally
         *
         */
        template <unsigned int N, typename T>
        struct Vector {
        private:
            T items[N];

            /** \brief Returns a copy of the data stored in this Vector
             *
             * \return T[] copy of the array storing this vector's data
             *
             */
            T *get_data() const {
                T *return_data = new T[N];
                for (unsigned int i = 0; i < N; i++) {
                    return_data[i] = items[i];
                }
                return return_data;
            }

            bool valid_size() const { return N > 1; }
        public:
            /** \brief Creates a new vector initialized with a specific value.
             *
             * \param T <u>init</u>: The value with which the vector's elements are to
             *       be initialized
             *
             */
            Vector(T init) {
                if (!valid_size()) {
                    std::string err = "Invalid vector size: " + std::to_string(N);
                    throw Error(err);
                }
                for (unsigned int i = 0; i < N; i++)
                    items[i] = init;
            }

            /** \brief Creates a new empty vector.
             */
            Vector() : Vector(0) { }

            /** \brief Creates a new vector from a list of values.
             *
             * \param <u>initlist</u>: an initializer list containing values to populate
             * this vector with
             *
             */
            Vector(std::initializer_list<T> initlist) {
                if (!valid_size()) {
                    std::string err = "Invalid vector size: " + std::to_string(N);
                    throw Error(err);
                }

                if (initlist.size() == 1) {
                    for (unsigned int i = 0; i < N; i++)
                        items[i] = *initlist.begin();
                } else if (initlist.size() <= N) {
                    for (auto iter = initlist.begin(); iter != initlist.end(); iter++)
                        items[(int)(iter - initlist.begin())] = *iter;
                }
            }

            /** \brief Copy constructor for Vector.
             *
             * \param Vector <u>other</u>: another vector
             *
             */
            Vector(const Vector<N,T> &other) {
                memcpy(items, other.items, sizeof(items));
            }

            /** \brief Copy constructor for Vector.
             *
             * \param Vector <u>other</u>: another vector
             *
             */
            Vector(Vector<N,T> &&other) {
                T *data = other.get_data();
                for (unsigned int i = 0; i < N; i++)
                    items[i] = data[i];
                delete[] data;
            }

// ------ OPERATORS -------------------------------------------------------------------------------

            /** \brief Assignment operator for Vector.
             * \param Vector <u>other</u>: another vector
             *
             */
            Vector<N,T> &operator= (const Vector<N,T> &other) {
                memcpy(items, other.items, sizeof(items));
                return *this;
            }

            /** \brief Assignment operator for Vector.
             * \param Vector <u>other</u>: another Vector
             *
             */
            Vector<N,T> &operator= (Vector<N,T> &&other) {
                T *data = other.get_data();
                for (unsigned int i = 0; i < N; i++)
                    items[i] = data[i];
                delete[] data;
                return *this;
            }

            /** \brief Assignment operator for Vector.
             * \param <u>initlist</u>: new values for to put in the Vector
             *
             */
            Vector<N,T> &operator= (std::initializer_list<T> initlist) {
                if (initlist.size() == 1) {
                    for (unsigned int i = 0; i < N; i++)
                        items[i] = *initlist.begin();
                } else if (initlist.size() <= N) {
                    for (auto iter = initlist.begin(); iter != initlist.end(); iter++)
                        items[(int)(iter - initlist.begin())] = *iter;
                }
                return *this;
            }

            /** \brief Equality operator with another Vector
             *
             * \param Vector <u>other</u>: another Vector
             * \return bool TRUE if all values in both Vectors are equivalent
             *
             */
            bool operator== (Vector<N,T> other) {
                //T *data = other.get_data();
                for (unsigned int i = 0; i < N; i++) {
                    if (absv(other[i] - items[i]) > FLT_EPSILON) {
                        //delete[] data;
                        return false;
                    }
                }
                //delete[] data;
                return true;
            }

            /** \brief Non-equality operator with another Vector
             *
             * \param Vector <u>other</u>: another Vector
             * \return bool FALSE if all values in both Vectors are equivalent
             *
             */
            bool operator!= (Vector<N,T> other) {
                return !(*this == other);
            }

            /** \brief Vector cast.
             *
             * \return Vector M-dimensional Vector using type U for values
             *
             */
            template <unsigned int M, typename U>
            operator Vector<M,U> () {
                Vector<M,U> vec;
                for (unsigned int i = 0; i < N && i < M; i++)
                    vec[i] = (U)items[i];
                return vec;
            }

            /** \brief Cast Vector to SDL_Point
             *
             * \return SDL_Point Point where {x, y} = {*this[0], *this[1]}
             *
             */
            operator SDL_Point () {
                return { (int)std::round(items[0]), (int)std::round(items[1]) };
            }

            /** \brief In-place vector addition.
             *
             * \param Vector <u>other</u>: Other vector to use for addition; Must be of the
             *       same size and type as this vector
             *
             */
            Vector<N,T> &operator+= (const Vector<N,T> &other) {
                for (unsigned int i = 0; i < N; i++)
                    items[i] += other[i];
                return *this;
            }

            /** \brief In-place vector addition.
             *
             * \param Vector <u>other</u>: Other vector to use for addition; Must be of the
             *       same size and type as this vector
             *
             */
            Vector<N,T> &operator+= (Vector<N,T> &&other) {
                for (unsigned int i = 0; i < N; i++)
                    items[i] += other[i];
                return *this;
            }

            /** \brief In-place vector subtraction.
             *
             * \param Vector <u>other</u>: Other vector to use for subtraction; Must be of
             *       the same size and type as this vector
             *
             */
            Vector<N,T> &operator-= (const Vector<N,T> &other) {
                for (unsigned int i = 0; i < N; i++)
                    items[i] -= other[i];
                return *this;
            }

            /** \brief In-place vector subtraction.
             *
             * \param Vector <u>other</u>: Other vector to use for subtraction; Must be of
             *       the same size and type as this vector
             *
             */
            Vector<N,T> &operator-= (Vector<N,T> &&other) {
                for (unsigned int i = 0; i < N; i++)
                    items[i] -= other[i];
                return *this;
            }

            /** \brief In-place scalar vector multiplication.
             *
             * \param T <u>scalar</u>: Value to use to scale the items in the vector
             *
             */
            Vector<N,T> &operator*= (T scalar) {
                for (unsigned int i = 0; i < N; i++)
                    items[i] *= scalar;
                return *this;
            }

            /** \brief In-place scalar vector division.
             *
             * \param T <u>scalar</u>: Value to use to scale the items in the vector
             *
             */
            Vector<N,T> &operator/= (T scalar) {
                for (unsigned int i = 0; i < N; i++)
                    items[i] /= scalar;
                return *this;
            }

            /** \brief Vector dot product.
             *
             * \param Vector <u>other</u>: Vector to calculate dot-product with
             *
             */
            T operator* (const Vector<N,T> &other) {
                T ret_val;
                for (unsigned int i = 0; i < N; i++)
                    ret_val += items[i]*other[i];
                return ret_val;
            }

            /** \brief Vector dot product.
             *
             * \param Vector <u>other</u>: Vector to calculate dot-product with
             *
             */
            T operator* (Vector<N,T> &&other) {
                T ret_val;
                for (unsigned int i = 0; i < N; i++)
                    ret_val += items[i]*other[i];
                return ret_val;
            }

            /** \brief Vector addition. Adds two vectors together into a new vector.
             *
             * \param Vector <u>other</u>: Another vector to add into this one;
             * \return Vector A new vector of the same size & type of this and the other
             *        vector containing the sums of the values of each
             *
             */
            Vector<N,T> operator+ (const Vector<N,T> &other) {
                Vector<N, T> ret_val(*this);
                return ret_val += other;
            }

            /** \brief Vector addition. Adds two vectors together into a new vector.
             *
             * \param Vector <u>other</u>: Another vector to add into this one;
             * \return Vector A new vector of the same size & type of this and the other
             *        vector containing the sums of the values of each
             *
             */
            Vector<N,T> operator+ (Vector<N,T> &&other) {
                Vector<N, T> ret_val(*this);
                return ret_val += other;
            }

            /** \brief Vector subtraction. Subtracts two vectors together into a new vector.
             *
             * \param Vector <u>other</u>: Another vector to subtract from this one;
             * \return Vector A new vector of the same size & type of this and the
             *        other vector containing the differences of the values of each
             *
             */
            Vector<N,T> operator- (const Vector<N,T> &other) {
                Vector<N, T> ret_val(*this);
                return ret_val -= other;
            }

            /** \brief Vector subtraction. Subtracts two vectors together into a new vector.
             *
             * \param Vector <u>other</u>: Another vector to subtract from this one;
             * \return Vector A new vector of the same size & type of this and the
             *        other vector containing the differences of the values of each
             *
             */
            Vector<N,T> operator- (Vector<N,T> &&other) {
                Vector<N, T> ret_val(*this);
                return ret_val -= other;
            }

            /** \brief Returns the item at the given index
             *
             * \param unsigned int <u>index</u>: Index into this vector
             * \return T& Reference to the item in the vector
             * \throw GenEx::Error if index is invalid
             *
             */
            T &operator[] (unsigned int index) {
                if (index >= N || index < 0) {
                    std::string err = "Invalid index into vector: " + std::to_string(index);
                    throw Error(err);
                }
                return items[index];
            }

            Vector<N,T> operator- () {
                Vector<N,T> ret_val;
                for (unsigned int i = 0; i < N; i++)
                    ret_val[i] = -items[i];
                return ret_val;
            }

// ------ FUNCTIONS -------------------------------------------------------------------------------

            /** \brief Returns the square of the values in this vector.
             *
             * \return T Square of the values in this vector
             *
             */
            T square() {
                T ret_val = 0;
                for (unsigned int i = 0; i < N; i++)
                    ret_val += items[i]*items[i];
                return ret_val;
            }

            /** \brief Returns the magnitude of this vector.
             *
             * \return T Magnitude of this vector
             *
             */
            T magnitude() {
                return SDL_sqrt(square());
            }

            /** \brief Normalizes this vector.
             */
            Vector<N,T> &normalize() {
                if (absv(magnitude()) < FLT_EPSILON ) {
                    return Vector<N,T>();
                }
                *this /= magnitude();
                return *this;
            }

            /** \brief Returns the distance between two vectors.
             *
             * \param Vector <u>other</u>: the vector you're trying to find the distance to
             * \return T Distance between this vector and the other
             *
             */
            T distance(const Vector<N,T> &other) {
                if (&other != this) {
                    Vector<N,T> n(*this);
                    n -= other;
                    return n.magnitude();
                }
                return 0;
            }

            /** \brief Returns the distance between two vectors.
             *
             * \param Vector <u>other</u>: the vector you're trying to find the distance to
             * \return T Distance between this vector and the other
             *
             */
            T distance(Vector<N,T> &&other) {
                if (&other != this) {
                    Vector<N,T> n(*this);
                    n -= other;
                    return n.magnitude();
                }
                return 0;
            }

            /** \brief Gets the size of the vector.
             *
             * \return unsigned int Size of the vector
             *
             */
            unsigned int size() const {
                return N;
            }
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
        Vector<N,T> operator* (Vector<N,T> &vec, T scalar) {
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
        Vector<N,T> operator* (T scalar, Vector<N,T> &vec) {
            return vec * scalar;
        }

        /** \brief Scalar vector division. Multiplies the values of this vector by a
         * constant scalar.
         *
         * \param Vector <u>vec</u>: The vector to divide
         * \param T <u>scalar</u>: Value from which scale the values of this vector
         * \return Vector A new vector of the same size & type of this one
         *        containing the each value in this one divided by the scalar
         *
         */
        template <unsigned int N, typename T>
        Vector<N,T> operator/ (Vector<N,T> &vec, T scalar) {
            Vector<N, T> ret_val;
            return ret_val /= scalar;
        }

        /** \brief Scalar vector division. Multiplies the values of this vector by a
         * constant scalar.
         *
         * \param Vector <u>vec</u>: The vector to divide
         * \param T <u>scalar</u>: Value from which scale the values of this vector
         * \return Vector A new vector of the same size & type of this one
         *        containing the each value in this one divided by the scalar
         *
         */
        template <unsigned int N, typename T>
        Vector<N,T> operator/ (T scalar, Vector<N,T> &vec) {
            return vec / scalar;
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
        Vector<3,T> CrossProduct3D(Vector<3,T> &v1, Vector<3,T> &v2) {
            return Vector<3,T>{
                v1[1]*v2[2] - v1[2]*v2[1],
                v1[2]*v2[0] - v1[0]*v2[2],
                v1[0]*v2[1] - v1[1]*v2[0]
            };
        }

        /** \brief Returns the vector cross product of two 2D vectors.
         *
         * \param Vector <u>v1</u>: A 2D vector
         * \param Vector <u>v2</u>: A 2D vector
         * \return T The cross product of <i>v1</i> and <i>v2</i>
         *
         */
        template<typename T>
        T CrossProduct2D(Vector<2,T> &v1, Vector<2,T> &v2) {
            return v1[0]*v2[1] - v1[1]*v2[0];
        }

        /** \brief Returns the orthogonal vector of a given 2D vector.
         *
         * \param Vector <u>vec</u>: A 2D vector
         * \return Vector The orthogonal vector of <i>vec</i>
         *
         */
        template<typename T>
        Vector<2,T> OrthoVector2D(Vector<2,T> &vec) {
            return Vector<2,T>{-vec[1], vec[0]};
        }

        /** \brief Rotates the vector by <i>angle</i> degrees.
         *
         * \param Vector <u>vec</u>: The vector you want to rotate
         * \param double <u>angle</u>: The angle in degrees
         * \return Vector The rotated vector
         *
         */
        template<typename T>
        Vector<2,T> RotateVector2D(Vector<2,T> &vec, double angle) {
            double rad = DegreesToRadians(angle);
            return Vector<2,T>{
                vec[0]*SDL_cos(rad) - vec[1]*SDL_sin(rad),
                vec[0]*SDL_sin(rad) - vec[1]*SDL_cos(rad)
            };
        }

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
        Vector<2,T> GetMidpoint2D(Vector<2,T> v1, Vector<2,T> v2, T t = 0.5) {
            return Vector<2,T>{ (v2[0]-v1[0])*t + v1[0],
                                (v2[1]-v1[1])*t + v1[1] };
        }

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
    std::string to_string(GenEx::Math::Vector<N,T> &_vec) {
        std::stringstream sst;
        sst << '[';
        for (unsigned int i = 0; i < N-1; i++) sst << _vec[i] << ", ";
        sst << _vec[N-1] << ']';
        return sst.str();
    }
}

#endif // MATH_VECTOR_HPP
