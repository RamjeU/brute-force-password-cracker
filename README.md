# brute-force-password-cracker

## Overview

This project is a brute-force password cracking tool built in C for a course assignment. The password consists of 12 characters and can include any character in the ASCII range from 33 to 126. The task involves discovering the password by brute-forcing three characters at a time using a provided function `checkPassword`.

The project demonstrates:
- Process creation and control in a Linux environment.
- The usage of system calls like `fork()`, `getpid()`, `getppid()`, and `wait()` to manage child processes.
- The performance benefit of parallel processing using forking compared to sequential execution.

## Functionality

The program can either:
1. Run sequentially in a single process and brute-force the entire password one chunk at a time (3 characters at a time).
2. Utilize forking to create four child processes, each responsible for cracking a different portion of the password (characters 0-2, 3-5, 6-8, and 9-11). This speeds up the brute-force process by dividing the workload among the child processes.

### Key Features

- **Brute-Force Strategy:** Checks every possible combination of ASCII characters (from 33 to 126) for a specific portion of the password.
- **Forking with Multiple Processes:** When forking is enabled, four processes are created, each assigned to crack a different part of the password in parallel, allowing for faster completion.
- **Password Length:** The password is exactly 12 characters long.

### Command-Line Arguments

- The program accepts an optional `-f` argument to enable forking.

#### Example Commands:
- Without forking (sequential):
  ```bash
  ./assignment-1
- With forking
  ```bash
  ./assignment-1 -f

