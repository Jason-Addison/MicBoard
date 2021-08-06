#include "stdafx.h"
#include "FBO.h"

#include "WindowManager.h"

FBO::FBO()
{
}
FBO::FBO(int width, int height)
{
	this->width = width;
	this->height = height;
	create();
}

FBO::~FBO()
{
}

int FBO::createColourBufferAttachment(int attachment)
{
	GLuint colourBuffer = 0;
	glGenRenderbuffers(1, &colourBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, colourBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, colourBuffer);
	return colourBuffer;
}
void FBO::create()
{
	made = true;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	bind();
	int size = 0;
	uint32_t renderBuffers[8];
	addBuffer(1, GL_RGBA16);
	addBuffer(2, GL_RGBA16);
	addBuffer(7, GL_RGBA32F);
	for (int i = 0; i < 8; i++)
	{
		if (buffers[i] != 0)
		{
			renderBuffers[size++] = GL_COLOR_ATTACHMENT0 + i;
		}
	}
	glDrawBuffers(size, (GLenum*)renderBuffers);

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_INT, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenRenderbuffers(1, &depthTexture);
	glBindRenderbuffer(GL_RENDERBUFFER, depthTexture);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthTexture);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);


	unbind();
}
void FBO::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, width, height);
}
void FBO::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, WindowManager::getWidth(), WindowManager::getHeight());
}

void FBO::update(int width, int height)
{
	if (this->width != width || this->height != height)
	{
		this->width = width;
		this->height = height;
		destroy();
		create();
	}
}

void FBO::resolve(int readBuffer, FBO output)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, output.framebuffer);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->framebuffer);
	glReadBuffer(readBuffer);
	glBlitFramebuffer(0, 0, width, height, 0, 0, output.width, output.height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	//unbind();
}
void FBO::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 0);
}

void FBO::addBuffer(int attachment, int format)
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &buffers[attachment]);
	glBindTexture(GL_TEXTURE_2D, buffers[attachment]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, (GLint)format, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_2D, buffers[attachment], 0);
}

void FBO::destroy()
{
	for (int i = 0; i < 8; i++)
	{
		if (buffers[i] != 0)
		{
			glDeleteTextures(1, &buffers[i]);
			glDeleteRenderbuffers(1, &buffers[i]);
		}
	}
	glDeleteTextures(1, &texture);
	glDeleteRenderbuffers(1, &depthTexture);
	glDeleteFramebuffers(1, &framebuffer);
}

void FBO::addBuffer(int attachment)
{
	addBuffer(attachment, GL_RGBA16);
}