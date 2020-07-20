//
//  image_generator.cpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 11/27/19.
//
#include "image_generator.h"

void image_generator::CreateTrainingSet(std::string labels_file, std::string font_directory_path) {
	std::ifstream file(labels_file);
	std::string line;

	for (int i = 0; getline(file, line); i++) {
		LoopAllFonts(font_directory_path, line);
	}
	file.close();
}

void image_generator::LoopAllFonts(std::string font_directory_path, std::string text) {
	// Loops through all files in the given directory.
	for (const auto & entry : std::filesystem::directory_iterator(font_directory_path)) {
		font = LoadKoreanTTF(entry.path());
		ofImage image = TTFToImage(font, text);
		cv::Mat mat_image = Deskew(image);
		
		ofImage deskewed_image;
		ofxCv::toOf(mat_image, deskewed_image);

		std::string save_path = "../../hanguldata/training_images/";
		SaveImage(deskewed_image, save_path);
	}
}

ofTrueTypeFont image_generator::LoadKoreanTTF(const boost::filesystem::path font_path) {
	// Settings of font to include unicode of Korean.
	ofTrueTypeFontSettings settings(font_path, fontScale);
	settings.antialiased = true;
	settings.contours = true;
	
	// Allow for typing of Korean.
	settings.ranges = {
		ofAlphabet::Korean
	};
	
	// Loads TTF Settings into TTF.
	ttf.load(settings);	
	
	CheckTTFSize(ttf, font_path);
	return ttf;
}

void image_generator::CheckTTFSize(ofTrueTypeFont &ttf, const boost::filesystem::path font_path) {
	char_width = ttf.stringWidth("가");
	char_height = ttf.stringHeight("가");

	// If font size is larger than image size, then decrease fontScale. If it is to small, then increase fontScale.
	if(char_width > kPixelCount || char_height > kPixelCount) {
		fontScale--;
		LoadKoreanTTF(font_path);
	} else if (char_width < kPixelCount-kRange && char_height < kPixelCount-kRange) {
		fontScale++;
		LoadKoreanTTF(font_path);
	}
}

ofImage image_generator::TTFToImage(ofTrueTypeFont &ttf, std::string character) {
	fboText.allocate(kPixelCount, kPixelCount);
	
	// Add drawn TTF into fboText.
	fboText.begin();
			ofBackground(0);
			ofSetColor(255);
	
	float x_center = TextToCenter(ttf, character, 'x');
	float y_center = TextToCenter(ttf, character, 'y');

	// Set image in the middle of the canvas.
	float x = (kPixelCount)/2 - x_center;
	float y = (kPixelCount)/2 - y_center;

	ttf.drawString(character, x, y);
	fboText.end();
	
	// Add fboText data into ofPixels to be made into an ofImage that can be saved.
	ofPixels pixels;
	fboText.readToPixels(pixels);

	ofImage image;
	image.setFromPixels(pixels);
	
	return image;
}

float image_generator::TextToCenter(ofTrueTypeFont &ttf, std::string character, char coordinate) {
	bool vflip = true;
	// Set filled as false in order to get contours.
	bool filled = false;
	
	vector <ofPath> paths = font.getStringAsPoints(character, vflip, filled);
	// Get outline of only the first element in paths, as the text is of length 1.
	ofPolyline polylines = paths[0].getOutline()[0];
	
	if(coordinate == 'x') {
		return polylines.getCentroid2D().x;
	} else if (coordinate == 'y') {
		return polylines.getCentroid2D().y;
	} else {
		throw "Incorrect Coordinate Type.";
	}
}

cv::Mat image_generator::Deskew(ofImage& image) {
	cv::Mat mat_img = ofxCv::toCv(image);
	int SZ = 20;
	float affineFlags = cv::WARP_INVERSE_MAP|cv::INTER_LINEAR;

	cv::Mat converted;

	cv::cvtColor(mat_img, converted, CV_BGR2GRAY);

	cv::Moments m = moments(converted);
	if(abs(m.mu02) < 1e-2) {
		// No deskewing needed.
		return mat_img.clone();
	}
	// Calculate skew based on central momemts.
	double skew = m.mu11/m.mu02;
	// Calculate affine transform to correct skewness.
	cv::Mat warpMat = (cv::Mat_<double>(2,3) << 1, skew, -0.5*SZ*skew, 0, 1 , 0);

	cv::Mat imgOut = cv::Mat::zeros(mat_img.rows, mat_img.cols, mat_img.type());
	warpAffine(mat_img, imgOut, warpMat, imgOut.size(),affineFlags);

	return imgOut;
}

void image_generator::SaveImage(ofImage image, std::string training_images_directory) {
	// Set up naming of saved training image file.
	std::string file_name = training_images_directory + to_string(count) + ".jpg";
	image.save(file_name);
	count++;
	
	// Print out confirmation statement every 10 images loaded.
	if(count%100 == 0) {
		std::cout << to_string(count) << " images loaded." << std::endl;
	}
}
