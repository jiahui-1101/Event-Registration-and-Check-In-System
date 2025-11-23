#ifndef EVENTORGANIZER_H
#define EVENTORGANIZER_H

#include <string>

class EventOrganizer {
private:
    std::string organizerID;
    std::string password;
    std::string eventID;

public:
    EventOrganizer();
    EventOrganizer(std::string orgID, std::string pw, std::string evID);

    std::string getOrganizerID() const;
    std::string getPassword() const;
    std::string getEventID() const;

    void setPassword(std::string newPw);
    void setEventID(std::string newEventID);
};

#endif
