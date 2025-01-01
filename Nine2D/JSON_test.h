#pragma once
#include <iostream>
#include "base\simdjson.h"
using namespace std;
using namespace simdjson;





bool Test_JSON()
{
	ondemand::parser parser;
    auto json = padded_string::load("farmer11.json");

    for (ondemand::object points : parser.iterate(json)) {
      for (auto point : points) {
        // Get the key corresponding the the field 'point'.
        std::cout << "-- " << std::string_view(point.unescaped_key());
        std::cout <<  std::endl;
      }
    }

/*
    // Parse and iterate through an array of objects
    for (ondemand::object points : parser.iterate(json)) {
      // Iterating through an object, you iterate through key-value pairs (a 'field').
      for (auto point : points) {
        // Get the key corresponding the the field 'point'.
        cout << "id: " << std::string_view(point.unescaped_key()) << ": (";
        // Get the value corresponding the the field 'point'.
        ondemand::object xyz = point.value();
        cout << xyz["x"].get_double() << ", ";
        cout << xyz["y"].get_double() << ", ";
        cout << xyz["z"].get_int64() << endl;
      }
    }

*/

	return true;
}
