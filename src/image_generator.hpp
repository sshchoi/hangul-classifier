//
//  image_generator.hpp
//  fantastic-finale-seunghoon0821
//
//  Created by SeungHoon Choi on 11/27/19.
//

#ifndef image_generator_hpp
#define image_generator_hpp

#include <stdio.h>
#include "ofxOpenCv.h"

class image_generator {
private:
	ofImage characters;
	
public:
	void CreateImage();
};

/**
 Create method that  creates an image with a collection of the same character in different fonts.
 */


#endif /* image_generator_hpp */
