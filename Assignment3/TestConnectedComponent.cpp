#include "catch.hpp"
#include "ConnectedComponent.h"
#include <unordered_map>
#include <set>
#include <memory>
#include <utility>

using ComponentYSetPtr = std::unique_ptr<std::set<int>>;
using ComponentMap = std::unordered_map<int, ComponentYSetPtr>;

TEST_CASE("CONSTRUCTORS", "[default]"){
    yhxjin001::ConnectedComponent testComponent;
    testComponent.id = 0;
    testComponent.pixels = std::make_unique<ComponentMap>();

    SECTION("ADD POINT"){
        testComponent.add_point(4, 12);
        ComponentMap & pixelMap = *testComponent.pixels;
        for (int yVal : *pixelMap[4]){
            REQUIRE(yVal == 12);
        }
    }

    SECTION ("COPY CONSTRUCTOR"){
        testComponent.add_point(3, 56);
        yhxjin001::ConnectedComponent copiedComoponent(testComponent);
        REQUIRE(*((*copiedComoponent.pixels)[3]->begin()) == 56);
    }
    
    SECTION ("MOVE CONSTRUCTOR"){
        testComponent.add_point(3, 56);
        yhxjin001::ConnectedComponent copiedComoponent(std::move(testComponent));
        REQUIRE(*((*copiedComoponent.pixels)[3]->begin()) == 56);
    }


    yhxjin001::ConnectedComponent testComponent2; 
    SECTION("< OPERATOR"){
        testComponent2.add_point(3, 12);
        testComponent2.add_point(2, 24);
        testComponent.add_point(1, 5);
        REQUIRE((testComponent < testComponent2) == true);
        REQUIRE((testComponent2 < testComponent) == false);
    }

    SECTION("COPY ASSIGNMENT"){
        testComponent.add_point(3, 56);
        testComponent2 = testComponent;
        REQUIRE(*((*testComponent2.pixels)[3]->begin()) == 56);
    }

    SECTION("MOVE ASSIGNMENT"){
        testComponent.add_point(3, 56);
        testComponent2 = std::move(testComponent);
        REQUIRE(*((*testComponent2.pixels)[3]->begin()) == 56);
        REQUIRE(testComponent.id == -1);
    }

}


// TEST_CASE("COPYING", "[copy]"){
    
// }