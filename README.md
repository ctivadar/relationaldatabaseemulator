# SillyQL - A Simple Database Management System  

SillyQL is a lightweight database management system that allows users to create, modify, and query tables using a set of simple commands. Below is a guide on how to use the available commands to interact with the database.

---

## **Available Commands**  

### **1. Creating a Table**  
Use the `CREATE` command to define a new table with columns and their data types.  

**Syntax:**  
```
CREATE <tablename> <N> <coltype1> <coltype2> ... <coltypeN> <colname1> <colname2> ... <colnameN>
```

**Example:**

```
CREATE table1 3 string string bool emotion person Y/N
```

### **2. Remove Existing table from database**
Use the `REMOVE` command to delete an existing table.

**Syntax:**
```
REMOVE <tablename>
```

**Example:**

```
REMOVE table1
```

### **3. Inserting Data into a Table**
Use the `INSERT INTO` command to add new rows of data into a table.

**Syntax:**
```
INSERT INTO <tablename> <N> ROWS 
<value11> <value12> ... <value1M> 
<value21> <value22> ... <value2M> 
... 
<valueN1> <valueN2> ... <valueNM>
```

**Example:**

```
INSERT INTO table1 8 ROWS
happy Matt true
stressed Students false
busy Office_Hours true
stressed Students true
stressed Ben true
happy Matt true
happy Jedi true
victorious Jedi true
```

### **4. Printing Table Contents**
Use the `PRINT FROM` command to display all rows in a table.

**Syntax:**
```
PRINT FROM <tablename> <N> <print_colname1> <print_colname2> ... <print_colnameN> {WHERE <colname> <OP> <value> | ALL}
```

**Example:**

```
PRINT FROM table1 2 person emotion WHERE Y/N = true
```
