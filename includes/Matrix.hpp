#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <array>
#include "Vector.hpp"

template <typename T, size_t H, size_t W>
struct Matrix : public std::array<vec<T, W>, H>
{
        Matrix(void) {}
        Matrix(T value) {
		    for (unsigned y = 0; y < H; ++y) {
                for (unsigned x = 0; x < W; ++x) {
                    (*this)[y][x] = (x == y) ? value : 0;
                }
            }
        }
        Matrix(const Matrix & matrix) {
			(*this) = matrix;
        }
        Matrix(const std::array<T, W * H>& matrix) {
            (*this) = matrix;
        }

        Matrix &operator=(const Matrix& rhs) {
            memcpy(this, &rhs, sizeof(std::array<std::array<T, W>, H>));
            return (*this);
        }

        Matrix& operator=(const std::array<T, W * H>& rhs) {
            memcpy(this, &rhs, sizeof(std::array<T, W * H>));
            return (*this);
        }

        Matrix operator+(const Matrix& rhs) {
            Matrix result;

		    for (unsigned y = 0; y < W; ++y)
                for (unsigned x = 0; x < H; ++x)
			        result[y][x] = (*this)[y][x] + rhs[y][x];
            return (result);
        }

        Matrix operator-(const Matrix& rhs) {
            Matrix result;

            for (unsigned y = 0; y < W; ++y)
                for (unsigned x = 0; x < H; ++x)
                    result[y][x] = (*this)[y][x] - rhs[y][x];
            return (result);
        }

        Matrix operator*(const T rhs) const {
            Matrix result;

            for (unsigned y = 0; y < W; ++y)
                for (unsigned x = 0; x < H; ++x)
                    result[y][x] = (*this)[y][x] * rhs;
            return (result);
        }

        Matrix operator/(const T rhs) const {
            Matrix result;

            for (unsigned y = 0; y < W; ++y)
                for (unsigned x = 0; x < H; ++x)
                    result[y][x] = (*this)[y][x] / rhs;
            return (result);
        }

        vec<T, W> operator*(const vec<T, W>& rhs) const {
            vec<T, W> result;

            for (unsigned y = 0; y < H; ++y)
                for (unsigned x = 0; x < W; ++x)
			        result[y] += (*this)[y][x] * rhs[x];
            return (result);
        }

        template <size_t _W>
        Matrix<T, H, _W> operator*(const Matrix<T, W, _W>& rhs) const {
            Matrix<T, H, _W> result(0); //maybe do a memset instead
            
            for (unsigned v = 0; v < _W; ++v)
                for (unsigned y = 0; y < H; ++y)
                    for (unsigned x = 0; x < W; ++x)
			            result[y][v] += (*this)[y][x] * rhs[x][v];
            return (result);
        }

        T trace(void) {
            T result;
            size_t size;

            size = (W > H) ? H : W;
            result = 0;
            for (size_t n = 0; n < size; ++n)
                result = (*this)[n][n];
            return (result); 
        }

        Matrix<T, W, H> transpose(void) {
            Matrix<T, W, H> result;

            for (unsigned y = 0; y < H; ++y)
                for (unsigned x = 0; x < W; ++x)
			        result[x][y] = (*this)[y][x];
            return (result);
        }

        size_t width(void) const {
            return W;
        }

        size_t height(void) const {
            return H;
        }
        
        void print(void) {
            std::cout << *this << std::endl;
        }

        void operator+=(const Matrix& rhs) {*this = *this + rhs;};
        void operator-=(const Matrix& rhs) {*this = *this - rhs;};
        void operator*=(const T rhs) {*this = *this * rhs;};
        void operator*=(const Matrix& rhs) {*this = *this * rhs;};
        void operator/=(const T rhs) {*this = *this / rhs;};
};

template <typename T, size_t H, size_t W>
std::ostream& operator<<(std::ostream& os, const Matrix<T, H, W>& matrix) {
    for (size_t y = 0; y < H; y++) {
        os << "[";
        for (size_t x = 0; x < W - 1; x++)
            os << matrix[y][x] <<  ", ";
        if (W)
            os << matrix[y][W - 1];
        os << "]" << std::endl;
    }
    return (os);
}

typedef Matrix<float, 2, 2> mat2;
typedef Matrix<float, 3, 3> mat3;
typedef Matrix<float, 4, 4> mat4;

template <typename T, size_t H, size_t W>
Matrix<T, H, W> lerp(const Matrix<T, H, W>&u, const Matrix<T, H, W>&v, const float t) {
    Matrix<T, H, W> result;

    result = u * (1 - t) + v * t;
    return (result);
}

#endif
