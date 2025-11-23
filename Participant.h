#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <string>
#include <vector>

class Participant {
private:
    std::string name;
    std::string email;
    std::string id;
    std::string eventID;
    std::string registrationTime;
    bool checkedIn;
    std::string checkInTime;

public:
    Participant();
    Participant(std::string name, std::string email, std::string id, std::string eventID, std::string time);

    // Getters & Setters
    std::string getName();
    std::string getEmail();
    std::string getID();
    std::string getEventID();
    std::string getRegistrationTime();
    bool isCheckedIn();
    std::string getCheckInTime();

    void setCheckedIn(std::string time);
    void setName(std::string newName);
    void setEmail(std::string newEmail);
    void setEventID(std::string newEvent);
};

#endif
