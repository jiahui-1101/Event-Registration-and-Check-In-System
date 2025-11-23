#include "SystemManager.h"
#include "Participant.h"
#include "Event.h"
#include <iostream>

int main()
{
    SystemManager sys;
    sys.loadAllFromFile();
    sys.mainMenu();
    return 0;
}
