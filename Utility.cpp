#include "Utility.h"
 
Utility::Utility()
{
}

void Utility::SaveToFile(std::string filename, std::string contents)
{
	std::ofstream a_file(filename);
	// Outputs to example.txt through a_file
	a_file << contents;
	// Close the file stream explicitly
	a_file.close();
}


Utility::~Utility()
{
}
