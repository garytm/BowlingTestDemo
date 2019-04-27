#include "Ball.hpp"
#include<iostream>
using namespace glm;
void Ball::init(BallVertex* vertices, unsigned int verticesAmt, unsigned int* indices, unsigned int indicesAmt){
	IndexedModel model;
	for (unsigned int i = 0; i < verticesAmt; i++){
		model.positions.push_back(*vertices[i].GetPosition());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < indicesAmt; i++)
		model.indices.push_back(indices[i]);

	initModel(model);//intitialises the model using the information stored in the initModel method
}

void Ball::initModel(const IndexedModel& model){

	drawNum = model.indices.size();
	CreateModels(model);//Creates the model using CreateModels method
	BallCollisionSphere ballCollisionSphere();
}

void Ball::update() {
	if (control.isJustReleased(SDLK_SPACE)) {
		velocity.z += speed;
	}
	transform.SetPosition(transform.GetPosition() + velocity);
	ballCollisionSphere.SetPosition(transform.GetPosition());
	ballCollisionSphere.SetRadius(0.50f);
}

 void Ball::updateBallSphere(vec3 position,  float radius)
{
	ballCollisionSphere.SetPosition(position);
	ballCollisionSphere.SetRadius(radius);
}
 Ball::Ball(Input& input) :
	 control(input),
	 speed(10),
	 velocity(0.0f, 0.0f, 0.01f)
 {
	 drawNum = NULL;
 };

void Ball::loadModel(const string& nameOfFile){
	IndexedModel model = OBJModel(nameOfFile).ToIndexedModel();
	initModel(model);
}

Ball::~Ball(){
	glDeleteVertexArrays(1, &vertexAO);
}

void Ball::draw(){
	glBindVertexArray(vertexAO);
	glDrawElements(GL_TRIANGLES, drawNum, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, drawNum);
	glBindVertexArray(0);
}
void Ball::draw(const MoveableCamera& newCamera) {
	shader->ShaderBinding();
	shader->Update(transform, newCamera);
	draw();
}
void Ball::CreateModels(const IndexedModel& model) {
	
	glGenVertexArrays(1, &vertexAO);
	glBindVertexArray(vertexAO);

	glGenBuffers(BUFFER_AMT, vertexABs);

	glBindBuffer(GL_ARRAY_BUFFER, vertexABs[POSITION_VERTEXBUFFER]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexABs[TEXCOORD_VERTEXBUFFER]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexABs[NORMAL_VERTEXBUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexABs[INDEX_VERTEXBUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

