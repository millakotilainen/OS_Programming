#include <stdio.h>
#include <stdlib.h>

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
        char current_char, prev_char;
        prev_char = fgetc(file);

        while ((current_char = fgetc(file)) != EOF)
        {
            if (current_char == prev_char)
            {
                count++;
            }
            else
            {
                fwrite(&count, 4, 1, stdout);
                fwrite(&prev_char, 1, 1, stdout);
                count = 1;
                prev_char = current_char;
            }
        }
        fclose(file);
    }

    exit(0);
}