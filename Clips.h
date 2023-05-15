#pragma once

#include <vector>
#include "Clip.h"

class Clips
{
private:
	std::vector<Clip> clips;
	int noClips;
public:
	Clips();
	~Clips();
	void addClip(int iFrame);
	void clipIt();
	std::string showClips();
};

