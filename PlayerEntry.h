#ifndef _PlayerEntry_h_
#define _PlayerEntry_h_

#include <iostream>

class PlayerEntry
{
public:
    friend std::ostream & operator<<(std::ostream & out, const PlayerEntry & entry);
    friend std::istream & operator>>(std::istream & in, PlayerEntry & entry);

    PlayerEntry() : name_(""), category_("N/A"), isPaid_(false), year_(0) {}
    PlayerEntry(std::string name, std::string category, bool ispaid, int year):name_(name), category_(category), isPaid_(ispaid), year_(year){}

    std::string name() const { return name_; }
    std::string category() const { return category_; }
    int year() const { return year_; }

    void name(const std::string & new_name) { name_ = new_name; }
    void category(const std::string & new_category) { category_ = new_category; }
    void year(const int & new_year) { year_ = new_year; }

    // Status can either be set with string "paid" or "unpaid" or can be set with a bool
    // true => paid, false => unpaid
    std::string status_string() const { return isPaid_ ? "paid" : "unpaid"; }
    bool status() const { return isPaid_; }

    void status(const bool & new_status) { isPaid_ = new_status; }
    bool status(const std::string & new_status);

private:
    std::string name_;
    std::string category_;
    int year_;
    bool isPaid_;
};

#endif // _PlayerEntry_h_
