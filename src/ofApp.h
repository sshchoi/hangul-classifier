#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "image_generator.h"

class ofApp : public ofBaseApp{
private:
	const double kWindowSize = ofGetWindowWidth();
	const double kPixelCount = 28;
	const double kThickness = 2;
	const double kBrushSize = kWindowSize / (kPixelCount / kThickness);
	
	const std::string kFontPath = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/fonts";
	const std::string kLabelsPath = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/labels.txt";
	
	image_generator H;
	
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	ofFbo fbo;
	
	ofxButton clear_button;
	ofxButton analyze_button;
	ofxPanel gui;

};
