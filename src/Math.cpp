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
float Vector2::x() const {
	return data_[0];
}

float Vector2::y() const {
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
float Vector3::x() const {
	return data_[0];
}

float Vector3::y() const {
	return data_[1];
}

float Vector3::z() const {
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
 * Cross product
 */
Vector3 Vector3::cross(const Vector3& v) {
	float v0 = data_[1] * v.data_[2] - data_[2] * v.data_[1];
	float v1 = data_[2] * v.data_[0] - data_[0] * v.data_[2];
	float v2 = data_[0] * v.data_[1] - data_[1] * v.data_[0];
	return Vector3(v0, v1, v2);
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

/*
 * 3D Matrix
 */
Matrix3 Matrix3::identity() {
	Matrix3 matrix = zero();
	matrix.data_[0] = 1.0f;
	matrix.data_[4] = 1.0f;
	matrix.data_[8] = 1.0f;
	return matrix;
}

Matrix3 Matrix3::zero() {
	Matrix3 matrix;
	
	for (int i = 0; i < 9; i++)
		matrix.data_[i] = 0.0f;
		
	return matrix;
}
 
Matrix3::Matrix3() {
}

Matrix3::Matrix3(const Matrix3& m) {
	*this = m;
}

Matrix3& Matrix3::operator = (const Matrix3& m) {
	for (int i = 0; i < 9; i++)
		data_[i] = m.data_[i];
		
	return *this;
}

float* Matrix3::data() {
	return data_;
}

float& Matrix3::operator () (int r, int c) {
	return data_[3 * r + c];
}

Vector3 Matrix3::operator * (const Vector3& v) {
	float v0 = data_[0] * v.x() + data_[1] * v.y() + data_[2] * v.z();
	float v1 = data_[3] * v.x() + data_[4] * v.y() + data_[5] * v.z();
	float v2 = data_[6] * v.x() + data_[7] * v.y() + data_[8] * v.z();
	return Vector3(v0, v1, v2);
}

Matrix3 Matrix3::operator * (Matrix3& m) {
	Matrix3 matrix;
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float sum = 0.0f;
			
			for (int k = 0; k < 3; k++) {
				sum += (*this)(i, k) * m(k, j);
			}
			
			matrix(i, j) = sum;
		}
	}
	
	return matrix;
}

Matrix3 rotationMatrix3(const Vector3& axis, const float& angle) {
	float c = std::cos(angle);
	float s = std::sin(angle);
	
	Matrix3 matrix;
	
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

