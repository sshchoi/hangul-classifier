//
//  image_generator.hpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 11/27/19.
//

#ifndef image_generator_h
#define image_generator_h

#include <stdio.h>
#include "ofxOpenCv.h"
#include "ofMain.h"
#include "ofxCv.h"


class image_generator {
public:
	void CreateImage();
	void LoadKorean();
	
	string text = "Hi";
	int fontFace = cv::FONT_HERSHEY_PLAIN;
	int baseline = 0;
	int thickness = 1;
	double fontScale = 1;
	
	int count = 4;
};

#endif /* image_generator_hpp */
