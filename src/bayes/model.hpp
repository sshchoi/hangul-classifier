//
//  model.hpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 12/5/19.
//

#ifndef model_hpp
#define model_hpp

#pragma once

#include "image.hpp"
#include <math.h>

constexpr size_t NUM_CLASSES = 24;  // The extent of the basic Korean alphabet.
const double K = 0.1;

/**
 * Represents a Naive Bayes classification model for determining the
 * likelihood that an individual pixel for an individual class is
 * white or black.
 */
struct Model {
	double probs[IMAGE_SIZE][IMAGE_SIZE][NUM_CLASSES];
	int shaded_count[IMAGE_SIZE][IMAGE_SIZE];
};

/**
 * Increases the shaded count for an index by 1 if the character at that index in the binary image is 1.
 * @param dataset Image structure.
 * @param model Model structure.
 */
void ShadedCount(Image &dataset, Model &model);

/**
 * Goes to the line of the text file that was specified.
 * @param file The file that will be searched through.
 * @param num The line number.
 */
std::ifstream& GotoLine(std::ifstream& file, unsigned int num);

/**
 * Calculates probability of a certain pixel being shaded or not per class and outputs it to a txt file.
 * @param dataset The vector filled with Image.
 */
void ShadedProbability(std::vector<Image> dataset);

/**
 * Copies details from probabilities text to create 2D vector of probabilities for each number
 * in testing to be a certain class.
 *
 * @param probabilities_txt Probability of a certain pixel being shaded or not per class.
 * @param guess Testing image vector.
 * @param training_labels Labels of training images.
 * @return 2D vector of probabilities for each number in testing to be a certain class
 */
std::vector<std::vector<double>>
MapClassification(std::string probabilities_txt, std::vector<Image> &guess, std::string training_labels);

/**
 * Choosing largest posterior probability
 * @param classifications
 * @return Class with largest posterior probability
 */
int PosteriorProbabilities(std::vector<double> classifications);

#endif /* model_hpp */
