#include "SystemManager.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

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
        {
            int orgIndex = loginOrganizer();
            if (orgIndex != -1)
                organizerMenu(orgIndex);
        }
        break;

        case 3:
        {
            if (loginAdmin())
                adminMenu();
        }
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
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

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
// FEATURE METHODS
// =======================
void SystemManager::registerParticipant()
{
    string name, email, eventID;

    cout << "\n--- Participant Registration ---\n";

    // ============ STEP 1: SAFE INPUT FOR NAME & EMAIL ============
    cout << "Enter Name: ";
    getline(cin, name);
    while (true)
    {
        cout << "Enter Email: ";
        getline(cin, email);

        // validation for email format
        if (email.find('@') != string::npos && email.find('.') != string::npos)
            break;

        cout << "❌ Invalid email format. Please try again.\n";
    }
    // ============ STEP 2: CHECK EXISTING PARTICIPANT ============
    int existingIndex = searchParticipantByEmail(email);

    if (existingIndex != -1)
    {
        Participant &existingParticipant = participants[existingIndex];
        cout << "\n👋 Welcome back, " << existingParticipant.getName() << "!\n";
        cout << "You are currently registered for Event: " << existingParticipant.getEventID() << "\n";

        char choice;
        cout << "Do you want to register for another event? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice != 'y' && choice != 'Y')
        {
            cout << "Thank you for visiting!\n";
            return;
        }
    }

    // ============ STEP 3: Event ID (max 3 attempts) ============
    int attempts = 0;

    while (attempts < 3)
    {
        cout << "Enter Event ID to register: ";
        getline(cin, eventID);

        // event exists?
        if (searchEventByID(eventID) != -1)
        {
            // if same event as before
            if (existingIndex != -1 && participants[existingIndex].getEventID() == eventID)
            {
                cout << "❌ You are already registered for this event! Choose another.\n";
            }
            else
            {
                break; // valid event ID
            }
        }
        else
        {
            cout << "❌ This Event ID does not exist.\n";
        }

        attempts++;
        if (attempts == 3)
        {
            cout << "❌ Too many invalid attempts. Registration cancelled.\n";
            return;
        }
    }
    // ============ STEP 4: Generate ID & timestamp ============
    string newID = generateParticipantID();
    time_t now = time(0);
    string registrationTime = ctime(&now);
    if (!registrationTime.empty() && registrationTime.back() == '\n')
        registrationTime.pop_back();

    Participant newParticipant(name, email, newID, eventID, registrationTime);

    // ============ STEP 5: Add to system ============
    if (participantCount < 1000)
    {
        participants[participantCount++] = newParticipant;
        cout << "\n✅ Successfully registered!\n";
        displayRegistrationInfo(newParticipant);
        saveParticipantsToFile();
    }
    else
    {
        cout << "❌ Error: Registration database is full!\n";
    }
}

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

// =======================
// SEARCH METHODS
// =======================
int SystemManager::searchParticipantByID(std::string id)
{
    return SequenceSearchParticipant(id, participants, participantCount, true);
}

int SystemManager::searchParticipantByEmail(std::string email)
{
    return SequenceSearchParticipant(email, participants, participantCount, false);
}
int SystemManager::searchEventByID(std::string eventID)
{
    return SequenceSearchEvent(eventID, events, eventCount);
}
int SystemManager::SequenceSearchParticipant(string search_key, Participant array[], int array_size, bool searchByID)
{
    int index = -1;
    for (int p = 0; p < array_size; p++)
    {
        if (searchByID)
        {
            if (array[p].getID() == search_key)
            {
                index = p;
                break;
            }
        }
        else
        {
            if (array[p].getEmail() == search_key)
            {
                index = p;
                break;
            }
        }
    }
    return index;
}

int SystemManager::SequenceSearchEvent(string search_key, Event array[], int array_size)
{
    int index = -1;
    for (int p = 0; p < array_size; p++)
    {

        if (array[p].getEventID() == search_key)
        {
            index = p;
            break;
        }
    }
    return index;
}

// =======================
// SORT METHODS
// =======================
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

// =======================
// AUTO-GENERATE PARTICIPANT ID
// =======================
string SystemManager::generateParticipantID()
{
    // Generate ID in format: P001, P002, etc.
    stringstream ss;
    ss << "P" << setw(3) << setfill('0') << (participantCount + 1);
    return ss.str();
}

// =======================
// DISPLAY REGISTRATION INFO
// =======================
void SystemManager::displayRegistrationInfo(const Participant &participant)
{
    cout << "=================================\n";
    cout << "      REGISTRATION CONFIRMED     \n";
    cout << "=================================\n";
    cout << "Name: " << participant.getName() << "\n";
    cout << "Email: " << participant.getEmail() << "\n";
    cout << "Participant ID: " << participant.getID() << "\n";
    cout << "Event ID: " << participant.getEventID() << "\n";
    cout << "Registration Time: " << participant.getRegistrationTime() << "\n";
    cout << "Status: Registered\n";
    cout << "=================================\n";
}

// =======================
// FILE READING FUNCTIONS
// =======================

void SystemManager::loadEventsFromFile()
{
    ifstream file("events.txt");
    if (!file.is_open())
    {
        cout << "⚠️  events.txt not found. Starting with empty events.\n";
        return;
    }

    string line;
    while (getline(file, line) && eventCount < 100)
    {
        stringstream ss(line);
        string id, name, date, time, venue, capacityStr;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        getline(ss, venue, ',');
        getline(ss, capacityStr, ',');

        int capacity = stoi(capacityStr);
        events[eventCount] = Event(id, name, date, time, venue, capacity);
        eventCount++;
    }
    file.close();
    cout << "✅ Loaded " << eventCount << " events from file.\n";
}

void SystemManager::loadParticipantsFromFile()
{
    ifstream file("participants.txt");
    if (!file.is_open())
    {
        cout << "⚠️  participants.txt not found. Starting with empty participants.\n";
        return;
    }

    string line;
    while (getline(file, line) && participantCount < 1000)
    {
        stringstream ss(line);
        string id, name, email, eventID, regTime, checkedInStr, checkInTime;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, eventID, ',');
        getline(ss, regTime, ',');
        getline(ss, checkedInStr, ',');
        getline(ss, checkInTime, ',');

        Participant p(name, email, id, eventID, regTime);
        if (checkedInStr == "true")
        {
            p.setCheckedIn(checkInTime);
        }
        participants[participantCount] = p;
        participantCount++;
    }
    file.close();
    cout << "✅ Loaded " << participantCount << " participants from file.\n";
}

void SystemManager::loadOrganizersFromFile()
{
    ifstream file("organizers.txt");
    if (!file.is_open())
    {
        cout << "⚠️  organizers.txt not found. Starting with empty organizers.\n";
        return;
    }

    string line;
    while (getline(file, line) && organizerCount < 100)
    {
        stringstream ss(line);
        string orgID, password, eventID;

        getline(ss, orgID, ',');
        getline(ss, password, ',');
        getline(ss, eventID, ',');

        organizers[organizerCount] = EventOrganizer(orgID, password, eventID);
        organizerCount++;
    }
    file.close();
    cout << "✅ Loaded " << organizerCount << " organizers from file.\n";
}
void SystemManager::loadAllFromFile()
{
    loadEventsFromFile();
    loadParticipantsFromFile();
    loadOrganizersFromFile();
}

void SystemManager::saveParticipantsToFile()
{
    ofstream file("participants.txt");
    if (!file.is_open())
    {
        cout << "❌ Error: Cannot save participants to file!\n";
        return;
    }

    for (int i = 0; i < participantCount; i++)
    {
        file << participants[i].getID() << ","
             << participants[i].getName() << ","
             << participants[i].getEmail() << ","
             << participants[i].getEventID() << ","
             << participants[i].getRegistrationTime() << ","
             << (participants[i].isCheckedIn() ? "true" : "false") << ","
             << participants[i].getCheckInTime() << "\n";
    }
    file.close();
    cout << "💾 Saved " << participantCount << " participants to file.\n";
}
