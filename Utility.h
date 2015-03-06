#pragma once

#include <fstream>

#include <iostream>

#include <string>

class Utility
{
public:
	Utility();
	~Utility();
	static void Utility::SaveToFile(std::string filename, std::string contents);
};

