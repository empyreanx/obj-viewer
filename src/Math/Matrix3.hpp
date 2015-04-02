#ifndef _MATRIX3_HPP
#define _MATRIX3_HPP

#include "Vector3.hpp"

template <class T>
class Matrix3 {
	public:
		static Matrix3<T> zero();
		static Matrix3<T> identity();
		static Matrix3<T> rotation(const Vector3<T>& axis, const T& angle);
		
		Matrix3();
		Matrix3(const Matrix3<T>& m);
		Matrix3& operator = (const Matrix3<T>& m);
		
		T* data();
		
		T& operator () (int i, int j);
		T operator () (int i, int j) const;
		
		Vector3<T> operator * (const Vector3<T>& v);
		Matrix3<T> operator * (const Matrix3<T>& m);
		
	private:
		T data_[9];
};

template <class T>
Matrix3<T> Matrix3<T>::identity() {
	Matrix3<T> matrix = zero();
	matrix.data_[0] = 1.0f;
	matrix.data_[4] = 1.0f;
	matrix.data_[8] = 1.0f;
	return matrix;
}

template <class T>
Matrix3<T> Matrix3<T>::zero() {
	Matrix3<T> matrix;
	
	for (int i = 0; i < 9; i++)
		matrix.data_[i] = 0.0f;
		
	return matrix;
}

template <class T>
Matrix3<T> Matrix3<T>::rotation(const Vector3<T>& axis, const T& angle) {
	T c = std::cos(angle);
	T s = std::sin(angle);
	
	Matrix3<T> matrix;
	
	matrix(0, 0) = c + (1.0f - c) * axis.x() * axis.x();
	matrix(0, 1) = (1.0f - c) * axis.x() * axis.y() - s * axis.z();
	matrix(0, 2) = (1.0f - c) * axis.x() * axis.z() + s * axis.y();
	
	matrix(1, 0) = (1.0f - c) * axis.x() * axis.y() + s * axis.z(); 
	matrix(1, 1) = c + (1.0f - c) * axis.y() * axis.y();
	matrix(1, 2) = (1.0f - c) * axis.y() * axis.z() - s * axis.x();
	
	matrix(2, 0) = (1.0f - c) * axis.x() * axis.z() - s * axis.y();
	matrix(2, 1) = (1.0f - c) * axis.y() * axis.z() + s * axis.x();
	matrix(2, 2) = c + (1.0f - c) * axis.z() * axis.z();
	
	return matrix;
}
 
template <class T>
Matrix3<T>::Matrix3() {
}

template <class T>
Matrix3<T>::Matrix3(const Matrix3& m) {
	*this = m;
}

template <class T>
Matrix3<T>& Matrix3<T>::operator = (const Matrix3<T>& m) {
	for (int i = 0; i < 9; i++)
		data_[i] = m.data_[i];
		
	return *this;
}

template <class T>
T* Matrix3<T>::data() {
	return data_;
}

template <class T>
T& Matrix3<T>::operator () (int i, int j) {
	return data_[3 * i + j];
}

template <class T>
T Matrix3<T>::operator () (int i, int j) const {
	return data_[3 * i + j];
}

template <class T>
Vector3<T> Matrix3<T>::operator * (const Vector3<T>& v) {
	T x = data_[0] * v.x() + data_[1] * v.y() + data_[2] * v.z();
	T y = data_[3] * v.x() + data_[4] * v.y() + data_[5] * v.z();
	T z = data_[6] * v.x() + data_[7] * v.y() + data_[8] * v.z();
	return Vector3<T>(x, y, z);
}

template <class T>
Matrix3<T> Matrix3<T>::operator * (const Matrix3& m) {
	Matrix3 matrix;
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			T sum = 0.0f;
			
			for (int k = 0; k < 3; k++) {
				sum += (*this)(i, k) * m(k, j);
			}
			
			matrix(i, j) = sum;
		}
	}
	
	return matrix;
}

typedef Matrix3<float> Matrix3f;
typedef Matrix3<double> Matrix3d;

#endif
