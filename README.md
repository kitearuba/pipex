
---

# 🛠️ **Pipex - Pipe Redirection in C** 🛠️

![Pipex](https://img.shields.io/badge/Pipex-Project-blue?style=flat-square) ![C Programming](https://img.shields.io/badge/Language-C-green?style=flat-square) ![Makefile](https://img.shields.io/badge/Build-Makefile-yellow?style=flat-square) ![42 Network](https://img.shields.io/badge/42Network-Pipex-lightblue?style=flat-square)

Welcome to **Pipex**, a project that focuses on handling pipes and executing commands in a **Unix** environment using **C programming**. This project is part of the **42 Network** curriculum and provides a deeper understanding of process creation, pipe redirection, and command execution.

This version includes the **enhanced Libft** with `ft_printf` and `get_next_line`, giving you access to a robust set of utilities while managing standard and custom I/O operations.

---

## 📑 **Table of Contents**

1. [Introduction](#introduction)
2. [Project Structure](#project-structure)
3. [Technologies Used](#technologies-used)
4. [Installation](#installation)
5. [Usage](#usage)
6. [Pipex Functionality](#pipex-functionality)
   - [Pipex Workflow](#pipex-workflow)
   - [Error Handling](#error-handling)
7. [Contributing](#contributing)
8. [Acknowledgements](#acknowledgements)
9. [Author](#author)

---

## 📖 **Introduction**

**Pipex** is a project designed to implement a basic program capable of emulating the behavior of Unix shell pipes (`|`). The project will handle file input/output redirection while piping the output of one command to the input of another, much like:

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
├── src/               # Source files implementing the main functionality
│   └── pipex.c        # Main source file for pipex
├── libft/             # Enhanced Libft with ft_printf and get_next_line
│   ├── include/       # Header files for libft
│   └── src/           # Source files for libft
├── Makefile           # Makefile to compile the project
└── README.md          # This README file
```

This structure ensures that **pipex** is modular and maintains a clear separation between **pipex-specific code** and **libft** functionalities, allowing for easy management and extensibility.

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

### **Example with `grep` and `wc`**:
```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```
This will:
- Read from `input.txt`.
- Execute `grep hello`.
- Pipe its output to `wc -l`.
- Write the result to `output.txt`.

### **Commands with Multiple Arguments**:
```bash
./pipex input.txt "ls -la" "sort -r" output.txt
```

---

## 🔨 **Pipex Functionality**

### 🔄 **Pipex Workflow**

**Pipex** reads from an input file, executes the first command (`cmd1`), pipes its output as the input to the second command (`cmd2`), and finally writes the output of `cmd2` to an output file.

**Steps Involved**:
1. **File Opening**: Opens the input and output files.
2. **Pipe Creation**: Creates a pipe for the communication between `cmd1` and `cmd2`.
3. **Process Forking**: Forks two child processes:
   - The first child executes `cmd1` and sends output to the pipe.
   - The second child takes input from the pipe and executes `cmd2`.
4. **File Redirection**: Manages input/output redirection for file descriptors.
5. **Error Handling**: Detects and handles errors like file opening, command execution, or pipe failures.

### 🛑 **Error Handling**

The program includes comprehensive error handling for scenarios such as:
- **Invalid file paths**.
- **Command not found**.
- **Insufficient permissions**.
- **Pipe creation failures**.

In case of any error, **pipex** displays an appropriate error message using `perror()` or `ft_printf()` and exits gracefully.

---

## 🤝 **Contributing**

Contributions are welcome! Feel free to open issues or submit pull requests for bug fixes, improvements, or new features.

To contribute:

1. **Fork the Repository**.
2. **Create a Branch** (`git checkout -b feature/NewFeature`).
3. **Commit Your Changes** (`git commit -m 'Add NewFeature'`).
4. **Push to Your Branch** (`git push origin feature/NewFeature`).
5. **Open a Pull Request**.

---

## 🙌 **Acknowledgements**

A special thanks to the **42 Network** and the open-source community for their continuous support and for providing the resources to learn and improve.

---

## 👨‍💻 **Author**

- **chrrodri**  
  [GitHub Profile](https://github.com/kitearuba)

---

## 🎉 **Final Thoughts**

**Pipex** is an excellent project to help you understand **process management**, **pipes**, and **command execution** in a **Unix-based environment**. By integrating the enhanced **Libft**, you get to reuse custom functions like `ft_printf` and `get_next_line`, ensuring that your I/O handling is robust and efficient.

Good luck with the project, and happy coding! 🎉

---

### 🎨 **Enhancements for Visual Appeal**:

- Used icons for each section to make the README visually appealing.
- Included badges to represent key technologies used.
- Used **bold** and **code blocks** to emphasize key terms and commands.

---
