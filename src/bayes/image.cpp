//
//  image.cpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 12/5/19.
//

#include "image.hpp"

void CreateProbabilityModel() {
	std::vector<Image> training(NUM_TRAINING_IMAGES);
	std::string training_labels =  "/Users/seunghoonchoi/Documents/Coding/CS 126/of_v20191111_osx_release/apps/myApps/fantastic-finale-seunghoon0821/hanguldata/labels.txt";
	std::string training_images = argv[3];
	
	//Filling training vector with images and labels that are connected through its classification.
	ImageVector(training_labels, training_images, training);
	ShadedProbability(training, training_labels);
}


// TODO: Change std::string data_text to the folder of ofImages.
void ImageVector(std::string data_labels, std::string data_text, std::vector<Image> &dataset) {
	
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
	
	//Each image has its classification as the label it is given. Every 100 images, the label shifts to the next.
	file.open(data_text);
	int j = 0;
	for (int i = 0; i < labels.size(); i++) {
		do {
			dataset[j].classification = labels[i];
			j++;
		} while (j % 100 != 0);
	}
	
	//Each image is the vector string of 28 lines worth of text.
	int i = 0, z = 0;
	
	//Add all 28 lines per vector.
	while (!file.eof()) {
		getline(file, line);
		
		for (int k = 0; k < line.length(); k++) {
			if (line.at(k) == WHITE) {
				line.at(k) = '0';
			} else {
				line.at(k) = '1';
			}
		}
		
		dataset[i].image.push_back(line);
		z++;
		if (z % IMAGE_SIZE == 0) {
			i++;
		}
	}
	file.close();
}

double TotalNumberOfSample(std::string data_labels, int wanted) {
	//File stream of labels
	std::ifstream data(data_labels);
	std::string line;
	
	//Vector containing classifications in order
	std::vector<int> labels;
	for (int i = 0; getline(data, line); i++) {
		labels.push_back(stoi(line));
	}
	data.close();
	
	double num_of_occurrences = 0;
	
	//Number of occurences of class
	for (int i = 0; i < labels.size(); i++) {
		if (labels[i] == wanted) {
			num_of_occurrences++;
		}
	}
	
	return num_of_occurrences;
}

double ComputePriors(double occurrences) {
	return (occurrences / NUM_TRAINING_IMAGES);
}
