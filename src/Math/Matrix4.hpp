#ifndef _MATRIX4_HPP
#define _MATRIX4_HPP

#include "Matrix3.hpp"
#include "Vector4.hpp"

template <class T>
class Matrix4 {
	public:
		static Matrix4<T> zero();
		static Matrix4<T> identity();
		static Matrix4<T> isometry(const Matrix3<T>& rot, const Vector3<T>& trans);
		
		Matrix4();
		Matrix4(const Matrix4<T>& m);
		Matrix4& operator = (const Matrix4<T>& m);
		
		T* data();
		
		T& operator () (int i, int j);
		T operator () (int i, int j) const;
		
		Vector4<T> operator * (const Vector4<T>& v);
		Matrix4<T> operator * (Matrix4<T>& m);
		
	private:
		T data_[16];
};

template <class T>
Matrix4<T> Matrix4<T>::identity() {
	Matrix4 matrix = zero();
	matrix.data_[0] = 1.0f;
	matrix.data_[5] = 1.0f;
	matrix.data_[10] = 1.0f;
	matrix.data_[15] = 1.0f;
	return matrix;
}

template <class T>
Matrix4<T> Matrix4<T>::zero() {
	Matrix4<T> matrix;
	
	for (int i = 0; i < 16; i++)
		matrix.data_[i] = 0.0f;
		
	return matrix;
}

template <class T>
Matrix4<T> Matrix4<T>::isometry(const Matrix3<T>& rot, const Vector3<T>& trans) {
	Matrix4<T> matrix = zero();
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix(i, j) = rot(i, j);
		}
	}
	
	for (int i = 0; i < 3; i++)
		matrix(i, 3) = trans(i);
	
	matrix(3, 3) = 1.0;
	
	return matrix;
}

template <class T>
Matrix4<T>::Matrix4() {
}

template <class T>
Matrix4<T>::Matrix4(const Matrix4& m) {
	*this = m;
}

template <class T>
Matrix4<T>& Matrix4<T>::operator = (const Matrix4<T>& m) {
	for (int i = 0; i < 16; i++)
		data_[i] = m.data_[i];
		
	return *this;
}

template <class T>
T* Matrix4<T>::data() {
	return data_;
}

template <class T>
T& Matrix4<T>::operator () (int i, int j) {
	return data_[4 * i + j];
}

template <class T>
Vector4<T> Matrix4<T>::operator * (const Vector4<T>& v) {
	T x = data_[0] * v.x() + data_[1] * v.y() + data_[2] * v.z() + data_[3] * v.w();
	T y = data_[4] * v.x() + data_[5] * v.y() + data_[6] * v.z() + data_[7] * v.w();
	T z = data_[8] * v.x() + data_[9] * v.y() + data_[10] * v.z() + data_[11] * v.w();
	T w = data_[12] * v.x() + data_[13] * v.y() + data_[14] * v.z() + data_[15] * v.w();
	return Vector4<T>(x, y, z, w);
}

template <class T>
Matrix4<T> Matrix4<T>::operator * (Matrix4& m) {
	Matrix4<T> matrix;
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			T sum = 0.0f;
			
			for (int k = 0; k < 4; k++) {
				sum += (*this)(i, k) * m(k, j);
			}
			
			matrix(i, j) = sum;
		}
	}
	
	return matrix;
}

typedef Matrix4<float> Matrix4f;
typedef Matrix4<double> Matrix4d;

#endif
