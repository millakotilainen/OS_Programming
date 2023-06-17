#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *file;
    char buff[1024];

    for (int i = 1; i < argc; i++)
    {
        if ((file = fopen(argv[i], "r")) == NULL)
        {
            printf("my-cat: cannot open file\n");
            exit(1);
        }

        while (fgets(buff, 1024, file))
        {
            printf("%s", buff);
        }

        fclose(file);
    }

    exit(0);
}