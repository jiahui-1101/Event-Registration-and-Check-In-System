# 🎟️ Event Registration and Check-In System (C++)

A **console-based Event Registration and Check-In System** developed in **C++**, applying **Advanced Data Structures and Algorithms** concepts.
This project demonstrates the practical use of **Queues** and **Singly Linked Lists** to manage real-world event workflows efficiently and fairly.

> 📚 Course: Advanced Data Structure & Algorithms (MCSS1023)
> 🏫 Universiti Teknologi Malaysia (UTM)

---

## 📌 Project Overview

Traditional event management systems often rely on manual processes or static spreadsheets, which lead to:

* Long queues and overcrowding
* Unfair queue handling
* Limited storage due to static arrays
* Lack of real-time attendance tracking

This system solves these issues by implementing **dynamic data structures** to simulate real-world event operations such as **registration queues, check-in queues, waiting lists, and admin task queues**.

---

## 🎯 Objectives

* Apply **Queue (FIFO)** for sequential processing (registration, check-in, waiting list, admin requests)
* Use **Singly Linked Lists** for dynamic data storage (participants, events, organizers)
* Implement searching, sorting, and capacity monitoring algorithms
* Build a structured and user-friendly **menu-driven console application**
* Support **data persistence** using text files

---

## 👥 User Roles

### 1️⃣ Participant

* Submit registration requests
* Check registration status
* View queue position
* Join waiting list automatically if event is full

### 2️⃣ Event Organizer

* Manage on-site check-in
* Use a digital check-in queue (FIFO)
* Monitor event capacity
* Delete participants and trigger auto-promotion from waiting list

### 3️⃣ Admin

* Create events
* Sort participant records
* View attendance dashboard
* Manage admin tasks using an Admin Request Queue

---

## 🧠 Data Structures Used

### 🔹 Queue (ADT)

Used to ensure fairness and order:

* Registration Queue
* Check-In Queue
* Waiting List Queue
* Admin Request Queue

Operations:

* `enqueue()`
* `dequeue()`
* `front()`
* `isEmpty()`
* `size()`

### 🔹 Singly Linked List

Used as the main data storage:

* Participants
* Events
* Event Organizers

Supports:

* Dynamic insertion & deletion
* Linear search
* Sorting (Bubble, Selection, Insertion Sort)

---

## ⚙️ Key Features

* ✅ FIFO-based registration and check-in
* ✅ Automatic waiting list promotion
* ✅ Real-time capacity alerts
* ✅ Attendance dashboard with statistics
* ✅ Manual & queued admin task processing
* ✅ Persistent data storage using `.txt` files
* ✅ Robust input validation & error handling

---

## 🗂️ File Structure

```
📁 Event-Registration-System
│
├── main.cpp
├── SystemManager.h / SystemManager.cpp
├── Participant.h / Participant.cpp
├── Event.h / Event.cpp
├── EventOrganizer.h / EventOrganizer.cpp
├── Queue.h
│
├── events.txt
├── participants.txt
├── organizers.txt
│
└── README.md
```

---

## 🧪 Sample Data Files

### `events.txt`

```
E001,Tech Conference 2024,2024-04-15,09:00,Main Auditorium,200
E002,Startup Workshop,2024-04-16,14:00,Room 101,50
```

### `organizers.txt`

```
ORG001,password123,E001
ORG002,pass456,E002
```

---

## ▶️ How to Run

### 1️⃣ Compile

```bash
g++ main.cpp SystemManager.cpp Participant.cpp Event.cpp EventOrganizer.cpp -o event_system
```

### 2️⃣ Run

```bash
./event_system
```

⚠️ Make sure the `.txt` data files are in the **same directory** as the executable.

---

## 🧩 Algorithms Implemented

* **Searching**: Linear Search
* **Sorting**:

  * Insertion Sort (by Name)
  * Selection Sort (by Participant ID)
  * Bubble Sort (by Registration Time)
* **Queue Processing**: FIFO simulation for real-world workflows

---

## 📊 Attendance Dashboard Example

* Total Registered
* Total Checked-In
* Total Not Checked-In
* Attendance Percentage (%)

---

## 🚀 Learning Outcomes

* Practical application of data structures
* Real-world queue simulation
* Dynamic memory management in C++
* Modular and maintainable program design

---

## 📝 License

This project is developed for **academic purposes** as part of coursework at **Universiti Teknologi Malaysia (UTM)**.
