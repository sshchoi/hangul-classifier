//
//  model.h
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 12/5/19.
//

#ifndef model_h
#define model_h

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
 * @param dataset Image structure
 * @param model Model structure
 */
void ShadedCount(Image &dataset, Model &model) {
    for (int b = 0; b < IMAGE_SIZE; b++) {
        for (int c = 0; c < IMAGE_SIZE; c++) {
            //If character is 1, then increase shaded count for that index.
            if (dataset.image[b].at(c) == '1') {
                model.shaded_count[b][c]++;
            }
        }
    }
}

/**
 * Calculates probability of a certain pixel being shaded or not per class and outputs it to a txt file.
 * @param dataset
 */
void ShadedProbability(std::vector<Image> dataset, std::string path) {
    std::vector<Model> model(NUM_CLASSES);

    //Looping through each possible class.
    for (int i = 0; i < NUM_CLASSES; i++) {
        //Looping through numbers 0-9
        for (int j = 0; j < NUM_TRAINING_IMAGES; j++) {
            //Loop through dataset to find classification that matches 0-9.
            if (dataset[j].classification == i) {
                //Loop through the entire image
                ShadedCount(dataset[j], model[i]);
            }
        }
        for (int a = 0; a < IMAGE_SIZE; a++) {
            for (int b = 0; b < IMAGE_SIZE; b++) {
                // Using the given equation, calculating the numerator and denominator for
                // probability of a certain pixel to be shaded or not for the given class.
                // Probability equation: ((k + # of times F[i][j] ​= f when class=c) / (2k + TotalNumberOfSample))
                double numerator = (K + model[i].shaded_count[a][b]);
                double denominator = ((2 * K) + TotalNumberOfSample(path, i));

                model[i].probs[a][b][i] = (numerator / denominator);
            }
        }
    }

    //Create an output file where the probability model will be.
    std::ofstream output_file("/Users/seunghoonchoi/Documents/Coding/CLion/HW9 Naive Numbers/probability_model.txt");

    //Output in each line the probability for each class per pixel in order into the file.
    for (int i = 0; i < model.size(); i++) {
        for (int a = 0; a < IMAGE_SIZE; a++) {
            for (int b = 0; b < IMAGE_SIZE; b++) {

                output_file << model[i].probs[a][b][i] << std::endl;
            }
        }
    }
    output_file.close();
}

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
MapClassification(std::string probabilities_txt, std::vector<Image> &guess, std::string training_labels) {

    std::ifstream probability_model(probabilities_txt);
    std::vector<Model> probability(NUM_CLASSES);

    //Copy details of probabilities_txt input into a Model vector.
    while (!probability_model.eof()) {
        for (int i = 0; i < NUM_CLASSES; i++) {
            for (int a = 0; a < IMAGE_SIZE; a++) {
                for (int b = 0; b < IMAGE_SIZE; b++) {
                    std::string line;
                    getline(probability_model, line);

                    //Avoid error cause by scanning last empty line.
                    if (line == "") {
                        break;
                    }
                    probability[i].probs[a][b][i] = std::stod(line);
                }
            }
        }
    }

    std::vector<std::vector<double>> log_probability = {};
    double total;

    //Looping through all of the testing image vector.
    for (int i = 0; i < guess.size(); i++) {
        std::vector<double> newColumn;
        log_probability.push_back(newColumn);

        //Looping through all of the classes (numbers from 0-9).
        for (int j = 0; j < NUM_CLASSES; j++) {
            double a = 0;
            log_probability[i].push_back(a);

            //Looping through each pixel of the image.
            for (int a = 0; a < IMAGE_SIZE; a++) {
                for (int b = 0; b < IMAGE_SIZE; b++) {
                    //Convert image so that if shaded, turn into 1, if not, then 0.
                    if (guess[i].image[a][b] == '1') {
                        total += log(probability[j].probs[a][b][j]);
                    } else {
                        total += log(1 - probability[j].probs[a][b][j]);
                    };
                }
            }

            //Compute prior probabilities with Laplace Smoothing per class for each pixel.
            double log_probability_class = log(ComputePriors(NUM_FONTS));
            log_probability[i][j] = log_probability_class + total;

            total = 0;
        }
    }

    return log_probability;
}

/**
 * Choosing largest posterior probability
 * @param classifications
 * @return Class with largest posterior probability
 */
int PosteriorProbabilities(std::vector<double> classifications) {
    int max = classifications[0];
    int max_index = 0;

    //Loops through all posterior probabilities to find the largest one.
    for (int i = 1; i < classifications.size(); i++) {
        if (classifications[i] > max) {
            max = classifications[i];
            max_index = i;
        }
    }
    return max_index;
}

#endif /* model_h */
