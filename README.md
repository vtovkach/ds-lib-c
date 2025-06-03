# C Data Structures Library 
A lightweight, modular C library implementing essential data structures like vectors, linked lists, stacks, queues, graphs, heaps, and hash tables, designed for efficiency and ease of integration into any C project.

## Features

- Written in pure C (C99)
- Modular architecture with separate header/source files
- Unit tested components
- MIT licensed

## Available Data Structures

Each data structure is documented in its own Markdown file:

- [Doubly Linked List](docs/Doubly-Linked-List.md)
- [Singly Linked List](docs/Singly-Linked-List.md)
- [Dynamic Array (Vector)](docs/Dynamic-Array.md)
- [Stack](docs/Stack.md)
- [Queue](docs/Queue.md)
- [Binary Search Tree](docs/Binary-Search-Tree.md)
- [Hash Table](docs/Hash-Table.md)
- [Heap](docs/Heap.md)

## Repository Structure

```text
ds-lib-c/
├── docs/           # Documentation files
├── include/        # Public headers
├── src/            # Source code
├── tests/          # Unit tests
├── Makefile        # Build automation
└── README.md       # Library overview 

'''

## Library Structure

```
ds-lib-c/
├── include/         # Public headers (e.g., ds_vector.h, ds_stack.h, etc.)
├── src/             # Implementation files (.c)
├── LICENSE          # MIT license
├── Makefile         # Build script
```

---

## Download & Extract

1. Navigate to the [Releases]([https://github.com/your-username/ds-lib-c/releases](https://github.com/vtovkach/ds-lib-c/releases/tag/v0.1.0))
2. Download the release archive:
   ```
   linux-release-1.0.0.tar.gz
   ```
3. Extract it in your terminal:
   ```bash
   tar -xzf linux-release-1.0.0.tar.gz
   cd ds-lib-c
   ```

---

## Build the Library

Compile the static library using `make`:

```bash
make
```

This will create the following directory:

```
lib/
└── libds_lib.a      # Static library for linking
```

---

## Linking with Your Program

Compile your C program using `gcc` and link it with `ds-lib-c`:

```bash
gcc -o my_program your_project.c -L./lib -lds_lib -I./include
```

Explanation:
- `-L./lib` — specifies the path to the static library
- `-lds_lib` — links the `libds_lib.a` file
- `-I./include` — points to the directory containing all header files

---

## Usage

In your your project file, simply include the master header:

```c
#include "ds_lib.h"
```

This exposes all core data structures:
- Vector
- Stack
- Queue
- Singly Linked List
- Doubly Linked List
- Heap (min/max)
- AVL Tree
- Hash Table (separate chaining)

---

## License

This project is licensed under the MIT License.  
See the `LICENSE` file for details.
