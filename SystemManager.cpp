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
        cout << "1. Add Registration Request (Queue)\n";
        cout << "2. Check Registration Status\n";
        cout << "3. Process Next Registration (Dequeue)\n";
        cout << "4. View Queue Size / Position\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            registerParticipant(); // now enqueue
            break;
        case 2:
            participantSelfCheck();
            break;
        case 3:
            processNextRegistration();
            break;
        case 4:
            cout << "\nRegistration Queue Size: " << registrationQueue.size() << endl;
            cout << "Waiting List Queue Size: " << waitingListQueue.size() << endl;
            cout << "Press Enter to continue...";
            cin.get();
            break;
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
        cout << "1. Check-In Participant (Manual)\n";
        cout << "2. View Checked-in & Not Checked-in Participants\n";
        cout << "3. Check Capacity Alert\n";
        cout << "4. Delete Participant\n";
        cout << "5. Add Arrived Participant to Check-in Queue\n";
        cout << "6. Serve Next from Check-in Queue (Dequeue)\n";
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
            checkCapacityAlert(eventID);
            break;
        case 4:
            deleteParticipant();
            break;
        case 5:
        {
            string pid;
            cout << "Enter Participant ID to enqueue: ";
            getline(cin, pid);
            CheckInRequest r{pid, eventID};
            checkInQueue.enqueue(r);
            cout << "✅ Added to Check-in Queue. Position: " << checkInQueue.size() << endl;
            cout << "Press Enter to continue...";
            cin.get();
            break;
        }
        case 6:
            processNextCheckIn();
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
        cout << "1. Create Event (Manual)\n";
        cout << "2. Sort Participant List (Manual)\n";
        cout << "3. Attendance Dashboard (Manual)\n";
        cout << "4. Add Admin Request to Queue\n";
        cout << "5. Process Next Admin Request (Dequeue)\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            createEvent();
            break;
        case 2:
            sortParticipantList();
            break;
        case 3:
            attendanceDashboard();
            break;
        case 4:
        {
            int c;
            cout << "\n--- Add Admin Request ---\n";
            cout << "1. CREATE_EVENT\n";
            cout << "2. SORT\n";
            cout << "3. DASHBOARD\n";
            cout << "Enter request: ";
            cin >> c;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            AdminRequest r;
            if (c == 1)
                r.command = "CREATE_EVENT";
            else if (c == 2)
                r.command = "SORT";
            else if (c == 3)
                r.command = "DASHBOARD";
            else
            {
                cout << "Invalid.\n";
                break;
            }

            adminQueue.enqueue(r);
            cout << "✅ Added to Admin Queue. Queue size: " << adminQueue.size() << endl;
            cout << "Press Enter to continue...";
            cin.get();
            break;
        }
        case 5:
            processNextAdminRequest();
            break;
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

    cout << "\n--- Add Registration Request (Queue) ---\n";

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

    int attempts = 0;
    while (attempts < 3)
    {
        cout << "Enter Event ID to register: ";
        getline(cin, eventID);

        if (searchEventByID(eventID) != NULL)
        {
            if (existingParticipant != NULL && existingParticipant->getEventID() == eventID)
                cout << "❌ You are already registered for this event! Choose another.\n";
            else
                break;
        }
        else
            cout << "❌ This Event ID does not exist.\n";

        attempts++;
        if (attempts == 3)
        {
            cout << "❌ Too many invalid attempts. Registration cancelled.\n";
            return;
        }
    }

    RegistrationRequest req{name, email, eventID};
    registrationQueue.enqueue(req);

    cout << "\n✅ Added to Registration Queue.\n";
    cout << "📌 Your position in queue: " << registrationQueue.size() << endl;
    cout << "Press Enter to continue...";
    cin.get();
}

void SystemManager::participantSelfCheck()
{
    cout << "\n--- [Feature 2] Check Registration Status ---\n";

    string input;
    cout << "Please Enter your Email or Participant ID to verify: ";
    getline(cin, input);
    // search participant by email first
    Participant *p = searchParticipantByEmail(input);

    // if email not found, search by ID
    if (p == NULL)
    {
        p = searchParticipantByID(input);
    }

    // if participant found
    if (p != NULL)
    {
        string eventName = "Unknown Event";
        Event *eventObj = searchEventByID(p->getEventID());
        if (eventObj != NULL)
        {
            eventName = eventObj->getEventName();
        }

        cout << "\n✅ Record Found!\n";
        cout << "=================================\n";
        cout << "Name: " << p->getName() << "\n";
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

void SystemManager::sortParticipantList()
{
    if (participantHead == NULL || participantHead->getNext() == NULL)
    {
        cout << "⚠️ No participants to sort or only one participant.\n";
        return;
    }

    int choice;
    cout << "\n--- Sort Participants ---\n";
    cout << "1. Name (Alphabetical)\n";
    cout << "2. Participant ID (Ascending)\n";
    cout << "3. Registration Time (Newest First)\n";
    cout << "0. Cancel\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice)
    {
    case 1:
        sortByName();
        cout << "✅ Sorted by Name.\n";
        break;
    case 2:
        sortByID();
        cout << "✅ Sorted by ID.\n";
        break;
    case 3:
        sortByRegistrationTime();
        cout << "✅ Sorted by Time.\n";
        break;
    case 0:
        return;
    default:
        cout << "Invalid choice.\n";
        return;
    }

    saveParticipantsToFile();
    cout << "Press Enter to continue...";
    cin.get();
}

// Feature 4: Attendance Dashboard
void SystemManager::attendanceDashboard()
{
    cout << "\n--- [Feature 4] Attendance Dashboard ---\n";
    cout << "\n========================================" << endl;
    cout << "       EVENT ATTENDANCE DASHBOARD       " << endl;
    cout << "========================================" << endl;

    int totalRegistered = 0;
    int totalCheckedIn = 0;
    int totalNotCheckedIn = 0;

    // Use Linked List Traversal
    Participant *curr = participantHead;

    while (curr != NULL)
    {
        totalRegistered++;

        if (curr->isCheckedIn())
        {
            totalCheckedIn++;
        }
        else
        {
            totalNotCheckedIn++;
        }

        curr = curr->getNext();
    }

    // Calculate percentage
    double attendancePercent = 0.0;
    if (totalRegistered > 0)
    {
        attendancePercent = ((double)totalCheckedIn / totalRegistered) * 100.0;
    }

    cout << left << setw(25) << "Total Registered:" << totalRegistered << endl;
    cout << left << setw(25) << "Total Checked-In:" << totalCheckedIn << endl;
    cout << left << setw(25) << "Total Not Checked-In:" << totalNotCheckedIn << endl;
    cout << "----------------------------------------" << endl;
    cout << fixed << setprecision(2); // Set decimal precision for percentage
    cout << left << setw(25) << "Attendance Percentage:" << attendancePercent << "%" << endl;
    cout << "========================================" << endl;

    cout << "\nPress Enter to continue...";
    cin.get();
}

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

        Event *eventObj = searchEventByID(eventID);
        if (eventObj != NULL)
        {
            int maxCap = eventObj->getCapacity();
            int currentCount = 0;

            Participant *scanner = participantHead;
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
    Participant *checkedInList[1000];
    Participant *notCheckedInList[1000];
    int ciCount = 0;  // number of checked-in participants
    int nciCount = 0; // number of not checked-in participants

    // TRANVERSING participant list, filtering checked-in and not checked-in
    Participant *curr = participantHead; // start from head
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
                Participant *temp = checkedInList[j];
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
                Participant *temp = notCheckedInList[j];
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

// Feature 8: Capacity Monitor
void SystemManager::checkCapacityAlert(string eventID)
{
    cout << "\n--- [Feature 8] Capacity Monitor for Event: " << eventID << " ---\n";

    // 1. Find the Event to get Max Capacity
    Event *eventObj = searchEventByID(eventID);
    if (eventObj == NULL)
    {
        cout << "❌ Error: Event not found.\n";
        return;
    }

    int maxCapacity = eventObj->getCapacity();
    string eventName = eventObj->getEventName();

    // 2. Count Current Check-Ins for this specific event using Linked List
    int currentCheckIns = 0;
    Participant *curr = participantHead;

    while (curr != NULL)
    {
        // Only count if they are in THIS event AND checked in
        if (curr->getEventID() == eventID && curr->isCheckedIn())
        {
            currentCheckIns++;
        }
        curr = curr->getNext();
    }

    // 3. Display Status
    cout << "Event: " << eventName << endl;
    cout << "Status: " << currentCheckIns << " / " << maxCapacity << " Checked In.\n";
    cout << "----------------------------------------\n";

    // 4. Alert Logic
    double percentage = 0.0;
    if (maxCapacity > 0)
    {
        percentage = ((double)currentCheckIns / maxCapacity) * 100.0;
    }

    if (currentCheckIns >= maxCapacity)
    {
        cout << "🔴 CRITICAL ALERT: EVENT FULL!\n";
        cout << "   No further check-ins will be allowed.\n";
    }
    else if (percentage >= 90.0)
    {
        cout << "⚠️  WARNING: Near Capacity (" << percentage << "%)\n";
    }
    else
    {
        cout << "🟢 Status Normal. Capacity available.\n";
    }

    cout << "\nPress Enter to continue...";
    cin.get();
}

void SystemManager::createEvent()
{
    if (eventCount >= 100)
    {
        cout << "❌ Error: Event limit reached.\n";
        return;
    }

    string id, name, date, time, venue;
    int capacity;

    cout << "\n--- [Feature 7] Create New Event ---\n";

    while (true)
    {
        cout << "Enter new Event ID (e.g., E001): ";
        getline(cin, id);

        if (id.empty())
        {
            cout << "❌ ID cannot be empty.\n";
            continue;
        }

        if (searchEventByID(id) == NULL)
        {
            break;
        }
        cout << "❌ Error: Event ID '" << id << "' already exists. Try again.\n";
    }

    do
    {
        cout << "Enter Event Name: ";
        getline(cin, name);
    } while (name.empty() && cout << "❌ Name cannot be empty.\n");

    cout << "Enter Date (DD/MM/YYYY): ";
    getline(cin, date);

    cout << "Enter Time (HH:MM AM/PM): ";
    getline(cin, time);

    cout << "Enter Venue: ";
    getline(cin, venue);

    while (true)
    {
        cout << "Enter Max Capacity: ";
        if (cin >> capacity && capacity > 0)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        else
        {
            cout << "❌ Invalid capacity. Must be > 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    Event *newEvent = new Event(id, name, date, time, venue, capacity);

    if (eventHead == NULL)
    {
        eventHead = newEvent;
    }
    else
    {
        Event *curr = eventHead;
        while (curr->getNext() != NULL)
        {
            curr = curr->getNext();
        }
        curr->setNext(newEvent);
    }

    eventCount++;
    cout << "\n✅ Event '" << name << "' created successfully!\n";

    saveEventsToFile();
}

void SystemManager::deleteParticipant()
{
    cout << "\n--- Delete Participant ---\n";
    string id;
    cout << "Enter Participant ID to delete: ";
    getline(cin, id);

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

    // ✅ store eventID before delete
    string eventID = curr->getEventID();

    if (prev == NULL)
        participantHead = curr->getNext();
    else
        prev->setNext(curr->getNext());

    cout << "🗑️ Deleted Participant: " << curr->getName() << endl;
    delete curr;
    participantCount--;

    saveParticipantsToFile();

    // ✅ NEW: promote from waiting list if any
    promoteFromWaitingList(eventID);

    cout << "Press Enter to continue...";
    cin.get();
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
// 1. Insertion Sort - Sorting by Name
void SystemManager::sortByName()
{
    if (participantHead == NULL || participantHead->getNext() == NULL)
    {
        return;
    }

    Participant *sortedHead = NULL;
    Participant *curr = participantHead;

    while (curr != NULL)
    {
        Participant *nextNode = curr->getNext();

        if (sortedHead == NULL || curr->getName() < sortedHead->getName())
        {
            curr->setNext(sortedHead);
            sortedHead = curr;
        }
        else
        {
            Participant *temp = sortedHead;
            while (temp->getNext() != NULL && temp->getNext()->getName() < curr->getName())
            {
                temp = temp->getNext();
            }
            curr->setNext(temp->getNext());
            temp->setNext(curr);
        }

        curr = nextNode;
    }

    participantHead = sortedHead;
}

// 2. Selection Sort - Sorting by ID
void SystemManager::sortByID()
{
    if (participantHead == NULL)
        return;

    Participant *curr = participantHead;

    while (curr != NULL)
    {
        Participant *minNode = curr;
        Participant *r = curr->getNext();

        while (r != NULL)
        {
            if (r->getID() < minNode->getID())
            {
                minNode = r;
            }
            r = r->getNext();
        }

        if (minNode != curr)
        {
            curr->swapData(minNode);
        }

        curr = curr->getNext();
    }
}

// 3. Bubble Sort - Sorting by Registration Time
void SystemManager::sortByRegistrationTime()
{
    if (participantHead == NULL)
        return;

    bool swapped;
    Participant *ptr1;
    Participant *lptr = NULL;

    do
    {
        swapped = false;
        ptr1 = participantHead;

        while (ptr1->getNext() != lptr)
        {
            if (ptr1->getRegistrationTime() < ptr1->getNext()->getRegistrationTime())
            {
                ptr1->swapData(ptr1->getNext());
                swapped = true;
            }
            ptr1 = ptr1->getNext();
        }
        lptr = ptr1;
    } while (swapped);
}

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

int SystemManager::countRegisteredByEvent(const std::string &eventID) const
{
    int count = 0;
    Participant *curr = participantHead;
    while (curr != NULL)
    {
        if (curr->getEventID() == eventID)
            count++;
        curr = curr->getNext();
    }
    return count;
}

int SystemManager::countCheckedInByEvent(const std::string &eventID) const
{
    int count = 0;
    Participant *curr = participantHead;
    while (curr != NULL)
    {
        if (curr->getEventID() == eventID && curr->isCheckedIn())
            count++;
        curr = curr->getNext();
    }
    return count;
}

// dequeue registrationQueue -> register participant OR move to waiting list
void SystemManager::processNextRegistration()
{
    if (registrationQueue.isEmpty())
    {
        cout << "\n⚠️ Registration Queue is empty.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    RegistrationRequest req;
    registrationQueue.front(req);
    registrationQueue.dequeue();

    if (!registerParticipantFromRequest(req))
    {
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    cout << "Press Enter to continue...";
    cin.get();
}

bool SystemManager::registerParticipantFromRequest(const RegistrationRequest &req)
{
    Event *ev = searchEventByID(req.eventID);
    if (ev == NULL)
    {
        cout << "\n❌ Event not found. Request discarded.\n";
        return false;
    }

    int maxCap = ev->getCapacity();
    int currentRegistered = countRegisteredByEvent(req.eventID);

    if (currentRegistered >= maxCap)
    {
        waitingListQueue.enqueue(req);
        cout << "\n⛔ Event FULL. Added to Waiting List Queue.\n";
        cout << "Waiting list position: " << waitingListQueue.size() << endl;
        return true;
    }

    // create participant
    string newID = generateParticipantID();

    time_t now = time(0);
    string registrationTime = ctime(&now);
    if (!registrationTime.empty() && registrationTime.back() == '\n')
        registrationTime.pop_back();

    Participant *newParticipant = new Participant(newID, req.name, req.email, req.eventID, registrationTime);
    newParticipant->setNext(participantHead);
    participantHead = newParticipant;
    participantCount++;

    cout << "\n✅ Registration processed (Dequeued).\n";
    displayRegistrationInfo(newParticipant);
    saveParticipantsToFile();
    return true;
}

// dequeue checkInQueue -> check in participant by ID
void SystemManager::processNextCheckIn()
{
    if (checkInQueue.isEmpty())
    {
        cout << "\n⚠️ Check-in Queue is empty.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    CheckInRequest r;
    checkInQueue.front(r);
    checkInQueue.dequeue();

    bool ok = checkInParticipantByID(r.eventID, r.participantID);
    if (!ok)
    {
        cout << "❌ Failed to check in this request.\n";
    }

    cout << "Press Enter to continue...";
    cin.get();
}

bool SystemManager::checkInParticipantByID(const std::string &eventID, const std::string &participantID)
{
    Participant *p = searchParticipantByID(participantID);
    if (p == NULL)
    {
        cout << "❌ Participant not found.\n";
        return false;
    }

    if (p->getEventID() != eventID)
    {
        cout << "❌ Participant not registered for this event.\n";
        return false;
    }

    if (p->isCheckedIn())
    {
        cout << "⚠️ Already checked in at " << p->getCheckInTime() << ".\n";
        return false;
    }

    Event *eventObj = searchEventByID(eventID);
    if (eventObj != NULL)
    {
        int maxCap = eventObj->getCapacity();
        int currentCheckedIn = countCheckedInByEvent(eventID);

        if (currentCheckedIn >= maxCap)
        {
            cout << "⛔ CHECK-IN BLOCKED: EVENT IS FULL.\n";
            return false;
        }
    }

    time_t now = time(0);
    string checkInTime = ctime(&now);
    if (!checkInTime.empty() && checkInTime.back() == '\n')
        checkInTime.pop_back();

    p->setCheckedIn(checkInTime);
    cout << "✅ Checked in: " << p->getName() << " at " << checkInTime << endl;
    saveParticipantsToFile();
    return true;
}

// when slot available, promote next from waiting list
void SystemManager::promoteFromWaitingList(const std::string &eventID)
{
    if (waitingListQueue.isEmpty())
        return;

    RegistrationRequest req;
    waitingListQueue.front(req);

    // Only promote if the HEAD of the queue matches the event
    if (req.eventID != eventID)
    {
        return;
    }

    // Check capacity one last time to be safe
    Event *ev = searchEventByID(eventID);
    int maxCap = ev->getCapacity();
    int currentRegistered = countRegisteredByEvent(eventID);

    if (currentRegistered < maxCap)
    {
        waitingListQueue.dequeue(); // Actually remove them now
        cout << "\n🎉 Slot available! Promoting " << req.name << " from waiting list...\n";

        registerParticipantFromRequest(req);
    }
}

// admin queue processing
void SystemManager::processNextAdminRequest()
{
    if (adminQueue.isEmpty())
    {
        cout << "\n⚠️ Admin Queue is empty.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    AdminRequest r;
    adminQueue.front(r);
    adminQueue.dequeue();

    cout << "\n--- Processing Admin Request: " << r.command << " ---\n";

    if (r.command == "CREATE_EVENT")
        createEvent();
    else if (r.command == "SORT")
        sortParticipantList();
    else if (r.command == "DASHBOARD")
        attendanceDashboard();
    else
        cout << "❌ Unknown admin command.\n";
}
