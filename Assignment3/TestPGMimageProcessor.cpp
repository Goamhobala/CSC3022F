// TestPGMimageProcessor.cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PGMimageProcessor.h"
#include <string>

using namespace yhxjin001;
TEST_CASE("Processing Image", "[handle]"){
    PGMimageProcessor processor;
    string fileName = "Birds.pgm";
    processor.read(fileName);
    int width = 1018; int height = 1016;
    processor.getDims(width, height);
    SECTION("Extract Components"){
        REQUIRE(processor.extractComponents(35, 1000) == 8);
    }
    processor.extractComponents(35, 1000);
    SECTION("Filter Components"){
        REQUIRE(processor.filterComponentsBySize(4009, 6448) == 5);
    }

    SECTION("Largest Component"){
        REQUIRE(processor.getLargestSize() == 7671);
    }

    SECTION("Smallest Component"){
        REQUIRE(processor.getSmallestSize() == 4007);
    }

    SECTION("Write Component"){
        std::string output = "birdsOutput.pgm";
        REQUIRE(processor.writeComponents(output) == true);
    }

}