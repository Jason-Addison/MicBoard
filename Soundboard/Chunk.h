#pragma once
class Chunk
{
public:
	Chunk();
	~Chunk();

	const static int chunkSize = 16;
	const static int chunkHeight = 1;
	const static int size = chunkSize * chunkHeight * chunkSize;
	//GLuint vbo;
	int tiles[size];

	void generate();

	void render();
};

