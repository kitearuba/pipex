---

# 🛠️ **Pipex - Unix Pipe Handling in C** 🛠️

![Pipex](https://img.shields.io/badge/Pipex-Project-blue?style=flat-square) ![C Programming](https://img.shields.io/badge/Language-C-green?style=flat-square) ![Makefile](https://img.shields.io/badge/Build-Makefile-yellow?style=flat-square) ![42 Network](https://img.shields.io/badge/42Network-Pipex-lightblue?style=flat-square)

Welcome to **Pipex**, a foundational project in the **42 School** curriculum designed to deepen understanding of **Unix** pipe mechanics, process creation, and inter-process communication through the use of **C programming**. This implementation adheres strictly to the **42 Norm** and project specifications, featuring modular code, centralized error handling, and a clean structure to ensure maintainability.

---

## 📑 **Table of Contents**

1. [Introduction](#introduction)
2. [Project Structure](#project-structure)
3. [Key Features](#key-features)
4. [Technologies Used](#technologies-used)
5. [Installation](#installation)
6. [Usage](#usage)
7. [Error Handling and Exit Codes](#error-handling-and-exit-codes)
8. [Contributing](#contributing)
9. [Acknowledgements](#acknowledgements)
10. [Author](#author)

---

## 📖 **Introduction**

**Pipex** emulates Unix shell behavior for piping commands, allowing you to execute:

```bash
< infile cmd1 | cmd2 > outfile
```

The program demonstrates:
- **Process management** using `fork`.
- **Pipe redirection** with `dup2`.
- **File I/O operations** with `open`, `close`, and system calls.
- Handling complex edge cases (e.g., missing files, invalid commands).

This project lays a strong foundation for more advanced projects like **Minishell** and **Philosophers**.

---

## 📂 **Project Structure**

```bash
.
├── include/           # Header files
│   └── pipex.h        # Centralized function declarations and macros
├── libft/             # Enhanced Libft with additional utilities
│   ├── include/       # Header files for libft
│   └── src/           # Source files for libft
├── src/               # Pipex implementation files
│   ├── cmd/           # Command execution logic
│   ├── core/          # Core application logic
│   ├── error/         # Centralized error handling
│   ├── file/          # File and pipe management
│   └── utils/         # Utility functions for memory/resource cleanup
├── Makefile           # Automates compilation
└── README.md          # Documentation (this file)
```

---

## 🔑 **Key Features**

### **Modular Codebase**
- Functions grouped by responsibilities for better organization and reusability:
  - **cmd/**: Command path resolution and execution (`exec_cmd`, `get_cmd_path`).
  - **core/**: Application entry point (`pipex.c`).
  - **error/**: Unified error handling (`free_resources_on_error`).
  - **file/**: File and pipe operations (`open_files`, `create_pipe`).
  - **utils/**: Resource cleanup utilities (`free_2d_array`, `free_pipex`).

### **Centralized Error Handling**
- Errors are processed through a single entry point, ensuring proper cleanup and detailed error messages. Exit codes conform to Unix standards:
  - `127`: Command not found.
  - `126`: Permission denied.
  - `1`: Generic error.

### **Comprehensive Comments**
- Documentation for each function following 42 Norm, making the project beginner-friendly and easy to extend.

---

## 🛠️ **Technologies Used**

- **C Programming**: Core implementation.
- **Libft Library**: Extended functionality with `ft_printf` and utilities.
- **Makefile**: For efficient compilation.
- **GCC Compiler**: Compilation with strict warnings and memory debugging enabled.

---

## 🚀 **Installation**

### **Step 1: Clone the Repository**
```bash
git clone https://github.com/kitearuba/pipex.git
```

### **Step 2: Navigate to the Project Directory**
```bash
cd pipex
```

### **Step 3: Compile the Project**
Run:
```bash
make
```

---

## 💡 **Usage**

### **Basic Example**
To emulate:
```bash
< infile cmd1 | cmd2 > outfile
```

Run:
```bash
./pipex infile "cmd1" "cmd2" outfile
```

---

## 🛑 **Error Handling and Exit Codes**

### **Exit Codes**
- `127`: Command not found or invalid path.
- `126`: Permission denied for the command.
- `1`: Other errors (e.g., failed file open).

### **Examples**
1. **Missing Input File**:
   ```bash
   ./pipex nonexistent.txt "ls" "wc" output.txt
   ```
   Output:
   ```bash
   pipex: Unable to open input file: No such file or directory
   ```

2. **Invalid Command**:
   ```bash
   ./pipex infile "invalidcmd" "wc" outfile
   ```
   Output:
   ```bash
   pipex: invalidcmd: command not found
   ```

---

## 🤝 **Contributing**

Suggestions and improvements are always welcome! Feel free to fork the repository and submit a pull request.

---

## 🙌 **Acknowledgements**

Special thanks to the **42 Network** community for providing a collaborative learning environment and valuable feedback.

---

## 👨‍💻 **Author**

- **chrrodri**  
  [GitHub Profile](https://github.com/kitearuba)

---
