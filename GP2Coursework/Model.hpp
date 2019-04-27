#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
#include "Transform.hpp"
#include "Shader.hpp"
using namespace glm;
using namespace std;
//Header file holding all information for models used within the game
struct CollisionSphere {
public:
	CollisionSphere()
	{
	}

	CollisionSphere(const vec3& position, const float& radius)
	{
		this->position = position;
		this->radius = radius;
	}

	vec3* GetPosition() { return &position; }
	float* GetRadius() { return &radius; }

	void SetPosition(vec3& position) { this->position = position; }
	void SetRadius(float& radius) { this->radius = radius; }
private:
	vec3 position;
	float radius;
};
//Vertex struct which will hold all relevant information for vertices
struct Vertex {
public://Setting the position, texture co-ordinates and normals for vertices
	Vertex(const vec3& position, const vec2& texCoord, const vec3& normal) {
		this->position = position;
		this->texCoord = texCoord;
		this->normal = normal;
	}
	//Getters for the position, texture co-ordinates and normals.
	//Allows .GetPosition() etc. to be used during initialisation
	vec3* GetPosition() { return &position; }
	vec2* GetTexCoord() { return &texCoord; }
	vec3* GetNormal() { return &normal; }
private:
	vec3 position;
	vec2 texCoord;
	vec3 normal;
};

class Model {
public:
	Model();
	~Model();

	Transform transform;
	Shader* shader;

	void draw();
	//init is used to initialise everything required to begin loading models into the game
	void init(Vertex* vertices, unsigned int verticeAmt, unsigned int* indices, unsigned int indiceAmt);
	void loadModel(const string& nameOfFile);
	void initModel(const IndexedModel& model);
	void CreateModels(const IndexedModel& model);
	void updateSphere(vec3& position, float& radius);
	void draw(const MoveableCamera& newCamera);


	//Getting the position of the spheres that will be used for collision detection
	vec3 getSpherePosition()
	{
		return*collisionSphere.GetPosition();
	}
	//Getting the radius
	float getSphereRadius()
	{
		return*collisionSphere.GetRadius();
	}

private:
	//An enum containing information used for the vertex buffers
	enum {
		POSITION_VERTEXBUFFER,
		TEXCOORD_VERTEXBUFFER,
		NORMAL_VERTEXBUFFER,
		INDEX_VERTEXBUFFER,
		BUFFER_AMT
	};

	CollisionSphere collisionSphere;
	GLuint vertexAO;
	//Storing all of the buffers in an array
	GLuint vertexABs[BUFFER_AMT];
	unsigned int drawNum;
};

