#pragma once
#include <iostream>
#include "car.h"
#include "json.hpp"
#include "curl_easy.h"
#include "json.hpp"
#include "car.h"
#include <optional>
#include <unordered_set>
#include <queue>


namespace moovit
{
    class App
    {
    public:
        enum class CLI_OPTION
        {
            FASTEST_CAR = 0,
            UNIQUE_BRANDS,
            TEN_NEWEST_CARS,
            REQUEST_INFO
        };
        App() = default;
        CLI_OPTION GetOptionFromPrompt() const;
        void Run();

    private:
        const nlohmann::json GetJsonData() const;
        std::vector<Car> GetTenNewestCarsFromJsonData(const nlohmann::json &js) const;
        uint16_t GetResponseCode() const;
        Car GetFastestCarFromJsonData(const nlohmann::json &js) const;
        std::unordered_set<std::string> GetUniqueBrandsFromJsonData(const nlohmann::json &js) const;
        static CLI_OPTION OptionFromString(const std::string& str);
        const std::string kDataURL{"https://raw.githubusercontent.com/vega/vega/master/docs/data/cars.json"};
    };


} // moovit