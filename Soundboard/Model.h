#pragma once
#include <gl\glew.h>
#include "GLFW\glfw3.h"
#include <vector>
#include "OBJMaterial.h"
class Model
{
public:

	Model();
	Model(GLuint vao, int vertexCount);
	Model(GLuint vao, GLuint elementBuffer, int vertexCount);
	~Model();

	std::vector<OBJMaterial> materials;

	std::string name;

	GLuint vao;
	int count;
	GLuint getVAO();
	int getCount();

	GLuint elementBuffer;
	GLuint getElementBuffer();

	void setTexture(int index, Texture texture);

	static Model load2DModel(std::vector<float> vertices);

	static Model load2DModel(std::vector<float> vertices, std::vector<float> texCoords);

	static Model loadIndexed3DModel(std::vector<float> vertices, std::vector<float> normals, std::vector<unsigned int> indices);

	static Model load3DModel(std::vector<float> vertices, std::vector<float> normals);

	static Model load3DModel(std::vector<float> vertices, std::vector<float> normals, std::vector<float> tex);

	static Model load3DModel(std::vector<float> vertices, std::vector<float> normals, std::vector<float> tex, std::vector<float> materials);

	static Model load3DModel(std::vector<float> vertices);

	void setMaterials(std::vector<OBJMaterial> materials);

	std::vector<OBJMaterial> getMaterials();

private:

	static GLuint generateVAO();

	static GLuint addVertexAttribute(int attrib, int size, std::vector<float> attribs);

	static GLuint addIndicesBuffer(std::vector<unsigned int> indices);
};

