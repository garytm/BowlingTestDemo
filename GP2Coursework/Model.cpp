#include "Model.hpp"
using namespace glm;

void Model::init(Vertex* vertices, unsigned int verticesAmt, unsigned int* indices, unsigned int indicesAmt) {
	IndexedModel model;
	for (unsigned int i = 0; i < verticesAmt; i++) {
		model.positions.push_back(*vertices[i].GetPosition());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < indicesAmt; i++)
		model.indices.push_back(indices[i]);

	initModel(model);
}

void Model::initModel(const IndexedModel& model) {

	drawNum = model.indices.size();
	CreateModels(model);
	CollisionSphere collisionSphere();
}

void Model::updateSphere(vec3& position, float& radius)
{
	collisionSphere.SetPosition(position);
	collisionSphere.SetRadius(radius);
}
Model::Model() {
	drawNum = NULL;
}

void Model::loadModel(const string& nameOfFile) {
	IndexedModel model = OBJModel(nameOfFile).ToIndexedModel();
	initModel(model);
}

Model::~Model() {
	glDeleteVertexArrays(1, &vertexAO);
}

void Model::draw() {
	glBindVertexArray(vertexAO);
	glDrawElements(GL_TRIANGLES, drawNum, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, drawNum);
	glBindVertexArray(0);
}
void Model::draw(const MoveableCamera& newCamera) {
	shader->ShaderBinding();
	shader->Update(transform, newCamera);
	draw();
}
void Model::CreateModels(const IndexedModel& model) {

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

