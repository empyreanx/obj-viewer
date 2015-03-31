#ifndef _MATH_HPP
#define _MATH_HPP

class Vector2 {
	public:
		Vector2();
		Vector2(float x, float y);
		Vector2(const Vector2& v);
		Vector2& operator = (const Vector2& v);
		
		//accessors
		float x();
		float y();
		
		float* data();
		
		//operators
		Vector2 operator - ();
		Vector2 operator + (const Vector2& v);
		Vector2 operator - (const Vector2& v);
		
		Vector2& operator += (const Vector2& v);
		Vector2& operator -= (const Vector2& v);
		
		Vector2 operator * (const float& c);
		Vector2 operator / (const float& c);
		
		Vector2& operator *= (const float& c);
		Vector2& operator /= (const float& c);
		
		//inner product
		float operator* (const Vector2& v);
		
		//distance & length
		float norm();
		float distance(const Vector2& v);
		
	private:
		float data_[2];
};

class Vector3 {
	public:
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector3& v);
		Vector3& operator = (const Vector3& v);
	
		//accessors
		float x();
		float y();
		float z();
		
		float* data();
		
		//operators
		Vector3 operator - ();
		Vector3 operator + (const Vector3& v);
		Vector3 operator - (const Vector3& v);
		
		Vector3& operator += (const Vector3& v);
		Vector3& operator -= (const Vector3& v);
		
		Vector3 operator * (const float& c);
		Vector3 operator / (const float& c);
		
		Vector3& operator *= (const float& c);
		Vector3& operator /= (const float& c);
		
		//inner product
		float operator* (const Vector3& v);
		
		//distance & length
		float norm();
		float distance(const Vector3& v);
		
	private:
		float data_[3];
};

typedef Vector2 Point2;
typedef Vector3 Point3;

#endif
