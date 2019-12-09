// name, year of birth, category and registration status
class PlayerEntry
{
public:
    PlayerEntry() : name(""), category("N/A"), status("N/A"), year(0) {}
    //PlayerEntry(string name, string category, string status, int year) : name_(name), category_(category), status_(status), year_(year) {}

    std::string name;
    std::string category;
    std::string status;
    int year;
};
