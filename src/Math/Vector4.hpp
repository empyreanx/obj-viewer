#ifndef _VECTOR4_HPP
#define _VECTOR4_HPP

#include <cmath>

template <class T>
class Vector4 {
	public:
		static Vector4<T> zero();
		
		Vector4();
		Vector4(T x, T y, T z, T w);
		Vector4(const Vector4<T>& v);
		Vector4& operator = (const Vector4<T>& v);
	
		//accessors
		T x() const;
		T y() const;
		T z() const;
		T w() const;
		
		T* data();
		
		T& operator() (int i);
		T operator() (int i) const;
		
		//operators
		Vector4<T> operator - ();
		Vector4<T> operator + (const Vector4<T>& v);
		Vector4<T> operator - (const Vector4<T>& v);
		
		Vector4<T>& operator += (const Vector4<T>& v);
		Vector4<T>& operator -= (const Vector4<T>& v);
		
		Vector4<T> operator * (const T& c);
		Vector4<T> operator / (const T& c);
		
		Vector4<T>& operator *= (const T& c);
		Vector4<T>& operator /= (const T& c);
		
		//inner product
		T operator* (const Vector4<T>& v);
		
		//distance & length
		T norm();
		T distance(const Vector4<T>& v);
		
		Vector4<T> normalize();
		
	private:
		float data_[4];
};

template <class T>
Vector4<T> Vector4<T>::zero() {
	return Vector4<T>(0.0, 0.0, 0.0, 0.0);
} 

template <class T>
Vector4<T>::Vector4() {
} 

template <class T>
Vector4<T>::Vector4(T x, T y, T z, T w) {
	data_[0] = x;
	data_[1] = y;
	data_[2] = z;
	data_[3] = w;
}

template <class T>
Vector4<T>::Vector4(const Vector4<T>& v) {
	*this = v;
}

template <class T>
Vector4<T>& Vector4<T>::operator = (const Vector4<T>& v) {
	data_[0] = v.data_[0];
	data_[1] = v.data_[1];
	data_[2] = v.data_[2];
	data_[3] = v.data_[3];
	return *this;
}

template <class T>
T Vector4<T>::x() const {
	return data_[0];
}

template <class T>
T Vector4<T>::y() const {
	return data_[1];
}

template <class T>
T Vector4<T>::z() const {
	return data_[2];
}

template <class T>
T Vector4<T>::w() const {
	return data_[3];
}

template <class T>
T* Vector4<T>::data() {
	return data_;
}

template <class T>
T& Vector4<T>::operator () (int i) {
	return data_[i];
}

template <class T>
T Vector4<T>::operator () (int i) const {
	return data_[i];
}

template <class T>
Vector4<T> Vector4<T>::operator - () {
	return Vector4(-data_[0], -data_[1], -data_[2], -data_[3]);
}

template <class T>
Vector4<T> Vector4<T>::operator + (const Vector4& v) {
	return Vector4(data_[0] + v.data_[0], data_[1] + v.data_[1], data_[2] + v.data_[2], data_[3] + v.data_[3]);
}

template <class T>
Vector4<T> Vector4<T>::operator - (const Vector4& v) {
	return Vector4(data_[0] - v.data_[0], data_[1] - v.data_[1], data_[2] - v.data_[2], data_[3] - v.data_[3]);
}

template <class T>
Vector4<T>& Vector4<T>::operator += (const Vector4<T>& v) {
	data_[0] += v.data_[0];
	data_[1] += v.data_[1];
	data_[2] += v.data_[2];
	data_[3] += v.data_[3];
	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator -= (const Vector4<T>& v) {
	data_[0] -= v.data_[0];
	data_[1] -= v.data_[1];
	data_[2] -= v.data_[2];
	data_[3] -= v.data_[3];
	return *this;
}

template <class T>
Vector4<T> Vector4<T>::operator * (const T& c) {
	return Vector4<T>(data_[0] * c, data_[1] * c, data_[2] * c, data_[3] * c);
}

template <class T>
Vector4<T> Vector4<T>::operator / (const T& c) {
	return Vector4<T>(data_[0] / c, data_[1] / c, data_[2] / c, data_[3] / c);
}

template <class T>
Vector4<T>& Vector4<T>::operator *= (const T& c) {
	data_[0] *= c;
	data_[1] *= c;
	data_[2] *= c;
	data_[3] *= c;
	return *this;
}

template <class T>
Vector4<T>& Vector4<T>::operator /= (const T& c) {
	data_[0] /= c;
	data_[1] /= c;
	data_[2] /= c;
	data_[3] /= c;
	return *this;
}

template <class T>
T Vector4<T>::operator* (const Vector4<T>& v) {
	return data_[0] * v.data_[0] + data_[1] * v.data_[1] + data_[2] * v.data_[2] + data_[3] * v.data_[3];
}

template <class T>
T Vector4<T>::norm() {
	return std::sqrt(*this * *this);
}

template <class T>
T Vector4<T>::distance(const Vector4<T>& v) {
	return (*this - v).norm();
}

template <class T>
Vector4<T> Vector4<T>::normalize() {
	return *this / this->norm();
}

typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;

typedef Vector4f Point4f;
typedef Vector4d Point4d;

#endif
