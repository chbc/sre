#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include<glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sre
{

/*!
	Class to handle rotations
*/
class Quaternion
{
	private:
		float w, x, y, z;

	public:
		Quaternion();

		void setRotation(const glm::vec3 &axis, float angle);
		void getMatrix(float *matrix);
		glm::mat4 getMatrix();
};

} // namespace

#endif
