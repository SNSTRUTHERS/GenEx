/**
 * \file math/transform.hpp
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
 * The header file defining various transform operations for 2D & 3D points.
 *
 */

#ifndef MATH_TRANSFORM_HPP
#define MATH_TRANSFORM_HPP

#include "base.hpp"

namespace GenEx {
    namespace Math {

        /** \brief Translates a set of points by a certain amount.
         *
         * \param std::vector<SDL_Point> &<u>points</u>: Reference to a vector of points to
         *        transform
         * \param int <u>dx</u>: Displacement X
         * \param int <u>dy</u>: Displacement Y
         *
         */
        void TranslateSDL(std::vector<SDL_Point> &points, int dx, int dy);

        /** \brief Translates a set of points by a certain amount.
         *
         * \param std::vector<Vector> &<u>points</u>: Reference to a vector of 2D Vectors to
         *        transform
         * \param int <u>dx</u>: Displacement X
         * \param int <u>dy</u>: Displacement Y
         *
         */
        template <typename T>
        void Translate2D(std::vector< Vector<2,T> > &points, int dx, int dy);

        /** \brief Translates a set of points by a certain amount.
         *
         * \param std::vector<Vector> &<u>points</u>: Reference to a vector of 3D Vectors to
         *        transform
         * \param int <u>dx</u>: Displacement X
         * \param int <u>dy</u>: Displacement Y
         * \param int <u>dz</u>: Displacement Z
         *
         */
        template <typename T>
        void Translate3D(std::vector< Vector<3,T> > &points, int dx, int dy, int dz);

        /** \brief Rotates a set of points around a center point.
         *
         * \param std::vector<SDL_Point> &<u>points</u>: Reference to a vector of points to
         *        transform
         * \param float <u>angle</u>: How many radians to rotate the points
         * \param int <u>cx</u>: Center X
         * \param int <u>cy</u>: Center Y
         *
         */
        void RotateSDL(std::vector<SDL_Point> &points, float angle, int cx, int cy);

        /** \brief Rotates a set of points around the origin.
         *
         * \param std::vector<SDL_Point> &<u>points</u>: Reference to a vector of points to
         *        transform
         * \param float <u>angle</u>: How many radians to rotate the points
         *
         */
        void RotateSDL(std::vector<SDL_Point> &points, float angle);

        /** \brief Rotates a set of points around a center point.
         *
         * \param std::vector<Vector> &<u>points</u>: Reference to a vector of 2D Vectors to
         *        transform
         * \param float <u>angle</u>: How many radians to rotate the points
         * \param T <u>cx</u>: Center X
         * \param T <u>cy</u>: Center Y
         *
         */
        template <typename T>
        void Rotate2D(std::vector< Vector<2,T> > &points, float angle, T cx, T cy);

        /** \brief Rotates a set of points around the origin.
         *
         * \param std::vector<Vector> &<u>points</u>: Reference to a vector of 2D Vectors to
         *        transform
         * \param float <u>angle</u>: How many radians to rotate the points
         *
         */
        template <typename T>
        void Rotate2D(std::vector< Vector<2,T> > &points, float angle);

        /** \brief Rotates a set of points around a center point.
         *
         * \param std::vector<Vector> &<u>points</u>: Reference to a vector of 3D Vectors to
         *        transform
         * \param float <u>pitch</u>: Radians to rotate in the pitch direction
         * \param float <u>roll</u>: Radians to rotate in the roll direction
         * \param float <u>yaw</u>: Radians to rotate in the yaw direction
         * \param T <u>cx</u>: Center X
         * \param T <u>cy</u>: Center Y
         * \param T <u>cz</u>: Center Z
         *
         */
        template <typename T>
        void Rotate3D(std::vector< Vector<3,T> > &points, float pitch, float roll, float yaw,
                      T cx, T cy, T cz);

        /** \brief Rotates a set of points around the origin.
         *
         * \param std::vector<Vector> &<u>points</u>: Reference to a vector of 3D Vectors to
         *        transform
         * \param float <u>pitch</u>: Radians to rotate in the pitch direction
         * \param float <u>roll</u>: Radians to rotate in the roll direction
         * \param float <u>yaw</u>: Radians to rotate in the yaw direction
         *
         */
        template <typename T>
        void Rotate3D(std::vector< Vector<3,T> > &points, float pitch, float roll, float yaw);

        /** \brief Scales a set of points from a center point.
         *
         * \param std::vector<SDL_Point> &<u>points</u>: Reference to a vector of points to
         *        transform
         * \param float <u>angle</u>: How much to scale the points; 1.0 for no change
         * \param int <u>cx</u>: Center X
         * \param int <u>cy</u>: Center Y
         *
         */
        void ScaleSDL(std::vector<SDL_Point> &points, float scale, int cx, int cy);

        /** \brief Scales a set of points from the origin.
         *
         * \param std::vector<SDL_Point> &<u>points</u>: Reference to a vector of points to
         *        transform
         * \param float <u>angle</u>: How much to scale the points; 1.0 for no change
         *
         */
        void ScaleSDL(std::vector<SDL_Point> &points, float scale);

        /** \brief Scales a set of points from a center point.
         *
         * \param std::vector<Vector> &<u>points</u>: Reference to a vector of 2D Vectors to
         *        transform
         * \param T <u>angle</u>: How much to scale the points; 1.0 for no change
         * \param T <u>cx</u>: Center X
         * \param T <u>cy</u>: Center Y
         *
         */
        template <typename T>
        void Scale2D(std::vector< Vector<2,T> > &points, T scale, T cx, T cy);

        /** \brief Scales a set of points from the origin.
         *
         * \param std::vector<Vector> &<u>points</u>: Reference to a vector of 2D Vectors to
         *        transform
         * \param T <u>angle</u>: How much to scale the points; 1.0 for no change
         *
         */
        template <typename T>
        void Scale2D(std::vector< Vector<2,T> > &points, T scale);

        /** \brief Scales a set of points from a center point.
         *
         * \param std::vector<Vector> &<u>points</u>: Reference to a vector of 3D Vectors to
         *        transform
         * \param T <u>angle</u>: How much to scale the points; 1.0 for no change
         * \param T <u>cx</u>: Center X
         * \param T <u>cy</u>: Center Y
         * \param T <u>cz</u>: Center Z
         *
         */
        template <typename T>
        void Scale3D(std::vector< Vector<3,T> > &points, T scale, T cx, T cy, T cz);

        /** \brief Scales a set of points from the origin.
         *
         * \param std::vector<Vector> &<u>points</u>: Reference to a vector of 3D Vectors to
         *        transform
         * \param T <u>angle</u>: How much to scale the points; 1.0 for no change
         *
         */
        template <typename T>
        void Scale3D(std::vector< Vector<3,T> > &points, T scale);
    }
}

#endif // MATH_TRANSFORM_HPP
