//
//  image.hpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 12/5/19.
//

#ifndef image_hpp
#define image_hpp

#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <iostream>

constexpr size_t IMAGE_SIZE = 28;
const char WHITE = ' ';
const int NUM_TRAINING_IMAGES = 2400;

struct Image {
    char pixels[IMAGE_SIZE][IMAGE_SIZE];

    std::vector<std::string> image;
    //What Korean character the image is.
    std::string classification;

};

/**
 * Creates an image with each pixel changed to 0 or 1 depending on whether or not its unshaded or not, respectively.
 * @param data_labels
 * @param data_text
 * @param dataset
 */
void ImageVector(std::string data_labels, std::string data_text, std::vector<Image> &dataset);

/**
 * Find total number of occurences for a certain class.
 * @param data_labels
 * @param wanted
 * @return Total number of occurences for a certain class as an integer.
 */
double TotalNumberOfSample(std::string data_labels, int wanted);

/**
 * Computes the prior probability (# of occurences for a certain class / # of all images)
 * @param occurrences The number of occurences for a certain class
 * @return The prior probability for a specific class.
 */
double ComputePriors(double occurrences);


#endif /* image_hpp */
