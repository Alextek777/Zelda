#include <RPG_Engine.h>


class Menu : public olc::PixelGameEngine
{
public:
    Menu();

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

private:
    //RPG_Engine game;
    std::vector<std::string> vecMenuOptions;
    int nSelectedOption{};
};