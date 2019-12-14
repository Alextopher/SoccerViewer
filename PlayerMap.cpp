#include "PlayerMap.h"
#include <fstream>
#include <iostream>

// Changes current player to previous and returns, circularly linked
PlayerEntry PlayerMap::previous_player() {
    if (current_player_ == player_map_.begin()) {
        current_player_ == player_map_.end();
    }

    return (--current_player_) -> second;
}

// Changes current player to next and returns, circularly linked
PlayerEntry PlayerMap::next_player() {
    ++current_player_;

    if (current_player_ == player_map_.end()) {
        current_player_ == player_map_.begin();
    }

    return current_player_ -> second;
}

// Returns false if entry already exists
bool PlayerMap::add(PlayerEntry entry) {
    // Check if player already exists
    if (player_map_.find(entry.name()) != player_map_.end()) {
        return false;
    }

    player_map_[entry.name()] = entry;
    return true;
}

// Returns false if entry could not be found
bool PlayerMap::remove(PlayerEntry entry) {
    // Auto doesn't work here, find wants to return a const iterator
    auto entry_itr = player_map_.find(entry.name());

    if (entry_itr == player_map_.end()) {
        return false;
    }

    player_map_.erase(entry_itr);
}

// Returns false if entry doesn't exist
bool PlayerMap::edit_player(PlayerEntry old_entry, PlayerEntry new_entry) {
    // Possible could be more efficient
    // Check that old_entry exists and new_entry is either new_entry or end
    auto old_itr = player_map_.find(old_entry.name());
    auto new_itr = player_map_.find(new_entry.name());

    if (old_itr != player_map_.end() && (new_itr == player_map_.end() || new_itr == old_itr)) {
        return false;
    }

    remove(old_entry);
    add(new_entry);

    return true;
}

// Search last map for prefixed last names
PlayerMap PlayerMap::search_by_last_name(std::string last_name) {
    std::map<std::string, PlayerEntry> new_map;

    auto itr = player_map_.lower_bound(last_name);

    if (itr != player_map_.end()) {
        while ((itr -> first).compare(0, last_name.size(), last_name) == 0) {
            new_map.insert(new_map.end(), itr);
        }
    }

    return PlayerMap(year_, new_map);
}

// Returns a new PlayerMap by using binary predicate over PlayerEntries
template <class Binary_Predicate>
PlayerMap PlayerMap::get_filtered_map(Binary_Predicate predicate) {
    std::map<std::string, PlayerEntry> new_map;

    for (auto itr = player_map_.begin(); itr != player_map_.end(); ++itr) {
        if (predicate(*itr)) {
            new_map[itr -> first] = itr -> second;
        }
    }

    return PlayerMap(year_, new_map);
}

void PlayerMap::save_map() const
{
    std::string filename;
    std::cout << "Save file as: \n";
    std::cin >> filename;
    std::ofstream out_to_file (filename);
    for (auto itr = player_map_.begin(); itr != player_map_.end(); itr++)
    {
        out_to_file << itr -> second;
    }
}

void PlayerMap::load_map(const std::string & filename)
{
    std::ifstream in_from_file (filename);
    PlayerEntry i = PlayerEntry();
    while(in_from_file >> i)
    {
        this->add(i);
    }
}
