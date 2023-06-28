#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *file;

    if (argc <= 1)
    {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++)
    {
        if ((file = fopen(argv[i], "r")) == NULL)
        {
            printf("cannot open file\n");
            exit(1);
        }

        int count = 1;
        char line[256];
        char *prev_line = NULL;

        while (fgets(line, sizeof(line), file) != NULL)
        {
            // removing the newline char
            line[strcspn(line, "\n")] = '\0';

            if (prev_line != NULL && strcmp(prev_line, line) == 0)
            {
                count++;
            }
            else if (prev_line != NULL)
            {
                fwrite(&count, 4, 1, stdout);
                fwrite(prev_line, 1, 1, stdout);
                count = 1;
            }

            free(prev_line);
            prev_line = strdup(line);
        }

        if (prev_line != NULL)
        {
            fwrite(&count, 4, 1, stdout);
            fwrite(prev_line, 1, 1, stdout);
        }

        free(prev_line);
        fclose(file);
    }

    exit(0);
}
