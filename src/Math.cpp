#include "Math.hpp"

Vector2::Vector2(float x, float y) {
	v_[0] = x;
	v_[1] = y;
}

Vector2::Vector2(const Vector2& vector) {
	*this = vector;
}

Vector2& Vector2::operator = (const Vector2& vector) {
	v_[0] = vector.v_[0];
	v_[1] = vector.v_[1];
	return *this;
}

float* Vector2::data() {
	return v_;
}

/*glm::vec2 Vector2::glm() {
	return glm::vec2(v_[0], v_[1]);
}*/

Vector3::Vector3(float x, float y, float z) {
	v_[0] = x;
	v_[1] = y;
	v_[2] = z;
}

Vector3::Vector3(const Vector3& vector) {
	*this = vector;
}

Vector3& Vector3::operator = (const Vector3& vector) {
	v_[0] = vector.v_[0];
	v_[1] = vector.v_[1];
	v_[2] = vector.v_[2];
	return *this;
}

float* Vector3::data() {
	return v_;
}

/*glm::vec3 Vector3::glm() {
	return glm::vec3(v_[0], v_[1], v_[2]);
}*/
