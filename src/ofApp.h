#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "image_generator.h"
#include "image.hpp"
#include "model.hpp"

class ofApp : public ofBaseApp{
private:
	const double kWindowSize = ofGetWindowWidth();
	const double kPixelCount = 28;
	const double kThickness = 2;
	const double kBrushSize = kWindowSize / (kPixelCount / kThickness);
	const int kTestingSize = 96;
	const int kTrainingSize = 2400;
	const int kNumCharacters = 24;
	const int kMinBrightness = 180;
    
    const std::string kHangulDataPath = ofDirectory("hanguldata/").getAbsolutePath();
	
	const std::string kFontPath = kHangulDataPath + "/fonts";
	const std::string kLabelsPath = kHangulDataPath + "/labels.txt";
    const std::string kTrainingImagesPath = kHangulDataPath + "/training_images";
	const std::string kTestingLabelsPath = kHangulDataPath + "/testing_labels.txt";
	const std::string kTestingImagesPath = kHangulDataPath + "/test_images";
	const std::string kProbabilityModel = kHangulDataPath + "/probability_model.txt";
	
	image_generator H;
	
public:
	void setup();
	void draw();

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	
	void CreateProbabilityModel();
	void TestModelAccuracy();
	
	ofFbo fbo;
	
	ofxButton clear_button;
	ofxButton analyze_button;
	ofxPanel gui;
	ofTrueTypeFont print;
	std::string line;

};
