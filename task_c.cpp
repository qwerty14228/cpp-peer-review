#include <iostream>
#include <vector>
#include <string>

struct City {
    std::string name;
    std::string iso_code;
    std::string phone_code;
    std::string country_name;
    std::string country_iso_code;
    std::string country_time_zone;
    std::vector<std::string> languages;
};

void ParseCitySubjson(std::vector<City>& cities,
                      const std::vector<std::string>& city_json,
                      const std::string& country_name,
                      const std::string& country_iso_code,
                      const std::string& country_phone_code,
                      const std::string& country_time_zone,
                      const std::vector<std::string>& languages) {
    for (const auto& city_str : city_json) {
        size_t pos = 0;
        std::vector<std::string> city_data;

        while ((pos = city_str.find(',')) != std::string::npos) {
            city_data.push_back(city_str.substr(0, pos));
            city_str.erase(0, pos + 1);
        }
        city_data.push_back(city_str);

        City new_city;
        new_city.name = city_data[0];
        new_city.iso_code = city_data[1];
        new_city.phone_code = country_phone_code + city_data[2];
        new_city.country_name = country_name;
        new_city.country_iso_code = country_iso_code;
        new_city.country_time_zone = country_time_zone;
        new_city.languages = languages;

        cities.push_back(new_city);
    }
}
