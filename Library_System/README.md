# Library Management System — C++

A console-based library management system that handles books and users with full borrow/return tracking.

---

## Features

| Feature | Description |
|---|---|
| Add books | Add new books or restock existing ones by ID |
| Search by prefix | Find books whose names start with a given prefix |
| Borrow a book | Track which user borrowed which book, with quantity check |
| Return a book | Restore book quantity on return |
| Who borrowed? | List all users who currently have a specific book |
| Sort by ID / Name | View the catalog sorted either way |
| Add users | Register users with name and ID |
| Print users / books | View full catalog and user list |

---

## Concepts Used

- Structs with nested vectors (`user` tracks borrowed/returned books)
- Custom comparators for `std::sort`
- Prefix-based search using `string::find`
- Input validation (duplicate users, unavailable books, unregistered users)
- Interactive menu-driven CLI

---

## How to Run

```bash
g++ library.cpp -o library && ./library
```

---

## Example Interaction

```
Library Menu:
1) add_book
2) search_books_by_prefix
...

Enter your menu choice: 1
name: TheGreatGatsby
Id: 101
Quantity: 3
```

---

## What I Learned

- Managing relationships between entities (users ↔ books) without a database
- Building a clean interactive CLI with input validation
- Using STL (vector, sort, find) effectively for real-world logic
