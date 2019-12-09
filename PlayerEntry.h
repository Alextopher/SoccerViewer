// name, year of birth, category and registration status
class PlayerEntry
{
public:
    PlayerEntry() : name_(""), category_("N/A"), status_("N/A"), year_(0) {}
    //PlayerEntry(string name, string category, string status, int year) : name_(name), category_(category), status_(status), year_(year) {}

    std::string name() {return name_;}
    std::string category() {return category_;}
    bool status() {return status_;}
    int year() {return year_;}

    void name(const std::string & new_name) {name_ = new_name;}
    void category(const std::string & new_category) {category_ = new_category;}
    void status(const bool new_status) {status_ = new_status;}
    void year(const int new_year) {year_ = new_year;}

private:
    std::string name_;
    std::string category_;
    bool status_;
    int year_;
};
