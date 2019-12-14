#include "PlayerMap.h"
#include <fstream>
#include <iostream>

const std::string short_separator(8, '-');

// Prints current player to cout
void PlayerMap::print_current_player() {
    std::cout << "*" << year_ << " season*" << std::endl;
    std::cout << short_separator << std::endl;
    if (player_map_.size()) {
        std::cout << player_map_.size() << std::endl;

        std::cout << (current_player_ -> second);
        std::cout << (current_player_ -> second).category() << std::endl;
        std::cout << short_separator << std::endl;
        std::cout << index_ + 1 << " out of " << player_map_.size() << std::endl;;
    }
}

// Recalculates local index
void PlayerMap::calculate_index() {
    int i = 0;
    for (auto itr = player_map_.begin(); itr != player_map_.end(); ++itr, ++i) {
        if (itr == current_player_) {
            index_ = i;
            break;
        }
    }
}

// Changes current player to previous and returns, circularly linked
PlayerEntry PlayerMap::previous_player() {
    --current_player_;
    --index_;

    if (index_ == -1) {
        current_player_ = --player_map_.end();
        index_ = player_map_.size() - 1;
    }

    return current_player_ -> second;
}

// Changes current player to next and returns, circularly linked
PlayerEntry PlayerMap::next_player() {
    ++current_player_;
    ++index_;

    if (index_ == (int)player_map_.size()){
        current_player_ = player_map_.begin();
        index_ = 0;
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
    current_player_ = player_map_.find(entry.name());
    calculate_index();
    return true;
}


// Returns false if entry with name doesn't exist
bool PlayerMap::remove(map_iterator entry_itr) {
    if (entry_itr == player_map_.end()) {
        return false;
    }

    player_map_.erase(entry_itr);
    current_player_ = player_map_.begin();
    calculate_index();

    return true;
}

// Returns false if entry with name doesn't exist
bool PlayerMap::remove(const std::string & name) {
    auto entry_itr = player_map_.find(name);
    return remove(entry_itr);
}

// Removes current player
bool PlayerMap::remove() {
    return remove(current_player_);
}

// Returns false if entry doesn't exist
bool PlayerMap::edit_name(const std::string & new_name) {
    PlayerEntry new_entry = current_player_ -> second;
    new_entry.set_name(new_name);

    return edit_all(new_entry);
}

bool PlayerMap::edit_year(int year) {
    (current_player_ -> second).set_year(year);
    return true;
}

// Returns false if invalid string
bool PlayerMap::edit_status(const std::string & status) {
    if (status == "paid" || status == "unpaid") {
        (current_player_ -> second).set_status(status);
    } else {
        return false;
    }
    return true;
}

// Returns false if entry doesn't exist
bool PlayerMap::edit_all(PlayerEntry new_entry) {
    auto new_itr = player_map_.find(new_entry.name());

    // unique name or same name
    if (new_itr != player_map_.end() && new_itr != current_player_) {
        return false;
    }

    remove(current_player_);
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

void PlayerMap::save_map(const std::string & filename) const
{
    std::ofstream out_to_file (filename);
    out_to_file << "-" << year_ << "-\n";

    for (auto itr = player_map_.begin(); itr != player_map_.end(); itr++)
    {
        out_to_file << itr -> second;
    }
}

bool PlayerMap::load_map(const std::string & filename) {
    std::ifstream in_from_file (filename);
    int year;

    in_from_file.get(); //-
    in_from_file >> year;
    in_from_file.get(); //-
    in_from_file.get(); //\n

    if (year < 0) {
        return false;
    }

    PlayerEntry i = PlayerEntry();
    while(in_from_file >> i) {
        i.auto_set_category(year);
        add(i);
    }

    current_player_ = player_map_.begin();
    index_ = 0;

    year_ = year;
    in_from_file.close();

    return true;
}

// Returns a new PlayerMap by using a filter over PlayerEntries
template <class Unary_Predicate>
PlayerMap PlayerMap::get_filtered_map(Unary_Predicate predicate) {
    std::map<std::string, PlayerEntry> new_map;

    for (auto itr = player_map_.begin(); itr != player_map_.end(); ++itr) {
        if (predicate(itr -> second)) {
            new_map[itr -> first] = itr -> second;
        }
    }

    std::cout << new_map.size();
    return PlayerMap(year_, new_map);
}

class FilterCategory {
public:
    FilterCategory(std::string cat) : cat(cat) {}
    bool operator()(PlayerEntry e) { return e.category() == cat; }

private:
    std::string cat;
};

PlayerMap PlayerMap::search_by_category(std::string category) {
    FilterCategory filter(category);
    return get_filtered_map(filter);
}

class FilterYear {
public:
    FilterYear(int year) : year(year) {}
    bool operator()(PlayerEntry e) { return e.year() == year; }

private:
    int year;
};
PlayerMap PlayerMap::search_by_year(int year) {
    FilterYear filter(year);
    return get_filtered_map(filter);
}

class FilterStatus {
public:
    FilterStatus(std::string status) : status(status) {}
    bool operator()(PlayerEntry e) { return e.status() == status; }

private:
    std::string status;
};
PlayerMap PlayerMap::search_by_status(std::string status) {
    FilterStatus filter(status);
    return get_filtered_map(filter);
}
