# C++ Contact Management System

A console-based contact management system built in C++ using object-oriented programming principles. It supports storing, searching, grouping, and tracking contacts with persistent file I/O and search history.

---

## Features

- **Contact Management** — Add, view, update, delete, and search contacts with full details (name, phone, email, address).
- **Smart Search** — Substring/character-level search across all contact fields with automatic history logging.
- **Groups** — Organize contacts into named groups; add or remove members per group.
- **Sorting** — Sort and display contacts by first name or last name using Bubble Sort.
- **Duplicate Detection** — Detect and merge duplicate contacts automatically.
- **View Tracking** — Tracks how many times each contact has been viewed; surfaces the top 5 most-viewed contacts.
- **Search History** — Logs all searches with timestamps, displayed in reverse-chronological order.
- **File Persistence** — Load contacts from an input file; save contacts, groups, search history, and top-5 to output files automatically on exit.
- **Dynamic Resizing** — The contacts array and internal `List<T>` template grow automatically when full.

---

## Project Structure

```
ContactsBook/
├── Main.cpp               # Entry point & interactive menu loop
├── ContactsBook.h/.cpp    # Core manager class
├── Contact.h/.cpp         # Contact model
├── Address.h/.cpp         # Address model
├── Group.h/.cpp           # Group model (stores contact IDs)
├── HistoryObject.h/.cpp   # Search history record with timestamp
├── List.h/.cpp            # Generic dynamic array template
│
├── contacts_input.txt     # Input file for bulk contact loading
├── contacts_output.txt    # Saved contacts (written on exit)
├── groups_output.txt      # Saved groups (written on exit)
├── search_history.txt     # Saved search history (written on exit)
└── frequently_searched.txt# Top 5 most-viewed contacts
```

---

## Class Overview

| Class | Responsibility |
|---|---|
| `Address` | Stores house, street, city, country. Supports equality check and copying. |
| `Contact` | Stores personal info + a heap-allocated `Address*`. Tracks view count and unique ID. |
| `Group` | Named group storing a `List<int>` of contact IDs. |
| `HistoryObject` | A search string paired with a `time_t` timestamp. |
| `List<T>` | Generic dynamic array with doubling resize strategy. |
| `ContactsBook` | Orchestrates all features: contacts array, groups list, history list, and file I/O. |

---

## Menu Options

| # | Action |
|---|---|
| 1 | Create Contacts List (set size + auto-load from `contacts_input.txt`) |
| 2 | Add New Contact (manual input) |
| 3 | Merge Duplicate Contacts |
| 4 | Save to File |
| 5 | Load from File |
| 6 | Print Contacts Sorted (by `first_name` or `last_name`) |
| 7 | Print All Contacts (then view/update/delete a specific one) |
| 8 | Search Contacts |
| 9 | Display Contact Count |
| 10 | Create a Group |
| 11 | Add a Contact to a Group |
| 12 | Print Groups & Group Contacts |
| 13 | View Groups of a Contact |
| 14 | Delete a Group |
| 15 | View Search History |
| 16 | View Top 5 Most-Viewed Contacts |
| 17 | Exit (auto-saves all data) |

---

## Input File Format (`contacts_input.txt`)

```
<number_of_contacts>
<FirstName> <LastName> <MobileNumber> <EmailAddress>
<House> <Street> <City> <Country>
```

Example:
```
1
Ali Meekal 03XXXXXXXXX alimeekal.work@gmail.com
62 Sitara Faisalabad Pakistan
```

---

## Authors

- Ali Meekal & Rayyan Asim
