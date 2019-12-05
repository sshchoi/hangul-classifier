#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofBackground(0);

	gui.setup();
	gui.add(clear_button.setup("clear"));
	gui.add(analyze_button.setup("analyze"));

	fbo.allocate(kWindowSize, kWindowSize);
	fbo.begin();
	ofClear(0);
	fbo.end();
	
//	H.CreateImage();			// <-------- Use when needed to test.
	H.LoadKoreanTexture();				// <-------- Use when needed to test.
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	if(clear_button) {
		fbo.begin();
		ofClear(0);
		fbo.end();
	}
	
	if(analyze_button) {
		// TODO: Put scanned image into trained naive bayes classifier.
		ofPixels myPixels;
		fbo.readToPixels(myPixels);
		
		ofImage image (myPixels);
		
		image.resize(28, 28);
		
		std::string folder_path = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/";
		
		// TODO: Delete the naming using time if not needed.
		auto p = std::chrono::system_clock::now();
		std::time_t t = std::chrono::system_clock::to_time_t(p);
		
		std::string file_name = folder_path + to_string(t) + ".jpg";
		image.save(file_name);
	}
	
	fbo.draw(0, 0);
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	// Same procedure as mousePressed, with placeholders for the parameters.
	ofApp::mousePressed(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	fbo.begin();
	ofSetColor(ofColor::white);
	ofDrawRectangle(mouseX-(kBrushSize/2),mouseY-(kBrushSize/2),kBrushSize,kBrushSize);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
