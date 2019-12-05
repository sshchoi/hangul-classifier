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
	void LoopAllFonts(std::string font_directory_path);
	ofTrueTypeFont LoadKoreanTTF(const boost::filesystem::path font_path);
	ofImage TTFToImage(ofTrueTypeFont &ttf);
	void SaveImage(ofImage image, std::string training_images_directory);
	
	ofTrueTypeFont ttf;
	ofTexture tex;
	ofFbo fboText;
	
	int count = 0;
};

#endif /* image_generator_hpp */
