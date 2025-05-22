# UNO! Game – C++ Terminal Edition

## 📋 Overview

This is a terminal-based UNO game built in C++ (Version 3.3) that lets you play against an NPC. It features:

- Full UNO rules (including skip, draw two, draw four, and wild cards)
- Player name input
- Combo tracking and scoring system
- Save and update high scores to a binary file

---

## 🛠️ Requirements

- A C++ compiler (e.g., `g++`)
- A terminal or command prompt
- C++17 or later recommended (for safety with `string` and file handling)

---

## 📁 File Structure

- `main.cpp` — Main program logic
- `Card.h` — Definitions for card colors and types (enums and struct)
- `Player.h` — Player structure and member functions
- `Scores.h` — Score tracking structure
- `scores.dat` — Binary save file (auto-created when needed)

---

## ▶️ How to Compile and Run

### Using g++ (Linux/Mac/WSL/Git Bash):

```bash
g++ main.cpp -o uno
./uno
```

### Using g++ on Windows:

```
g++ main.cpp -o uno.exe
uno.exe
```
