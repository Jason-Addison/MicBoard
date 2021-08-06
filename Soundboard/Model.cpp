#include <Windows.h>
#include "stdafx.h"
#include "Model.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#pragma comment(lib, "C:\\Users\\Owner\\Downloads\\glew-2.1.0-win32 (1)\\glew-2.1.0\\lib\\Release\\Win32\\glew32.lib")
#include "Util.h"
#include <vector>
#include "Model.h"
#include <iostream>
GLuint vao;
int count;
GLuint elementBuffer;

Model::Model()
{

}
Model::Model(GLuint vao, int count)
{
	this->vao = vao;
	this->count = count;
}
Model::Model(GLuint vao, GLuint elementBuffer, int count)
{
	this->vao = vao;
	this->count = count;
	this->elementBuffer = elementBuffer;
}

Model::~Model()
{

}

GLuint Model::getVAO()
{
	return vao;
}

int Model::getCount()
{
	return count;
}

GLuint Model::getElementBuffer()
{
	return elementBuffer;
}
void Model::setMaterials(std::vector<OBJMaterial> materials)
{
	this->materials = materials;
}

std::vector<OBJMaterial> Model::getMaterials()
{
	return materials;
}

void Model::setTexture(int index, Texture texture)
{
	materials.at(index).texture = texture;
}

Model Model::load2DModel(std::vector<float> vertices)
{
	GLuint vao = generateVAO();

	addVertexAttribute(0, 2, vertices);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return Model(vao, vertices.size());
}
Model Model::load2DModel(std::vector<float> vertices, std::vector<float> texCoords)
{
	GLuint vao = generateVAO();

	addVertexAttribute(0, 2, vertices);
	addVertexAttribute(1, 2, texCoords);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return Model(vao, vertices.size());
}

Model Model::loadIndexed3DModel(std::vector<float> vertices, std::vector<float> normals, std::vector<unsigned int> indices)
{
	GLuint vao = generateVAO();
	GLuint elementBuffer = 0;

	addVertexAttribute(0, 3, vertices);
	addVertexAttribute(1, 3, normals);
	elementBuffer = addIndicesBuffer(indices);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return Model(vao, elementBuffer, indices.size());
}
Model Model::load3DModel(std::vector<float> vertices, std::vector<float> normals)
{
	GLuint vao = generateVAO();

	if (vertices.size() != 0)
	{
		addVertexAttribute(0, 3, vertices);
		addVertexAttribute(1, 3, normals);
	}
	else
	{
		std::cerr << "Model without data!\n";
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return Model(vao, vertices.size());
}
Model Model::load3DModel(std::vector<float> vertices, std::vector<float> normals, std::vector<float> tex)
{
	GLuint vao = generateVAO();

	addVertexAttribute(0, 3, vertices);
	addVertexAttribute(1, 3, normals);
	addVertexAttribute(2, 2, tex);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return Model(vao, vertices.size());
}
Model Model::load3DModel(std::vector<float> vertices, std::vector<float> normals, std::vector<float> tex, std::vector<float> materials)
{
	GLuint vao = generateVAO();

	addVertexAttribute(0, 3, vertices);
	addVertexAttribute(1, 3, normals);
	addVertexAttribute(2, 2, tex);
	addVertexAttribute(3, 3, materials);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return Model(vao, vertices.size());
}
Model Model::load3DModel(std::vector<float> vertices)
{
	GLuint vao = generateVAO();

	addVertexAttribute(0, 3, vertices);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return Model(vao, vertices.size());
}

GLuint Model::generateVAO()
{
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	return vao;
}

GLuint Model::addVertexAttribute(int attrib, int size, std::vector<float> attribs)
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, attribs.size() * sizeof(float), &attribs[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, 0, NULL);
	return vbo;
}

GLuint Model::addIndicesBuffer(std::vector<unsigned int> indices)
{
	GLuint elementBuffer;
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	return elementBuffer;
}