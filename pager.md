To move from memory to disk, you need to abandon the idea of `std::vector<Row>`. You cannot dump a C++ vector directly to a file because it contains pointers and dynamic memory.

You need to build a **Paging System**.

Here is the roadmap for implementing Disk I/O.

### **Step 1: Serialization (The Protocol)**
Before you touch a file, you must be able to convert your `Row` object into a flat, continuous block of bytes (and back again).

*   **Current State:** Your `Row` is a list of objects scattered in heap memory.
*   **Goal:** Create a `serialize_row(Row, buffer)` function.
*   **The Challenge:** Since you chose **Variable Length Strings**, you can't just copy bytes. You need a format.
    *   *Example Format:* `[Total Length] [Col1 Type] [Col1 Length] [Col1 Data] [Col2 Type] ...`
*   **Outcome:** A unit test where you create a Row, serialize it to a byte array, discard the Row, deserialize the byte array, and get the exact same Row back.

### **Step 2: The Pager (The File Manager)**
You need a component that talks to the Operating System's file system.

*   **Create File:** `include/pager.h` / `src/backend/pager.cpp`
*   **Key Concept:** Databases split files into fixed-size blocks called **Pages** (standard is 4KB = 4096 bytes).
*   **Responsibilities:**
    *   **Open:** Open the database file (create it if it doesn't exist).
    *   **Get Page:** `get_page(page_number)` -> Returns a pointer to a 4KB block of memory.
    *   **Flush:** `flush(page_number)` -> Writes that 4KB block back to the disk.
    *   **Close:** Close the file descriptor.

### **Step 3: The Cursor (The Navigator)**
The VM (Virtual Machine) should no longer access the `Table` directly. It should use a **Cursor**.

*   **Why?** In a `vector`, `rows[i]` is fast. On disk, finding "Row 50" is hard. You need an object that points to a specific location (Page Number + Offset inside the page).
*   **Functionality:**
    *   `cursor_start()`: Point to the beginning of the file.
    *   `cursor_advance()`: Move to the next row (handling jumping from the end of Page 1 to the start of Page 2).

### **Step 4: Integrate into Table**
Finally, you rewrite `include/table.h`.

*   **Remove:** `std::vector<Row> rows`.
*   **Add:** `Pager* pager`.
*   **Logic Change:**
    *   When inserting: Ask Pager for the current page. Serialize the row into that page's memory buffer.
    *   When selecting: Use the Cursor to read bytes from the page buffer and Deserialize them back into a `Row` object to print.

---

### **Where to start?**

Start with **Step 2 (The Pager)**. It is independent of your Row implementation.

**Instructions for `include/pager.h`:**
1.  Define a constant `PAGE_SIZE = 4096`.
2.  Create a class `Pager`.
3.  Member: `std::fstream` (or a file descriptor `int` if using Linux system calls).
4.  Member: `uint32_t file_length`.
5.  Method: `get_page(uint32_t page_num)` which returns a `void*` or `char*`.

Do not worry about caching (Buffer Pool) yet. Just make `get_page` read from disk every time for now.