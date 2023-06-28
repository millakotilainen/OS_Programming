#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

char error_message[] = "An error has occurred\n";

void executeCommand(char *command)
{
    // Tokenize the command
    char *token = strtok(command, " ");
    if (token == NULL)
    {
        return; // Empty command
    }

    // built-in commands
    if (strcmp(token, "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(token, "cd") == 0)
    {
        token = strtok(NULL, " ");
        if (token == NULL)
        {
            printf("cd: directory argument missing\n");
            write(STDERR_FILENO, error_message, strlen(error_message));
        }
        else
        {
            if (chdir(token) != 0)
            {
                printf("cd: could not change directory.\n");
                write(STDERR_FILENO, error_message, strlen(error_message));
            }
        }
    }
    else if (strcmp(token, "path") == 0)
    {
        // Clear the existing path
        unsetenv("PATH");

        token = strtok(NULL, " ");
        while (token != NULL)
        {
            // Append each path to the evironment var PATH
            setenv("PATH", token, 1);
            // Get the next path
            token = strtok(NULL, " ");
        }
    }
    else
    {
        printf("Command not recognized.\n");
        write(STDERR_FILENO, error_message, strlen(error_message));
        return;
    }
}

void interactiveMode()
{
    char *command = NULL;
    size_t buff_size = 0;

    while (1)
    {
        printf("wish> ");

        ssize_t num_chars = getline(&command, &buff_size, stdin);

        if (num_chars > 0)
        {
            // Remove the newline char from the end
            command[strcspn(command, "\n")] = '\0';

            executeCommand(command);
        }
        else if (num_chars == -1) // End of file
        {
            exit(0);
        }
    }

    free(command);
}

void batchMode(const char *file)
{
    FILE *batchFile = fopen(file, "r");

    if (batchFile == NULL)
    {
        printf("Cannot to open batch file.\n");
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
    }

    char *cmd = NULL;
    size_t buff_s = 0;
    size_t num_chars;

    while ((num_chars = getline(&cmd, &buff_s, batchFile)) != -1)
    {
        cmd[strcspn(cmd, "\n")] = '\0';

        executeCommand(cmd);
    }

    free(cmd);

    fclose(batchFile);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        interactiveMode();
    }
    else if (argc == 2)
    {
        const char *file = argv[1];
        batchMode(file);
    }
    else
    {
        // If more than 1 batch file, or anything else
        printf("Invalid arguments.\nUsage: ./wish [filename] (for batch mode)\n");
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
    }

    return (0);
}
