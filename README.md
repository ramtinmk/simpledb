
# SimpleDB - A Database from Scratch

This project is an implementation of a simple, single-node, disk-based relational database management system (DBMS) in C++. The goal is to understand the internal components of a database, including query parsing, storage management, execution, and transaction control.

## Project Goals

-   Implement a functional subset of the SQL language (CREATE, INSERT, SELECT, DELETE).
-   Build a persistent, disk-based storage engine using a B-Tree data structure.
-   Understand the relationship between the query processor, the execution engine, and the storage manager.
-   Implement a basic client/server model for database interaction.

## High-Level Architecture

The system is broken down into several key components:

1.  **Frontend (Query Processor):**
    *   **Parser:** Converts a raw SQL query string into an Abstract Syntax Tree (AST).
    *   **Semantic Analyzer:** Validates the AST (e.g., checks if tables and columns exist). (Future goal)
    *   **Query Planner:** Converts the AST into an executable plan. (Future goal)

2.  **Execution Engine:**
    *   Interprets the execution plan and performs the requested operations by interacting with the storage engine.

3.  **Backend (Storage Engine):**
    *   **Pager / Buffer Pool Manager:** Manages the movement of data pages between disk and memory. Caches frequently used pages to minimize disk I/O.
    *   **File Manager:** Handles low-level file operations (read/write).
    *   **Data Structures:** Implements the on-disk data structures for storing tables and indexes (e.g., B-Tree).
    *   **Transaction Manager:** Ensures ACID properties via concurrency control and a write-ahead log (WAL).

4.  **Networking Layer:**
    *   A simple TCP server that listens for client connections and processes incoming queries.

---

## Implementation Plan

The project will be developed incrementally through the following milestones.

### Milestone 0: The In-Memory REPL

The simplest possible starting point to get the core logic in place without file I/O or SQL parsing.

-   **Goal:** Create a command-line Read-Eval-Print-Loop (REPL).
-   **Features:**
    -   Implement a simple command parser for `insert {id} {name} {email}` and `select`.
    -   Store data in an in-memory data structure (e.g., `std::vector<Row>`).
    -   No persistence. Data is lost when the program exits.
-   **Outcome:** A working interactive shell that can manage data for a single session. This establishes the basic execution loop.

### Milestone 1: The SQL Parser (Frontend)

This stage replaces the simple command parser with a proper SQL parser.

-   **Goal:** Convert SQL strings into a structured, in-memory representation (AST).
-   **Features:**
    -   **Lexer (Tokenizer):** Breaks the SQL string into a stream of tokens (e.g., `SELECT`, `*`, `FROM`, `users`, `;`).
    -   **Parser:** Consumes the token stream and builds an AST that represents the query's structure.
    -   Support for simple `INSERT` and `SELECT` statements initially.
        -   `INSERT INTO users VALUES (1, 'user1', 'user1@example.com');`
        -   `SELECT * FROM users;`
-   **Implementation:** A handwritten recursive descent parser or using tools like Flex/Bison.
-   **Outcome:** A function that takes a `const char*` SQL query and returns a pointer to the root of an AST, or an error.

### Milestone 2: Persistent Storage Layer (The Pager)

This is the first step in building the storage engine. It abstracts away direct file I/O.

-   **Goal:** Manage reading and writing fixed-size pages from the database file to an in-memory buffer pool.
-   **Components:**
    -   **Page:** A fixed-size block of memory (e.g., 4KB) that mirrors a block on disk.
    -   **Pager:** Responsible for requesting pages. If a page is in the buffer pool (cache), it's returned immediately. If not, the Pager reads it from disk, evicting another page if the buffer is full (using an eviction policy like LRU).
    -   **Buffer Pool Manager:** Manages the array of in-memory pages.
-   **Outcome:** A class/module that provides `getPage(page_id)` and `flushPage(page_id)` functions, hiding the complexity of disk I/O and caching.

### Milestone 3: On-Disk Data Structure (B-Tree)

This milestone implements the core data structure for storing table data efficiently on top of the Pager.

-   **Goal:** Store rows in a B-Tree to enable efficient lookups, insertions, and scans.
-   **Features:**
    -   **Node Layout:** Define the binary format for B-Tree nodes (internal and leaf) within a page. This includes headers (node type, number of keys) and the data itself (keys, pointers/offsets).
    -   **Serialization/Deserialization:** Write functions to convert between the in-memory representation of a node and its on-disk binary format.
    -   **Core Operations:** Implement `insert`, `search`, and `delete` operations on the B-Tree. These operations will use the Pager to fetch and write nodes.
-   **Outcome:** A B-Tree implementation that can store key-value pairs persistently. The table rows will be serialized as the "value" part of the B-Tree.

### Milestone 4: The Virtual Machine & Execution Engine

This connects the SQL Parser (Milestone 1) to the Storage Engine (Milestone 3).

-   **Goal:** "Compile" the AST into a simple bytecode format and execute it.
-   **Components:**
    -   **Compiler:** A function that traverses the AST and generates a series of simple instructions (opcodes) like `OP_INSERT`, `OP_SELECT`, `OP_HALT`.
    -   **Virtual Machine (VM):** A loop that executes the bytecode. For `OP_INSERT`, it serializes the row and calls the B-Tree's insert function. For `OP_SELECT`, it creates a cursor to iterate over the B-Tree and prints the results.
-   **Outcome:** The REPL can now accept a SQL query, parse it, compile it, execute it, and persist the results to the database file.

### Milestone 5: The System Catalog

A database needs to store metadata about itself (e.g., table schemas).

-   **Goal:** Create a mechanism for storing schema information.
-   **Implementation:**
    -   Create a master table (often called `sqlite_master` or `pg_catalog`) that stores information about other tables.
    -   This master table is itself stored in a B-Tree at a known page number (e.g., page 0).
    -   Implement `CREATE TABLE` statement support. The parser will generate an AST for it, and the execution engine will add a new entry to the master table.
-   **Outcome:** The database is self-describing. It can now handle multiple tables with different schemas.

### Milestone 6: Networking Layer

Convert the single-process REPL into a client-server application.

-   **Goal:** Allow remote clients to connect and execute queries.
-   **Components:**
    -   **Server:** A TCP server that listens on a port. On connection, it spawns a new thread/process to handle the client. It reads SQL queries from the socket, executes them, and writes results back.
    -   **Client:** A simple command-line application that connects to the server, sends queries, and prints the responses.
    -   **Wire Protocol:** A simple protocol for communication (e.g., length-prefixed strings for queries and results).
-   **Outcome:** A decoupled client-server architecture.

### Milestone 7: Transactions & Concurrency (Advanced)

Implement basic ACID properties.

-   **Goal:** Ensure data integrity and enable concurrent operations.
-   **Components:**
    -   **Write-Ahead Log (WAL):** Before modifying a page, log the change to a separate WAL file on disk. This ensures durability in case of a crash. Upon restart, the WAL can be replayed to restore the database to a consistent state.
    -   **Concurrency Control:** Implement a basic locking mechanism (e.g., page-level locking) to prevent race conditions when multiple clients try to access the same data.
-   **Outcome:** A more robust database that can handle crashes and basic concurrent access.

---

## Project Structure

```
/
├── src/
│   ├── main.cpp          # REPL and server entry point
│   ├── frontend/         # Parser, AST definitions
│   ├── vm/               # Virtual machine and bytecode
│   └── backend/          # Pager, B-Tree, transaction manager
├── include/
│   └── ...               # Header files
├── tests/
│   └── ...               # Unit tests
├── build/
└── CMakeLists.txt
```

## Build & Run

The project will use CMake for build management.

```bash
# Clone the repository
git clone <your-repo-url>
cd <repo-name>

# Configure and build
mkdir build
cd build
cmake ..
make

# Run the database REPL
./bin/simpledb
```