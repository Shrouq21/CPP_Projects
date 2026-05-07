# AskFM Console System (C++ Project)

##  Overview
This project is a console-based AskFM-style system developed in C++. It simulates a simple social Q&A platform where users can register, log in, ask questions, and answer other users' questions.

---

##  Features

- User registration and login system
- Ask questions to other users
- Support for anonymous questions
- Threaded questions (follow-up discussions)
- Answer questions and edit answers
- Edit or delete questions
- Display questions sent to and from a user
- Show unanswered questions
- Search questions and answers using keywords
- List all system users
- File handling for data persistence

---

##  Concepts Used

- Object-Oriented Programming (OOP)
- File Handling (read/write/append/truncate)
- Data Structures (map, vector, string)
- String manipulation and parsing
- Modular design using structs and functions

---

##  Data Storage

The system stores data in text files:
- `users.txt` → stores user information
- `questions.txt` → stores questions and answers

Data is loaded at program start and saved automatically during runtime.

---

##  How It Works

1. The system loads existing users and questions from files.
2. Users can either register or log in.
3. After login, a menu system allows interaction with questions.
4. All changes are saved back to files to maintain persistence.

---

##  Purpose

The goal of this project is to practice advanced C++ concepts, especially:
- File handling
- Data structures
- System design
- Problem decomposition