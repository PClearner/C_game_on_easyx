#include "gamerun.h"

int main()
{
    std::string s_motion1("../img/main/Poses/adventurer_walk1.png");
    std::string s_motion2("../img/main/Poses/adventurer_walk2.png");
    std::vector<std::string> s_allmotion{s_motion1, s_motion2};
    std::string s_attack1("../img/main/Poses/adventurer_action1.png");
    std::string s_attack2("../img/main/Poses/adventurer_action2.png");
    std::vector<std::string> s_allattack{s_attack1, s_attack2};

    std::string m_attack1("../img/monster/Poses/zombie_action1.png");
    std::string m_attack2("../img/monster/Poses/zombie_action2.png");
    std::vector<std::string> m_allattack{m_attack1, m_attack2};
    std::string m_motion1("../img/monster/Poses/zombie_walk1.png");
    std::string m_motion2("../img/monster/Poses/zombie_walk2.png");
    std::vector<std::string> m_allmotion{m_motion1, m_motion2};

    star::Game *g = new star::Game(600, 800, s_allmotion, s_allattack, m_allmotion, m_allattack);

    g->init();
    g->start();
    system("pause");

    // ¹Ø±ÕÍ¼ÐÎ´°¿Ú
    closegraph();
    return 0;
}
