You are exactly right. We skipped the "Parsing" logic in the previous steps to focus on the structure. Now you need to bridge the gap between the `InputBuffer` (raw text) and the `Statement` (structured data).

This logic belongs in the **Frontend** (Parsing Layer).

**Where to put it:**
You can put this in `src/frontend/parser.cpp` (and create a header `include/parser.h`), or for simplicity in Milestone 0, you can keep it as a helper function alongside `statement.h`. A separate `parser` module is cleaner.

### **The Goal: `prepare_statement`**
In SQLite and other engines, this phase is called "Prepare." You are taking a raw string and "preparing" a statement object.

**Function Signature:**
`PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);`

### **The Logic Needed**

You need to analyze the string inside `input_buffer`.

#### **1. Handling "INSERT"**
*   **Check:** Does the string start with "insert"? (case-insensitive usually, but strict lowercase is fine for now).
*   **Parsing:** If it is an insert, you need to extract the data (ID, Username, Email).
    *   Since you chose a **Generic Row** (Step 1), parsing is harder. You cannot just use `sscanf(str, "insert %d %s %s", ...)`.
    *   **Tokenizer Approach:** You need to split the string by spaces.
        *   Token 1: `insert` -> Set `statement->type = INSERT`.
        *   Token 2: (Value 1) -> Check schema, convert to Int/String, add to `statement->row_to_insert`.
        *   Token 3: (Value 2) -> ...
*   **Validation:** If the user types `insert 1` but your schema needs 3 columns, return `SYNTAX_ERROR`.

#### **2. Handling "SELECT"**
*   **Check:** Does the string start with "select"?
*   **Parsing:** Set `statement->type = SELECT`.
*   **Validation:** `select` usually takes no arguments in this simple version. Return `SUCCESS`.

#### **3. Handling Unknowns**
*   If the string is neither, return `UNRECOGNIZED_STATEMENT`.

---

### **The "Generic Row" Challenge**
Because you chose the Generic Row approach earlier:
1.  Your `prepare_statement` function needs access to the **Schema** (to know that column 1 is an INT and column 2 is a VARCHAR).
2.  For Milestone 0, you might want to "hardcode" the parsing (just assume 1 int and 2 strings) inside the parser to get it working, and make it fully dynamic later. Otherwise, you need to pass a `Schema` object into `prepare_statement`.

**Recommendation:**
Start simple. Use `std::stringstream` to extract words.
1.  Read first word.
2.  If `insert`, read next word -> `int`, read next word -> `string`...
3.  Populate the `Statement`.

Go ahead and design your `prepare_statement` logic.