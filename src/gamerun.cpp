#include "gamerun.h"
#include <functional>

namespace star
{

    Game::Game(int width, int height, std::vector<std::string> steven_motion_path,
               std::vector<std::string> steven_attack_path,
               std::vector<std::string> monster_motion_path,
               std::vector<std::string> monster_attack_path)
    {
        m_width = width;
        m_height = height;
        sendHeight(height);
        sendWidth(width);
        steven = m_character(20, steven_motion_path, steven_attack_path);
        unknow1 = monster(1, width, 0, monster_motion_path, monster_attack_path);
        IMAGE tmp;
        loadimage(&tmp, _T(monster_motion_path[0].c_str()));
        unknow2 = monster(1, width, tmp.getheight(), monster_motion_path, monster_attack_path);

        RECT tmpt = unknow1.get_location();
        get_function1 = strengthen(tmpt);
        tmpt = unknow2.get_location();
        get_function2 = strengthen(tmpt);

        is_exit = false;
        is_stop = false;
        monster_or_function = false;
    }
    void Game::init()
    {
        initgraph(m_height, m_width);
        std::stringstream tmp;
        tmp << "height = " << m_height << " width = " << m_width;
        logtxt(tmp.str());
    }

    void Game::imagerefresh()
    {
        putimage(steven.get_location().left, steven.get_location().top, &steven.m_motion[0]);
        RECT loa = {steven.get_location().left, steven.get_location().top, steven.get_location().left + 50, steven.get_location().top + 20};
        drawtext(steven.get_text().c_str(), &loa, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        if (monster_or_function)
        {
            unknow1.refresh(); // refresh unkown location
            loa = {unknow1.get_location().left, unknow1.get_location().top, unknow1.get_location().left + 50, unknow1.get_location().top + 20};
            putimage(unknow1.get_location().left, unknow1.get_location().top, &unknow1.m_motion[0]);
            drawtext(unknow1.get_text().c_str(), &loa, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            unknow2.refresh();
            loa = {unknow2.get_location().left, unknow2.get_location().top, unknow2.get_location().left + 50, unknow2.get_location().top + 20};
            putimage(unknow2.get_location().left, unknow2.get_location().top, &unknow2.m_motion[0]);
            drawtext(unknow2.get_text().c_str(), &loa, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
        else
        {
            get_function1.refresh(); // refresh unkown location
            loa = {get_function1.get_location().left, get_function1.get_location().top + 20, get_function1.get_location().left + 50, get_function1.get_location().top + 50};
            rectangle(get_function1.get_location().left, get_function1.get_location().top, get_function1.get_location().right, get_function1.get_location().bottom);
            drawtext(get_function1.get_text().c_str(), &loa, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            get_function2.refresh();
            loa = {get_function2.get_location().left, get_function2.get_location().top + 20, get_function2.get_location().left + 50, get_function2.get_location().top + 50};
            rectangle(get_function2.get_location().left, get_function2.get_location().top, get_function2.get_location().right, get_function2.get_location().bottom);
            drawtext(get_function2.get_text().c_str(), &loa, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
    }

    void Game::start()
    {
        std::thread t(std::bind(acceptkey, this));
        while (true)
        {
            if (is_exit)
            {
                return;
            }

            imagerefresh();

            Sleep(200);
            if (unknow1.get_location().left <= steven.get_location().right)
            {
                is_stop = true;
                if (unknow1.get_location().top == steven.get_location().top)
                {
                    if (steven.getm_power() >= unknow1.getm_power())
                    {
                        steven.setm_power(steven.getm_power() - unknow1.getm_power());
                    }
                    else
                    {
                        exit();
                    }
                }
                else if (unknow2.get_location().top == steven.get_location().top)
                {
                    if (steven.getm_power() >= unknow2.getm_power())
                    {
                        steven.setm_power(steven.getm_power() - unknow2.getm_power());
                    }
                    else
                    {
                        exit();
                    }
                }
                unknow1.reset();
                unknow2.reset();
                is_stop = false;
                monster_or_function = false;
            }
            else if (get_function1.get_location().left <= steven.get_location().right)
            {
                is_stop = true;
                if (get_function1.get_location().top == steven.get_location().top)
                {
                    if (get_function1.get_mothod() == strengthen::choose::addtion)
                    {
                        steven.setm_power(steven.getm_power() + get_function1.get_value());
                    }
                    else if (get_function1.get_mothod() == strengthen::choose::subtraction)
                    {
                        steven.setm_power(steven.getm_power() - get_function1.get_value());
                    }
                    else if (get_function1.get_mothod() == strengthen::choose::multiplication)
                    {
                        steven.setm_power(steven.getm_power() * get_function1.get_value());
                    }
                    else
                    {
                        steven.setm_power(steven.getm_power() / get_function1.get_value());
                    }
                }
                else if (get_function2.get_location().top == steven.get_location().top)
                {
                    if (get_function2.get_mothod() == strengthen::choose::addtion)
                    {
                        steven.setm_power(steven.getm_power() + get_function2.get_value());
                    }
                    else if (get_function2.get_mothod() == strengthen::choose::subtraction)
                    {
                        steven.setm_power(steven.getm_power() - get_function2.get_value());
                    }
                    else if (get_function2.get_mothod() == strengthen::choose::multiplication)
                    {
                        steven.setm_power(steven.getm_power() * get_function2.get_value());
                    }
                    else
                    {
                        steven.setm_power(steven.getm_power() / get_function2.get_value());
                    }
                }
                get_function1.reset();
                get_function2.reset();
                is_stop = false;
                monster_or_function = true;
            }

            cleardevice();
        }
    }

    void Game::acceptkey()
    {
        while (1)
        {
            if (!is_stop)
            {
                ExMessage msg;
                if (peekmessage(&msg, EX_KEY))
                {
                    if (msg.message == WM_KEYDOWN)
                    {
                        if (msg.vkcode == VK_DOWN)
                        {
                            steven.setm_location(direction::UP);
                            std::stringstream tmp;
                            tmp << "steven DOWN";
                            logtxt(tmp.str());
                        }
                        else if (msg.vkcode == VK_UP)
                        {
                            steven.setm_location(direction::DOWN);
                            std::stringstream tmp;
                            tmp << "steven UP";
                            logtxt(tmp.str());
                        }
                        else if (msg.vkcode == VK_ESCAPE)
                        {
                            exit();
                            std::stringstream tmp;
                            tmp << "game exit";
                            logtxt(tmp.str());
                        }
                    }
                }
            }
            else if (is_exit)
            {
                return;
            }
        }
    }

}
