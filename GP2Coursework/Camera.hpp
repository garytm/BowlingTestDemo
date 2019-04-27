#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;
//Header file holding all information for cameras used within the game
struct MoveableCamera
{
public:
	MoveableCamera(){
	}
	//When the camera is being set up it will be passed a position, field of view, aspect ratio and near and far clipping planes.
	void setupCamera(const vec3& position, float fieldOfView, float aspectRatio, float nearClip, float farClip){
		this->position = position;
		this->forward = vec3(0.0f, 0.0f, 1.0f);
		this->up = vec3(0.0f, 1.0f, 0.0f);
		this->projection = perspective(fieldOfView, aspectRatio, nearClip, farClip);
	}
	//Calculating the view and projection matrices and storing them in getVP
	inline mat4 getVP() const{
		return projection * lookAt(position, position + forward, up);
	}
	vec3 getPosition()
	{
		return this->position;
	}
	void CameraForward(float amt){
		position += forward * amt;
	}
	void CameraRight(float amt){
		position += cross(up, forward) * amt;
	}
	void CameraPitch(float angle){
		vec3 right = normalize(cross(up, forward));
		forward = vec3(normalize(rotate(angle, right) * vec4(forward, 0.0)));
		up = normalize(cross(forward, right));
	}
	void RotateY(float angle){
		static const vec3 UP(0.0f, 1.0f, 0.0f);

		mat4 rotation = rotate(angle, UP);

		forward = vec3(normalize(rotation * vec4(forward, 0.0)));
		up = vec3(normalize(rotation * vec4(up, 0.0)));
	}
private:
	mat4 projection;
	vec3 position;
	vec3 forward;
	vec3 up;
};