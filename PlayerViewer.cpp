#include "PlayerViewer.h"
#include "PlayerEntry.h"

void PlayerViewer::display(bool & done, bool & searching) {
    std::cout << mapBuffer.size();

    if (searching) {
        search_view(done, searching);
    } else {
        display_view(done, searching);
    }
}

void PlayerViewer::display_view(bool & done, bool & searching) {
    if (mapBuffer.size() == 0) {
        std::cout << "No player data loaded" << std::endl;
        std::cout << long_separator << std::endl;
        std::cout << "  open  create  quit\n";

        char c = get_command();
        switch (c) {
            case 'o' : {
                open_map();
                break;
            }

            case 'c' : {
                create_map();
                break;
            }

            case 'q' : {
                done = true;
                break;
            }
        }
    } else {
        std::cout << filename_ << std::endl;
        std::cout << long_separator << std::endl;
        currentMap -> print_current_player();
        std::cout << long_separator << std::endl;
        std::cout << "  next  previous  add  delete  edit  find  go-print  save  open  create  quit\n";

        char c = get_command();
        switch (c) {
            case 'n' : {
                currentMap -> next_player();
                break;
            }
            case 'p' : {
                currentMap -> previous_player();
                break;
            }
            case 'a': {
                PlayerEntry entry = new_entry();

                if (!(currentMap -> add(entry))) {
                    error_ = "name already taken or invalid";
                }
                break;
            }
            case 'd': {
                delete_entry();
                break;
            }
            case 'e': {
                edit_entry();
                break;
            }
            case 'f' : {
                searching = true;
                search_map();
                break;
            }
            case 'g': {
                break;
            }
            case 's' : {
                save_map();
                break;
            }
            case 'o' : {
                open_map();
                break;
            }
            case 'c' : {
                create_map();
                break;
            }
            case 'q' : {
                done = true;
                break;
            }
        }
    }
}

void PlayerViewer::search_view(bool & done, bool & searching) {
    std::cout << "Searching..." << std::endl;
    std::cout << long_separator << std::endl;
    currentMap -> print_current_player();
    std::cout << long_separator << std::endl;
    std::cout << "  next  previous  find  save  go-print  back  quit\n";

    char c = get_command();
    switch (c) {
        case 'n': {
            currentMap -> next_player();
            break;
        }
        case 'p': {
            currentMap -> previous_player();
            break;
        }
        case 'f': {
            search_map();
            break;
        }
        case 's': {
            save_map();
            break;
        }
        case 'g': {
            break;
        }
        case 'b': {
            mapBuffer.pop_back();
            currentMap = --mapBuffer.end();
            if (mapBuffer.size() == 1) {
                searching = false;
            }
            break;
        }
        case 'q': {
            done = true;
            break;
        }
    }
}

void PlayerViewer::search_map() {
    std::cout << "Search by?" << std::endl;
    std::cout << short_separator << std::endl;
    std::cout << "  lastname  year  status  category\n";
    char c = get_command();
    switch (c) {
        case 'l': {
            std::cout << "Enter last name or prefix to last name" << std::endl;
            std::string name;
            std::cin >> name;
            mapBuffer.push_back(currentMap -> search_by_last_name(name));
            ++currentMap;

            break;
        }
        case 'y': {
            int year;

            std::cout << "Enter year" << std::endl;
            if (!(std::cin >> year)) {
                mapBuffer.push_back(currentMap -> search_by_year(year));
                ++currentMap;
            } else {
                error_ = "invalid year";
            }

            break;
        }
        case 's': {
            std::string status;
            std::cout << "Enter status \"paid\" or \"unpaid\"" << std::endl;

            if (std::cin >> status) {
                mapBuffer.push_back(currentMap -> search_by_status(status));
                ++currentMap;
            } else {
                error_ = "invalid status, status is case sensitive";
            }

            break;
        }
        case 'c': {
            std::string category;
            std::cout << "Enter category U6, U8, U10, U12, U14, U17" << std::endl;
            std::cin >> category;

            if (category != "U6" && category != "U8" && category != "U10" && category != "U12" && category != "U14" && category != "U17") {
                error_ = "invalid category. options are U6, U10, U12, U14, U17";
            } else {
                mapBuffer.push_back(currentMap -> search_by_category(category));
            }

            break;
        }
    }
}

void PlayerViewer::open_map() {
    std::string name;
    std::cout << "Enter filename to open" << std::endl;
    std::cin >> name;

    PlayerMap player_map;
    if (!player_map.load_map(name)) {
        error_ = "invalid format for save file. did you mean create?";
        return;
    }

    // Opening a map unloads the current
    mapBuffer.clear();
    mapBuffer.push_back(player_map);
    currentMap = --mapBuffer.end();

    filename_ = name;
}

void PlayerViewer::create_map() {
    std::string name;
    std::cout << "Enter filename to save as" << std::endl;
    std::cin >> name;

    std::cout << "Enter season year" << std::endl;
    int year;
    if (!(std::cin >> year)) {
        error_ = "invalid year";
        return;
    }

    std::ofstream file;
    file.open(name, std::ofstream::out | std::ofstream::trunc);
    file.close();

    PlayerMap player_map = PlayerMap(year);
    mapBuffer.push_back(player_map);

    filename_ = name;
}

void PlayerViewer::save_map() {
    std::cout << "Enter filename to save players to... or enter nothing to overwrite current file" << std::endl;
    std::string name;
    std::cin >> name;

    if (name == "") {
        currentMap -> save_map(filename_);
    } else {
        currentMap -> save_map(name);
    }
}

PlayerEntry PlayerViewer::new_entry() {
    std::string first;
    std::string last;
    std::string status;
    int year;

    std::cout << "Enter first name\n";
    std::cin >> first;
    std::cout << "Enter last name\n";
    std::cin >> last;
    std::cout << "Enter status \"paid\" or \"unpaid\"\n";
    std::cin >> status;
    if (status != "paid" && status != "unpaid") {
        error_ = "invalid status, status is case sensitive";
    }

    std::cout << "Enter year of birth\n";
    if (!(std::cin >> year)) {
        error_ = "invalid year";
    }

    PlayerEntry entry(last + ", " + first, "", status, year);
    entry.auto_set_category(currentMap -> year());

    return entry;
}

void PlayerViewer::delete_entry() {
    std::cout << "Deleting " << (currentMap -> current_player()).name() << ". Are you sure? <y/n>" << std::endl;
    char command = get_command();
    if (command != 'y') {
        return;
    }

    if (!(currentMap -> remove())) {
        error_ = "name not found";
    }
}

void PlayerViewer::edit_entry() {
    std::cout << "Edit?" << std::endl;
    std::cout << short_separator << std::endl;
    std::cout << "  name  year  status  all\n";

    char c2 = get_command();
    switch(c2) {
        case 'n': {
            std::string first;
            std::string last;

            std::cout << "Enter first name\n";
            std::cin >> first;
            std::cout << "Enter last name\n";
            std::cin >> last;

            if (!(currentMap -> edit_name(last + ", " + first))) {
                error_ = "Name already taken";
            }

            break;
        }
        case 'y': {
            int year;

            std::cout << "Enter year of birth\n";
            if (!(std::cin >> year)) {
                error_ = "invalid year";
                break;
            }

            currentMap -> edit_year(year);
            break;
        }
        case 's': {
            std::string status;

            std::cout << "Enter status \"paid\" or \"unpaid\"\n";
            std::cin >> status;
            if (status != "paid" && status != "unpaid") {
                error_ = "invalid status, status is case sensitive";
                break;
            }

            currentMap -> edit_status(status);
            break;
        }
        case 'a': {
            PlayerEntry entry = new_entry();

            if (!(currentMap -> edit_all(entry))) {
                error_ = "something went wrong...";
            }

            break;
        }
    }
}

char PlayerViewer::get_command() const {
    std::cout << short_separator << std::endl;
    std::cout << "command: ";
    char command;
    std::cin >> command;
    std::cin.get(); // '\n'

    return command;
}
