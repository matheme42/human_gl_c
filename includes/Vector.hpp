#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <string>
#include <array>
#include <math.h>

#define VECTOR_ABS(x) ((x > 0) ? x : -x)


template <typename T, size_t W>
struct vec : public std::array<T, W>
{
        vec(void) {}
        vec(T value) {
		    for (unsigned n = 0; n < W; ++n)
                (*this)[n] = value;
        }
        vec(const vec & vec) {
			(*this) = vec;
        }
        vec(const std::array<T, W> & vec) {
            (*this) = vec;
		}

        vec &operator=(const std::array<T, W> & rhs) {
		    for (unsigned n = 0; n < W; ++n)
                (*this)[n] = rhs[n];
            return (*this);
        }
        
        vec &operator=(const vec& rhs) {
		    for (unsigned n = 0; n < W; ++n)
                (*this)[n] = rhs[n];
            return (*this);
        }

        vec operator+(const vec& rhs) const {
            vec result(*this);

		    for (unsigned n = 0; n < W; ++n)
			    result[n] += rhs[n];
            return (result);
        }

        vec operator-(const vec& rhs) const {
            vec result(*this);

		    for (unsigned n = 0; n < W; ++n)
			    result[n] -= rhs[n];
            return (result);
        }

        vec operator*(const T rhs) const {
            vec result(*this);

		    for (unsigned n = 0; n < W; ++n)
			    result[n] *= rhs;
            return (result);
        }

        vec operator/(const T rhs) const {
            vec result(*this);

		    for (unsigned n = 0; n < W; ++n)
			    result[n] /= rhs;
            return (result);
        }

        T dot(const vec& vec) const {
            T result;
            
            result = 0;
            for (int n = 0; n < W; n++)
                result += (*this)[n] * vec[n];
            return (result);
        }

        float norm_1() const {
            float result;

            result = 0.0f;
            for (int n = 0; n < W; n++)
                result += vec_ABS((*this)[n]);
            return (result);
        }

        float norm() const {
            float result;

            result = 0.0f;
            for (int n = 0; n < W; n++)
                result += (*this)[n] * (*this)[n];
            return (sqrt(result));
        }

        float norm_inf() const {
            float result;

            result = 0;
            for (int n = 0; n < W; n++)
                if (vec_ABS((*this)[n]) > result)
                    result = VECTOR_ABS((*this)[n]);
            return (result);
        }

        std::string to_string() {
            std::string result = "v = [";
            
            for (int n = 0; n < W - 1; n++) {
                result += std::to_string((*this)[n]) + ", ";
            }
            if (W)
                result += std::to_string((*this)[W - 1]);
            result += "]";
            return result;
        }
        
        void print(void) {std::cout << *this << std::endl;}

        const size_t size() const { return W; };
        
        void operator+=(const vec & rhs) {*this = *this + rhs;};
        void operator-=(const vec & rhs) {*this = *this - rhs;};
        void operator*=(const T rhs) {*this = *this * rhs;};
        void operator/=(const T rhs) {*this = *this / rhs;};
};

template <typename T, size_t W>
std::ostream& operator<<(std::ostream& os, const vec<T, W> &vec) {
    os << "v = [";
    for (int n = 0; n < W - 1; n++) {
        os << vec[n] <<  ", ";
    }
    if (W)
        os << vec[W - 1];
    os << "]";
    return (os);
}

template <typename T, size_t W, size_t H>
vec<T, W> linear_combination(const std::array<vec<T, W>, H> &vecs, const vec<T, W> &coefs) {
    vec<T, W> result(0);

    for (unsigned n = 0; n < H; n++)
        result += vecs[n] * coefs[n];
    return (result);
}

template <typename T, size_t W>
vec<T, W> lerp(const vec<T, W> &u, const vec<T, W> &v, const float t) {
    vec<T, W> result;

    result = u * (1 - t) + v * t;
    return (result);
}

template <typename T, size_t W>
float angle_cos(const vec<T, W> &u, const vec<T, W> &v) {
    float result;

    result = u.dot(v) / (u.norm() * v.norm());
    return (result);
}

template <typename T>
 vec<T, 3> cross_product(const vec<T, 3> &u, const vec<T, 3> &v) {
    vec<T, 3> result;

    result[0] = u[1] * v[2] - u[2] * v[1];
    result[1] = -u[0] * v[2] + u[2] * v[0];
    result[2] = u[0] * v[1] - u[1] * v[0];
    return (result);
 }

 template <typename T, size_t W>
 vec<T, W> normalize(const vec<T, W> &vector) {
     vec<T, W> result;
     float invNormal = 1.0f / vector.norm();

     for (size_t n = 0; n < W; n++)
         result[n] = vector[n] * invNormal;
     return (result);
 }
 
typedef vec<float, 2> vec2;
typedef vec<float, 3> vec3;
typedef vec<float, 4> vec4;

typedef vec<int, 2> ivec2;
typedef vec<int, 3> ivec3;
typedef vec<int, 4> ivec4;
#endif
