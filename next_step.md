
### The Next Step: Step 2 (The Input Buffer)

Now that you have a way to represent data, you need a way to talk to your database. You need to build the mechanism that accepts commands from the keyboard.

**Goal:** Abstract away `std::cin` so your main loop remains clean.

**Files to create:**
1.  `include/input_buffer.h`
2.  `src/frontend/input_buffer.cpp` (Don't forget to update CMakeLists.txt!)

**Instructions for `InputBuffer` Class:**

1.  **The Container:**
    It needs a member variable (a `std::string`) to hold the raw text line user types in.

2.  **The Method (`read_input`):**
    It needs a public method that performs the actual reading.
    *   This method should use `std::getline` (reading from `std::cin`).
    *   **Logic Check:** It should check if the line is empty. If the buffer size is 0, handle it gracefully (e.g., just return, or read again).

3.  **The Getter:**
    Since the string member variable will be private, you need a method (e.g., `get_buffer()`) that returns the string so other parts of the program (like the Parser) can look at what was typed.

Once you have this, you will be able to type text into your console and have the program capture it.