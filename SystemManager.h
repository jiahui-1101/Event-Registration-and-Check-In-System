#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <string>
#include "Participant.h"
#include "Event.h"
#include "EventOrganizer.h"

class SystemManager
{
private:
    Participant participants[1000];
    int participantCount;

    Event events[100];
    int eventCount;

    EventOrganizer organizers[100];
    int organizerCount;

public:
    SystemManager();

    // Menus
    void mainMenu();
    void participantMenu();
    void organizerMenu(int orgIndex);
    void adminMenu();

    // Features
    void registerParticipant();  // Feature 1 : Wong Jia Hui
    void participantSelfCheck(); // Feature 2 : Lee Mei Shuet
    void sortParticipantList();  // Feature 3 : Loh Su Ting
    void attendanceDashboard();  // Feature 4 : Christ Ting Shin Ling
    void checkInParticipant(std::string eventID);   // Feature 5 : Wong Jia Hui
    void viewCheckInStatus(std::string eventID);    // Feature 6 : Lee Mei Shuet
    void createEvent();          // Feature 7 : Loh Su Ting
    void checkCapacityAlert(std::string eventID);   // Feature 8 : Christ Ting Shin Ling

    // sub functions (search & sort)
    int searchParticipantByID(std::string id);
    int searchParticipantByEmail(std::string email);
    int searchEventByID(std::string eventID);

    void sortByName();
    void sortByRegistrationTime();
    void sortByID();

    // login function
    int loginOrganizer();
    bool loginAdmin();
};

#endif
