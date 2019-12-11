//
//  image.cpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 12/5/19.
//

#include "image.hpp"

void ImageVector(std::string data_labels, std::string images_directory_path, std::vector<Image> &dataset) {
	
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
		} while (image_count % NUM_FONTS != 0);
	}
	
	// Each image consists of 28x28 pixels.
	int i = 0, z = 0;
	
	// Loop through all images and create dataset vector.
	for (const auto & entry : std::filesystem::directory_iterator(images_directory_path)) {
		
		ofImage img;
		std::string line = "";
		if(img.load(entry.path())) {
			for (int k = 0; k < IMAGE_SIZE; k++) {
				for (int l = 0; l < IMAGE_SIZE; l++) {
					if (img.getColor(l, k) == ofColor::black) {
						line.push_back('0');
					} else {
						line.push_back('1');
					}
				}
				dataset[i].image.push_back(line);
				z++;
				if (z % IMAGE_SIZE == 0) {
					i++;
				}
			}
		}
	}
}

double ComputePriors(double occurrences) {
	return (occurrences / NUM_TRAINING_IMAGES);
}
