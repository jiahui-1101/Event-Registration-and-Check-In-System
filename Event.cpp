#include "Event.h"
using namespace std;

Event::Event() {
    eventID = "";
    eventName = "";
    eventDate = "";
    eventTime = "";
    venue = "";
    capacity = 0;
}

Event::Event(string id, string name, string date, string time, string v, int cap)
{
    eventID = id;
    eventName = name;
    eventDate = date;
    eventTime = time;
    venue = v;
    capacity = cap;
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
