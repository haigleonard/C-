#include "pch.h"
#include "Song.h"

Song::~Song()
{
}

void Song::print()
{
	std::cout << "\t\t" << name << std::endl;
}