#ifndef _PlayerViewer_h
#define _PlayerViewer_h

#include "PlayerMap.h"
#include "PlayerEntry.h"

#include <vector>
#include <iostream>

const char clear_command[] = "cls"; // for Windows
//const char clear_command[] = "clear"; // for Linux and possibly Mac's

const std::string long_separator(20, '-');
const std::string short_separator(8, '-');

class PlayerViewer
{
public:
    PlayerViewer() {
        mapBuffer = std::vector<PlayerMap>();
    }

    void run() {
        bool done = false;
        bool searching = false;

        while (!done) {
            display(done, searching);
        }
    }

private:
    // The 0th map is always the default one
    std::vector<PlayerMap> mapBuffer;
    PlayerMap currentMap;

    std::string filename;

    void display(bool & done, bool & searching) {
        if (searching) {
            search_view(done, searching);
        } else {
            display_view(done, searching);
        }
    }

    void search_view(bool & done, bool & searching) {
        std::cout << filename << std::endl;
        std::cout << long_separator << std::endl;
        std::cout << "  next  previous  back  search  quit\n";

        char c = get_command();
        switch (c) {

        }
    }

    void display_view(bool & done, bool & searching) {
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
            std::cout << filename << std::endl;
            std::cout << long_separator << std::endl;
            std::cout << "  next  previous  open  search  create  quit\n";

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

                case 'o' : {
                    open_map();
                    break;
                }

                case 'c' : {
                    create_map();
                    break;
                }

                case 's' : {
                    searching = true;
                    search_map();
                    break;
                }

                case 'q' : {
                    done = true;
                    break;
                }
            }
        }
    }

    char get_command() const {
        std::cout << "command: ";
        char command;
        std::cin >> command;
        std::cin.get(); // '\n'

        return command;
    }

    void open_map() {

    }

    void search_view(bool & searching) {

    }

    void search_map() {
        std::cout << "Search by?" << std::endl;
        std::cout << short_separator << std::endl;
        std::cout << "  lastname  year  status  category  " << std::endl;
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

                // Convert string to boolean
                bool b;
                if (status == "paid") {
                    b = true;
                } else {
                    b = false;
                }

                mapBuffer.push_back(currentMap.search_by_status(b));
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

    void create_map() {

    }

    void new_map() {

    }
};

#endif // PlayerViewer_h
