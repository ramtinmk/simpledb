

***

# Stage: Schema Implementation & Type Enforcement

**Goal:** Transition the database from a schema-less key-value store to a strongly-typed relational system.

In this stage, we move beyond simple string parsing and introduce metadata management. The system will now be able to define the structure of a table (columns and data types) and validate user input against that structure before execution.

## Key Concepts

### 1. Metadata Management (The Schema)
A new component, `TableSchema`, is introduced to define the "blueprint" of a table. It stores a list of column definitions, where each column has:
*   **Name:** An identifier (e.g., "id", "email").
*   **Type:** A data type constraint (e.g., `INT`, `VARCHAR`).

### 2. Type-Aware Parsing
The parser (specifically the `build_statement` function) is upgraded to be "schema-aware."
*   **Previous Behavior:** It blindly converted tokens into data fields based on their appearance (digits became Ints, quotes became Strings).
*   **New Behavior:** It accepts the `TableSchema` as an input argument. For every token in an `INSERT` statement, it checks the corresponding column definition in the schema.
    *   If the schema expects an `INT`, the parser validates that the token is numeric.
    *   If the schema expects a `VARCHAR`, the parser validates string syntax.
    *   **Outcome:** Use of strict type checking prevents invalid data (e.g., text in an ID field) from ever reaching the storage engine.

### 3. Strongly-Typed Rows
The `Row` class functions as a generic container of `DataField` objects (Variant types). However, the creation of these rows is now strictly controlled by the schema validation logic.

## Technical Implementation Details

*   **`schema.h`**: Defines `ColumnDefinition` and `TableSchema`.
*   **`Table` Class**: Updated to own an instance of `TableSchema`.
*   **`DataField`**: Acts as the atomic unit of storage, capable of serializing itself to raw bytes (`std::vector<uint8_t>`) for future disk persistence.
*   **Statement Builder**: Now performs semantic analysis (type checking) in addition to syntactic analysis (tokenizing).

## Example Workflow

1.  **Define Schema:** `ID (INT)`, `USERNAME (VARCHAR)`.
2.  **Input Query:** `INSERT 1, 'admin'`.
3.  **Validation:**
    *   Token "1" matches Column 0 (`INT`)? -> **Yes**.
    *   Token "'admin'" matches Column 1 (`VARCHAR`)? -> **Yes**.
4.  **Execution:** Row created and inserted.

*If Input was `INSERT 'admin', 1`: Validation fails (Type Mismatch).*