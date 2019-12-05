//
//  image_generator.cpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 11/27/19.
//

#include "image_generator.h"

void image_generator::LoopAllFonts(std::string font_directory_path) {
	// Loops through all files in the given directory.
	for (const auto & entry : std::filesystem::directory_iterator(font_directory_path)) {
		std::cout << entry.path() << std::endl;
		ofTrueTypeFont font = LoadKoreanTTF(entry.path());
		ofImage image = TTFToImage(font);
		
		std::string save_path = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/test_images/";
		SaveImage(image, save_path);
	}
}

ofTrueTypeFont image_generator::LoadKoreanTTF(const boost::filesystem::path font_path) {
	// Settings of font to include unicode of Korean.
	ofTrueTypeFontSettings settings(font_path,24);
	settings.antialiased = true;
	
	// Allow for typing of Korean.
	settings.ranges = {
		ofAlphabet::Korean
	};
	
	// Loads TTF Settings into TTF.
	ttf.load(settings);
	
	return ttf;
}

ofImage image_generator::TTFToImage(ofTrueTypeFont &ttf) {
	fboText.allocate(28, 28);
	
	// Add drawn TTF into fboText.
	fboText.begin();
			ofBackground(0);
			ofSetColor(255);
			ttf.drawString("ㄱ", 5, 18);
	fboText.end();
	
	// Add fboText data into ofPixels to be made into an ofImage that can be saved.
	ofPixels pixels;
	fboText.readToPixels(pixels);

	ofImage image;
	image.setFromPixels(pixels);
	
	return image;
}

void image_generator::SaveImage(ofImage image, std::string training_images_directory) {
	// Set up naming of saved training image file.
	std::string file_name = training_images_directory + to_string(count) + ".jpg";
	image.save(file_name);
	count++;
}
