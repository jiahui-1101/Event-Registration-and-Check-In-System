#include "Participant.h"
#include <iostream>
using namespace std;

Participant::Participant()
{
    id = "";
    name = "";
    email = "";
    eventID = "";
    registrationTime = "";
    checkedIn = false;
    checkInTime = "";
}

Participant::Participant(string i,string n, string e, string evID, string time)
{
    id = i;
    name = n;
    email = e;
    eventID = evID;
    registrationTime = time;
    checkedIn = false;
    checkInTime = "";
}

string Participant::getName() const
{
    return name;
}

string Participant::getEmail() const
{
    return email;
}

string Participant::getID() const
{
    return id;
}

string Participant::getEventID() const
{
    return eventID;
}

string Participant::getRegistrationTime() const
{
    return registrationTime;
}

bool Participant::isCheckedIn() const
{
    return checkedIn;
}

string Participant::getCheckInTime() const
{
    return checkInTime;
}

void Participant::setCheckedIn(string time)
{
    checkedIn = true;
    checkInTime = time;
}

void Participant::setName(string newName)
{
    name = newName;
}

void Participant::setEmail(string newEmail)
{
    email = newEmail;
}

void Participant::setEventID(string newEvent)
{
    eventID = newEvent;
}
