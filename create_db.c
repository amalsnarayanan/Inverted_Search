#include "main.h"

/* Create database */
int create_db(Flist *f_head, Hash_t *ht)
{
    Flist *temp = f_head;

    // Traverse all nodes present in Flist
    while (temp != NULL)
    {
        FILE *fptr = fopen(temp->arr, "r");

        if (fptr == NULL)
        {
            printf("Error:Unable to open %s\n", temp->arr);
            temp = temp->link;
            continue;
        }

        char word[100];

        /* Read every word from file */
        while (fscanf(fptr, "%99s", word) == 1)
        {
            /* Get hash index using first character */
            int index = get_index(word[0]);

            /* Insert word into database */
            if (insert_hash(ht, index, word, temp->arr) == FAILURE)
            {
                fclose(fptr);
                return FAILURE;
            }
        }

        fclose(fptr);

        temp = temp->link;
    }

    return SUCCESS;
}