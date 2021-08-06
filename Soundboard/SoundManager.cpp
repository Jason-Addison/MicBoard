#include "stdafx.h"
#include "SoundManager.h"
#include "al.h"
#include "alc.h"
#include <string>
#include <windows.h>
#include <iostream>
#include "WAVE.h"
#include "Sound.h"
#include "Log.h"
#include "AL/alut.h"
#include "efx.h"
#include "efx-creative.h"
#include "EFX-Util.h"

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

ALCdevice* device;
ALCcontext* context;
const ALCchar* list_audio_devices(const ALCchar *devices)
{
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	fprintf(stdout, "Devices list:\n");
	fprintf(stdout, "----------\n");
	int i = 0;
	while (device && *device != '\0' && next && *next != '\0') {
		fprintf(stdout, "%s\n", device);
		if (i == 1)
		{
			return device;
		}
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
		i++;
	}
	fprintf(stdout, "----------\n");
	return NULL;
}

void SoundManager::start()
{
	ALboolean enumeration;
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (enumeration == AL_FALSE)
	{
	}
	const ALCchar* name = list_audio_devices(alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER));
	device = alcOpenDevice(name);

	if (!device)
	{
		printf("Error with device\n");
	}

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
	{
		printf("Error with context\n");
	}
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	
	alListenerf(AL_GAIN, 2);
	//alListener3f(AL_VELOCITY, 0, 0, 0);
	//alListenerfv(AL_ORIENTATION, listenerOri);
	alListenerf(AL_AIR_ABSORPTION_FACTOR, 100);
	//std::cout << "Data Size : " << dataSize << "\n";
}

void SoundManager::stop()
{
}
