#include <olcPixelGameEngine.h>

class Menu : public olc::PixelGameEngine
{
public:
    Menu();

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

private:
    std::vector<std::string> vecMenuOptions;
    int nSelectedOption;
};