#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <string>
#include <fstream>
#include "Participant.h"
#include "Event.h"
#include "EventOrganizer.h"

class SystemManager
{
private:
    Participant* participantHead;
    int participantCount;

    Event* eventHead;
    int eventCount;

    EventOrganizer* organizerHead;
    int organizerCount;

    // void swapParticipantData(Participant* a, Participant* b);

public:
    SystemManager();
    ~SystemManager();

    // Menus
    void mainMenu();
    void participantMenu();
    
    void organizerMenu(EventOrganizer* organizer);
    void adminMenu();

    // Features
    void registerParticipant();  // Feature 1： Wong Jia Hui
    // void participantSelfCheck(); // Feature 2： Lee Mei Shuet
    // void sortParticipantList();  // Feature 3: Loh Su Ting
    // void attendanceDashboard();  // Feature 4: Christ Ting Shin Ling
    void checkInParticipant(std::string eventID);   // Feature 5： Wong Jia Hui
    // void viewCheckInStatus(std::string eventID);    // Feature 6: Lee Mei Shuet
    // void createEvent();                             // Feature 7: Loh Su Ting
    // void checkCapacityAlert(std::string eventID);   // Feature 8: Christ Ting Shin Ling
    void deleteParticipant(); //Feature 9: Wong Jia Hui

    // Search functions
    Participant* searchParticipantByID(std::string id);
    Participant* searchParticipantByEmail(std::string email);
    Event* searchEventByID(std::string eventID);
    
    Participant* SequenceSearchParticipant(std::string search_key, bool searchByID);
    Event* SequenceSearchEvent(std::string search_key);

    // void sortByName();
    // void sortByRegistrationTime();
    // void sortByID();

    // login function
    EventOrganizer* loginOrganizer();
    bool loginAdmin();

    // ID generation
    std::string generateParticipantID();
    
    // Display functions
    void displayRegistrationInfo(Participant* participant);

    // File handling functions
    void loadEventsFromFile();
    void loadParticipantsFromFile();
    void loadOrganizersFromFile();
    void loadAllFromFile();
    void saveParticipantsToFile();
    void saveEventsToFile();
};

#endif