### **Step 5: The Virtual Machine (Execution Engine)**

You have all the building blocks:
*   **Input:** `InputBuffer`
*   **Data:** `Row` and `Table`
*   **Instructions:** `Statement`

Now you need the "Brain" that actually performs the work. In database terminology, this is often called the Execution Engine or the Virtual Machine (VM). It takes a generic `Statement` and applies it to the `Table`.

**File to Create:** `src/vm/virtual_machine.cpp` (and `include/virtual_machine.h` if you want a separate header, though a simple function in the main loop works for Milestone 0. A class is cleaner).

### **Instructions**

You need to implement a function (or class method) that executes a statement.

#### **1. Define Execution Results**
Just like the Parser can fail (Syntax Error), the Execution Engine can also fail (e.g., "Table Full" or "Duplicate Key").
*   **Action:** Create an `enum class` named `ExecuteResult`.
*   **Values:**
    *   `SUCCESS`
    *   `TABLE_FULL` (You won't hit this with `std::vector`, but it's good practice for later).

#### **2. The Execute Function**
This is the core logic function.
*   **Name:** `execute_statement`
*   **Arguments:**
    *   `Statement* statement`: The command to run.
    *   `Table* table`: The place to run it on.
*   **Returns:** `ExecuteResult`.

#### **3. The Logic (Switch Statement)**
Inside the function, switch on `statement->type`.

*   **Case INSERT:**
    *   Take the `row_to_insert` from inside the statement object.
    *   Call `table->insert_row(...)` passing that row.
    *   Return `SUCCESS`.

*   **Case SELECT:**
    *   Get the number of rows from the table (`table->size()`).
    *   Create a loop from 0 to that count.
    *   Inside the loop, get the row at that index.
    *   Call the `print()` method of that row (the one you wrote in Step 1).
    *   Return `SUCCESS`.

### **Summary**
The Virtual Machine is very simple right now. It is just a dispatcher.
1.  Check the type of command.
2.  Call the appropriate method on the `Table` object.
3.  Report success.

**Important Note for CMake:**
Since you are adding a new `.cpp` file (`src/vm/virtual_machine.cpp`), do not forget to add it to your `CMakeLists.txt` executable sources, or you will get linker errors!