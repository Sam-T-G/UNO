# UNO! — C++ Terminal Game

A two-player terminal UNO game built across five course phases in C++17. The current phase (Phase 5, CSC/CIS 17C) demonstrates the C++ Standard Template Library: all five container families, explicit iterator usage, and all three algorithm categories.

---

## Versions

| Tag | Branch | What it contains |
|---|---|---|
| v5.0 | main | Containers foundation: `stack`, `queue`, `list`, two `map` variants |
| v5.1 | main | Algorithms: `shuffle`, `count_if`, `list::sort` |
| v5.2 | v5.2 | Active: writeup finalization, additional STL demonstrations |

Earlier milestones (v4.1-v4.3) cover inheritance, polymorphism, templates, and exceptions. Phases 1-3 cover foundational C++ and binary file I/O.

---

## Build

```bash
cd phase_5_CSC-17C_project1
g++ -std=c++17 unoV5.2.cpp NPCPlayer.cpp -o uno
./uno
```

Requires g++ with C++17 support. No external dependencies.

---

## File Structure

```
phase_5_CSC-17C_project1/
    unoV5.2.cpp       Main driver: game loop, STL containers, algorithms
    unoV5.1.cpp       v5.1 snapshot
    unoV5.0.cpp       v5.0 snapshot
    Card.h            Card struct, enums, operator overloads
    Player.h          Abstract base class, copy constructor, friend function
    Player.cpp        Base class method implementations
    NPCPlayer.h/.cpp  Derived NPC class with overridden turn logic
    Scores.h          Template score tracking
    scores.dat        Binary save file (auto-created on first run)
```

---

## STL Containers

| Container | Role | Iterator category |
|---|---|---|
| `list<Card>` | Player hand | Bidirectional |
| `set<Card>` | Legal plays per turn | Bidirectional (const) |
| `map<string, Scores>` | In-memory score lookup | Bidirectional |
| `map<CardClr, int>` | NPC color tally for wild strategy | Bidirectional |
| `stack<Card>` | Discard pile — top is the active card | None (adaptor) |
| `queue<Card>` | Draw deck — front is the next card | None (adaptor) |

---

## STL Algorithms

| Algorithm | Category | Where used |
|---|---|---|
| `shuffle` | Mutating | Deck initialization, seeded with `mt19937` |
| `count_if` | Non-mutating | Playable-card count in the turn status line |
| `list::sort` | Organizational | Hand display; member sort because `std::sort` requires random-access iterators |

---

## Game Rules

Standard two-player UNO. Each player starts with seven cards. On your turn, play a card matching the active card's color or number, or play a Wild. Action cards apply immediately: Skip loses the opponent's turn, Draw Two forces the opponent to draw two, Wild Draw Four does the same while letting you pick the new color. The first player to empty their hand wins the round. Scores carry over across rounds.

---

## Course Context

| Phase | Course | Focus |
|---|---|---|
| 1-2 | CIS5 | Foundational C++: loops, arrays, functions, file I/O |
| 3 | CIS-17A Project 1 | Pointers, structs, binary files |
| 4 | CIS-17A Project 2 | Classes, inheritance, polymorphism, templates, exceptions |
| 5 | CSC/CIS 17C Project 1 | STL containers, iterators, algorithms |
