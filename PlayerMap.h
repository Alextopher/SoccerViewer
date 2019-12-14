#ifndef _PlayerMap_h
#define _PlayerMap_h

#include <map>
#include "PlayerEntry.h"

class PlayerMap
{
public:
    PlayerMap() : year_(0) {};
    PlayerMap(int year) : year_(year) {};
    PlayerMap(int year, std::map<std::string, PlayerEntry> player_map) : year_(year), player_map_(player_map) {}

    PlayerEntry current_player() { return current_player_ -> second; }

    PlayerEntry previous_player();
    PlayerEntry next_player();
    bool add(PlayerEntry entry);
    bool remove(PlayerEntry entry);
    bool edit_player(PlayerEntry old_entry, PlayerEntry new_entry);

    PlayerMap search_by_last_name(std::string last_name);

    template <class Unary_Predicate>
    PlayerMap get_filtered_map(Unary_Predicate predicate);

    PlayerMap search_by_category(std::string category);
    PlayerMap search_by_year(int year);
    PlayerMap search_by_status(bool status);

private:
    std::map<std::string, PlayerEntry> player_map_;
    std::map<std::string, PlayerEntry>::iterator current_player_;

    int year_;
};

#endif // _PlayerMap_h
