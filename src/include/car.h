#pragma once
#include <stdint.h>
#include <string.h>
#include "date.h"
#include "json.hpp"

// smaple JSON data
/*{"Acceleration":19.4,"Cylinders":4,
"Displacement":119,
"Horsepower":82,
"Miles_per_Gallon":31,
"Name":"chevy s-10",
"Origin":"USA",
"Weight_in_lbs":2720,
"Year":"1982-01-01"}

*/
namespace moovit{
struct Car{
    std::string name;
    Date date;
    float acceleration;

    static Car FromJson(const nlohmann::json& js){
        Car ret;
        ret.name = js.at("Name");
        ret.acceleration = js.at("Acceleration");
        ret.date = Date::FromString(js.at("Year"));
        return ret;

    };
};
std::ostream& operator<<(std::ostream& os, const Car& car){
    os << "Car: " << car.name << std::endl <<"- Creation date: " << car.date << "- Acceleration " << car.acceleration << std::endl;;
    return os;
}

}//moovit