#include "stdafx.h"
#include "WAVE.h"
#include <windows.h>
#include <string>
#include <iostream>

WAVE::WAVE(const char* path)
{
	load(path);
}


WAVE::~WAVE()
{
}

void WAVE::load(const char * path)
{
	alGenBuffers((ALuint)1, &buffer);
	
	ALvoid *data;
	ALboolean loop = AL_FALSE;

	FILE *fp = NULL;
	fp = (FILE*)fopen(path, "rb");
	
	char type[4] = { 0, 0, 0, 0 };
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
	{
		printf("No RIFF\n");
	}
	fread(&size, sizeof(DWORD), 1, fp);
	fread(type, sizeof(char), 4, fp);
	
	if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
	{
		printf("Not WAVE\n");
	}
	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
	{
		printf("Not fmt \n");
	}
	fread(&chunkSize, sizeof(DWORD), 1, fp);
	fread(&formatType, sizeof(short), 1, fp);
	fread(&channels, sizeof(short), 1, fp);
	fread(&sampleRate, sizeof(DWORD), 1, fp);
	fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
	fread(&bytesPerSample, sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
	{
		printf("Missing data\n");
	}
	fread(&dataSize, sizeof(DWORD), 1, fp);

	unsigned char* buf = new unsigned char[dataSize];
	fread(buf, sizeof(BYTE), dataSize, fp);

	if (bitsPerSample == 8)
	{
		if (channels == 1)
		{
			format = AL_FORMAT_MONO8;
		}
		if (channels == 2)
		{
			format = AL_FORMAT_STEREO8;
		}
	}
	if (bitsPerSample == 16)
	{
		if (channels == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		if (channels == 2)
		{
			format = AL_FORMAT_STEREO16;
		}
	}
	ALuint frequency = sampleRate;
	alBufferData(buffer, format, buf, dataSize, frequency);
	this->buf = buf;
}
