#include "Engine.h"

Engine::Engine()
{
    sAppName = "Zelda_Game";
}

bool Engine::OnUserCreate() {
    std::string defPath = "/home/kalex/practice/olcGames/tutorial/Zelda/build/bin/";
    olc::Sprite* spr = new olc::Sprite(defPath + "images/house.png");
    house = new olc::Decal(spr);

    return true;
}

bool Engine::OnUserUpdate(float fElapsedTime) {
    Clear(olc::VERY_DARK_BLUE);

    DrawDecal({0,0}, house, {1,1}, olc::YELLOW);

    return true;
}