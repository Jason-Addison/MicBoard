#include "stdafx.h"
#include "Log.h"
#include <iostream>
#include <Windows.h>

Log::Log()
{
}


Log::~Log()
{
}
static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void Log::out(std::string msg, int colour)
{
	if (1)
	{
		SetConsoleTextAttribute(console, colour);
		std::cout << msg << std::endl;
	}
	else
	{
		std::cout << "Unsupported OS!";
	}
}
void Log::outNNL(std::string msg)
{
	SetConsoleTextAttribute(console, WHITE);
	std::cout << msg;
}
void Log::outNNL(std::string msg, int colour)
{
	SetConsoleTextAttribute(console, colour);
	std::cout << msg;
}
void Log::out(std::string src, std::string msg)
{
	out("[" + src + "] : " + msg);
}
void Log::out(std::string src, std::string msg, int colour)
{
	outNNL("[");
	outNNL(src, colour);
	outNNL("] : " + msg + "\n");
}

void Log::out(std::string msg)
{
	std::cout << msg << '\n';
}
