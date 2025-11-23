#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <string>
#include "Participant.h"
#include "Event.h"

class SystemManager {
private:
    Participant participants[1000];
    int participantCount;

    Event events[100];
    int eventCount;

public:
    SystemManager();

    // Menus
    void mainMenu();
    void participantMenu();
    void organizerMenu();
    void adminMenu();

    // Features
    void registerParticipant();                 // Feature 1 : Wong Jia Hui
    void participantSelfCheck();                // Feature 2 : Lee Mei Shuet
    void sortParticipantList();                 // Feature 3 : Loh Su Ting
    void attendanceDashboard();                 // Feature 4 : Christ Ting Shin Ling
    void checkInParticipant();                  // Feature 5 : Wong Jia Hui
    void viewCheckInStatus();                   // Feature 6 : Lee Mei Shuet
    void createEvent();                         // Feature 7 : Loh Su Ting
    void checkCapacityAlert();                  // Feature 8 : Christ Ting Shin Ling

    // helper functions (search & sort)
    int searchParticipantByID(std::string id);
    int searchParticipantByEmail(std::string email);
    int searchEventByID(std::string eventID);

    void sortByName();
    void sortByRegistrationTime();
    void sortByID();
};

#endif
