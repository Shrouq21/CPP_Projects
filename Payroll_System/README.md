# Payroll System — C++ OOP

A payroll management system built in C++ that demonstrates core Object-Oriented Programming principles through a real-world HR and billing scenario.

---

## Class Hierarchy

```
payable (abstract interface)
├── Staff_member
│   ├── volunteer
│   └── employee
│       ├── salaried_based
│       │   └── commission_salaried
│       └── hourly_based
└── invoice

inventory
├── food
└── books

payroll
company
```

---

## Key OOP Concepts Used

- **Abstraction** — `payable` interface defines `GetAmountmoney()` as a contract
- **Inheritance** — multi-level hierarchy (employee → salaried_based → commission_salaried)
- **Polymorphism** — `payroll::pay()` processes any `payable*` without knowing its type
- **Encapsulation** — private data with getters/setters throughout
- **Virtual Destructors** — proper cleanup across the inheritance chain

---

## Employee Types

| Type | Payment Calculation |
|---|---|
| `volunteer` | Fixed current payment |
| `salaried_based` | Fixed monthly salary |
| `hourly_based` | Hours worked × hourly rate |
| `commission_salaried` | Monthly salary + (commission × rate) |

---

## Features

- Add different staff types to a unified payroll system
- Process invoices (books, food) alongside employee payments via the same `payable` interface
- Print all staff info and calculate total payments
- Clean memory management with virtual destructors

---

## How to Run

```bash
g++ payroll.cpp -o payroll && ./payroll
```

---

## Example Output

```
Volunteer Payment: 20000
Hourly Employee: 1900
Salaried Employee: 5000
Commission Salaried: 12000
Total Item Price: 300
```

---

## What I Learned

- Designing extensible class hierarchies using abstract interfaces
- Applying polymorphism to process heterogeneous objects uniformly
- Managing object lifetimes with virtual destructors and heap allocation
