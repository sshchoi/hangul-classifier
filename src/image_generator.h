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
	/**
	 Creates the 2400 image training set.
	 @param labels_file The file path of the labels text file.
	 @param font_directory_path The path of the directory with all fonts that the user wishes to be looped through.
	 */
	void CreateTrainingSet(std::string labels_file, std::string font_directory_path);
	
	/**
	 Loops through all of the fonts in the given directory path with the given text.
	 @param font_directory_path The path of the directory with all fonts that the user wishes to be looped through.
	 @param text The string that will be produced in all of the fonts.
	 */
	void LoopAllFonts(std::string font_directory_path, std::string text);
	
	/**
	 Returns the ofTrueTypeFont from the given file path.
	 @param font_path File path of the font.
	 @return ofTrueTypeFont from the file path.
	 */
	ofTrueTypeFont LoadKoreanTTF(const boost::filesystem::path font_path);
	
	/**
	 Creates an ofImage with the given character printed out with the given ofTrueTypeFont.
	 @param ttf ofTrueTypeFont with settings that will be checked.
	 @param character The text that will be printed out onto the ofImage.
	 @return ofImage with character printed out with the given ofTrueTypeFont.
	*/
	void CheckTTFSize(ofTrueTypeFont &ttf, const boost::filesystem::path font_path);
	
	/**
	 Creates an ofImage with the given character printed out with the given ofTrueTypeFont.
	 @param ttf ofTrueTypeFont with correct settings in place.
	 @param character The text that will be printed out onto the ofImage.
	 @return ofImage with character printed out with the given ofTrueTypeFont.
	*/
	ofImage TTFToImage(ofTrueTypeFont &ttf, std::string character);
	
	
	//TODO: Fix param names.
	/**
	 Centers the text in the ofImage to increase the classifier's effectiveness.
	 @param img The unfixed ofImage.
	 @return The ofImage with the centered text.
	 */
	float TextToCenter(ofTrueTypeFont &ttf, std::string character, char coordinate);
	
	/**
	 Deskews text images to allow classifier to identify characters easier.
	 @param image The original image that is skewed.
	 @return Mat with the deskewed text.
	 */
	cv::Mat Deskew(ofImage& image);
	
	/**
	 Takes in an ofImage and saves it to the given directory.
	 @param image ofImage that will be saved as a jpg file.
	 @param training_images_directory The directory where training images will be saved to.
	*/
	void SaveImage(ofImage image, std::string training_images_directory);
	
	ofTrueTypeFont ttf;
	ofFbo fboText;
	ofTrueTypeFont font;
	
	float char_width;
	float char_height;
		
	int count = 1;
};

#endif /* image_generator_hpp */
