#ifndef _PlayerEntry_h_
#define _PlayerEntry_h_

#include <iostream>

class PlayerEntry
{
public:
    friend std::ostream & operator<<(std::ostream & out, const PlayerEntry & entry);
    friend std::istream & operator>>(std::istream & in, PlayerEntry & entry);

    PlayerEntry() : name_(""), category_("N/A"), status_("unpaid"), year_(0) {}
    PlayerEntry(std::string name, std::string category, std::string status, int year) : name_(name), category_(category), status_(status), year_(year) {}
    PlayerEntry(const PlayerEntry & entry);

    std::string name() const { return name_; }
    std::string category() const { return category_; }
    std::string status() const { return status_; }
    int year() const { return year_; }

    void set_name(const std::string & new_name) { name_ = new_name; }
    void set_category(const std::string & new_category) { category_ = new_category; }
    void set_status(const std::string & new_status) { status_ = new_status; }
    void set_year(const int & new_year) { year_ = new_year; }

    void auto_set_category(int year);

private:
    std::string name_;
    std::string category_;
    std::string status_;
    int year_;
};

#endif // _PlayerEntry_h_
