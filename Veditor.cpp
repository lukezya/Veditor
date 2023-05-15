// Program just taking an image -> bilateralFilter image -> take ROI -> take White pixels -> Flip white and black colours -> OCR basically the white pixels.

#include "pch.h"
#include "Clips.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include <iostream> // std::cout
#include <opencv2/core/core.hpp> // cv::Mat
#include <opencv2/highgui/highgui.hpp> // cv::imread()
#include <opencv2/imgproc/imgproc.hpp> // cv::Canny()

#include <fstream>
#include <string>
#include <regex>

using namespace std;
using namespace cv;

int main()
{
	ofstream myfile("highlights.txt");

	String folderpath = "./Ninja_Video_1_Trim_3_Frames/*.png";
	vector<String> filenames;
	glob(folderpath, filenames);

	Clips clips;

	cout << "Highlights:" << endl;
	myfile << "Highlights:" << endl;

	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path - might be able to train tesseract on few characters and digits
	if (api->Init(NULL, "eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	for (size_t j = 0; j < filenames.size(); j++) {
		Mat input = imread(filenames[j], IMREAD_COLOR);

		//smooth/blur image keeping sharp 
		int i = 20;
		Mat bilateral;
		bilateralFilter(input, bilateral, i, i * 2, i / 2);

		//color boundaries
		//white boundary
		Vec3b minWBGR(200, 130, 190);
		Vec3b maxWBGR(255, 255, 255);

		//regions of interest
		Rect rectEliminated(720, 745, 500, 25);

		Mat imgEliminated = bilateral(rectEliminated); //white and yellow

		//get masks
		Mat pixEliminated;

		//Mat white, yellow;
		inRange(imgEliminated, minWBGR, maxWBGR, pixEliminated);

		//flip black and white colours
		threshold(pixEliminated, pixEliminated, 0, 255, THRESH_BINARY_INV);

		//read ROIs
		api->SetImage((uchar*)pixEliminated.data, pixEliminated.size().width, pixEliminated.size().height, pixEliminated.channels(), pixEliminated.step1());
		const char *knockedText = api->GetUTF8Text();
		//---------------------------------------
		//Check if highlight
		string s(knockedText);
		smatch mElim;
		regex eElim("(ELI|LIM|IMI|MIN|INA|NAT|ATE|TED)");

		if (regex_search(s, mElim, eElim)) {
			myfile << filenames[j] << " - Elimination" << endl;
			cout << filenames[j] << " - Elimination" << endl;

			//get frame number - number of seconds
			smatch mFrame;
			regex eFrame("[0-9]*.png");   //
			int iFrame = 0;
			if (regex_search(filenames[j], mFrame, eFrame)) {
				for (auto x : mFrame) {
					string check(x);
					int pos = check.find(".");
					check.erase(pos, 4); //take away .png
					iFrame = stoi(check);
				}
			}

			//got iFrame
			clips.addClip(iFrame);

		}
		else {
			//check for knockdown
			regex eKD("(KNO|NOC|OCK|CKE|KED|ED |D D| DO|DOW|OWN)");
			smatch mKD;
			if (regex_search(s, mKD, eKD)) {
				myfile << filenames[j] << " - Knock Down" << endl;
				cout << filenames[j] << " - Knock Down" << endl;

				//get frame number - number of seconds
				smatch mFrame;
				regex eFrame("[0-9]*.png");   //
				int iFrame = 0;
				if (regex_search(filenames[j], mFrame, eFrame)) {
					for (auto x : mFrame) {
						string check(x);
						int pos = check.find(".");
						check.erase(pos, 4); //take away .png
						iFrame = stoi(check);
					}
				}

				//got iFrame
				clips.addClip(iFrame);
			}

		}
		
		//---------------------------------------
		delete[] knockedText;

	};

	myfile<<clips.showClips();
	clips.clipIt();
	api->End();
	myfile.close();

	return 0;
}
