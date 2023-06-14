#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// Linked list where node contains a line of text
typedef struct linkedList
{
    char *line;
    struct linkedList *next;
} LinkedList;

int main(int argc, char *argv[])
{
    LinkedList *head = NULL;
    char *line = NULL;
    size_t len = 0;
    FILE *input_file = stdin;
    FILE *output_file = stdout;

    // Too many arguments passed to the program:
    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // When one argument passed to the program:
    if (argc == 2 && (input_file = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "error: cannot open file '%s'", argv[1]);
        exit(1);
    }

    // When two arguments passed to the program:
    if (argc == 3)
    {
        if ((input_file = fopen(argv[1], "r")) == NULL)
        {
            fprintf(stderr, "error: cannot open file '%s'", argv[1]);
            exit(1);
        }
        if ((output_file = fopen(argv[2], "w")) == NULL)
        {
            fprintf(stderr, "error: cannot open file '%s'", argv[2]);
            exit(1);
        }

        // Inputfile is same as outputfile:
        if (strcmp(argv[1], argv[2]) == 0)
        {
            fprintf(stderr, "Input and output file must differ\n");
            fclose(input_file);
            fclose(output_file);
            exit(1);
        }
    }

    // Store lines in linked list reverse order:
    // getline() reads line from a file stream and stores it in buffer 'line'
    // getline returns the number of characters read
    while (getline(&line, &len, input_file) != -1)
    {
        LinkedList *node = malloc(sizeof(LinkedList));
        if (node == NULL)
        {
            free(line);
            fprintf(stderr, "malloc failed\n");
            fclose(input_file);
            fclose(output_file);
            exit(1);
        }
        // Assigning node->line with duplicate of the line
        node->line = strdup(line);

        if (node->line == NULL)
        {
            fprintf(stderr, "error: strdup failed\n");
            fclose(input_file);
            fclose(output_file);
            exit(1);
        }

        node->next = head;
        head = node;
    }

    // Print/write the linked list
    while (head != NULL)
    {
        LinkedList *temp = head;
        fprintf(output_file, "%s", head->line);
        head = head->next;
        free(temp->line);
        free(temp);
    }

    free(line);
    fclose(input_file);
    fclose(output_file);
    exit(0);
}