#ifndef EVENT_H
#define EVENT_H
#include <string>

class Event {
private:
    std::string eventID;
    std::string eventName;
    std::string eventDate;
    std::string eventTime;
    std::string venue;
    int capacity;

public:
    Event();
    Event(std::string id, std::string name, std::string date, std::string time, std::string venue, int cap);

    // Getters
    std::string getEventID();
    std::string getEventName();
    std::string getEventDate();
    std::string getEventTime();
    std::string getVenue();
    int getCapacity();
};

#endif