#pragma once
#include <iostream>
#include "easyx.h"
#include "graphics.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>

namespace star
{
    extern int Height;
    extern int Width;
    extern std::random_device rd;

    void logtxt(std::string text);

    inline void sendHeight(int h) { Height = h; }
    inline void sendWidth(int w) { Width = w; }

    enum direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    class m_character
    {
    public:
        m_character(int power, std::vector<std::string> motion_path, std::vector<std::string> attack_path);
        m_character() {}
        // ~m_character();

        int getm_power() const { return m_power; }
        int setm_power(int power);
        int setm_location(direction d);
        RECT get_location() const { return m_location; }
        std::string get_text() { return text; }

        std::vector<IMAGE> m_motion;
        std::vector<IMAGE> m_attack;

    private:
        int m_power;
        bool is_alive;
        RECT m_location;

        std::string text;
    };

    class monster
    {
    public:
        monster(int power, int x, int y, std::vector<std::string> motion_path, std::vector<std::string> attack_path);
        monster() {}
        std::vector<IMAGE> m_motion;
        std::vector<IMAGE> m_attack;

        int getm_power() const { return m_power; }
        int setm_power(int power);
        RECT get_location() const { return m_location; }
        std::string get_text() { return text; }

        void refresh();
        void reset();

    private:
        int m_power;
        RECT m_location;
        RECT resetdata;
        bool is_alive;
        std::string text;
    };

    class strengthen
    {
    public:
        enum choose
        {
            addtion,
            subtraction,
            multiplication,
            division
        };
        strengthen(RECT location);
        strengthen() {}
        RECT get_location() const { return m_location; }
        void refresh();
        void reset();
        std::string get_text() const { return text; }
        choose get_mothod() const { return mothod; }
        int get_value() const { return value; }

    private:
        int value;
        RECT m_location;
        RECT resetdata;
        bool is_alive;
        std::string text;
        choose mothod;
    };

}
