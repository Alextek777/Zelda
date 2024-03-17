#define OLC_PGE_APPLICATION
#include <menu/menu.h>


int main()
{
    Menu menu;
    if (menu.Construct(320, 240, 2, 2))
        menu.Start();

    return 0;
}