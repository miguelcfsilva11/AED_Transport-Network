#include "transport_network.h"
#include "Menu.h"

int main()
{
    Menu menu = Menu();
    int chosenOption = menu.printMenu();
    while (chosenOption == 1)
    {
        menu.execute();
        chosenOption = menu.printMenu();
    }
    return 0;
}