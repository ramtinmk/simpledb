### **Step 4: The Table (The In-Memory Storage)**

**File to Create:** `include/table.h`

### **Instructions**

You need to create a class that represents the database table.

#### **1. The Container**
The Table needs to store the data.
*   **Action:** Add a private member variable to hold the rows.
*   **Type:** `std::vector<Row>` is perfect for this milestone. It allows you to add as many rows as you want without worrying about memory size yet.

#### **2. The Cursor (Iterator)**
Eventually, you won't just say "give me all rows." You will need to "iterate" over the table (start at the beginning, move to the next, stop at the end).
*   **Action:** You need methods that allow the Execution Engine (VM) to loop through the data.
*   **Simple Approach:** For now, you can just expose the `begin()` and `end()` iterators of your internal vector, or provide a helper method like `get_row(index)`.

#### **3. Persistence (The Placeholder)**
Since the `Table` class will eventually be responsible for saving data to disk:
*   **Concept:** Later, this class will have `open_db_file()` and `flush_to_disk()` methods.
*   **Current Task:** For now, you don't need to write them, but keep in mind that this `Table` class is the **owner** of the data.

### **Summary for `include/table.h`**
1.  Include `"row.h"`.
2.  Define class `Table`.
3.  Give it a `std::vector<Row>` member.
4.  Give it a method `insert_row(Row& row)` to add data.
5.  Give it a method (or iterators) to allow reading the data back.

**Why this order?**
Now you have the **Data** (`Row`), the **Command** (`Statement`), and the **Storage** (`Table`). The only thing missing is the logic to connect them (The Parser and The Virtual Machine).