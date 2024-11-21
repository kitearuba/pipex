---

# 🛠️ **Pipex - Pipe Redirection in C** 🛠️

![Pipex](https://img.shields.io/badge/Pipex-Project-blue?style=flat-square) ![C Programming](https://img.shields.io/badge/Language-C-green?style=flat-square) ![Makefile](https://img.shields.io/badge/Build-Makefile-yellow?style=flat-square) ![42 Network](https://img.shields.io/badge/42Network-Pipex-lightblue?style=flat-square)

Welcome to **Pipex**, a project that focuses on handling pipes and executing commands in a **Unix** environment using **C programming**. This project is part of the **42 Network** curriculum and provides a deeper understanding of process creation, pipe redirection, and command execution.

This version includes the **enhanced Libft** with `ft_printf` and `get_next_line`, giving you access to a robust set of utilities while managing standard and custom I/O operations.

---

## 📑 **Table of Contents**

1. [Introduction](#introduction)
2. [Project Structure](#project-structure)
3. [Changes in This Version](#changes-in-this-version)
4. [Technologies Used](#technologies-used)
5. [Installation](#installation)
6. [Usage](#usage)
7. [Pipex Functionality](#pipex-functionality)
8. [Contributing](#contributing)
9. [Acknowledgements](#acknowledgements)
10. [Author](#author)

---

## 📖 **Introduction**

**Pipex** is a project designed to implement a basic program capable of emulating the behavior of Unix shell pipes (`|`). The project handles file input/output redirection while piping the output of one command to the input of another, much like:

```bash
< file1 cmd1 | cmd2 > file2
```

With **Pipex**, you will gain a solid understanding of how to create and manage processes, handle pipe communication between commands, and manage file descriptors in **C**.

---

## 📂 **Project Structure**

```bash
.
├── include/           # Header files
│   └── pipex.h        # Header file for pipex project
├── libft/             # Enhanced Libft with ft_printf and get_next_line
│   ├── include/       # Header files for libft
│   └── src/           # Source files for libft
├── src/               # Source files implementing the main functionality
│   ├── cmd/           # Functions related to command handling
│   ├── core/          # Core program logic (e.g., pipex.c)
│   ├── error/         # Error-handling functions
│   ├── file/          # Functions for file and pipe management
│   └── utils/         # Utility functions for memory and resource management
├── Makefile           # Makefile to compile the project
└── README.md          # This README file
```

---

## 🔄 **Changes in This Version**

### **Modular Structure**
- The project has been reorganized to separate concerns and improve maintainability.
- Functions are grouped by their responsibilities:
  - **cmd/**: Command-related operations (e.g., `get_cmd_path`, `handle_fork`).
  - **core/**: Main program logic (`pipex.c`).
  - **error/**: Error-handling functions (`fatal_error`, `free_on_error`).
  - **file/**: File and pipe management (`open_files`, `create_pipe`).
  - **utils/**: Utility functions (`free_2d_array`, `cleanup_and_handle`).

### **Why This Structure?**
- Encourages modularity, making the codebase easier to navigate and extend.
- Simplifies debugging and testing by isolating functionality into smaller files.
- Prepares the project for potential extensions (e.g., **Minishell**).

---

## 🛠️ **Technologies Used**

- **C Language**: Core language for the pipex implementation and libft integration.
- **Makefile**: Automates the build process for both **pipex** and **libft**.
- **GCC Compiler**: Used to compile the source files and create executables.

---

## 🚀 **Installation**

To install and compile the **pipex** project, follow these steps:

1. **Clone the Repository**:
   ```bash
   git clone git@github.com:kitearuba/pipex.git
   ```

2. **Navigate to the Project Directory**:
   ```bash
   cd pipex
   ```

3. **Compile the Project**:
   Use the `make` command to compile the project and generate the executable:
   ```bash
   make
   ```

This will compile both the **pipex** and **libft** parts of the project, resulting in an executable for **pipex**.

---

## 💡 **Usage**

Once compiled, you can use **pipex** to mimic pipe redirections between commands.

### **Basic Example**:
To execute the equivalent of:
```bash
< file1 cmd1 | cmd2 > file2
```

You would run:
```bash
./pipex file1 "cmd1" "cmd2" file2
```

---

## 🔨 **Pipex Functionality**

### 🔄 **Pipex Workflow**

**Pipex** reads from an input file, executes the first command (`cmd1`), pipes its output as the input to the second command (`cmd2`), and finally writes the output of `cmd2` to an output file.

### 🛑 **Error Handling**

The program includes comprehensive error handling for scenarios such as:
- **Invalid file paths**.
- **Command not found**.
- **Insufficient permissions**.
- **Pipe creation failures**.

All errors are reported through a centralized `fatal_error` function for consistency.

---

## 🤝 **Contributing**

Contributions are welcome! Feel free to open issues or submit pull requests for bug fixes, improvements, or new features.

---

## 🙌 **Acknowledgements**

A special thanks to the **42 Network** and the open-source community for their continuous support and for providing the resources to learn and improve.

---

## 👨‍💻 **Author**

- **chrrodri**  
  [GitHub Profile](https://github.com/kitearuba)

---
