/**
 * \file math.hpp
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
 * The header file for general math-related functions & classes.
 *
 */

#ifndef MATH_HPP
#define MATH_HPP

#include <cfloat>
#include <cmath>

#define fracofnum(x) ((x>0) ? (x - ((int)x)) : x - (((int)x)+1))
#define freciprocal(x) (1 - ((x>0) ? (x - ((int)x)) : x - (((int)x)+1)))

namespace GenEx {
    namespace Math {
        static const double PI = 3.1415926535897932384626433832795;

        /** \brief Converts from degrees to radians.
         *
         * \param double <u>deg</u>: Angle in degrees
         * \return double Angle in radians
         *
         */
        double DegreesToRadians(double deg);

        /** \brief Converts from radians to degrees.
         *
         * \param double <u>rad</u>: Angle in radians
         * \return double Angle in degrees
         *
         */
        double RadiansToDegrees(double rad);
    }
}

#include "math/vector.hpp"
#include "math/bezier.hpp"
#include "math/transform.hpp"

#endif // MATH_HPP
