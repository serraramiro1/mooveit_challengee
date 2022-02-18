#include <iostream>
#include "curl_easy.h"
#include "json.hpp"
#include "car.h"
#include "date.h"


using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;
using curl::curl_ios;
using json = nlohmann::json;

static const std::string kDataURL = "https://raw.githubusercontent.com/vega/vega/master/docs/data/cars.json";
int main(){
  std::ostringstream ss_output;
  curl_ios<std::ostringstream> writer(ss_output);
  curl_easy easy(writer);
  // Add some options.
  easy.add<CURLOPT_URL>(kDataURL.c_str());
  easy.add<CURLOPT_FOLLOWLOCATION>(1L);
  easy.perform();
  
  auto x = easy.get_info<CURLINFO_CONTENT_TYPE>();
  auto j = json::parse(ss_output.str());
  for(const auto& entry : j){
    moovit::Car car{moovit::Car::FromJson(entry)};
    std::cout << car;
  }

  return 0;
};
