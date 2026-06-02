# Sparse Matrix — Two Implementations in C++

A sparse matrix is a matrix where most elements are zero. Storing all elements wastes memory, so this project implements an efficient sparse matrix using **Linked Lists** — in two different approaches.

---

## Implementations

### Version 1 — 1D Array-Based Linked List (`sparse_1d`)
- Represents each row as a **doubly linked list** of fixed size
- Every node stores a value; zeros are stored explicitly but handled efficiently
- Supports: `set_value`, `get_value`, `print`, `print_nonzero`, `add`

### Version 2 — True Sparse Linked List (`sparse_2d`)
- Represents the matrix as a **linked list of rows**, each row is a **linked list of columns**
- Only **non-zero elements** are stored as nodes — fully memory efficient
- Uses sentinel/dummy head nodes for cleaner insertion logic
- Supports: `SetValue`, `GetValue`, `print_matrix`, `print_matrix_nonzero`, `Add`

---

## Key Concepts Used

- Doubly Linked Lists (custom implementation)
- 2D sparse representation with row/column chaining
- Sentinel nodes for edge case handling
- Matrix addition with structural merging
- OOP design: separated `ColumnList`, `RowNode`, `SparseMatrix` classes

---

## Features

| Feature | Version 1 | Version 2 |
|---|---|---|
| Set value at (row, col) | ✅ | ✅ |
| Get value at (row, col) | ✅ | ✅ |
| Print full matrix | ✅ | ✅ |
| Print non-zero elements only | ✅ | ✅ |
| Add two sparse matrices | ✅ | ✅ |
| Memory: stores only non-zeros | ❌ | ✅ |

---

## How to Run

```bash
g++ sparse_1d.cpp -o sparse_1d && ./sparse_1d
g++ sparse_2d.cpp -o sparse_2d && ./sparse_2d
```

---

## Example

```cpp
SparseMatrix mat(10, 10);
mat.SetValue(5, 3, 5);   // row 3, col 5 = 5
mat.SetValue(7, 3, 7);   // row 3, col 7 = 7
mat.print_matrix_nonzero();

// Matrix 10 X 10
// 5 7 2
```

---

## What I Learned

- How to design memory-efficient data structures from scratch
- Trade-offs between simplicity (V1) and true sparsity (V2)
- Linked list manipulation: insertion, traversal, merging
