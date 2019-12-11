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
#include "ofxCv.h"
#include "ofxOpenCv.h"

constexpr size_t IMAGE_SIZE = 28;
const char WHITE = ' ';
const int NUM_TRAINING_IMAGES = 2400;
const int NUM_FONTS = 100;

struct Image {
    char pixels[IMAGE_SIZE][IMAGE_SIZE];

    std::vector<std::string> image;
    // What Korean character the image is.
    std::string classification;

};

/**
 * Creates an image with each pixel changed to 0 or 1 depending on whether or not its unshaded or not, respectively.
 * @param data_labels
 * @param data_text
 * @param dataset
 */
void ImageVector(std::string data_labels, std::string images_directory_path, std::vector<Image> &dataset);

/**
 * Computes the prior probability (# of occurences for a certain class / # of all images)
 * @param occurrences The number of occurences for a certain class
 * @return The prior probability for a specific class.
 */
double ComputePriors(double occurrences);


#endif /* image_hpp */
