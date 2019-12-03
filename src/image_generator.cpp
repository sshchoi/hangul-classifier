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

void image_generator::LoadKorean() {
	
//	std::string file_path = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/fonts/CuteFont-Regular.ttf";
//	
//	
//	ofTrueTypeFont my_font;
//	my_font.load(file_path, fontScale);
//	my_font.drawString("hi!!", 10,10);
	
//	ofTrueTypeFontSettings settings(file_path, fontScale);
//	settings.antialiased = true;
//	settings.direction = OF_TTF_LEFT_TO_RIGHT;
//	settings.addRanges(ofAlphabet::Korean);
//	ofTrueTypeFont my_font;
//	my_font.load(settings);
//	my_font.drawString("ㅁㄴㅇ러ㅏㅣ;ㅁㄴㅇ리ㅏㅓ", 20, 10);
	
	
	
//	for (const auto & entry : std::filesystem::directory_iterator(file_path)) {
//		std::cout << entry.path() << std::endl;
//		//ofTrueTypeFontSettings(entry.path(), fontScale);
//		ofTrueTypeFont my_font;
//		my_font.load(entry.path(), fontScale);
//		my_font.drawString("hi!!", 100,100);
//	}
}
