#include "EventOrganizer.h"

EventOrganizer::EventOrganizer() {
    organizerID = "";
    password = "";
    eventID = "";
}

EventOrganizer::EventOrganizer(std::string orgID, std::string pw, std::string evID) {
    organizerID = orgID;
    password = pw;
    eventID = evID;
}

std::string EventOrganizer::getOrganizerID() const {
    return organizerID;
}
std::string EventOrganizer::getPassword() const {
    return password;
}
std::string EventOrganizer::getEventID() const {
    return eventID;
}

void EventOrganizer::setPassword(std::string newPw) {
    password = newPw;
}
void EventOrganizer::setEventID(std::string newEventID) {
    eventID = newEventID;
}
