#include "app.h"

namespace moovit
{
    App::CLI_OPTION App::GetOptionFromPrompt() const
    {
        const std::unordered_set<std::string> kAvailableOptions{"fastest", "unique", "ten_newest", "info"};
        std::cout << "Select an option from the following list: " << std::endl;
        for (const auto &option : kAvailableOptions)
        {
            std::cout << option << std::endl;
        }
        std::cout << std::endl;
        // prompt user for input
        std::string input;
        while (true)
        {
            std::cin >> input;
            if (kAvailableOptions.count(input) > 0)
            {
                break;
            }
            std::cout << "Invalid option. Please try again." << std::endl;
        }
        return OptionFromString(input);
    };
    void App::Run()
    {
        auto opt = GetOptionFromPrompt();
        switch (opt)
        {
        case CLI_OPTION::FASTEST_CAR:
            std::cout << "Fastest car: " << std::endl
                      << GetFastestCarFromJsonData(GetJsonData()) << std::endl;
            break;
        case CLI_OPTION::UNIQUE_BRANDS:
            std::cout << "Unique brands: " << std::endl;
            for (const auto &brand : GetUniqueBrandsFromJsonData(GetJsonData()))
            {
                std::cout << "- " << brand << std::endl;
            }

            break;
        case CLI_OPTION::TEN_NEWEST_CARS:
            for (const auto &car : GetTenNewestCarsFromJsonData(GetJsonData()))
            {
                std::cout << car << std::endl;
            }

            break;
        case CLI_OPTION::REQUEST_INFO:
            auto response_code = GetResponseCode();
            std::cout << "Request info:" << std::endl;

            std::cout << "- Endpoint :" << kDataURL << std::endl;
            std::cout << "- Response code :" << response_code << std::endl;

            break;
        }
    }

    std::vector<Car> App::GetTenNewestCarsFromJsonData(const nlohmann::json &js) const
    {
        static constexpr uint16_t kMaxCars = 10;
        auto cmp = [](const Car &lhs, const Car &rhs)
        { return lhs.date > rhs.date; };
        std::priority_queue<Car, std::vector<Car>, decltype(cmp)> cars_queue(cmp);

        for (const auto &entry : js)
        {
            cars_queue.push(Car::FromJson(entry));
        }
        std::vector<Car> ret;
        while (!cars_queue.empty() && ret.size() < kMaxCars)
        {
            ret.push_back(cars_queue.top());
            cars_queue.pop();
        }
        return ret;
    }
    const nlohmann::json App::GetJsonData() const
    {
        using curl::curl_easy;
        using curl::curl_ios;
        std::ostringstream ss_output;
        curl_ios<std::ostringstream> writer(ss_output);
        curl_easy easy(writer);
        // Add some options.
        easy.add<CURLOPT_URL>(kDataURL.c_str());
        easy.add<CURLOPT_FOLLOWLOCATION>(1L);
        // TODO (add exception handling)
        easy.perform();
        easy.get_info<CURLINFO_CONTENT_TYPE>();
        return nlohmann::json::parse(ss_output.str());
    }

    uint16_t App::GetResponseCode() const
    {
        using curl::curl_easy;
        using curl::curl_ios;
        std::cout << "Sending request..." << std::endl;
        std::ostringstream ss_output;
        curl_ios<std::ostringstream> writer(ss_output);
        curl_easy easy(writer);
        // Add some options.
        easy.add<CURLOPT_URL>(kDataURL.c_str());
        easy.add<CURLOPT_FOLLOWLOCATION>(1L);
        // TODO (add exception handling)
        easy.perform();
        // this request library is ugly...
        return easy.get_info<CURLINFO_RESPONSE_CODE>().get();
    }
    Car App::GetFastestCarFromJsonData(const nlohmann::json &js) const
    {
        // TODO(check if there're no cars & error handling in json parsing)
        Car fastest_car{.name = "", .date = Date{}, .acceleration = -std::numeric_limits<float>::max()};
        for (const auto &entry : js)
        {
            auto car = Car::FromJson(entry);
            if (car.acceleration > fastest_car.acceleration)
            {
                fastest_car = car;
            }
        }
        return fastest_car;
    }
    std::unordered_set<std::string> App::GetUniqueBrandsFromJsonData(const nlohmann::json &js) const
    {
        // TODO(handle parsing errors)
        std::unordered_set<std::string> unique_brands;
        for (const auto &entry : js)
        {
            unique_brands.insert(Car::FromJson(entry).name);
        }
        return unique_brands;
    }

    App::CLI_OPTION App::OptionFromString(const std::string &str)
    {
        if (str == "fastest")
        {
            return CLI_OPTION::FASTEST_CAR;
        }
        if (str == "unique")
        {
            return CLI_OPTION::UNIQUE_BRANDS;
        }
        if (str == "ten_newest")
        {
            return CLI_OPTION::TEN_NEWEST_CARS;
        }
        if (str == "info")
        {
            return CLI_OPTION::REQUEST_INFO;
        }
        throw std::logic_error("Invalid option string " + str);
    }

} // moovit