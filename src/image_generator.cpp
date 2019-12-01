//
//  image_generator.cpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 11/27/19.
//

#include "image_generator.h"

void image_generator::CreateImage() {
	cv::Mat M (28, 28, CV_8UC1, cvScalar(0, 0, 0));
	
	cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;
	
	std::cout << "Font scale: " << fontScale << std::endl;
	
	if(textSize.width > M.cols) {
		if(fontScale > 0.1) {
			fontScale -= 0.1;
		}
		count++;
		CreateImage();
	} else {
		cv::putText(M, text, cvPoint((M.cols - textSize.width)/2, (M.rows + textSize.height - thickness)/2), fontFace, fontScale, cvScalar(255,255,255), thickness, 8);

		ofImage image;

		ofxCv::toOf(M, image);

		std::string file_name = "trial" + to_string(count) + ".jpg";
		image.save(file_name);
	}
}

void image_generator::LoadKorean() {
	std::string file_path = "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/fonts";
	
	for (const auto & entry : std::filesystem::directory_iterator(file_path)) {
		std::cout << entry.path() << std::endl;
	}
	
	//ofTrueTypeFontSettings(file_path, fontScale);
}
