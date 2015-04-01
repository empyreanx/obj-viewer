#ifndef _ARCBALL_HPP
#define _ARCBALL_HPP

#include "Math/Matrix3.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"

class Arcball {
	public:
		Arcball(const Vector3f& center, const float& radius);
		
		void setCenter(const Vector3f& center);
		Vector3f center();
		
		void setRadius(const float& radius);
		float radius();
		
		Matrix3f rotation(const Vector2f& start, const Vector2f& end);
		
	private:
		Vector3f center_;
		float radius_;
};

#endif
