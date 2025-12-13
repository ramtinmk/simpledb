
### **Step 3: Define the "Language" of your Database**

Now that you can read raw text (e.g., "insert 1 user"), your database needs to understand what that text *means*. You need to define the structure that holds parsed commands.

**Goal:** Create the types that represent a valid SQL statement in your system.

**File to Create:** `include/statement.h`

### **Instructions**

You need to define three specific things in this header file.

#### **1. Define "Preparation Results"**
When the user types a command, your parser will try to understand it. You need an Enum to report if the parsing succeeded or failed.
*   **Action:** Create an `enum class` named `PrepareResult`.
*   **Values:**
    *   `SUCCESS`: The command was parsed correctly.
    *   `UNRECOGNIZED_STATEMENT`: The command didn't start with `insert` or `select`.
    *   `SYNTAX_ERROR`: The command started correctly but had bad arguments (e.g., `insert` with no ID).

#### **2. Define "Statement Types"**
Your Execution Engine (Step 4) needs to know *what* to do. It shouldn't look at strings; it should look at a simple label.
*   **Action:** Create an `enum class` named `StatementType`.
*   **Values:**
    *   `INSERT`
    *   `SELECT`

#### **3. Define the "Statement" Object**
This is the most important part. This struct acts as the package that is passed from the **Parser** to the **Virtual Machine**.
*   **Action:** Create a `struct Statement`.
*   **Members:**
    1.  `type`: A variable of type `StatementType`.
    2.  `row_to_insert`: An instance of your `Row` class (from `row.h`).
        *   *Note:* This is only used if the type is `INSERT`. If the type is `SELECT`, this field is ignored.

### **Dependencies**
Because `struct Statement` contains a `Row`, you must include your row header at the top of this file:
`#include "row.h"`

### **Why this step matters**
You are creating a contract.
*   The **Frontend** promises to fill out this `Statement` struct.
*   The **Backend** promises to execute whatever is in this `Statement` struct.
*   By separating them, you can change how you store data later without breaking the parser.

**Go ahead and write `include/statement.h`.**