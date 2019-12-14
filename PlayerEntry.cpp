#include "PlayerEntry.h"

std::ostream & operator<<(std::ostream & out, const PlayerEntry & entry) {
    out << entry.name() << std::endl;
    out << entry.year() << std::endl;
    out << entry.status_string();

    return out;
}

std::istream & operator>>(std::istream & in, PlayerEntry & entry) {
    std::string name;
    in >> std::ws >> name;
    entry.name(name);

    int year;
    in >> year;
    entry.year(year);

    std::string isPaid;
    in >> std::ws >> isPaid;
    entry.status(isPaid);

    return in;
}

bool PlayerEntry::status(const std::string & new_status) {
    if (new_status == "paid") {
        isPaid_ = true;
        return true;
    } else if (new_status == "unpaid") {
        isPaid_ = false;
        return false;
    }

    // Return false is the setting failed
    return false;
}

