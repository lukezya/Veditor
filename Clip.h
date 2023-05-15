#pragma once
#include <string>

class Clip
{
private:
	int iBegin;
	int iEnd;
	std::string secondsToShowable(int iSeconds);
public:
	Clip(int begin, int end) :iBegin(begin), iEnd(end) {};
	~Clip();
	bool FrameInClip(int iFrame);
	void mergeClip(int iFrame);

	std::string getBeginClip();
	std::string getEndClip();
	std::string getDuration();

	std::string showClip();
};

