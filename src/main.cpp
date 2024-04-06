#define OLC_PGE_APPLICATION
#include <menu/menu.h>


auto main() -> int
{
    Menu menu;
    if (menu.Construct(320, 240, 2, 2) != 0) {
        menu.Start();
}

    return 0;
}