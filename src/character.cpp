#include "character.h"

namespace star
{
    int Height = 400;
    int Width = 400;
    std::random_device rd;

    void logtxt(std::string text)
    {
        std::fstream fs;
        fs.open("log.txt", std::ios::out | std::ios::app);
        fs << text << std::endl;
        fs.close();
    }

    int get_random_number()
    {
        std::mt19937 gen(rd()); // 以 random_device 的输出作为种子初始化 Mersenne Twister 生成器
        std::uniform_int_distribution<> distrib(0, 1000);
        return distrib(gen);
    }

    m_character::m_character(int power, std::vector<std::string> motion_path, std::vector<std::string> attack_path)
    {
        setm_power(power);
        for (int i = 0; i < motion_path.size(); i++)
        {
            IMAGE motion_img;
            loadimage(&motion_img, _T(motion_path[i].c_str()));
            m_motion.push_back(motion_img);
        }

        for (int i = 0; i < attack_path.size(); i++)
        {
            IMAGE attack_img;
            loadimage(&attack_img, _T(attack_path[i].c_str()));
            m_motion.push_back(attack_img);
        }
        m_location = {50, 0, m_motion[0].getwidth(), m_motion[0].getheight()};
        is_alive = true;
    }

    int m_character::setm_power(int power)
    {
        m_power = power;
        text = std::to_string(m_power);
    }

    int m_character::setm_location(direction d)
    {
        switch (d)
        {
        case direction::UP:
            if (m_location.top + m_motion[0].getheight() >= 0 && m_location.top + m_motion[0].getheight() <= m_location.bottom)
                m_location.top += m_motion[0].getheight();
            break;
        case direction::DOWN:
            if (m_location.top - m_motion[0].getheight() >= 0 && m_location.top - m_motion[0].getheight() <= m_location.bottom)
                m_location.top -= m_motion[0].getheight();
            break;
        }
    }

    monster::monster(int power, int x, int y, std::vector<std::string> motion_path, std::vector<std::string> attack_path)
    {
        setm_power(power);
        for (int i = 0; i < motion_path.size(); i++)
        {
            IMAGE motion_img;
            loadimage(&motion_img, _T(motion_path[i].c_str()));
            m_motion.push_back(motion_img);
        }

        for (int i = 0; i < attack_path.size(); i++)
        {
            IMAGE attack_img;
            loadimage(&attack_img, _T(attack_path[i].c_str()));
            m_motion.push_back(attack_img);
        }
        m_location = {x, y, x + m_motion[0].getwidth(), y + m_motion[0].getheight()};
        resetdata = m_location;
        is_alive = true;
    }

    void monster::refresh()
    {
        m_location.left -= 20;
        m_location.right -= 20;
        std::stringstream tmp;
        tmp << "monster now location: x = " << m_location.left << " y = " << m_location.top;
        logtxt(tmp.str());
    }

    void monster::reset()
    {
        m_location = resetdata;
        setm_power(getm_power() + get_random_number() % 10);
    }

    int monster::setm_power(int power)
    {
        m_power = power;
        text = std::to_string(m_power);
    }

    strengthen::strengthen(RECT location)
    {
        m_location = location;
        resetdata = location;
        int res = get_random_number() % 4;
        std::string tmpt;
        switch (res)
        {
        case choose::addtion:
            while (1)
            {
                value = get_random_number() % 10;
                if (value != 0)
                    break;
            }
            text = text + "+";
            tmpt = std::to_string(value);
            text = text + tmpt;
            break;
        case choose::subtraction:
            while (1)
            {
                value = get_random_number() % 8;
                if (value != 0)
                    break;
            }
            text = text + "-";
            tmpt = std::to_string(value);
            text = text + tmpt;
            break;
        case choose::multiplication:
            while (1)
            {
                value = get_random_number() % 6;
                if (value != 0)
                    break;
            }
            text = text + "*";
            tmpt = std::to_string(value);
            text = text + tmpt;
            break;
        case choose::division:
            while (1)
            {
                value = get_random_number() % 4;
                if (value != 0)
                    break;
            }
            text = text + "/";
            tmpt = std::to_string(value);
            text = text + tmpt;
            break;
        }
        mothod = (choose)res;
    }

    void strengthen::refresh()
    {
        m_location.left -= 15;
        m_location.right -= 15;
    }

    void strengthen::reset()
    {
        m_location = resetdata;
        int res = get_random_number() % 4;
        std::string tmpt;
        switch (res)
        {
        case choose::addtion:
            text = "";
            while (1)
            {
                value = get_random_number() % 10;
                if (value != 0)
                    break;
            }
            text = text + "+";
            tmpt = std::to_string(value);
            text = text + tmpt;
            break;
        case choose::subtraction:
            text = "";
            while (1)
            {
                value = get_random_number() % 10;
                if (value != 0)
                    break;
            }
            text = text + "-";
            tmpt = std::to_string(value);
            text = text + tmpt;
            break;
        case choose::multiplication:
            text = "";
            while (1)
            {
                value = get_random_number() % 6;
                if (value != 0)
                    break;
            }
            text = text + "*";
            tmpt = std::to_string(value);
            text = text + tmpt;
            break;
        case choose::division:
            text = "";
            while (1)
            {
                value = get_random_number() % 6;
                if (value != 0)
                    break;
            }
            text = text + "/";
            tmpt = std::to_string(value);
            text = text + tmpt;
            break;
        }
        mothod = (choose)res;
    }
}
