#include <olcPixelGameEngine.h>

class Engine : public olc::PixelGameEngine
{
public:
    Engine();

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
private:
    olc::Decal *house;
};