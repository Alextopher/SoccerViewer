#ifndef _PlayerMap_h
#define _PlayerMap_h

#include <map>
#include <iostream>
#include "PlayerEntry.h"

class PlayerMap
{
public:
    typedef std::map<std::string, PlayerEntry>::iterator map_iterator;

    PlayerMap() : year_(0), index_(0) {
        player_map_ = std::map<std::string, PlayerEntry>();
        current_player_ = player_map_.begin();
    };
    PlayerMap(int year) : year_(year), index_(0) {
        player_map_ = std::map<std::string, PlayerEntry>();
        current_player_ = player_map_.begin();
    }
    PlayerMap(int year, std::map<std::string, PlayerEntry> player_map) : year_(year), player_map_(player_map), index_(0) {
        current_player_ = player_map_.begin();
    }

    void print_current_player();
    PlayerEntry current_player() { return current_player_ -> second; }

    void calculate_index();

    PlayerEntry previous_player();
    PlayerEntry next_player();

    bool add(PlayerEntry entry);

    bool remove(map_iterator entry_itr);
    bool remove(const std::string & entry);
    bool remove();

    bool edit_name(const std::string & new_name);
    bool edit_year(int year);
    bool edit_status(const std::string & status);
    bool edit_all(PlayerEntry new_entry);


    int year() { return year_; }
    void save_map(const std::string & filename) const;
    bool load_map(const std::string & filename);

    PlayerMap search_by_last_name(std::string last_name);
    PlayerMap search_by_category(std::string category);
    PlayerMap search_by_year(int year);
    PlayerMap search_by_status(std::string status);

private:
    int year_;
    int index_;

    std::map<std::string, PlayerEntry> player_map_;
    std::map<std::string, PlayerEntry>::iterator current_player_;

    template <class Unary_Predicate>
    PlayerMap get_filtered_map(Unary_Predicate predicate);

};

#endif // _PlayerMap_h
