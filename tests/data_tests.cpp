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

    const V2D expected_data = {{"1","Goroka Airport","Goroka","Papua New Guinea","GKA","AYGA","-6.081689834590001","145.391998291","5282","10","U","Pacific/Port_Moresby","airport","OurAirports"},\
                                {"2","Madang Airport","Madang","Papua New Guinea","MAG","AYMD","-5.20707988739","145.789001465","20","10","U","Pacific/Port_Moresby","airport","OurAirports"},\
                                {"3","Mount Hagen Kagamuga Airport","Mount Hagen","Papua New Guinea","HGU","AYMH","-5.826789855957031","144.29600524902344","5388","10","U","Pacific/Port_Moresby","airport","OurAirports"}};


    REQUIRE(data == expected_data);
}