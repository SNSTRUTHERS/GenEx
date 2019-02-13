#ifndef MATH_BEZIER_HPP
#define MATH_BEZIER_HPP

#include "base.hpp"
#include "math/vector.hpp"

namespace GenEx {
    namespace Math {
        static constexpr int RECURSE_THRESHOLD = 1;

        /** \brief Default number of samples used when drawing this path
         */
        static const unsigned int DEFAULT_SAMPLES = 30;

        /** \brief 0 samples = use recurse sampling method
         */
        static const unsigned int RECURSE_SAMPLING = 0;

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
            Bezier() { }

            /** \brief Constructs a new Bezier curve from four 2D Vectors.
             *
             * \param Vector <u>_p0</u>: Starting point
             * \param Vector <u>_c0</u>: Control point for _p0
             * \param Vector <u>_c1</u>: Control point for _p1
             * \param Vector <u>_p1</u>: Ending point
             *
             */
            Bezier(VEC _p0, VEC _c0, VEC _c1, VEC _p1) : p0(_p0), c0(_c0), c1(_c1), p1(_p1)
            { }

            /** \brief Copy constructor for a new Bezier curve.
             *
             * \param Bezier &<u>other</u>: The Bezier curve to copy
             *
             */
            Bezier(const Bezier<T> &other) : p0(other.p0),
                                             c0(other.c0),
                                             c1(other.c1),
                                             p1(other.p1) { }

            /** \brief Move constructor for a new Bezier curve.
             *
             * \param Bezier &<u>other</u>: The Bezier curve to move
             *
             */
            Bezier(Bezier<T> &&other) : p0(std::move(other.p0)),
                                        c0(std::move(other.c0)),
                                        c1(std::move(other.c1)),
                                        p1(std::move(other.p1)) { }

            /** \brief Copy assignment for Bezier
             *
             * \param Bezier &<u>other</u>: The Bezier curve to copy
             *
             */
            Bezier<T> &operator= (const Bezier<T> &other) {
                p0 = other.p0;
                c0 = other.c0;
                c1 = other.c1;
                p1 = other.p1;
                return *this;
            }

            /** \brief Move assignment for Bezier
             *
             * \param Bezier &&<u>other</u>: The Bezier curve to move
             *
             */
            Bezier<T> &operator= (Bezier<T> &&other) {
                p0 = std::move(other.p0);
                c0 = std::move(other.c0);
                c1 = std::move(other.c1);
                p1 = std::move(other.p1);
                return *this;
            }

            /** \brief Calculates the point on this Bezier curve at time <i>t</>
             *
             * \param float <u>t</u>: Time between 0.0f and 1.0f; if t == 0: returns p0
             *       If t == 1: returns p1;
             * \return Vector point on this Bezier curve
             *
             */
            VEC calculate_curve_point(float t) {
                float tt  = t*t;
                float ttt = tt*t;
                float u   = 1.0f - t;
                float uu  = u*u;
                float uuu = uu*u;

                VEC pt = ((T)(uuu) ) * p0;
                pt += ( (T)(3.0 * uu * t) ) * c0;
                pt += ( (T)(3.0 * u * tt) ) * c1;
                pt += ( (T)(ttt) ) * p1;
                return pt;
            }

            /** \brief Returns how flat this Bezier curve is
             *
             * \return T How flat this curve is
             *
             */
            T flatness() {
                T ux = SDL_pow(3*c0[0] - 2*p0[0] - p1[0], 2);
                T uy = SDL_pow(3*c0[1] - 2*p0[1] - p1[1], 2);
                T vx = SDL_pow(3*c1[0] - 2*p1[0] - p0[0], 2);
                T vy = SDL_pow(3*c1[1] - 2*p1[1] - p0[1], 2);
                if (ux < vx) ux = vx;
                if (uy < vy) uy = vy;
                return ux + uy;
            }

            /** \brief Splits this curve into two curves
             *
             * \param T <u><i>t</i></u>: Where on the curve to split; 0.5 by default;
             *        0.0 to split at start, 1.0 to split at end
             *
             */
            void split(Bezier<T> *split_arr, T t = 0.5) {
                Vector<2,T> p12  = GetMidpoint2D(p0,  c0,  t);
                Vector<2,T> p23  = GetMidpoint2D(c0,  c1,  t);
                Vector<2,T> p34  = GetMidpoint2D(p1,  c1,  t);
                Vector<2,T> p123 = GetMidpoint2D(p12, p23, t);
                Vector<2,T> p234 = GetMidpoint2D(p23, p34, t);
                Vector<2,T> p1234= GetMidpoint2D(p123,p234,t);

                split_arr[0] = Bezier<T>(p0, p12, p123, p1234);
                split_arr[1] = Bezier<T>(p1234, p234, p34, p1);
            }

            void sample(std::vector< Vector<2,T> > &point_vec,
                        unsigned int samples = DEFAULT_SAMPLES) {
                // Valid number of samples
                if (samples > 1) {
                    for (float t = 0.0f; t <= 1.0f + (0.5f / samples); t += 1.0f / samples) {
                        if (t > 1.f) t = 1.f;
                        point_vec.emplace_back(calculate_curve_point(t));
                    }
                }
                // Otherwise use recursive sampling algorithm
                else {
                    if (flatness() < RECURSE_THRESHOLD) {
                        if (point_vec.size() > 1) {
                            if (p0 != *(point_vec.end()-1))
                                point_vec.emplace_back(p0);
                        } else {
                            point_vec.emplace_back(p0);
                        }
                        point_vec.emplace_back(p1);
                    }
                    else {
                        Bezier<T> curves[2];
                        split(curves);
                        curves[0].sample(point_vec, 0);
                        curves[1].sample(point_vec, 0);
                    }
                }
            }
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

// --- BEZIER PATH DECLARATION --------------------------------------------------------------------

        template <typename T>
        class Path;

// --- BEZIER HELPER FUNCTIONS --------------------------------------------------------------------

        // <placeholder>

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
            Path() { }

            Path(std::initializer_list< std::tuple< Bezier<T>, int> > initlist) {
                for (auto &entry : initlist) {
                    Bezier<T> c;
                    int s;
                    std::tie(c, s) = entry;
                    mCurves.emplace_back(c);
                    mSamples.emplace_back(s);
                }
            }

            Path(std::initializer_list< Bezier<T> > blist, std::initializer_list<int> slist) {
                if (blist.size() != slist.size()) {
                    throw Error("blist & slist parameters for Path<T> constructor must " +
                                std::string("be the same size"));
                }
                for (size_t i = 0; i < blist.size(); i++) {
                    mCurves.emplace_back(*(blist.begin()+i));
                    mSamples.emplace_back(*(slist.begin()+i));
                }
            }

            /** \brief Destructor for Path.
             */
            ~Path() {
                mCurves.clear();
                mSamples.clear();
            }

            std::vector< Bezier<T> > get_curves() const { return mCurves; }
            std::vector<int> get_sample_counts() const { return mSamples; }

            /** \brief Adds a new curve to this path.
             *
             * \param Bezier <u>curve</u>: The Bezier curve to add to the path
             * \param int <u>samples</u>: The amount of samples to use for this path when
             *        being drawn.
             *
             */
            void add_curve(Bezier<T> curve, int samples = DEFAULT_SAMPLES) {
                mCurves.emplace_back(curve);
                mSamples.emplace_back(samples);
            }

            /** \brief Places samples of this path into a given vector.
             *
             * \param std::vector<Vector> &<u>sampled_path</u>: Reference to a vector to deposit
             *        the sampled points of this path to
             *
             */
            void sample(std::vector< Vector<2,T> > &sampled_path) {
                for (size_t i = 0; i < mCurves.size(); i++)
                    mCurves[i].sample(sampled_path, mSamples[i]);
            }
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
