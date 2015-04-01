#ifndef _VECTOR3_HPP
#define _VECTOR3_HPP

#include <cmath>

template <class T>
class Vector3 {
	public:
		static Vector3<T> zero();
	
		Vector3();
		Vector3(T x, T y, T z);
		Vector3(const Vector3<T>& v);
		Vector3& operator = (const Vector3<T>& v);
	
		//accessors
		T x() const;
		T y() const;
		T z() const;
		
		T* data();
		
		T& operator() (int i);
				
		//operators
		Vector3<T> operator - ();
		Vector3<T> operator + (const Vector3<T>& v);
		Vector3<T> operator - (const Vector3<T>& v);
		
		Vector3<T>& operator += (const Vector3<T>& v);
		Vector3<T>& operator -= (const Vector3<T>& v);
		
		Vector3<T> operator * (const T& c);
		Vector3<T> operator / (const T& c);
		
		Vector3<T>& operator *= (const T& c);
		Vector3<T>& operator /= (const T& c);
		
		//inner product
		T operator* (const Vector3<T>& v);
		
		//cross product
		Vector3<T> cross(const Vector3<T>& v);
		
		//distance & length
		T norm();
		T distance(const Vector3<T>& v);
		
	private:
		T data_[3];
};

template <class T>
Vector3<T> Vector3<T>::zero() {
	return Vector3<T>(0.0, 0.0, 0.0);
} 

template <class T>
Vector3<T>::Vector3() {
} 

template <class T>
Vector3<T>::Vector3(T x, T y, T z) {
	data_[0] = x;
	data_[1] = y;
	data_[2] = z;
}

template <class T>
Vector3<T>::Vector3(const Vector3<T>& v) {
	*this = v;
}

template <class T>
Vector3<T>& Vector3<T>::operator = (const Vector3<T>& v) {
	data_[0] = v.data_[0];
	data_[1] = v.data_[1];
	data_[2] = v.data_[2];
	return *this;
}

template <class T>
T Vector3<T>::x() const {
	return data_[0];
}

template <class T>
T Vector3<T>::y() const {
	return data_[1];
}

template <class T>
T Vector3<T>::z() const {
	return data_[2];
}

template <class T>
T* Vector3<T>::data() {
	return data_;
}

template <class T>
T& Vector3<T>::operator() (int i) {
	return data_[i];
}

template <class T>
Vector3<T> Vector3<T>::operator - () {
	return Vector3(-data_[0], -data_[1], -data_[2]);
}

template <class T>
Vector3<T> Vector3<T>::operator + (const Vector3& v) {
	return Vector3(data_[0] + v.data_[0], data_[1] + v.data_[1], data_[2] + v.data_[2]);
}

template <class T>
Vector3<T> Vector3<T>::operator - (const Vector3& v) {
	return Vector3(data_[0] - v.data_[0], data_[1] - v.data_[1], data_[2] - v.data_[2]);
}

template <class T>
Vector3<T>& Vector3<T>::operator += (const Vector3<T>& v) {
	data_[0] += v.data_[0];
	data_[1] += v.data_[1];
	data_[2] += v.data_[2];
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator -= (const Vector3<T>& v) {
	data_[0] -= v.data_[0];
	data_[1] -= v.data_[1];
	data_[2] -= v.data_[2];
	return *this;
}

template <class T>
Vector3<T> Vector3<T>::operator * (const T& c) {
	return Vector3<T>(data_[0] * c, data_[1] * c, data_[2] * c);
}

template <class T>
Vector3<T> Vector3<T>::operator / (const T& c) {
	return Vector3<T>(data_[0] / c, data_[1] / c, data_[2] / c);
}

template <class T>
Vector3<T>& Vector3<T>::operator *= (const T& c) {
	data_[0] *= c;
	data_[1] *= c;
	data_[2] *= c;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator /= (const T& c) {
	data_[0] /= c;
	data_[1] /= c;
	data_[2] /= c;
	return *this;
}

template <class T>
T Vector3<T>::operator* (const Vector3<T>& v) {
	return data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2];
}

template <class T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& v) {
	float v0 = data_[1] * v.data_[2] - data_[2] * v.data_[1];
	float v1 = data_[2] * v.data_[0] - data_[0] * v.data_[2];
	float v2 = data_[0] * v.data_[1] - data_[1] * v.data_[0];
	return Vector3<T>(v0, v1, v2);
}

template <class T>
T Vector3<T>::norm() {
	return std::sqrt(*this * *this);
}

template <class T>
T Vector3<T>::distance(const Vector3<T>& v) {
	return (*this - v).norm();
}

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

typedef Vector3f Point3f;
typedef Vector3d Point3d;

#endif
