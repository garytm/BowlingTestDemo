#include "Pin.hpp"
using namespace glm;

void Pin::init(PinVertex* vertices, unsigned int verticesAmt, unsigned int* indices, unsigned int indicesAmt) {
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

void Pin::initModel(const IndexedModel& model) {

	drawNum = model.indices.size();
	CreateModels(model);
	PinCollisionSphere pinCollisionSphere();
}

void Pin::updatePinSphere(vec3 position, float radius)
{
	pinCollisionSphere.SetPosition(position);
	pinCollisionSphere.SetRadius(radius);
}
Pin::Pin() {
	drawNum = NULL;
}

void Pin::loadModel(const string& nameOfFile) {
	IndexedModel model = OBJModel(nameOfFile).ToIndexedModel();
	initModel(model);
}

Pin::~Pin() {
	glDeleteVertexArrays(1, &vertexAO);
}

void Pin::draw() {
	glBindVertexArray(vertexAO);
	glDrawElements(GL_TRIANGLES, drawNum, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, drawNum);
	glBindVertexArray(0);
}
void Pin::draw(const MoveableCamera& newCamera) {
	shader->ShaderBinding();
	shader->Update(transform, newCamera);
	draw();
}
void Pin::CreateModels(const IndexedModel& model) {

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

