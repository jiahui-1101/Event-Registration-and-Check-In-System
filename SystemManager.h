#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <string>
#include <fstream>
#include "Queue.h"
#include "Participant.h"
#include "Event.h"
#include "EventOrganizer.h"

// ===== Request Structs =====
struct RegistrationRequest {
    std::string name;
    std::string email;
    std::string eventID;
};

struct CheckInRequest {
    std::string participantID;
    std::string eventID;
};

struct AdminRequest {
    std::string command; // "CREATE_EVENT", "SORT", "DASHBOARD"
};

class SystemManager
{
private:
    Participant* participantHead;
    int participantCount;

    Event* eventHead;
    int eventCount;

    EventOrganizer* organizerHead;
    int organizerCount;

    void swapParticipantData(Participant* a, Participant* b);

    // ===== Queues =====
    Queue<RegistrationRequest> registrationQueue;
    Queue<RegistrationRequest> waitingListQueue;
    Queue<CheckInRequest> checkInQueue;
    Queue<AdminRequest> adminQueue;

    // ===== Queue Helpers =====
    int countRegisteredByEvent(const std::string& eventID) const;
    int countCheckedInByEvent(const std::string& eventID) const;

    // ===== Queue Processors =====
    void processNextRegistration();
    void processNextCheckIn();
    void promoteFromWaitingList(const std::string& eventID);
    void processNextAdminRequest();

public:
    SystemManager();
    ~SystemManager();

    // Menus
    void mainMenu();
    void participantMenu();
    void organizerMenu(EventOrganizer* organizer);
    void adminMenu();

    // Features (existing)
    void registerParticipant();
    void participantSelfCheck();
    void sortParticipantList();
    void attendanceDashboard();
    void checkInParticipant(std::string eventID);
    void viewCheckInStatus(std::string eventID);
    void createEvent();
    void checkCapacityAlert(std::string eventID);
    void deleteParticipant();

    // NEW: helpers used by queue
    bool registerParticipantFromRequest(const RegistrationRequest& req);
    bool checkInParticipantByID(const std::string& eventID, const std::string& participantID);

    // Search functions
    Participant* searchParticipantByID(std::string id);
    Participant* searchParticipantByEmail(std::string email);
    Event* searchEventByID(std::string eventID);

    Participant* SequenceSearchParticipant(std::string search_key, bool searchByID);
    Event* SequenceSearchEvent(std::string search_key);

    // Sort helpers
    void sortByName();
    void sortByRegistrationTime();
    void sortByID();

    // Login
    EventOrganizer* loginOrganizer();
    bool loginAdmin();

    // ID generation
    std::string generateParticipantID();

    // Display
    void displayRegistrationInfo(Participant* participant);

    // File handling
    void loadEventsFromFile();
    void loadParticipantsFromFile();
    void loadOrganizersFromFile();
    void loadAllFromFile();
    void saveParticipantsToFile();
    void saveEventsToFile();
};

#endif
