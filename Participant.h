#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <string>

class Participant {
private:
    std::string id;
    std::string name;
    std::string email;
    std::string eventID;
    std::string registrationTime;
    bool checkedIn;
    std::string checkInTime;
    Participant* next;

public:
    Participant();
    Participant(std::string i, std::string n, std::string e, std::string evID, std::string time);

    std::string getName() const;
    std::string getEmail() const;
    std::string getID() const;
    std::string getEventID() const;
    std::string getRegistrationTime() const;
    bool isCheckedIn() const;
    std::string getCheckInTime() const;

    void setCheckedIn(std::string time);
    void setName(std::string newName);
    void setEmail(std::string newEmail);
    void setEventID(std::string newEvent);
    Participant* getNext() const;
    void setNext(Participant* nextNode);
};

#endif