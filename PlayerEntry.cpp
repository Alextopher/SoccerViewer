#include "PlayerEntry.h"

void PlayerEntry::auto_set_category(int year) {
    int x = year - year_;

    if (x < 3) {
        category_ = "TOO YOUNG";
    } else if (x < 6) {
        category_ = "U6";
    } else if (x < 8) {
        category_ = "U8";
    } else if (x < 10) {
        category_ = "U10";
    } else if (x < 14) {
        category_ = "U14";
    } else if (x < 17) {
        category_ = "U17";
    } else {
        category_ = "TOO OLD";
    }
}

PlayerEntry::PlayerEntry(const PlayerEntry & entry) {
    name_ = entry.name_;
    category_ = entry.category_;
    status_ = entry.status_;
    year_ = entry.year_;
}

std::ostream & operator<<(std::ostream & out, const PlayerEntry & entry) {
    out << entry.name_ << std::endl;
    out << entry.year_ << std::endl;
    out << entry.status_ << std::endl;

    return out;
}

std::istream & operator>>(std::istream & in, PlayerEntry & entry) {
    in >> std::ws;
    std::string name;
    getline(in, name);
    entry.set_name(name);

    int year;
    in >> std::ws >> year;
    entry.set_year(year);

    std::string status;
    in >> std::ws >> status;
    entry.set_status(status);

    return in;
}
