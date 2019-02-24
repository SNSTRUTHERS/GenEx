/**
 * \file math.cpp
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
 * The source file for general math-related functions & classes.
 *
 */

#include "base.hpp"
#include "math.hpp"

// --- VECTOR CLASS -------------------------------------------------------------------------------
// ------ PRIVATE VECTOR FUNCTIONS ----------------------------------------------------------------

template <unsigned int N, typename T>
T *GenEx::Math::Vector<N,T>::get_data() const {
    T *return_data = new T[N];
    for (unsigned int i = 0; i < N; i++) {
        return_data[i] = items[i];
    }
    return return_data;
}

template <unsigned int N, typename T>
bool GenEx::Math::Vector<N,T>::valid_size() const { return N > 1; }

template <unsigned int N, typename T>
T GenEx::Math::Vector<N,T>::get_item(const unsigned int index) const {
    return items[index];
}

// ------ CONSTRUCTORS ----------------------------------------------------------------------------

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T>::Vector(T init) {
    static_assert(N > 1, "Vector size must be greater than 1");
    if (!valid_size()) {
        std::string err = "Invalid vector size: " + std::to_string(N);
        throw GenEx::Error(err);
    }
    for (unsigned int i = 0; i < N; i++)
        items[i] = init;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T>::Vector() : Vector(0) { }

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T>::Vector(std::initializer_list<T> initlist) {
    static_assert(N > 1, "Vector size must be greater than 1");
    if (!valid_size()) {
        std::string err = "Invalid vector size: " + std::to_string(N);
        throw GenEx::Error(err);
    }

    if (initlist.size() == 1) {
        for (unsigned int i = 0; i < N; i++)
            items[i] = *initlist.begin();
    } else if (initlist.size() <= N) {
        for (auto iter = initlist.begin(); iter != initlist.end(); iter++)
            items[(int)(iter - initlist.begin())] = *iter;
    }
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T>::Vector(const GenEx::Math::Vector<N,T> &other) {
    memcpy(items, other.items, sizeof(items));
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T>::Vector(GenEx::Math::Vector<N,T> &&other) {
    T *data = other.get_data();
    for (unsigned int i = 0; i < N; i++)
        items[i] = data[i];
    delete[] data;
}

// ------ ASSIGNMENT OPERATORS --------------------------------------------------------------------

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> &GenEx::Math::Vector<N,T>::operator= (
        const GenEx::Math::Vector<N,T> &other) {
    memcpy(items, other.items, sizeof(items));
    return *this;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> &GenEx::Math::Vector<N,T>::operator= (GenEx::Math::Vector<N,T> &&other) {
    T *data = other.get_data();
    for (unsigned int i = 0; i < N; i++)
        items[i] = data[i];
    delete[] data;
    return *this;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> &GenEx::Math::Vector<N,T>::operator= (std::initializer_list<T> initlist) {
    if (initlist.size() == 1) {
        for (unsigned int i = 0; i < N; i++)
            items[i] = *initlist.begin();
    } else if (initlist.size() <= N) {
        for (auto iter = initlist.begin(); iter != initlist.end(); iter++)
            items[(int)(iter - initlist.begin())] = *iter;
    }
    return *this;
}

// ------ OTHER VECTOR OPERATORS ------------------------------------------------------------------

template <unsigned int N, typename T>
bool GenEx::Math::Vector<N,T>::operator== (const GenEx::Math::Vector<N,T> &other) const {
    if (this == &other)
        return true;
    else {
        for (unsigned int i = 0; i < N; i++) {
            if (absv(other.get_item(i) - items[i]) > FLT_EPSILON) {
                return false;
            }
        }
        return true;
    }
}

template <unsigned int N, typename T>
bool GenEx::Math::Vector<N,T>::operator== (GenEx::Math::Vector<N,T> &&other) {
    for (unsigned int i = 0; i < N; i++) {
        if (absv(other.get_item(i) - items[i]) > FLT_EPSILON) {
            return false;
        }
    }
    return true;
}

template <unsigned int N, typename T>
bool GenEx::Math::Vector<N,T>::operator!= (const GenEx::Math::Vector<N,T> &other) const {
    return !(*this != other);
}

template <unsigned int N, typename T>
bool GenEx::Math::Vector<N,T>::operator!= (GenEx::Math::Vector<N,T> &&other) {
    return !(*this != other);
}

template <unsigned int N, typename T>
template <unsigned int M, typename U>
GenEx::Math::Vector<N,T>::operator GenEx::Math::Vector<M,U> () {
    GenEx::Math::Vector<M,U> vec;
    for (unsigned int i = 0; i < N && i < M; i++)
        vec[i] = (U)items[i];
    return vec;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T>::operator SDL_Point () {
    return { (int)std::round(items[0]), (int)std::round(items[1]) };
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> &GenEx::Math::Vector<N,T>::operator+= (
        const GenEx::Math::Vector<N,T> &other) {
    for (unsigned int i = 0; i < N; i++)
        items[i] += other.get_item(i);
    return *this;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> &GenEx::Math::Vector<N,T>::operator+= (GenEx::Math::Vector<N,T> &&other) {
    for (unsigned int i = 0; i < N; i++)
        items[i] += other.get_item(i);
    return *this;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> &GenEx::Math::Vector<N,T>::operator-= (
        const GenEx::Math::Vector<N,T> &other) {
    for (unsigned int i = 0; i < N; i++)
        items[i] -= other.get_item(i);
    return *this;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> &GenEx::Math::Vector<N,T>::operator-= (GenEx::Math::Vector<N,T> &&other) {
    for (unsigned int i = 0; i < N; i++)
        items[i] -= other.get_item(i);
    return *this;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> &GenEx::Math::Vector<N,T>::operator*= (T scalar) {
    for (unsigned int i = 0; i < N; i++)
        items[i] *= scalar;
    return *this;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> &GenEx::Math::Vector<N,T>::operator/= (T scalar) {
    for (unsigned int i = 0; i < N; i++)
        items[i] /= scalar;
    return *this;
}

template <unsigned int N, typename T>
T GenEx::Math::Vector<N,T>::operator* (const GenEx::Math::Vector<N,T> &other) {
    T ret_val;
    for (unsigned int i = 0; i < N; i++)
        ret_val += items[i]*other.get_item(i);
    return ret_val;
}

template <unsigned int N, typename T>
T GenEx::Math::Vector<N,T>::operator* (GenEx::Math::Vector<N,T> &&other) {
    T ret_val;
    for (unsigned int i = 0; i < N; i++)
        ret_val += items[i]*other.get_item(i);
    return ret_val;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> GenEx::Math::Vector<N,T>::operator+ (
        const GenEx::Math::Vector<N,T> &other) const {
    GenEx::Math::Vector<N, T> ret_val(*this);
    return ret_val += other;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> GenEx::Math::Vector<N,T>::operator+ (GenEx::Math::Vector<N,T> &&other) {
    GenEx::Math::Vector<N, T> ret_val(*this);
    return ret_val += other;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> GenEx::Math::Vector<N,T>::operator- (
        const GenEx::Math::Vector<N,T> &other) const {
    GenEx::Math::Vector<N, T> ret_val(*this);
    return ret_val -= other;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> GenEx::Math::Vector<N,T>::operator- (GenEx::Math::Vector<N,T> &&other) {
    GenEx::Math::Vector<N, T> ret_val(*this);
    return ret_val -= other;
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> GenEx::Math::Vector<N,T>::operator/ (T scalar) {
    GenEx::Math::Vector<N, T> ret_val(*this);
    return ret_val /= scalar;
}
template <unsigned int N, typename T>
T &GenEx::Math::Vector<N,T>::operator[] (unsigned int index) {
    if (index >= N || index < 0) {
        std::string err = "Invalid index into vector: " + std::to_string(index);
        throw GenEx::Error(err);
    }
    return items[index];
}

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> GenEx::Math::Vector<N,T>::operator- () {
    GenEx::Math::Vector<N,T> ret_val(*this);
    for (unsigned int i = 0; i < N; i++)
        ret_val[i] = -items[i];
    return ret_val;
}

// ------ VECTOR HELPER FUNCTIONS -----------------------------------------------------------------

template <unsigned int N, typename T>
T GenEx::Math::Vector<N,T>::square() {
    T ret_val = 0;
    for (unsigned int i = 0; i < N; i++)
        ret_val += items[i]*items[i];
    return ret_val;
}

template <unsigned int N, typename T>
T GenEx::Math::Vector<N,T>::magnitude() { return SDL_sqrt(square()); }

template <unsigned int N, typename T>
GenEx::Math::Vector<N,T> &GenEx::Math::Vector<N,T>::normalize() {
    if (absv(magnitude()) < FLT_EPSILON ) {
        GenEx::Math::Vector<N,T> nv = GenEx::Math::Vector<N,T>();
        return nv;
    }
    *this /= magnitude();
    return *this;
}

template <unsigned int N, typename T>
T GenEx::Math::Vector<N,T>::distance(const GenEx::Math::Vector<N,T> &other) {
    if (&other != this) {
        GenEx::Math::Vector<N,T> n(*this);
        n -= other;
        return n.magnitude();
    }
    return 0;
}

template <unsigned int N, typename T>
T GenEx::Math::Vector<N,T>::distance(GenEx::Math::Vector<N,T> &&other) {
    if (&other != this) {
        GenEx::Math::Vector<N,T> n(*this);
        n -= other;
        return n.magnitude();
    }
    return 0;
}

template <unsigned int N, typename T>
unsigned int GenEx::Math::Vector<N,T>::size() const {
    return N;
}

template<typename T>
GenEx::Math::Vector<3,T> CrossProduct3D(GenEx::Math::Vector<3,T> &v1, GenEx::Math::Vector<3,T> &v2)
{
    return GenEx::Math::Vector<3,T>{
        v1[1]*v2[2] - v1[2]*v2[1],
        v1[2]*v2[0] - v1[0]*v2[2],
        v1[0]*v2[1] - v1[1]*v2[0]
    };
}

template<typename T>
T CrossProduct2D(GenEx::Math::Vector<2,T> &v1, GenEx::Math::Vector<2,T> &v2) {
    return v1[0]*v2[1] - v1[1]*v2[0];
}

template<typename T>
GenEx::Math::Vector<2,T> OrthoVector2D(GenEx::Math::Vector<2,T> &vec) {
    return GenEx::Math::Vector<2,T>{-vec[1], vec[0]};
}

template<typename T>
GenEx::Math::Vector<2,T> RotateVector2D(GenEx::Math::Vector<2,T> &vec, double angle) {
    double rad = GenEx::Math::DegreesToRadians(angle);
    return GenEx::Math::Vector<2,T>{
        vec[0]*SDL_cos(rad) - vec[1]*SDL_sin(rad),
        vec[0]*SDL_sin(rad) - vec[1]*SDL_cos(rad)
    };
}

template<typename T>
GenEx::Math::Vector<2,T> GetMidpoint2D(GenEx::Math::Vector<2,T> &v1, GenEx::Math::Vector<2,T> &v2,
                                       T t = 0.5) {
    return GenEx::Math::Vector<2,T>{ (v2[0]-v1[0])*t + v1[0],
                                     (v2[1]-v1[1])*t + v1[1] };
}

template<unsigned int N, typename T>
std::string std::to_string(GenEx::Math::Vector<N,T> &_vec) {
    std::stringstream sst;
    sst << '[';
    for (unsigned int i = 0; i < N-1; i++) sst << _vec[i] << ", ";
    sst << _vec[N-1] << ']';
    return sst.str();
}

// ------ VECTOR INSTANTIATIONS -------------------------------------------------------------------

template class GenEx::Math::Vector<2, float>;
template class GenEx::Math::Vector<2, double>;
template class GenEx::Math::Vector<2, long double>;

template class GenEx::Math::Vector<3, float>;
template class GenEx::Math::Vector<3, double>;
template class GenEx::Math::Vector<3, long double>;

// --- MATRIX CLASS -------------------------------------------------------------------------------
// ------ CONSTRUCTORS ----------------------------------------------------------------------------



// --- BEZIER PATH CLASS --------------------------------------------------------------------------
// ------ CONSTRUCTORS ----------------------------------------------------------------------------

template <typename T>
GenEx::Math::Bezier<T>::Bezier() { }

template <typename T>
GenEx::Math::Bezier<T>::Bezier(GenEx::Math::Bezier<T>::VEC _p0,
                               GenEx::Math::Bezier<T>::VEC _c0,
                               GenEx::Math::Bezier<T>::VEC _c1,
                               GenEx::Math::Bezier<T>::VEC _p1) : p0(_p0),
                                                                  c0(_c0),
                                                                  c1(_c1),
                                                                  p1(_p1) { }

template <typename T>
GenEx::Math::Bezier<T>::Bezier(const GenEx::Math::Bezier<T> &other) : p0(other.p0),
                                                                      c0(other.c0),
                                                                      c1(other.c1),
                                                                      p1(other.p1) { }

template <typename T>
GenEx::Math::Bezier<T>::Bezier(GenEx::Math::Bezier<T> &&other) : p0(std::move(other.p0)),
                                                                 c0(std::move(other.c0)),
                                                                 c1(std::move(other.c1)),
                                                                 p1(std::move(other.p1)) { }

// ------ ASSIGNMENT OPERATORS --------------------------------------------------------------------

template <typename T>
GenEx::Math::Bezier<T> &GenEx::Math::Bezier<T>::operator= (const GenEx::Math::Bezier<T> &other) {
    p0 = other.p0;
    c0 = other.c0;
    c1 = other.c1;
    p1 = other.p1;
    return *this;
}

template <typename T>
GenEx::Math::Bezier<T> &GenEx::Math::Bezier<T>::operator= (GenEx::Math::Bezier<T> &&other) {
    p0 = std::move(other.p0);
    c0 = std::move(other.c0);
    c1 = std::move(other.c1);
    p1 = std::move(other.p1);
    return *this;
}

// ------ HELPER FUNCTIONS ------------------------------------------------------------------------

template <typename T>
GenEx::Math::Vector<2,T> GenEx::Math::Bezier<T>::calculate_curve_point(float t) {
    float tt  = t*t;
    float ttt = tt*t;
    float u   = 1.0f - t;
    float uu  = u*u;
    float uuu = uu*u;

    GenEx::Math::Vector<2,T> pt = ((T)(uuu) ) * p0;
    pt += ( (T)(3.0 * uu * t) ) * c0;
    pt += ( (T)(3.0 * u * tt) ) * c1;
    pt += ( (T)(ttt) ) * p1;
    return pt;
}

template <typename T>
T GenEx::Math::Bezier<T>::flatness() {
    T ux = SDL_pow(3*c0[0] - 2*p0[0] - p1[0], 2);
    T uy = SDL_pow(3*c0[1] - 2*p0[1] - p1[1], 2);
    T vx = SDL_pow(3*c1[0] - 2*p1[0] - p0[0], 2);
    T vy = SDL_pow(3*c1[1] - 2*p1[1] - p0[1], 2);
    if (ux < vx) ux = vx;
    if (uy < vy) uy = vy;
    return ux + uy;
}

template <typename T>
void GenEx::Math::Bezier<T>::split(GenEx::Math::Bezier<T> *split_arr, T t) {
    GenEx::Math::Vector<2,T> p12  = GenEx::Math::GetMidpoint2D(p0,  c0,  t);
    GenEx::Math::Vector<2,T> p23  = GenEx::Math::GetMidpoint2D(c0,  c1,  t);
    GenEx::Math::Vector<2,T> p34  = GenEx::Math::GetMidpoint2D(p1,  c1,  t);
    GenEx::Math::Vector<2,T> p123 = GenEx::Math::GetMidpoint2D(p12, p23, t);
    GenEx::Math::Vector<2,T> p234 = GenEx::Math::GetMidpoint2D(p23, p34, t);
    GenEx::Math::Vector<2,T> p1234= GenEx::Math::GetMidpoint2D(p123,p234,t);

    split_arr[0] = GenEx::Math::Bezier<T>(p0, p12, p123, p1234);
    split_arr[1] = GenEx::Math::Bezier<T>(p1234, p234, p34, p1);
}

template <typename T>
void GenEx::Math::Bezier<T>::sample(std::vector< GenEx::Math::Vector<2,T> > &point_vec,
                                    unsigned int samples) {
    // Valid number of samples
    if (samples > 1) {
        for (float t = 0.0f; t <= 1.0f + (0.5f / samples); t += 1.0f / samples) {
            if (t > 1.f) t = 1.f;
            point_vec.emplace_back(calculate_curve_point(t));
        }
    }
    // Otherwise use recursive sampling algorithm
    else {
        if (flatness() < GenEx::Math::RECURSE_THRESHOLD) {
            if (point_vec.size() > 1) {
                if (p0 != *(point_vec.end()-1))
                    point_vec.emplace_back(p0);
            } else {
                point_vec.emplace_back(p0);
            }
            point_vec.emplace_back(p1);
        }
        else {
            GenEx::Math::Bezier<T> curves[2];
            split(curves);
            curves[0].sample(point_vec, 0);
            curves[1].sample(point_vec, 0);
        }
    }
}

// --- BEZIER PATH CLASS --------------------------------------------------------------------------
// ------ CONSTRUCTORS ----------------------------------------------------------------------------

template <typename T>
GenEx::Math::Path<T>::Path() { }

template <typename T>
GenEx::Math::Path<T>::Path(std::initializer_list<
                               std::tuple< GenEx::Math::Bezier<T>, int>
                           > initlist) {
    for (auto &entry : initlist) {
        GenEx::Math::Bezier<T> c;
        int s;
        std::tie(c, s) = entry;
        mCurves.emplace_back(c);
        mSamples.emplace_back(s);
    }
}

template <typename T>
GenEx::Math::Path<T>::Path(std::initializer_list< GenEx::Math::Bezier<T> > blist,
                           std::initializer_list<int> slist) {
    if (blist.size() != slist.size()) {
        throw GenEx::Error("blist & slist parameters for Path<T> constructor must " +
                           std::string("be the same size"));
    }
    for (size_t i = 0; i < blist.size(); i++) {
        mCurves.emplace_back(*(blist.begin()+i));
        mSamples.emplace_back(*(slist.begin()+i));
    }
}

template <typename T>
GenEx::Math::Path<T>::Path(const GenEx::Math::Path<T> &other) : mCurves(other.mCurves),
                                                                mSamples(other.mSamples) { }

template <typename T>
GenEx::Math::Path<T>::Path(GenEx::Math::Path<T> &&other) : mCurves(std::move(other.mCurves)),
                                                           mSamples(std::move(other.mSamples)) { }

// ------ DESTRUCTOR ------------------------------------------------------------------------------

template <typename T>
GenEx::Math::Path<T>::~Path() {
    mCurves.clear();
    mSamples.clear();
}

// ------ HELPER FUNCTIONS ------------------------------------------------------------------------

template <typename T>
void GenEx::Math::Path<T>::add_curve(GenEx::Math::Bezier<T> curve, int samples) {
    mCurves.emplace_back(curve);
    mSamples.emplace_back(samples);
}

template <typename T>
void GenEx::Math::Path<T>::sample(std::vector< GenEx::Math::Vector<2,T> > &sampled_path) {
    for (size_t i = 0; i < mCurves.size(); i++)
        mCurves[i].sample(sampled_path, mSamples[i]);
}

// --- GENERAL MATH FUNCTIONS ---------------------------------------------------------------------
// ------ RADIAN-DEGREE FUNCTIONS -----------------------------------------------------------------

double GenEx::Math::DegreesToRadians(double deg) { return deg * (PI / 180.0); }
double GenEx::Math::RadiansToDegrees(double rad) { return rad * (180.0 / PI); }

// ------ TRANSFORM FUNCTION DEFS -----------------------------------------------------------------

void GenEx::Math::TranslateSDL(std::vector<SDL_Point> &points, int dx, int dy) {
    for (SDL_Point pt : points) {
        pt.x += dx;
        pt.y += dy;
    }
}

template <typename T>
void GenEx::Math::Translate2D(std::vector< GenEx::Math::Vector<2,T> > &points, int dx, int dy) {
    for (GenEx::Math::Vector<2,T> vec : points) {
        vec[0] += dx;
        vec[1] += dy;
    }
}

template <typename T>
void GenEx::Math::Translate3D(std::vector< GenEx::Math::Vector<3,T> > &points, int dx, int dy,
                              int dz) {
    for (GenEx::Math::Vector<3,T> vec : points) {
        vec[0] += dx;
        vec[1] += dy;
        vec[2] += dz;
    }
}

void GenEx::Math::RotateSDL(std::vector<SDL_Point> &points, float angle, int cx, int cy) {
    float s = SDL_sinf(angle);
    float c = SDL_cosf(angle);
    for (SDL_Point pt : points) {
        pt.x -= cx;
        pt.y -= cy;

        pt.x = ((pt.x * c) - (pt.y * s)) + cx;
        pt.y = ((pt.x * s) - (pt.y * c)) + cy;
    }
}
void GenEx::Math::RotateSDL(std::vector<SDL_Point> &points, float angle) {
    GenEx::Math::RotateSDL(points, angle, 0, 0);
}

template <typename T>
void GenEx::Math::Rotate2D(std::vector< GenEx::Math::Vector<2,T> > &points, float angle, T cx,
                           T cy) {
    float s = SDL_sinf(angle);
    float c = SDL_cosf(angle);
    for (GenEx::Math::Vector<2,T> pt : points) {
        pt[0] -= cx;
        pt[1] -= cy;

        pt[0] = ((pt[0] * c) - (pt[1] * s)) + cx;
        pt[1] = ((pt[0] * s) - (pt[1] * c)) + cy;
    }
}
template <typename T>
void GenEx::Math::Rotate2D(std::vector< GenEx::Math::Vector<2,T> > &points, float angle) {
    GenEx::Math::Rotate2D(points, angle, 0, 0);
}

template <typename T>
void GenEx::Math::Rotate3D(std::vector< GenEx::Math::Vector<3,T> > &points, float pitch, float roll,
                           float yaw, T cx, T cy, T cz) {
    float cosa = SDL_cosf(yaw);
    float sina = SDL_sinf(yaw);
    float cosb = SDL_cosf(pitch);
    float sinb = SDL_sinf(pitch);
    float cosc = SDL_cosf(roll);
    float sinc = SDL_sinf(roll);

    float Axx = cosa*cosb;
    float Axy = cosa*sinb*sinc - sina*cosc;
    float Axz = cosa*sinb*cosc + sina*sinc;

    float Ayx = sina*cosb;
    float Ayy = sina*sinb*sinc + cosa*cosc;
    float Ayz = sina*sinb*cosc - cosa*sinc;

    float Azx = -sinb;
    float Azy = cosb*sinc;
    float Azz = cosb*cosc;

    for (GenEx::Math::Vector<3,T> vec : points) {
        vec[0] -= cx;
        vec[1] -= cy;
        vec[2] -= cz;

        T px = vec[0];
        T py = vec[1];
        T pz = vec[2];

        vec[0] = (Axx*px + Axy*py + Axz*pz) + cx;
        vec[1] = (Ayx*px + Ayy*py + Ayz*pz) + cy;
        vec[2] = (Azx*px + Azy*py + Azz*pz) + cz;
    }
}

template <typename T>
void GenEx::Math::Rotate3D(std::vector< GenEx::Math::Vector<3,T> > &points, float pitch, float roll, float yaw) {
    GenEx::Math::Rotate3D(points, pitch, roll, yaw);
}

void GenEx::Math::ScaleSDL(std::vector<SDL_Point> &points, float scale, int cx, int cy) {
    for (SDL_Point pt : points) {
        pt.x -= cx;
        pt.y -= cy;

        pt.x *= scale;
        pt.y *= scale;

        pt.x += cx;
        pt.y += cy;
    }
}
void GenEx::Math::ScaleSDL(std::vector<SDL_Point> &points, float scale) {
    GenEx::Math::ScaleSDL(points, scale, 0, 0);
}

template <typename T>
void GenEx::Math::Scale2D(std::vector< GenEx::Math::Vector<2,T> > &points, T scale, T cx, T cy) {
    for (GenEx::Math::Vector<2,T> vec : points) {
        vec[0] -= cx;
        vec[1] -= cy;

        vec *= scale;

        vec[0] += cx;
        vec[1] += cy;
    }
}
template <typename T>
void Scale2D(std::vector< GenEx::Math::Vector<2,T> > &points, T scale) {
    GenEx::Math::Scale2D(points, scale, 0, 0);
}

template <typename T>
void GenEx::Math::Scale3D(std::vector< GenEx::Math::Vector<3,T> > &points, T scale, T cx, T cy,
                          T cz) {
    for (GenEx::Math::Vector<3,T> vec : points) {
        vec[0] -= cx;
        vec[1] -= cy;
        vec[2] -= cz;

        vec *= scale;

        vec[0] += cx;
        vec[1] += cy;
        vec[2] += cz;
    }
}

template <typename T>
void GenEx::Math::Scale3D(std::vector< GenEx::Math::Vector<3,T> > &points, T scale) {
    GenEx::Math::Scale3D(points, scale, 0, 0, 0);
}
