#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <string_view>

struct DBQueryParameters {
    int min_age;
    int max_age;
    std::string name_filter;
};

DBHandler ConnectToDatabase(const std::string& db_name, int db_connection_timeout, bool db_allow_exceptions, DBLogLevel db_log_level) {
    DBConnector connector(db_allow_exceptions, db_log_level);
    if (db_name.starts_with("tmp."s)) {
        return connector.ConnectTmp(db_name, db_connection_timeout);
    } else {
        return connector.Connect(db_name, db_connection_timeout);
    }
}

std::vector<Person> ExecutePersonQuery(const DBHandler& db, const DBQueryParameters& params) {
    std::ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << params.min_age << " and "s << params.max_age << " "s
              << "and Name like '%"s << db.Quote(params.name_filter) << "%'"s;
    DBQuery query(query_str.str());

    std::vector<Person> persons;
    for (auto [name, age] : db.LoadRows<std::string, int>(query)) {
        persons.push_back({std::move(name), age});
    }
    return persons;
}

std::vector<Person> LoadPersons(std::string_view db_name, int db_connection_timeout, bool db_allow_exceptions,
                           DBLogLevel db_log_level, int min_age, int max_age, std::string_view name_filter) {
    DBHandler db = ConnectToDatabase(std::string(db_name), db_connection_timeout, db_allow_exceptions, db_log_level);

    if (!db_allow_exceptions && !db.IsOK()) {
        return {};
    }

    DBQueryParameters params{min_age, max_age, std::string(name_filter)};
    return ExecutePersonQuery(db, params);
}
