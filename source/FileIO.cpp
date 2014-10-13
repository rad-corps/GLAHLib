#include "FileIO.h"

#include <string>
#include <fstream>

std::string LoadFileToStr(std::string fileName_)
{
	std::string data;
	//open shader file
	std::ifstream fileStream(fileName_.c_str());
	//if that worked ok, load file line by line
	if(fileStream.is_open())
	{
		std::string Line = "";
		while(std::getline(fileStream, Line))
		{
			data += "\n" + Line;
		}
		fileStream.close();
	}
	return data;
}