#include "Math.hpp"

#include <cmath>

/*
 * 2D Vector
 */
Vector2::Vector2() {
	data_[0] = data_[1] = 0;
}

Vector2::Vector2(float x, float y) {
	data_[0] = x;
	data_[1] = y;
}

Vector2::Vector2(const Vector2& v) {
	*this = v;
}

Vector2& Vector2::operator = (const Vector2& v) {
	data_[0] = v.data_[0];
	data_[1] = v.data_[1];
	return *this;
}

/*
 * Accessors
 */
float Vector2::x() {
	return data_[0];
}

float Vector2::y() {
	return data_[1];
}

float* Vector2::data() {
	return data_;
}

/*
 * Operators
 */
Vector2 Vector2::operator -() {
	return Vector2(-data_[0], -data_[1]);
}

Vector2 Vector2::operator + (const Vector2& v) {
	return Vector2(data_[0] + v.data_[0], data_[1] + v.data_[1]);
}

Vector2 Vector2::operator - (const Vector2& v) {
	return Vector2(data_[0] - v.data_[0], data_[1] - v.data_[1]);
}

Vector2& Vector2::operator += (const Vector2& v) {
	data_[0] += v.data_[0];
	data_[1] += v.data_[1];
	return *this;
}

Vector2& Vector2::operator -= (const Vector2& v) {
	data_[0] -= v.data_[0];
	data_[1] -= v.data_[1];
	return *this;
}

Vector2 Vector2::operator * (const float& c) {
	return Vector2(data_[0] * c, data_[1] * c);
}

Vector2 Vector2::operator / (const float& c) {
	return Vector2(data_[0] / c, data_[1] / c);
}

Vector2& Vector2::operator *= (const float& c) {
	data_[0] *= c;
	data_[1] *= c;
	return *this;
}

Vector2& Vector2::operator /= (const float& c) {
	data_[0] /= c;
	data_[1] /= c;
	return *this;
}

/*
 * Inner product
 */
float Vector2::operator* (const Vector2& v) {
	return data_[0] * data_[0] + data_[1] * data_[1];
}

/*
 * Distance & length
 */
float Vector2::norm() {
	return std::sqrt(*this * *this);
}

float Vector2::distance(const Vector2& v) {
	return (*this - v).norm();
}

/*
 * 3D Vector
 */
Vector3::Vector3() {
	data_[0] = data_[1] = data_[2] = 0;
} 

Vector3::Vector3(float x, float y, float z) {
	data_[0] = x;
	data_[1] = y;
	data_[2] = z;
}

Vector3::Vector3(const Vector3& v) {
	*this = v;
}

Vector3& Vector3::operator = (const Vector3& v) {
	data_[0] = v.data_[0];
	data_[1] = v.data_[1];
	data_[2] = v.data_[2];
	return *this;
}

/*
 * Accessors
 */
float Vector3::x() {
	return data_[0];
}

float Vector3::y() {
	return data_[1];
}

float Vector3::z() {
	return data_[2];
}

float* Vector3::data() {
	return data_;
}

/*
 * Operators
 */
Vector3 Vector3::operator - () {
	return Vector3(-data_[0], -data_[1], -data_[2]);
}

Vector3 Vector3::operator + (const Vector3& v) {
	return Vector3(data_[0] + v.data_[0], data_[1] + v.data_[1], data_[2] + v.data_[2]);
}

Vector3 Vector3::operator - (const Vector3& v) {
	return Vector3(data_[0] - v.data_[0], data_[1] - v.data_[1], data_[2] - v.data_[2]);
}

Vector3& Vector3::operator += (const Vector3& v) {
	data_[0] += v.data_[0];
	data_[1] += v.data_[1];
	data_[2] += v.data_[2];
	return *this;
}

Vector3& Vector3::operator -= (const Vector3& v) {
	data_[0] -= v.data_[0];
	data_[1] -= v.data_[1];
	data_[2] += v.data_[2];
	return *this;
}

Vector3 Vector3::operator * (const float& c) {
	return Vector3(data_[0] * c, data_[1] * c, data_[2] * c);
}

Vector3 Vector3::operator / (const float& c) {
	return Vector3(data_[0] / c, data_[1] / c, data_[2] / c);
}

Vector3& Vector3::operator *= (const float& c) {
	data_[0] *= c;
	data_[1] *= c;
	data_[2] *= c;
	return *this;
}

Vector3& Vector3::operator /= (const float& c) {
	data_[0] /= c;
	data_[1] /= c;
	data_[2] /= c;
	return *this;
}

/*
 * Inner product
 */
float Vector3::operator* (const Vector3& v) {
	return data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2];
}

/*
 * Distance & length
 */
float Vector3::norm() {
	return std::sqrt(*this * *this);
}

float Vector3::distance(const Vector3& v) {
	return (*this - v).norm();
}
