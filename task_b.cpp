#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <array>

struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

void CheckRange(int value, const std::string& field_name, int min_value, int max_value) {
    if (value < min_value || value > max_value) {
        throw std::domain_error(field_name + " is out of range");
    }
}

void CheckDateTimeValidity(const DateTime& dt) {
    CheckRange(dt.year, "year", 1, 9999);
    CheckRange(dt.month, "month", 1, 12);

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const std::array<int, 12> month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    CheckRange(dt.day, "day", 1, month_lengths[dt.month - 1]);
    CheckRange(dt.hour, "hour", 0, 23);
    CheckRange(dt.minute, "minute", 0, 59);
    CheckRange(dt.second, "second", 0, 59);
}
