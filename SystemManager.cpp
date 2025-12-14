#include "SystemManager.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// =======================
// CONSTRUCTOR & DESTRUCTOR
// =======================
SystemManager::SystemManager()
{
    participantHead = NULL;
    eventHead = NULL;
    organizerHead = NULL;

    participantCount = 0;
    eventCount = 0;
    organizerCount = 0;
}

SystemManager::~SystemManager()
{
    Participant *currP = participantHead;
    while (currP != NULL)
    {
        Participant *nextP = currP->getNext();
        delete currP;
        currP = nextP;
    }

    Event *currE = eventHead;
    while (currE != NULL)
    {
        Event *nextE = currE->getNext();
        delete currE;
        currE = nextE;
    }

    EventOrganizer *currO = organizerHead;
    while (currO != NULL)
    {
        EventOrganizer *nextO = currO->getNext();
        delete currO;
        currO = nextO;
    }
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            participantMenu();
            break;

        case 2:
        {
            EventOrganizer *org = loginOrganizer();
            if (org != NULL)
            {
                organizerMenu(org);
            }
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
void SystemManager::organizerMenu(EventOrganizer *org)
{
    int choice;
    string eventID = org->getEventID();

    do
    {
        cout << "\n------ EVENT ORGANIZER MENU ------\n";
        cout << "1. Check-In Participant\n";
        cout << "2. View Checked-in & Not Checked-in Participants\n";
        cout << "3. Check Capacity Alert\n";
        cout << "4. Delete Participant\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            checkInParticipant(eventID);
            break;
        case 2:
            viewCheckInStatus(eventID);
            break;
        case 3:
            // checkCapacityAlert(eventID);
            break;
        case 4:
            deleteParticipant();
            break;
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            // createEvent();
            break; // Feature 7 : Loh Su Ting
        case 2:
            // sortParticipantList();
            break; // Feature 3 : Loh Su Ting
        case 3:
            // attendanceDashboard();
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

    // STEP 1: INPUT NAME & EMAIL
    cout << "Enter Name: ";
    getline(cin, name);
    while (true)
    {
        cout << "Enter Email: ";
        getline(cin, email);
        if (email.find('@') != string::npos && email.find('.') != string::npos)
            break;
        cout << "❌ Invalid email format. Please try again.\n";
    }

    // STEP 2: CHECK EXISTING PARTICIPANT
    Participant *existingParticipant = searchParticipantByEmail(email);

    if (existingParticipant != NULL)
    {
        cout << "\n👋 Welcome back, " << existingParticipant->getName() << "!\n";
        cout << "You are currently registered for Event: " << existingParticipant->getEventID() << "\n";

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

    // STEP 3: Event ID Validation
    int attempts = 0;
    while (attempts < 3)
    {
        cout << "Enter Event ID to register: ";
        getline(cin, eventID);

        if (searchEventByID(eventID) != NULL)
        {
            if (existingParticipant != NULL && existingParticipant->getEventID() == eventID)
            {
                cout << "❌ You are already registered for this event! Choose another.\n";
            }
            else
            {
                break;
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

    // STEP 4: Create Data
    string newID = generateParticipantID();
    time_t now = time(0);
    string registrationTime = ctime(&now);
    if (!registrationTime.empty() && registrationTime.back() == '\n')
        registrationTime.pop_back();

    // STEP 5: Add to Linked List
    Participant *newParticipant = new Participant(newID, name, email, eventID, registrationTime);
    newParticipant->setNext(participantHead);
    participantHead = newParticipant;

    participantCount++;

    cout << "\n✅ Successfully registered!\n";
    displayRegistrationInfo(newParticipant);
    saveParticipantsToFile();
}

void SystemManager::participantSelfCheck()
{
    cout << "\n--- [Feature 2] Check Registration Status ---\n";

    string input;
    cout << "Please Enter your Email or Participant ID to verify: ";
    getline(cin, input);
    // search participant by email first
    Participant* p = searchParticipantByEmail(input);

    // if email not found, search by ID
    if (p == NULL)
    {
        p = searchParticipantByID(input);
    }
    
    // if participant found
if (p != NULL)
    {
        string eventName = "Unknown Event";
        Event* eventObj = searchEventByID(p->getEventID());
        if (eventObj != NULL)
        {
            eventName = eventObj->getEventName();
        }

         cout << "\n✅ Record Found!\n";
         cout << "=================================\n";
         cout << "Name: " << p->getName()<< "\n";
         // cout << "Event ID: " << p->getEventID() << "\n";
         cout << "Event: " << eventName << " (" << p->getEventID() << ")\n";
         cout << "Registration Time: " << p->getRegistrationTime() << "\n";
         // display check-in status
         cout << "Status: " << (p->isCheckedIn() ? "Checked-In" : "Registered Only") << "\n";

         if (p->isCheckedIn())
         {
             cout << "Check-in Time: " << p->getCheckInTime() << "\n";
         }
         cout << "=================================\n";
     }
    else
     {
        cout << "❌ Participant not found.\n";
     }
     cout << "\nPress Enter to continue...";
     cin.get();
 }

// void SystemManager::sortParticipantList()
// {
//     int choice;

//     if (participantCount == 0)
//     {
//         cout << "⚠️ No participants to sort.\n";
//         return;
//     }

//     cout << "Sort by:\n";
//     cout << "1. Name (Alphabetical)\n";
//     cout << "2. Participant ID (Ascending)\n";
//     cout << "3. Registration Time (Newest First)\n";
//     cout << "0. Cancel\n";
//     cout << "Enter your choice: ";

//     cin >> choice;
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');

//     switch (choice)
//     {
//     case 1:
//         sortByName();
//         cout << "✅ Participant list sorted by Name.\n";
//         break;
//     case 2:
//         sortByID();
//         cout << "✅ Participant list sorted by ID.\n";
//         break;
//     case 3:
//         sortByRegistrationTime();
//         cout << "✅ Participant list sorted by Registration Time (Newest First).\n";
//         break;
//     case 0:
//         cout << "Sort cancelled.\n";
//         return;
//     default:
//         cout << "Invalid choice. Sort cancelled.\n";
//     }

//     saveParticipantsToFile();

//     cout << "\nPress Enter to continue...";
//     cin.get();
// }

// // Feature 4: attendance dashboard
// void SystemManager::attendanceDashboard()
// {
//     cout << "\n --- [Feature 4] Attendance Dashboard ---\n";
//     cout << "\n========================================" << endl;
//     cout << "      EVENT ATTENDANCE DASHBOARD        " << endl;
//     cout << "========================================" << endl;
//     int totalRegistered = participantCount;
//     int totalCheckedIn = 0;
//     int totalNotCheckedIn = 0;
//     for (int i = 0; i < participantCount; i++)
//     {
//         if (participants[i].isCheckedIn())
//         {
//             totalCheckedIn++;
//         }
//         else
//         {
//             totalNotCheckedIn++;
//         }
//     }

//     // calculate percentage
//     double attendancePercent = 0.0;
//     if (totalRegistered > 0)
//     {
//         // Cast to double to ensure decimal precision
//         attendancePercent = ((double)totalCheckedIn / totalRegistered) * 100.0;
//     }
//     cout << left << setw(25) << "Total Registered:" << totalRegistered << endl;
//     cout << left << setw(25) << "Total Checked-In:" << totalCheckedIn << endl;
//     cout << left << setw(25) << "Total Not Checked-In:" << totalNotCheckedIn << endl;
//     cout << "----------------------------------------" << endl;
//     cout << fixed << setprecision(2); // Set decimal precision for percentage
//     cout << left << setw(25) << "Attendance Percentage:" << attendancePercent << "%" << endl;
//     cout << "========================================" << endl;

//     cout << "\nPress Enter to continue...";
//     cin.get();
// }

void SystemManager::checkInParticipant(string eventID)
{
    char continueChoice;
    do
    {
        cout << "\n--- Check-In Participant for Event " << eventID << " ---\n";
        string participantID;
        cout << "Enter Participant ID: ";
        getline(cin, participantID);

        // STEP 1: VALIDATIONS
        Participant *p = searchParticipantByID(participantID);

        if (p == NULL)
        {
            cout << "❌ Participant not found.\n";
            return;
        }

        if (p->getEventID() != eventID)
        {
            cout << "❌ Participant is not registered for this event.\n";
            return;
        }

        if (p->isCheckedIn())
        {
            cout << "⚠️ Participant " << p->getName() << " already checked in at " << p->getCheckInTime() << ".\n";
            return;
        }

        Event* eventObj = searchEventByID(eventID);
        if (eventObj != NULL) 
        {
            int maxCap = eventObj->getCapacity();
            int currentCount = 0;

            Participant* scanner = participantHead;
            while (scanner != NULL)
            {
                if (scanner->getEventID() == eventID && scanner->isCheckedIn()) 
                {
                    currentCount++;
                }
                scanner = scanner->getNext();
            }

            if (currentCount >= maxCap)
            {
                cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                cout << "⛔ CHECK-IN BLOCKED: EVENT IS FULL! ⛔" << endl;
                cout << "Current Status: " << currentCount << "/" << maxCap << endl;
                cout << "System blocked " << p->getName() << " from entering." << endl;
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                return;
            }
        }

        // STEP 2: CHECK-IN
        time_t now = time(0);
        string checkInTime = ctime(&now);
        if (!checkInTime.empty() && checkInTime.back() == '\n')
            checkInTime.pop_back();

        p->setCheckedIn(checkInTime);

        cout << "✅ Participant " << p->getName() << " successfully checked in.\n";
        saveParticipantsToFile();

        cout << "Check in another? (y/n): ";
        cin >> continueChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (continueChoice == 'y' || continueChoice == 'Y');
}

 void SystemManager::viewCheckInStatus(string eventID)
 {
     cout << "\n--- [Feature 6] Check-In Status List for Event: " << eventID << " ---\n";

     // CREATE ARRAYS TO HOLD CHECKED-IN AND NOT CHECKED-IN PARTICIPANTS
     Participant* checkedInList[1000];
     Participant* notCheckedInList[1000];
     int ciCount = 0;  // number of checked-in participants
     int nciCount = 0; // number of not checked-in participants

     // TRANVERSING participant list, filtering checked-in and not checked-in
    Participant* curr = participantHead; // start from head
    while (curr != NULL)
    {
        if (curr->getEventID() == eventID)
        { // only for the specified event
            if (curr->isCheckedIn())
            {
                checkedInList[ciCount] = curr;
                ciCount++;
            }
            else
            {
                notCheckedInList[nciCount] = curr;
                nciCount++;
            }
        }
        curr = curr->getNext(); // move to next participant
    }

     // SORTING (BUBBLE SORT)
     for (int i = 0; i < ciCount - 1; i++)
     { // SORTING checked-in list
         for (int j = 0; j < ciCount - i - 1; j++)
         {
             // COMPARING NAMES, SWAP IF j > j+1
             if (checkedInList[j]->getName() > checkedInList[j + 1]->getName())
             {
                 // swap(checkedInList[j], checkedInList[j + 1]);
                 Participant* temp = checkedInList[j];
                 checkedInList[j] = checkedInList[j + 1];
                 checkedInList[j + 1] = temp;
             }
         }
     }

     for (int i = 0; i < nciCount - 1; i++)
        { // SORTING not checked-in list
         for (int j = 0; j < nciCount - i - 1; j++)
         {
             // COMPARING NAMES, SWAP IF j > j+1
             if (notCheckedInList[j]->getName() > notCheckedInList[j + 1]->getName())
             {
                 Participant* temp = notCheckedInList[j];
                 notCheckedInList[j] = notCheckedInList[j + 1];
                 notCheckedInList[j + 1] = temp;
             }
         }
     }
     // DISPLAYING CHECKED-IN PARTICIPANTS
     cout << "\n--- Checked-In Participants ---\n";
     cout << left << setw(10) << "ID" << setw(25) << "Name" << "Check-in Time\n";
     cout << "----------------------------------------------------------------\n";
     if (ciCount == 0)
         cout << "(None)\n";
     for (int i = 0; i < ciCount; i++)
     {
         cout << left << setw(10) << checkedInList[i]->getID()
              << setw(25) << checkedInList[i]->getName()
              << checkedInList[i]->getCheckInTime() << "\n";
     }

     // DISPLAYING NOT CHECKED-IN PARTICIPANTS
     cout << "\n--- Not Checked-In Participants ---\n";
     cout << left << setw(10) << "ID" << setw(25) << "Name" << "Email\n";
     cout << "----------------------------------------------------------------\n";
     if (nciCount == 0)
         cout << "(None)\n";
     for (int i = 0; i < nciCount; i++)
     {
         cout << left << setw(10) << notCheckedInList[i]->getID()
              << setw(25) << notCheckedInList[i]->getName()
              << notCheckedInList[i]->getEmail() << "\n";
     }

     cout << "\nPress Enter to continue...";
     cin.get();
 }

// void SystemManager::checkCapacityAlert(string eventID)
// {
//     cout << "\n--- [Feature 8] Capacity Monitor for Event: " << eventID << " ---\n";

//     // 1. Get Event Capacity
//     int eventIndex = searchEventByID(eventID);
//     if (eventIndex == -1)
//     {
//         cout << "❌ Error: Event not found.\n";
//         return;
//     }
//     int maxCapacity = events[eventIndex].getCapacity();
//     string eventName = events[eventIndex].getEventName();

//     // 2. Count Current Check-Ins for this specific event
//     int currentCheckIns = 0;
//     for (int i = 0; i < participantCount; i++)
//     {
//         // Only count if they are in THIS event AND checked in
//         if (participants[i].getEventID() == eventID && participants[i].isCheckedIn())
//         {
//             currentCheckIns++;
//         }
//     }

//     // 3. Display Status
//     cout << "Event: " << eventName << endl;
//     cout << "Status: " << currentCheckIns << " / " << maxCapacity << " Checked In.\n";
//     cout << "----------------------------------------\n";

//     // 4. Alert Logic
//     if (currentCheckIns >= maxCapacity)
//     {
//         cout << "🔴 CRITICAL ALERT: EVENT FULL!\n";
//         cout << "   No further check-ins will be allowed.\n";
//     }
//     else if (currentCheckIns >= (maxCapacity * 0.9))
//     {
//         cout << "⚠️  WARNING: Near Capacity (Over 90%)\n";
//     }
//     else
//     {
//         cout << "🟢 Status Normal. Capacity available.\n";
//     }

//     cout << "\nPress Enter to continue...";
//     cin.get();
// }

// void SystemManager::createEvent()
// {
//     if (eventCount >= 100)
//     {
//         cout << "❌ Error: Event database is full! (Max 100 events).\n";
//         return;
//     }

//     string id, name, date, time, venue;
//     int capacity;

//     // STEP 1: Event ID (must be unique)
//     while (true)
//     {
//         cout << "Enter new Event ID (e.g., E001): ";
//         getline(cin, id);

//         if (searchEventByID(id) == -1)
//         {
//             break; // ID is unique
//         }
//         cout << "❌ Error: Event ID '" << id << "' already exists. Try again.\n";
//     }

//     // STEP 2: Get other details
//     cout << "Enter Event Name: ";
//     getline(cin, name);
//     cout << "Enter Date (DD/MM/YYYY): ";
//     getline(cin, date);
//     cout << "Enter Time (HH:MM AM/PM): ";
//     getline(cin, time);
//     cout << "Enter Venue: ";
//     getline(cin, venue);

//     // STEP 3: Capacity Input (must be a positive number)
//     cout << "Enter Max Capacity: ";
//     while (!(cin >> capacity) || capacity <= 0)
//     {
//         cout << "❌ Invalid input. Capacity must be a positive number. Enter again: ";
//         cin.clear();
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//     }
//     cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after int input

//     // STEP 4: Add to system and save
//     Event newEvent(id, name, date, time, venue, capacity);
//     events[eventCount++] = newEvent;

//     cout << "\n✅ Event '" << name << "' created successfully!\n";
//     cout << "ID: " << id << " | Capacity: " << capacity << endl;

//     saveEventsToFile();
// }
void SystemManager::deleteParticipant()
{
    cout << "\n--- Delete Participant ---\n";
    string id;
    cout << "Enter Participant ID to delete: ";
    getline(cin, id);

    // 1. Find the participant
    Participant *curr = participantHead;
    Participant *prev = NULL;

    while (curr != NULL && curr->getID() != id)
    {
        prev = curr;
        curr = curr->getNext();
    }

    if (curr == NULL)
    {
        cout << "❌ Participant not found.\n";
        return;
    }

    // 2. Delete the participant
    if (prev == NULL)
    {
        participantHead = curr->getNext();
    }

    else
    {
        prev->setNext(curr->getNext());
    }

    cout << "🗑️ Deleted Participant: " << curr->getName() << endl;
    delete curr;
    participantCount--;

    saveParticipantsToFile();
}
// =======================
// SEARCH METHODS
// =======================
Participant *SystemManager::searchParticipantByID(std::string id)
{
    return SequenceSearchParticipant(id, true);
}
Participant *SystemManager::searchParticipantByEmail(std::string email)
{
    return SequenceSearchParticipant(email, false);
}
Event *SystemManager::searchEventByID(std::string eventID)
{
    return SequenceSearchEvent(eventID);
}
Participant *SystemManager::SequenceSearchParticipant(string search_key, bool searchByID)
{
    Participant *curr = participantHead;
    while (curr != NULL)
    {
        if (searchByID)
        {
            if (curr->getID() == search_key)
                return curr;
        }
        else
        {
            if (curr->getEmail() == search_key)
                return curr;
        }
        curr = curr->getNext();
    }
    return NULL;
}

Event *SystemManager::SequenceSearchEvent(string search_key)
{
    Event *curr = eventHead;
    while (curr != NULL)
    {
        if (curr->getEventID() == search_key)
            return curr;
        curr = curr->getNext();
    }
    return NULL;
}

// // =======================
// // SORT METHODS
// // =======================

// // insertion sort
// void SystemManager::sortByName()
// {
//     if (participantCount <= 1)
//     {
//         return;
//     }

//     for (int i = 1; i < participantCount; i++)
//     {
//         Participant key = participants[i];
//         int j = i - 1;

//         while (j >= 0 && participants[j].getName() > key.getName())
//         {
//             participants[j + 1] = participants[j];
//             j = j - 1;
//         }

//         participants[j + 1] = key;
//     }
// }

// // bubble sort
// void SystemManager::sortByRegistrationTime()
// {
//     if (participantCount <= 1)
//     {
//         return;
//     }

//     for (int i = 0; i < participantCount - 1; i++)
//     {
//         for (int j = 0; j < participantCount - i - 1; j++)
//         {
//             if (participants[j].getRegistrationTime() < participants[j + 1].getRegistrationTime())
//             {
//                 Participant temp = participants[j];
//                 participants[j] = participants[j + 1];
//                 participants[j + 1] = temp;
//             }
//         }
//     }
// }

// // selection sort
// void SystemManager::sortByID()
// {
//     if (participantCount <= 1)
//     {
//         return;
//     }

//     int min_idx;

//     for (int i = 0; i < participantCount - 1; i++)
//     {
//         min_idx = i;

//         for (int j = i + 1; j < participantCount; j++)
//         {
//             if (participants[j].getID() < participants[min_idx].getID())
//             {
//                 min_idx = j;
//             }
//         }

//         if (min_idx != i)
//         {
//             Participant temp = participants[i];
//             participants[i] = participants[min_idx];
//             participants[min_idx] = temp;
//         }
//     }
// }

// =======================
// LOGIN FUNCTIONS
// =======================
EventOrganizer *SystemManager::loginOrganizer()
{
    string orgID, pw, evID;

    cout << "\nOrganizer Login\n";
    cout << "Enter Organizer ID: ";
    cin >> orgID;
    cout << "Enter Password: ";
    cin >> pw;
    cout << "Enter Event ID: ";
    cin >> evID;

    EventOrganizer *curr = organizerHead;
    while (curr != NULL)
    {
        if (curr->getOrganizerID() == orgID &&
            curr->getPassword() == pw &&
            curr->getEventID() == evID)
        {
            cout << "Login successful.\n";
            return curr;
        }
        curr = curr->getNext();
    }

    cout << "Invalid organizer credentials.\n";
    return NULL;
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
void SystemManager::displayRegistrationInfo(Participant *participant)
{
    if (participant == NULL)
        return;

    cout << "=================================\n";
    cout << "      REGISTRATION CONFIRMED     \n";
    cout << "=================================\n";
    cout << "Name: " << participant->getName() << "\n";
    cout << "Email: " << participant->getEmail() << "\n";
    cout << "Participant ID: " << participant->getID() << "\n";
    cout << "Event ID: " << participant->getEventID() << "\n";
    cout << "Registration Time: " << participant->getRegistrationTime() << "\n";
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
    Event *tail = NULL;

    while (getline(file, line))
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
        Event *newEvent = new Event(id, name, date, time, venue, capacity);

        if (eventHead == NULL)
        {
            eventHead = newEvent;
            tail = newEvent;
        }
        else
        {
            tail->setNext(newEvent);
            tail = newEvent;
        }
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
    Participant *tail = NULL;

    while (getline(file, line))
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

        Participant *p = new Participant(id, name, email, eventID, regTime);
        if (checkedInStr == "true")
        {
            p->setCheckedIn(checkInTime);
        }

        if (participantHead == NULL)
        {
            participantHead = p;
            tail = p;
        }
        else
        {
            tail->setNext(p);
            tail = p;
        }
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
    EventOrganizer *tail = NULL;

    while (getline(file, line))
    {
        stringstream ss(line);
        string orgID, password, eventID;

        getline(ss, orgID, ',');
        getline(ss, password, ',');
        getline(ss, eventID, ',');

        EventOrganizer *newOrg = new EventOrganizer(orgID, password, eventID);

        if (organizerHead == NULL)
        {
            organizerHead = newOrg;
            tail = newOrg;
        }
        else
        {
            tail->setNext(newOrg);
            tail = newOrg;
        }
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

// =======================
// FILE SAVING FUNCTIONS
// =======================

void SystemManager::saveParticipantsToFile()
{
    ofstream file("participants.txt");
    if (!file.is_open())
    {
        cout << "❌ Error: Cannot save participants to file!\n";
        return;
    }

    Participant *curr = participantHead;
    while (curr != NULL)
    {
        file << curr->getID() << ","
             << curr->getName() << ","
             << curr->getEmail() << ","
             << curr->getEventID() << ","
             << curr->getRegistrationTime() << ","
             << (curr->isCheckedIn() ? "true" : "false") << ","
             << curr->getCheckInTime() << "\n";

        curr = curr->getNext();
    }

    file.close();
    cout << "💾 Saved " << participantCount << " participants to file.\n";
}

void SystemManager::saveEventsToFile()
{
    ofstream file("events.txt");
    if (!file.is_open())
    {
        cout << "❌ Error: Cannot save events to file (events.txt)!\n";
        return;
    }

    Event *curr = eventHead;
    while (curr != NULL)
    {
        file << curr->getEventID() << ","
             << curr->getEventName() << ","
             << curr->getEventDate() << ","
             << curr->getEventTime() << ","
             << curr->getVenue() << ","
             << curr->getCapacity() << "\n";

        curr = curr->getNext();
    }

    file.close();
    cout << "💾 Saved " << eventCount << " events to file.\n";
}