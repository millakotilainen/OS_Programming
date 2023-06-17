#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;

    // If no command-line arguments
    if (argc <= 1)
    {
        printf("my-grep: searchterm [file ...]");
        exit(1);
    }

    if (argc >= 3 && (file = fopen(argv[2], "r")) == NULL)
    {
        printf("my-grep: cannot open file");
        exit(1);
    }

    // If search term given, but no file specified
    if (argc == 2)
    {
        file = stdin;
    }

    while (getline(&line, &len, file) != -1)
    {
        if (strstr(line, argv[1]))
        {
            printf("%s", line);
        }
    }

    free(line);
    fclose(file);

    exit(0);
}