#ifndef MATH_HPP
#define MATH_HPP

#include "base.hpp"
#include <cfloat>
#include <cmath>

namespace GenEx {
    namespace Math {
        static const double PI = 3.1415926535897932384626433832795;

        /** \brief Converts from degrees to radians.
         *
         * \param double <u>deg</u>: Angle in degrees
         * \return double Angle in radians
         *
         */
        double DegreesToRadians(double deg) {
            return deg * (PI / 180.0);
        }

        /** \brief Converts from radians to degrees.
         *
         * \param double <u>rad</u>: Angle in radians
         * \return double Angle in degrees
         *
         */
        double RadiansToDegrees(double rad) {
            return rad * (180.0 / PI);
        }
    }
}

#include "math/vector.hpp"
#include "math/bezier.hpp"

#endif // MATH_HPP
