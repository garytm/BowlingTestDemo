#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Camera.hpp"
using namespace glm;
//Header file holding all information for transforms used within the game
struct Transform
{
public:
	//Setting the position, rotation and scaling of the transforms
	Transform(const vec3& position = vec3(), const vec3& rotation = vec3(), const vec3& scaling = vec3(1.0f, 1.0f, 1.0f)){
		this->position = position;
		this->rotation = rotation;
		this->scaling = scaling;
	}
	//Getting the position of the models. Creating a rotation and scale matrix based on
	//previously defined parameters and then multiplying them all together
	inline mat4 GetModel() const{
		mat4 positionMatrix = translate(position);
		mat4 scaleMatrix = scale(scaling);
		mat4 rotateX = rotate(rotation.x, vec3(1.0, 0.0, 0.0));
		mat4 rotateY = rotate(rotation.y, vec3(0.0, 1.0, 0.0));
		mat4 rotateZ = rotate(rotation.z, vec3(0.0, 0.0, 1.0));
		mat4 rotateMat = rotateX * rotateY * rotateZ;

		return positionMatrix * rotateMat * scaleMatrix;
	}

	//Getting the View/Projection matrix from the Camera and multiplying it by the 
	//Model to return the MVP matrix
	inline mat4 GetMVP(const MoveableCamera& camera) const{
	mat4 ViewProjection = camera.getVP();
	mat4 Model = GetModel();

	return ViewProjection * Model;
	}
	//Getters for positon, rotation and scale
	inline vec3 GetPosition() { return position; }
	inline vec3 GetRotation() { return rotation; }
	inline vec3 GetScale() { return scaling; }
	//Setters
	inline void SetPosition(vec3& position) { this->position = position; } 
	inline void SetRotation(vec3& rotation) { this->rotation = rotation; }
	inline void SetScale(vec3& scale) { this->scaling = scale; }
protected:
private:
	vec3 position;
	vec3 rotation;
	vec3 scaling;
};


