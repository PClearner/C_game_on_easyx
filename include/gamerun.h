#pragma once
#include "character.h"
#include <thread>
#include <windows.h>

namespace star
{

    class Game
    {
    public:
        Game(int width, int height, std::vector<std::string> steven_motion_path,
             std::vector<std::string> steven_attack_path,
             std::vector<std::string> monster_motion_path,
             std::vector<std::string> monster_attack_path);
        ~Game();
        void init();
        void start();
        void exit() { is_exit = true; }
        void acceptkey();
        void imagerefresh();

    private:
        m_character steven;
        monster unknow1;
        monster unknow2;
        strengthen get_function1;
        strengthen get_function2;
        int m_width;
        int m_height;
        bool is_stop;
        bool is_exit;
        bool monster_or_function;
    };

}
