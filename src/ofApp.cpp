#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofBackground(255);
	
	gui.setup();
	gui.add(clear_button.setup("clear"));
	gui.add(analyze_button.setup("analyze"));
	
	fbo.allocate(1280,720);
	fbo.begin();
	ofClear(255);
	fbo.end();

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	if(clear_button) {
		fbo.allocate(1280,720);
		fbo.begin();
		ofClear(255);
		fbo.end();
	}
	
	if(analyze_button) {
		//TODO: Scan image into a square, then put into naive bayes.
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
	fbo.begin();
	ofSetColor(ofColor::black);
	ofDrawRectangle(mouseX-25,mouseY-25,50,50);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
