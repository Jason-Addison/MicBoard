#include "stdafx.h"
#include "Chunk.h"
#include "GFX.h"
#include "Assets.h"
Chunk::Chunk()
{
}


Chunk::~Chunk()
{
}

void Chunk::generate()
{
}

void Chunk::render()
{
	float scale = 32;
	int tex = Assets::getTexture("grass")->texture;
	for (int i = 0; i < size; i++)
	{
		int x = i % chunkSize;
		int z = i / chunkSize;

		GFX::drawImage(x * scale, z * scale, scale, scale, tex);
	}
}
