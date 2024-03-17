#include "menu.h"

Menu::Menu()
{
    sAppName = "Zelda";
}

bool Menu::OnUserCreate(){
    // Define menu options
    vecMenuOptions.push_back("Start Game");
    vecMenuOptions.push_back("Options");
    vecMenuOptions.push_back("Exit");

    // Initialize selected option to 0
    nSelectedOption = 0;

    return true;
}

bool Menu::OnUserUpdate(float fElapsedTime){
    // Clear screen
    Clear(olc::BLACK);

    // Draw menu options
    for (int i = 0; i < vecMenuOptions.size(); ++i)
    {
        olc::vi2d vTextPos(ScreenWidth() / 2 - 50, 100 + i * 30);
        if (i == nSelectedOption)
            DrawString(vTextPos, "> " + vecMenuOptions[i] + " <", olc::WHITE);
        else
            DrawString(vTextPos, vecMenuOptions[i], olc::WHITE);
    }

    // Handle menu selection with mouse
    if (GetMouse(0).bPressed)
    {
        int selectedOption = GetMouseY() / 30 - 3; // Assuming each option is 30 pixels tall
        if (selectedOption >= 0 && selectedOption < vecMenuOptions.size())
            nSelectedOption = selectedOption;
    }

    // Handle menu selection with keyboard
    if (GetKey(olc::Key::UP).bPressed)
    {
        nSelectedOption--;
        if (nSelectedOption < 0)
            nSelectedOption = vecMenuOptions.size() - 1;
    }
    else if (GetKey(olc::Key::DOWN).bPressed)
    {
        nSelectedOption++;
        if (nSelectedOption >= vecMenuOptions.size())
            nSelectedOption = 0;
    }
    else if (GetKey(olc::Key::ENTER).bPressed)
    {
        // Handle selected option
        if (nSelectedOption == 0)
        {
            // Start Game
        }
        else if (nSelectedOption == 1)
        {
            // Open Options
        }
        else if (nSelectedOption == 2)
        {
            // Exit
            return false;
        }
    }

    return true;
}