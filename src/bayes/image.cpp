//
//  image.cpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 12/5/19.
//
#include "image.hpp"

void ImageVector(std::string data_labels, std::string images_directory_path, std::vector<Image> &dataset, int num) {
	
	//File stream of labels
	std::ifstream file(data_labels);
	std::string line;
	
	//Vector containing classifications in order
	std::vector<std::string> labels;
	for (int i = 0; getline(file, line); i++) {
		if(line == "") {
			break;
		} else {
			labels.push_back(line);
		}
	}
	file.close();
	
	// Each image has its classification as the label it is given. Every 100 images, the label shifts to the next.
	int image_count = 0;
	for (int i = 0; i < labels.size(); i++) {
		do {
			dataset[image_count].classification = labels[i];
			image_count++;
		} while (image_count % num != 0);
	}
	
	// Each image consists of 28x28 pixels.
	int i = 0, z = 0;
	
	// Loop through all images and create dataset vector.
	for(int num = 1; num < NUM_TRAINING_IMAGES + 1; num++) {
		std::string path = images_directory_path + "/" + std::to_string(num) + ".jpg";
		
		ofImage img;
		if(img.load(path)) {
			img.setImageType(OF_IMAGE_GRAYSCALE);
			ofPixels &pixels = img.getPixels();
			
			for (int k = 0; k < IMAGE_SIZE; k++) {
				std::string line = "";
				for (int l = 0; l < IMAGE_SIZE; l++) {
					
					if(pixels[IMAGE_SIZE*k + l] > 180) {
						line.push_back('1');
					} else {
						line.push_back('0');
					}
				}
				dataset[i].image.push_back(line);
			}
			i++;
		}
	}
}

double ComputePriors(double occurrences) {
	return (occurrences / NUM_TRAINING_IMAGES);
}
