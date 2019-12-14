#include "PlayerViewer.h"
#include "PlayerEntry.h"

void PlayerViewer::display(bool & done, bool & searching) {
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
        currentMap.print_current_player();
        std::cout << short_separator << std::endl;
        std::cout << "  next  previous  add  delete  edit  find  go-print  save  open  create  quit\n";

        char c = get_command();
        switch (c) {
            case 'n' : {
                currentMap.next_player();
                break;
            }
            case 'p' : {
                currentMap.previous_player();
                break;
            }
            case 'a': {
                /*
                std::string first;
                std::string last;
                std::string status;
                int year;

                std::cout << "Enter first name\n";
                std::cin >> first;
                std::cout << "Enter last name\n";
                std::cin >> last;
                std::cout << "Enter status paid or unpaid\n";
                std::cin >> status;
                std::cout << "Enter year of birth\n";
                std::cin >> year;

                PlayerEntry entry(last + ", " + first, "", status, year);
                entry.auto_set_category(currentMap.year());

                currentMap.add(entry);
                */
                break;
            }
            case 'd': {
                break;
            }
            case 'e': {
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

char PlayerViewer::get_command() const {
    std::cout << "command: ";
    char command;
    std::cin >> command;
    std::cin.get(); // '\n'

    return command;
}

void PlayerViewer::search_view(bool & done, bool & searching) {
    std::cout << "Searching..." << std::endl;
    std::cout << long_separator << std::endl;
    currentMap.print_current_player();
    std::cout << short_separator << std::endl;
    std::cout << "  next  previous  find  save  go-print  back  quit\n";
    char c = get_command();
    switch (c) {
        case 'n': {
            break;
        }
        case 'p': {
            break;
        }
        case 'f': {
            break;
        }
        case 's': {
            break;
        }
        case 'g': {
            break;
        }
        case 'b': {
            mapBuffer.pop_back();
            currentMap = *(--mapBuffer.end());
            break;
        }
        case 'q': {
            //done = true;
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
            mapBuffer.push_back(currentMap.search_by_last_name(name));

            break;
        }
        case 'y': {
            int year;

            do {
                std::cout << "Enter year";
                std::cin >> year;
            } while(!std::cin.good());

            mapBuffer.push_back(currentMap.search_by_year(year));
            break;
        }
        case 's': {
            std::string status;

            while(status != "paid" || status != "unpaid") {
                std::cout << "Enter status \"paid\" or \"unpaid\" case sensitive" << std::endl;
                std::cin >> status;
            }

            mapBuffer.push_back(currentMap.search_by_status(status));
            break;
        }
        case 'c': {
            std::string category;

            while (category != "U6" && category != "U8" && category != "U10" && category != "U12" && category != "U14" && category != "U17") {
                std::cout << "Enter category U6, U8, U10, U12, U14, U17" << std::endl;
                std::cin >> category;
            }

            mapBuffer.push_back(currentMap.search_by_category(category));
            break;
        }
    }
}

void PlayerViewer::open_map() {
    std::string name;

    while (name == "") {
        std::cout << "Enter filename to open" << std::endl;
        std::cin >> name;
    }

    PlayerMap player_map;
    player_map.load_map(name);

    // Opening a map unloads the current
    mapBuffer.clear();
    mapBuffer.push_back(player_map);
    currentMap = *--mapBuffer.end();

    filename_ = name;
}

void PlayerViewer::create_map() {
    std::string name;
    while (name == "") {
        std::cout << "Enter filename to save as" << std::endl;
        std::cin >> name;
    }

    int year;
    do {
        std::cout << "Enter year" << std::endl;
        std::cin >> year;
    } while(!std::cin.good());

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
        currentMap.save_map(filename_);
    } else {
        currentMap.save_map(name);
    }
}
