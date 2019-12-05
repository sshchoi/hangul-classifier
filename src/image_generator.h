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
private:
	const double kPixelCount = 28;
	const double kRange = 5;
	int fontScale = 32;
	
public:
	void CreateTrainingSet();
	void LoopAllFonts(std::string font_directory_path);
	ofTrueTypeFont LoadKoreanTTF(const boost::filesystem::path font_path);
	void CheckTTFSize(ofTrueTypeFont &ttf, const boost::filesystem::path font_path);
	ofImage TTFToImage(ofTrueTypeFont &ttf);
	void SaveImage(ofImage image, std::string training_images_directory);
	cv::Mat Deskew(ofImage& image);
	
	ofTrueTypeFont ttf;
	ofTexture tex;
	ofFbo fboText;
	ofTrueTypeFont font;
	
	float char_width;
	float char_height;
	
	int count = 1;
};

#endif /* image_generator_hpp */
