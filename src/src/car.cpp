#include "car.h"
namespace moovit
{

    Car Car::FromJson(const nlohmann::json &js)
    {
        Car ret;
        ret.name = js.at("Name");
        ret.acceleration = js.at("Acceleration");
        ret.date = Date::FromString(js.at("Year"));
        return ret;
    }
    std::ostream &operator<<(std::ostream &os, const Car &car)
    {
        os << "Car: " << car.name << std::endl
           << "- Creation date: " << car.date << "- Acceleration " << car.acceleration << std::endl;
        return os;
    }

} // moovit