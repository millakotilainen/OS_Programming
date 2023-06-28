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

        int count = 0;
        char character;

        while (fread(&count, 4, 1, file) == 1 && fread(&character, 1, 1, file) == 1)
        {
            for (int i = 0; i < count; i++)
            {
                printf("%c", character);
            }
        }

        fclose(file);
    }

    exit(0);
}