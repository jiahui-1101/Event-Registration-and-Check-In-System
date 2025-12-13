#include "Event.h"
using namespace std;

Event::Event() {
    eventID = "";
    eventName = "";
    eventDate = "";
    eventTime = "";
    venue = "";
    capacity = 0;
    next = NULL;
}

Event::Event(string id, string name, string date, string time, string v, int cap)
{
    eventID = id;
    eventName = name;
    eventDate = date;
    eventTime = time;
    venue = v;
    capacity = cap;
    next = NULL;
}

string Event::getEventID() const {
    return eventID;
}
string Event::getEventName() const {
    return eventName;
}
string Event::getEventDate() const {
    return eventDate;
}
string Event::getEventTime() const {
    return eventTime;
}
string Event::getVenue() const {
    return venue;
}
int Event::getCapacity() const {
    return capacity;
}

Event* Event::getNext() const {
    return next;
}

void Event::setNext(Event* nextNode) {
    next = nextNode;
}