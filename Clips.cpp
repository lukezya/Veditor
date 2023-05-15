#include "pch.h"
#include "Clips.h"
#include "Clip.h"
#include <iostream>
#include <string>


Clips::Clips()
{
	noClips = 0;
}


Clips::~Clips()
{
	clips.clear();
}

void Clips::addClip(int iFrame) {
	if (noClips!=0&&clips[noClips-1].FrameInClip(iFrame)) {
		//if frame in another clip's highlights -> merge highlights
		clips[noClips-1].mergeClip(iFrame);
			
	}
	else {
		//new highlight, create another clip
		Clip newClip(iFrame - 8, iFrame + 3);
		clips.push_back(newClip);
		noClips += 1;
	}
}

void Clips::clipIt()
{
	for (int i = 0;i < clips.size();i++) {
		char showBuffer[5];
		sprintf_s(showBuffer, "%04d", i);
		std::string sCommand = "ffmpeg -i Ninja_Video_1_Trim_3.mp4 -ss " + clips[i].getBeginClip() + " -to "+clips[i].getEndClip()+" Clips/Clip"+std::string(showBuffer)+".mp4";
		system(sCommand.c_str());
	}
	//put names of clips to a textfile to concat with ffmpeg
	std::string sMp4ToTextfile = "(for %i in (Clips/*.mp4) do @echo file '%i') > Clips/clips.txt";
	system(sMp4ToTextfile.c_str());

	//concat clips
	std::string sConcatClips = "ffmpeg -f concat -i Clips/clips.txt -c copy Clips/Ninja_Video_1_Trim_3_Highlights.mp4";
	system(sConcatClips.c_str());
}

std::string Clips::showClips()
{
	std::string sClips = "";
	for (auto clip : clips) {
		std::cout << clip.showClip() << std::endl;
		sClips = sClips + clip.showClip() + "\n";
	}
	return sClips;
}
