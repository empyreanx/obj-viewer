#ifndef _VECTOR2_HPP
#define _VECTOR2_HPP

#include <cmath>

template <class T>
class Vector2 {
	public:
		static Vector2<T> zero();
	
		Vector2();
		Vector2(T x, T y);
		Vector2(const Vector2<T>& v);
		Vector2& operator = (const Vector2<T>& v);
		
		//accessors
		T x() const;
		T y() const;
		
		T* data();
		
		//operators
		Vector2<T> operator - ();
		Vector2<T> operator + (const Vector2<T>& v);
		Vector2<T> operator - (const Vector2<T>& v);
		
		Vector2<T>& operator += (const Vector2<T>& v);
		Vector2<T>& operator -= (const Vector2<T>& v);
		
		Vector2<T> operator * (const T& c);
		Vector2<T> operator / (const T& c);
		
		Vector2<T>& operator *= (const T& c);
		Vector2<T>& operator /= (const T& c);
		
		//inner product
		T operator* (const Vector2<T>& v);
		
		//distance & length
		T norm();
		T distance(const Vector2<T>& v);
		
	private:
		float data_[2];
};

template <class T>
Vector2<T> Vector2<T>::zero() {
	return Vector2<T>(0.0, 0.0);
}

template <class T>
Vector2<T>::Vector2() {
}

template <class T>
Vector2<T>::Vector2(T x, T y) {
	data_[0] = x;
	data_[1] = y;
}

template <class T>
Vector2<T>::Vector2(const Vector2& v) {
	*this = v;
}

template <class T>
Vector2<T>& Vector2<T>::operator = (const Vector2& v) {
	data_[0] = v.data_[0];
	data_[1] = v.data_[1];
	return *this;
}

template <class T>
T Vector2<T>::x() const {
	return data_[0];
}

template <class T>
T Vector2<T>::y() const {
	return data_[1];
}

template <class T>
T* Vector2<T>::data() {
	return data_;
}

template <class T>
Vector2<T> Vector2<T>::operator -() {
	return Vector2(-data_[0], -data_[1]);
}

template <class T>
Vector2<T> Vector2<T>::operator + (const Vector2<T>& v) {
	return Vector2<T>(data_[0] + v.data_[0], data_[1] + v.data_[1]);
}

template <class T>
Vector2<T> Vector2<T>::operator - (const Vector2<T>& v) {
	return Vector2(data_[0] - v.data_[0], data_[1] - v.data_[1]);
}

template <class T>
Vector2<T>& Vector2<T>::operator += (const Vector2<T>& v) {
	data_[0] += v.data_[0];
	data_[1] += v.data_[1];
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator -= (const Vector2<T>& v) {
	data_[0] -= v.data_[0];
	data_[1] -= v.data_[1];
	return *this;
}

template <class T>
Vector2<T> Vector2<T>::operator * (const T& c) {
	return Vector2<T>(data_[0] * c, data_[1] * c);
}

template <class T>
Vector2<T> Vector2<T>::operator / (const T& c) {
	return Vector2<T>(data_[0] / c, data_[1] / c);
}

template <class T>
Vector2<T>& Vector2<T>::operator *= (const T& c) {
	data_[0] *= c;
	data_[1] *= c;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator /= (const T& c) {
	data_[0] /= c;
	data_[1] /= c;
	return *this;
}

template <class T>
T Vector2<T>::operator* (const Vector2<T>& v) {
	return data_[0] * data_[0] + data_[1] * data_[1];
}

template <class T>
T Vector2<T>::norm() {
	return std::sqrt(*this * *this);
}

template <class T>
T Vector2<T>::distance(const Vector2<T>& v) {
	return (*this - v).norm();
}

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

typedef Vector2f Point2f;
typedef Vector2d Point2d;

#endif

