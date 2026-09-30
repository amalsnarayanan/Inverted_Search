#include "main.h"

void display_db(Hash_t *ht)
{
    
    printf(" Index   Word      Filecount   Filename    Wordcount    \n");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < 27; i++)
    {
        if (ht[i].link == NULL)
        {
            continue;
        }

        Mlist *temp_m = ht[i].link;

        while (temp_m != NULL)
        {
            printf("[%d]\t%-15s\t%d", i, temp_m->word, temp_m->fileCount);

            Slist *temp_s = temp_m->sublink;

            while (temp_s != NULL)
            {
                printf("\t%s\t%d", temp_s->fileName, temp_s->wordCount);
                temp_s = temp_s->link;
            }

            printf("\n");
            printf("--------------------------------------------------\n");

            temp_m = temp_m->link;
        }
    }
}