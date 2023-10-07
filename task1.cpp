#include <iostream>
#include <vector>

constexpr int MAXIMUM_USER_ID = 100001;
constexpr size_t MAXIMUM_PAGE_NUMBER = 1000;

class StimulatePeople {
public:
    StimulatePeople() : users_count_(MAXIMUM_PAGE_NUMBER, 0), pages_to_user_id_(MAXIMUM_USER_ID, 0) {}

    void read(int user_id, size_t pages);
    double cheer(int user_id);

private:
    std::vector<int> users_count_;
    std::vector<size_t> pages_to_user_id_;
    int people_ = 0;
};

void StimulatePeople::read(int user_id, size_t pages) {
    size_t pages_before = 0;

    if (pages_to_user_id_[user_id]) {
        pages_before = pages_to_user_id_[user_id];
    } else {
        ++people_;
    }

    pages_to_user_id_[user_id] = pages;

    for (int i = pages_before; i < pages; ++i) {
        users_count_[i] += 1;
    }
}

double StimulatePeople::cheer(int user_id) {
    if (!pages_to_user_id_[user_id]) {
        return 0.0;
    } else if (!(people_ - 1)) {
        return 1.0;
    } else {
        size_t pages_to_user = pages_to_user_id_[user_id];
        if (people_ == users_count_[pages_to_user - 1]) {
            return 0.0;
        } else {
            return (people_ - users_count_[pages_to_user - 1]) / (people_ * 1.0 - 1.0);
        }
    }
}

void request_handler(std::istream& input, std::ostream& output, StimulatePeople& stimulation) {
    std::string str;
    std::getline(input, str);
    int requests_amount = std::stoi(str);

    for (int i = 0; i < requests_amount; ++i) {
        std::string request_type;
        std::getline(input, request_type, ' ');

        if (request_type == "READ") {
            std::string user_id;
            std::getline(input, user_id, ' ');
            std::string pages;
            std::getline(input, pages);
            stimulation.read(std::stoi(user_id), std::stoi(pages));
        } else {
            std::string user_id;
            std::getline(input, user_id);
            output << stimulation.cheer(std::stoi(user_id)) << std::endl;
        }
    }
}

int main() {
    StimulatePeople stimulation;
    request_handler(std::cin, std::cout, stimulation);
    return 0;
}
