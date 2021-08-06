#pragma once
#include <string>
#define BLUEa 1
#define BLUEb 2
#define BLUEc 3
#define BLUEd 4
#define BLUEe 5
#define BLUEf 6
#define BLUEg 7
#define BLUEh 8
#define BLUE 9
#define GREEN 10
#define LBLUE 11
#define RED 12
#define MAGENTA 13
#define YELLOW 14
#define WHITE 15

class Log
{
public:
	Log();
	~Log();

	static void out(std::string src, std::string msg, int colour);

	static void out(std::string src, std::string msg);

	static void out(std::string msg, int colour);

	static void outNNL(std::string msg, int colour);

	static void outNNL(std::string msg);

	static void out(std::string msg);

};

