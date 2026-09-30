#include "main.h"

int save_db(Hash_t *ht)
{
    char file[100];

    printf("Enter the file to Save: ");
    scanf("%99s", file);

    if (strstr(file, ".txt") == NULL)
    {
        printf("Error: File should be '.txt'\n");
        return FAILURE;
    }

    FILE *fptr = fopen(file, "w");

    if (fptr == NULL)
    {
        printf("Error: Unable to open %s\n", file);
        return FAILURE;
    }

    for (int i = 0; i < 27; i++)
    {
        Mlist *temp_m = ht[i].link;

        while (temp_m != NULL)
        {
            fprintf(fptr, "#%d;%s;%d;", i, temp_m->word, temp_m->fileCount);

            Slist *temp_s = temp_m->sublink;

            while (temp_s != NULL)
            {
                fprintf(fptr, "%s;%d;", temp_s->fileName, temp_s->wordCount);
                temp_s = temp_s->link;
            }

            fprintf(fptr, "#\n");

            temp_m = temp_m->link;
        }
    }

    fclose(fptr);

    printf("Database saved successfully.\n");

    return SUCCESS;
}