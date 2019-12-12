//
//  test.cpp
//  fantastic-finale-tests
//
//  Created by SeungHoon Choi on 12/11/19.
//

#include <stdio.h>
#include "catch.hpp"
#include "../src/ofApp.h"
#include "../src/bayes/model.hpp"

TEST_CASE("Prior Probability") {
	SECTION("Non null number") {
		REQUIRE(1.0 == ComputePriors(2400));
	}
	
	SECTION("Testing for 0") {
		REQUIRE(0.0 == ComputePriors(0));
	}
}
