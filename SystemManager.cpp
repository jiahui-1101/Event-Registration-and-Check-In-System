#include "SystemManager.h"
#include <iostream>
using namespace std;

SystemManager::SystemManager()
{
    participantCount = 0;
    eventCount = 0;
    organizerCount = 0;
}

// =======================
// MAIN MENU
// =======================
void SystemManager::mainMenu()
{
    int choice;

    do
    {
        cout << "\n====== EVENT REGISTRATION & CHECK-IN SYSTEM ======\n";
        cout << "1. Participant Menu\n";
        cout << "2. Event Organizer Menu\n";
        cout << "3. Admin Menu\n";
        cout << "0. Exit System\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            participantMenu();
            break;
        case 2:
            int orgIndex = loginOrganizer();
            if (orgIndex != -1)
                organizerMenu(orgIndex);
            break;

        case 3:
            if (loginAdmin())
                adminMenu();
            break;

        case 0:
            cout << "Exiting system...\n";
            break;
        default:
            cout << "Invalid input. Try again.\n";
        }
    } while (choice != 0);
}

// =======================
// PARTICIPANT MENU
// =======================
void SystemManager::participantMenu()
{
    int choice;

    do
    {
        cout << "\n------ PARTICIPANT MENU ------\n";
        cout << "1. Register for Event\n";
        cout << "2. Check Registration Status\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            registerParticipant();
            break; // Feature 1 : Wong Jia Hui
        case 2:
            participantSelfCheck();
            break; // Feature 2 : Lee Mei Shuet
        case 0:
            return;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

// =======================
// EVENT ORGANIZER MENU
// =======================
void SystemManager::organizerMenu(int orgIndex)
{
    int choice;
    string eventID = organizers[orgIndex].getEventID();

    do
    {
        cout << "\n------ EVENT ORGANIZER MENU ------\n";
        cout << "1. Check-In Participant\n";
        cout << "2. View Checked-in & Not Checked-in Participants\n";
        cout << "3. Check Capacity Alert\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            checkInParticipant(eventID);
            break; // Feature 5 : Wong Jia Hui
        case 2:
            viewCheckInStatus(eventID);
            break; // Feature 6 : Lee Mei Shuet
        case 3:
            checkCapacityAlert(eventID);
            break; // Feature 8 : Christ Ting Shin Ling
        case 0:
            return;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

// =======================
// ADMIN MENU
// =======================
void SystemManager::adminMenu()
{
    int choice;

    do
    {
        cout << "\n------ ADMIN MENU ------\n";
        cout << "1. Create Event\n";
        cout << "2. Sort Participant List\n";
        cout << "3. Attendance Dashboard\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            createEvent();
            break; // Feature 7 : Loh Su Ting
        case 2:
            sortParticipantList();
            break; // Feature 3 : Loh Su Ting
        case 3:
            attendanceDashboard();
            break; // Feature 4 : Christ Ting Shin Ling
        case 0:
            return;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

// =======================
// PLACEHOLDERS
// =======================
void SystemManager::registerParticipant()
{
    cout << "[Feature 1] Register Participant - Not implemented yet\n";
}

/*************  ✨ Windsurf Command ⭐  *************/
/**
 * @brief Participant Self Check
 * 
 * This function is responsible for checking the registration status of a participant.
 * 
 * @note Not implemented yet
 */
/*******  7e64b932-f275-482e-958c-b95612e7c269  *******/
void SystemManager::participantSelfCheck()
{
    cout << "[Feature 2] Participant Self Check - Not implemented yet\n";
}

void SystemManager::sortParticipantList()
{
    cout << "[Feature 3] Sorting Participant List - Not implemented yet\n";
}

void SystemManager::attendanceDashboard()
{
    cout << "[Feature 4] Attendance Dashboard - Not implemented yet\n";
}

void SystemManager::checkInParticipant(string eventID)
{
    cout << "[Feature 5] Check-in Participant for Event " << eventID << " - Not implemented yet\n";
}

void SystemManager::viewCheckInStatus(string eventID)
{
    cout << "[Feature 6] View Check-in Status for Event " << eventID << " - Not implemented yet\n";
}

void SystemManager::checkCapacityAlert(string eventID)
{
    cout << "[Feature 8] Capacity Alert for Event " << eventID << " - Not implemented yet\n";
}

void SystemManager::createEvent()
{
    cout << "[Feature 7] Create Event - Not implemented yet\n";
}

// ---- Search & Sort helper placeholders -----
int SystemManager::searchParticipantByID(std::string id) { return -1; }
int SystemManager::searchParticipantByEmail(std::string email) { return -1; }
int SystemManager::searchEventByID(std::string eventID) { return -1; }

void SystemManager::sortByName() {}
void SystemManager::sortByRegistrationTime() {}
void SystemManager::sortByID() {}

// =======================
// LOGIN FUNCTIONS
// =======================
int SystemManager::loginOrganizer()
{
    string orgID, pw, evID;

    cout << "\nOrganizer Login\n";
    cout << "Enter Organizer ID: ";
    cin >> orgID;
    cout << "Enter Password: ";
    cin >> pw;
    cout << "Enter Event ID: ";
    cin >> evID;

    for (int i = 0; i < organizerCount; i++)
    {
        if (organizers[i].getOrganizerID() == orgID &&
            organizers[i].getPassword() == pw &&
            organizers[i].getEventID() == evID)
        {
            cout << "Login successful.\n";
            return i;
        }
    }

    cout << "Invalid organizer credentials.\n";
    return -1;
}
bool SystemManager::loginAdmin()
{
    string id, pass;

    cout << "\nAdmin Login\n";
    cout << "Enter Admin ID: ";
    cin >> id;
    cout << "Enter Admin Password: ";
    cin >> pass;

    if (id == "ADM001" && pass == "admin999")
    {
        cout << "Login successful.\n";
        return true;
    }

    cout << "Invalid Admin credentials.\n";
    return false;
}
