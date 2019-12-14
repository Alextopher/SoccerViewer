#ifndef _PlayerViewer_h
#define _PlayerViewer_h

#include "PlayerMap.h"
#include "PlayerEntry.h"

#include <vector>
#include <iostream>
#include <fstream>

const char clear_command[] = "cls"; // for Windows
//const char clear_command[] = "clear"; // for Linux and possibly Mac's

const std::string long_separator(24, '-');
const std::string short_separator(8, '-');

class PlayerViewer
{
public:
    PlayerViewer() { mapBuffer = std::vector<PlayerMap>(); }

    void run() {
        bool done = false;
        bool searching = false;

        while (!done) {
            system(clear_command);
            if (error_ != "") {
                std::cout << "ERROR: " << error_ << std::endl;
                error_ = "";
            }
            display(done, searching);
        }
    }

private:
    // The 0th map is always the default one
    std::vector<PlayerMap> mapBuffer;
    std::vector<PlayerMap>::iterator currentMap;

    std::string filename_;
    std::string error_;

    void display(bool & done, bool & searching);
    void display_view(bool & done, bool & searching);
    void search_view(bool & done, bool & searching);

    void search_map();
    void open_map();
    void create_map();
    void save_map();

    PlayerEntry new_entry();
    void delete_entry();
    void edit_entry();

    char get_command() const;
};

#endif // PlayerViewer_h
