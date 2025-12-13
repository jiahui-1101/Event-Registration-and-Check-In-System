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
    Event* next;

public:
    Event();
    Event(std::string id, std::string name, std::string date, std::string time, std::string venue, int cap);

    std::string getEventID() const;
    std::string getEventName() const;
    std::string getEventDate() const;
    std::string getEventTime() const;
    std::string getVenue() const;
    int getCapacity() const;
    Event* getNext() const;
    void setNext(Event* nextNode);
};

#endif