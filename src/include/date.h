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
        static Date FromString(const std::string &str)
        {
            Date ret;
            std::string aux;
            uint8_t cnt{0};
            std::stringstream ss(str);

            while (std::getline(ss, aux, '-'))
            {
                switch (cnt)
                {
                case 0:
                    ret.year = std::atoi(aux.c_str());
                    break;
                case 1:
                    ret.month = std::atoi(aux.c_str());
                    break;
                case 2:
                    ret.day = std::atoi(aux.c_str());
                    break;

                default:
                    std::stringstream err{"Invalid date format: "};
                    err << str;
                    throw std::runtime_error(err.str());
                }
                ++cnt;
            }
            return ret;
        }

        bool operator<(const Date& rhs) const
        {
            return year < rhs.year || month < rhs.month || day < rhs.day;
        }
        bool operator>(const Date& rhs) const
        {
            return year < rhs.year || month < rhs.month || day < rhs.day;
        }
    };
    std::ostream &operator<<(std::ostream &os, const Date &date)
    {
        os << "Date: " << date.year << "-" << date.month << "-" << date.day << std::endl;
        return os;
    }
} // moovit