# Event-Registration-and-Check-In-System 

## Objective

To develop a system that allows participants to register and verify for events, and enables admins and organizers to manage events and track attendance efficiently.

**Target Users:**

* **Participants:** Register, verify registration, and check in.
* **Admins:** Create and manage events, sort and view participant data, monitor attendance.
* **Organizers:** Check-in participants, monitor attendance, and enforce capacity limits.

---

## Features

### For Participants

1. **Register for Event**

   * Enter details to register.
   * System prevents duplicate registrations using linear search.

2. **Check Registration Status**

   * Search by Email or ID to see registration details (Name, Event, Registration Time, Status).

---

### For Admins

3. **Manage Participants**

   * View participant list.
   * Sort by Name, Registration Time, or Participant ID using sorting algorithms.

4. **Dashboard Summary**

   * See total registered, checked-in, and not checked-in participants, and attendance percentage.

5. **Event Management**

   * Create and store new events with details (Name, Date, Time, Venue, Capacity, Event ID).

---

### For Event Organizers

6. **Check-In Participants**

   * Search by Name or ID and check-in participants.
   * Ensures participant exists and has not checked in already.
   * Records check-in timestamp.

7. **View Checked-In & Not Checked-In Lists**

   * Separate lists for quick attendance tracking.
   * Lists can be sorted alphabetically.

8. **Capacity Alert System**

   * Blocks check-ins when the event reaches maximum capacity.
   * Alerts organizer to prevent overcrowding.

---
just simple explanation version

