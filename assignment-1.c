#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>  // Include string.h for strcmp
#include "checkPassword.h"  // Include the provided header file

// Function to brute force 3 characters at a time
void brute_force(int start) {
    char guess[4]; // 3 characters + null terminator
    guess[3] = '\0';  // Null-terminate the string

    for (char c1 = 33; c1 <= 126; c1++) {
        for (char c2 = 33; c2 <= 126; c2++) {
            for (char c3 = 33; c3 <= 126; c3++) {
                guess[0] = c1;
                guess[1] = c2;
                guess[2] = c3;

                int result = checkPassword(guess, start);
                if (result == 0) {
                    printf("Process %d with parent %d finds %d-%d: %s\n", getpid(), getppid(), start, start + 2, guess);
                    return;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int fork_flag = 0;

    // Check if the -f flag is provided for forking
    if (argc > 1 && strcmp(argv[1], "-f") == 0) {
        fork_flag = 1;
    }

    if (fork_flag) {
        // Forking enabled
        printf("Process %d cracking the password...\n", getpid());
        pid_t pid1, pid2, pid3, pid4;

        if ((pid1 = fork()) == 0) {
            brute_force(0); // Child 1 checks characters 0-2
            exit(0);
        } 
        if ((pid2 = fork()) == 0) {
            brute_force(3); // Child 2 checks characters 3-5
            exit(0);
        }
        if ((pid3 = fork()) == 0) {
            brute_force(6); // Child 3 checks characters 6-8
            exit(0);
        }
        if ((pid4 = fork()) == 0) {
            brute_force(9); // Child 4 checks characters 9-11
            exit(0);
        }

        // Parent waits for all child processes
        wait(NULL);
        wait(NULL);
        wait(NULL);
        wait(NULL);
    } else {
        // Non-forking case: One process handles everything sequentially
        printf("Process %d cracking the password...\n", getpid());
        brute_force(0);  // Check characters 0-2
        brute_force(3);  // Check characters 3-5
        brute_force(6);  // Check characters 6-8
        brute_force(9);  // Check characters 9-11
    }

    return 0;
}
