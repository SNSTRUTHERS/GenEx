/**
 * \file math/bezier.hpp
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
 * The header file defining Bezier curve & path objects.
 *
 */

#ifndef MATH_BEZIER_HPP
#define MATH_BEZIER_HPP

#include "base.hpp"
#include "math/vector.hpp"

namespace GenEx {
    namespace Math {
        static constexpr int RECURSE_THRESHOLD = 1;

        /** \brief Default number of samples used when drawing this path
         */
        static constexpr unsigned int DEFAULT_SAMPLES = 30;

        /** \brief 0 samples = use recurse sampling method
         */
        static constexpr unsigned int RECURSE_SAMPLING = 0;

// --- BEZIER CURVE CLASS -------------------------------------------------------------------------

        /** \brief A class representing a Bezier curve.
         *
         * \param class <u><i>T</i></u>: the type for the internal Vector classes to use
         *       for storage
         *
         */
        template <typename T>
        struct Bezier {
            typedef Vector<2,T> VEC;

            VEC p0; // start point
            VEC c0; // control point for p0
            VEC c1; // control point for p1
            VEC p1; // end point

            /** \brief Constructs an empty bezier
             */
            Bezier();

            /** \brief Constructs a new Bezier curve from four 2D Vectors.
             *
             * \param Vector <u>_p0</u>: Starting point
             * \param Vector <u>_c0</u>: Control point for _p0
             * \param Vector <u>_c1</u>: Control point for _p1
             * \param Vector <u>_p1</u>: Ending point
             *
             */
            Bezier(VEC _p0, VEC _c0, VEC _c1, VEC _p1);

            /** \brief Copy constructor for a new Bezier curve.
             *
             * \param Bezier &<u>other</u>: The Bezier curve to copy
             *
             */
            Bezier(const Bezier<T> &other);

            /** \brief Move constructor for a new Bezier curve.
             *
             * \param Bezier &<u>other</u>: The Bezier curve to move
             *
             */
            Bezier(Bezier<T> &&other);

            /** \brief Copy assignment for Bezier
             *
             * \param Bezier &<u>other</u>: The Bezier curve to copy
             *
             */
            Bezier<T> &operator= (const Bezier<T> &other);

            /** \brief Move assignment for Bezier
             *
             * \param Bezier &&<u>other</u>: The Bezier curve to move
             *
             */
            Bezier<T> &operator= (Bezier<T> &&other);

            /** \brief Calculates the point on this Bezier curve at time <i>t</>
             *
             * \param float <u>t</u>: Time between 0.0f and 1.0f; if t == 0: returns p0
             *       If t == 1: returns p1;
             * \return Vector point on this Bezier curve
             *
             */
            VEC calculate_curve_point(float t);

            /** \brief Returns how flat this Bezier curve is
             *
             * \return T How flat this curve is
             *
             */
            T flatness();

            /** \brief Splits this curve into two curves
             *
             * \param T <u><i>t</i></u>: Where on the curve to split; 0.5 by default;
             *        0.0 to split at start, 1.0 to split at end
             *
             */
            void split(Bezier<T> *split_arr, T t = 0.5);

            /** \brief Samples points on the curve to connect together as straight lines.
             *
             * \param std::vector<Vector<2,T>> &<u>point_vec</u>: Vector to populate with 2D points
             * \param unsigned int <u><i>samples</i></u>: How many times to sample the image; set
             *        <i>DEFAULT_SAMPLES</i> by default; if samples < 2, a recursive algorithm will
             *        be used to determine the amount of samples
             *
             */
            void sample(std::vector< Vector<2,T> > &point_vec,
                        unsigned int samples = DEFAULT_SAMPLES);
        };

// --- BEZIER CURVE ALIASES -----------------------------------------------------------------------

        /** \brief BezierCurve that uses Vector2F as the internal Vector type
         */
        typedef Bezier<float> BezierCurveF;

        /** \brief BezierCurve that uses Vector2 as the internal Vector type
         */
        typedef Bezier<double>  BezierCurve;

        /** \brief BezierCurve that uses Vector2L as the internal Vector type
         */
        typedef Bezier<long double> BezierCurveL;

// --- PATH CLASS ---------------------------------------------------------------------------------

        /** \brief A class representing a path made up of multiple Bezier curves.
         *
         * \param class <u>T</u>: a numeric type for the BezierCurve to use for its internal
         *       Vectors
         *
         */
        template <typename T>
        class Path {
            std::vector< Bezier<T> > mCurves;
            std::vector<int> mSamples;

        public:
            /** \brief Constructs a new Path.
             */
            Path();

            /** \brief Constructs a new path from a list of Bezier curves & sample counts.
             *
             * \param <u>initlist</u>: An initializer list containing tuples of Bezier curves
             *        and integers representing the amount of samples to take of each corresponding
             *        curve.
             *
             */
            Path(std::initializer_list< std::tuple< Bezier<T>, int> > initlist);

            /** \brief Constructs a new path from a list of Bezier curves & a list of sample
             *        counts.
             *
             * \param <u>blist</u>: An initializer list containing Bezier curves
             * \param <u>slist</u>: An initializer list containing sample counts for each curve
             *
             */
            Path(std::initializer_list< Bezier<T> > blist, std::initializer_list<int> slist);

            /** \brief Constructs a new path from the contents of another.
             *
             * \param Path &<u>other</u>: The path to derive from
             *
             */
            Path(const Path &other);

            /** \brief Constructs a new path from the contents of another.
             *
             * \param Path &<u>other</u>: The path to derive from
             *
             */
            Path(Path &&other);

            /** \brief Destructor for Path.
             */
            ~Path();

            /** \brief Adds a new curve to this path.
             *
             * \param Bezier <u>curve</u>: The Bezier curve to add to the path
             * \param int <u>samples</u>: The amount of samples to use for this path when
             *        being drawn.
             *
             */
            void add_curve(Bezier<T> curve, int samples = DEFAULT_SAMPLES);

            /** \brief Places samples of this path into a given vector.
             *
             * \param std::vector<Vector> &<u>sampled_path</u>: Reference to a vector to deposit
             *        the sampled points of this path to
             *
             */
            void sample(std::vector< Vector<2,T> > &sampled_path);
        };

// --- BEZIER PATH ALIASES ------------------------------------------------------------------------

        /** \brief BezierPath made up of BezierCurveF objects
         */
        typedef Path<float> BezierPathF;

        /** \brief BezierPath made up of BezerCurve objects
         */
        typedef Path<double> BezierPath;

        /** \brief BezierPath made up of BezierCurveL objects
         */
        typedef Path<long double> BezierPathL;
    }
}

#endif // MATH_BEZIER_HPP
