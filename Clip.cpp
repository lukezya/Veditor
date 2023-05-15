#include "pch.h"
#include "Clip.h"
#include <string>


std::string Clip::secondsToShowable(int iSeconds)
{
	int iHour = 0, iMin = 0, iSec = 0;
	//seconds to minutes ->
	iMin = iSeconds / 60;
	iHour = iMin / 60;
	iSec = iSeconds - iMin * 60;
	iMin = iMin - iHour * 60;

	char showBuffer[9];
	sprintf_s(showBuffer, "%02d:%02d:%02d", iHour, iMin, iSec);

	return std::string(showBuffer);
}

Clip::~Clip()
{
}

bool Clip::FrameInClip(int iFrame)
{
	//get new frames range
	int newFrameBegin = iFrame - 8;
	int newFrameEnd = iFrame + 3;

	if (((iBegin < newFrameBegin) && (newFrameBegin < iEnd))|| ((iBegin < newFrameEnd) && (newFrameEnd < iEnd)))
		return true;
	else
		return false;
}

void Clip::mergeClip(int iFrame)
{
	//get new frames range
	int newFrameBegin = iFrame - 8;
	int newFrameEnd = iFrame + 3;

	//need to bound so not to misclip

	//check what need to be changed
	if (newFrameBegin < iBegin)
		iBegin = newFrameBegin;

	if (newFrameEnd > iEnd)
		iEnd = newFrameEnd;
}

std::string Clip::getBeginClip()
{
	return secondsToShowable(iBegin);
}

std::string Clip::getEndClip()
{
	return secondsToShowable(iEnd);
}

std::string Clip::getDuration()
{
	return secondsToShowable(iEnd - iBegin);
}

std::string Clip::showClip()
{
	return secondsToShowable(iBegin) + " - " + secondsToShowable(iEnd);
}
