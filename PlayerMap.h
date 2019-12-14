#ifndef _PlayerMap_h
#define _PlayerMap_h

#include <map>
#include <iostream>
#include "PlayerEntry.h"

class PlayerMap
{
public:
    PlayerMap() : year_(0), index_(0) {
        std::map<std::string, PlayerEntry> player_map;
        player_map_ = player_map;
        current_player_ = player_map_.begin();
    };
    PlayerMap(int year) : year_(year), index_(0) {
        std::map<std::string, PlayerEntry> player_map;
        player_map_ = player_map;
        current_player_ = player_map_.begin();
    }
    PlayerMap(int year, std::map<std::string, PlayerEntry> player_map) : year_(year), player_map_(player_map), index_(0) {
        current_player_ = player_map_.begin();
    }

    PlayerEntry print_current_player() {
        if (player_map_.size()) {
            std::cout << current_player_ -> second;
        }
    }

    PlayerEntry previous_player();
    PlayerEntry next_player();
    bool add(PlayerEntry entry);
    bool remove(PlayerEntry entry);
    bool edit_player(PlayerEntry old_entry, PlayerEntry new_entry);
    int year() { return year_; }
    void save_map(const std::string & filename) const;
    void load_map(const std::string & filename);

    PlayerMap search_by_last_name(std::string last_name);

    template <class Unary_Predicate>
    PlayerMap get_filtered_map(Unary_Predicate predicate);

    PlayerMap search_by_category(std::string category);
    PlayerMap search_by_year(int year);
    PlayerMap search_by_status(bool status);

private:
    std::map<std::string, PlayerEntry> player_map_;
    std::map<std::string, PlayerEntry>::iterator current_player_;

    int index_;
    int year_;
};

#endif // _PlayerMap_h
