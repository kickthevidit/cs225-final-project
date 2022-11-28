#include <catch2/catch_test_macros.hpp>

#include <iostream>

#include "utils.h"
#include "airport.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


typedef std::vector<std::vector<std::string>> V2D;

TEST_CASE("file_to_V2D Public Simple Small Test 1", "[weight=5]") {
    V2D data = fileToV2D("../data/smallTest.txt");

    const V2D expected_data = {{"1", "2", "3", "Hello"},\
                                {"45", "6", "seven"},\
                                {"3.14", "pi"}};

    REQUIRE(data == expected_data);
}