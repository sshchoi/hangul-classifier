//
//  image_generator.cpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 11/27/19.
//

#include "image_generator.h"

void image_generator::CreateImage() {
	
	// Create 28x28 Greyscale Mat with Black background.
	cv::Mat M (28, 28, CV_8UC1, cvScalar(0, 0, 0));
	
	// Find the size of the text.
	cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;
	
	std::cout << "Font scale: " << fontScale << std::endl;
	
	// If the width of the text is larger than 28 pixels, then decrease font scale and recursively try CreateImage();
	if(textSize.width > M.cols) {
		if(fontScale > 0.1) {
			fontScale -= 0.1;
		}
		count++;
		CreateImage();
	} else {
		// Put text in the center of the Mat.
		cv::putText(M, text, cvPoint((M.cols - textSize.width)/2, (M.rows + textSize.height - thickness)/2), fontFace, fontScale, cvScalar(255,255,255), thickness, 8);

		ofImage image;

		// Change Mat to ofImage.
		ofxCv::toOf(M, image);

		// Print and save image to given path within folder.
		std::string folder_path = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/";
		std::string file_name = folder_path + "trial" + to_string(count) + ".jpg";
		image.save(file_name);
	}
}

ofTexture image_generator::LoadKoreanTexture() {
	
	// Example String path that holds in Korean font.
	std::string file_path = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/fonts/CuteFont-Regular.ttf";
	
	// Settings of font to include unicode of Korean.
	ofTrueTypeFontSettings settings(file_path,24);
	settings.antialiased = true;
	
	// Allow for typing of Korean.
	settings.ranges = {
		ofAlphabet::Korean
	};
	ttf.load(settings);
	
	// Getting the text as a string texture.
	tex = ttf.getStringTexture("ㄱ");
	
	return tex;
}

std::string image_generator::LoadFonts(std::string directory_path) {
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

ofImage image_generator::TextureToImage(ofTexture &tex) {
	
}
