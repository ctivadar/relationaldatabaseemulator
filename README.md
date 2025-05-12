# SillyQL - A Simple Database Management System  

SillyQL is a lightweight database management system that allows users to create, modify, and query tables using a set of simple commands. Below is a guide on how to use the available commands to interact with the database.

---

## **Available Commands**  

### **1. Creating a Table**  
Use the `CREATE` command to define a new table with columns and their data types.  

**Syntax:**  
```
CREATE <table_name> <number_of_columns> <column1_type> <column2_type> ... <columnN_type> <column1_name> <column2_name> ... <columnN_name>
```

**Example:**

```
CREATE table1 3 string string bool emotion person Y/N
```

### **2. Remove Existing table from database**

**Syntax:**
```
Remove <table_name>
```

**Example:**

```
Remove table1
```
