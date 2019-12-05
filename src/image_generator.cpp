//
//  image_generator.cpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 11/27/19.
//

#include "image_generator.h"

std::string image_generator::LoopAllFonts(std::string directory_path) {
	int to_count = 0;
	
	// Loops through all files in the given directory.
	for (const auto & entry : std::filesystem::directory_iterator(directory_path)) {
			std::cout << entry.path() << std::endl;
			//ofTrueTypeFontSettings(entry.path(), fontScale);
			ofTrueTypeFont my_font;
			my_font.load(entry.path(), fontScale);
			my_font.drawString("hi!!", 100,100);
			
			to_count++;
		}
	std::cout << "Number of fonts: " << to_count << std::endl;
}

ofTrueTypeFont image_generator::LoadKoreanTTF(std::string font_path) {
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
	image.save("file.jpg");
}
