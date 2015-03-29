#ifndef _MATH_HPP
#define _MATH_HPP

class Vector2 {
	public:
		Vector2(float x, float y);
		Vector2(const Vector2& vector);
		Vector2& operator = (const Vector2& vector);
	
		float* data();
	
	private:
		float v_[2];
};

class Vector3 {
	public:
		Vector3(float x, float y, float z);
		Vector3(const Vector3& vector);
		Vector3& operator = (const Vector3& vector);
	
		float* data();
	
	private:
		float v_[3];
};

typedef Vector2 Point2;
typedef Vector3 Point3;

#endif
