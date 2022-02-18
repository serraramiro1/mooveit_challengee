#pragma once
#include <stdint.h>
#include <iostream>
#include <string.h>
#include <sstream>      // std::stringstream

namespace moovit
{
    struct Date
    {
        uint32_t year;
        uint16_t month;
        uint16_t day;

        // constructs a Date object from a string of the form "YYYY-MM-DD"
        static Date FromString(const std::string &str);

        bool operator<(const Date& rhs) const;
        bool operator>(const Date& rhs) const;
    };
    std::ostream &operator<<(std::ostream &os, const Date &date);
} // moovit