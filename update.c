#include "main.h"

/* Free a Flist (local helper so update.c has no extra dependency) */
static void free_flist(Flist *f_head)
{
    while (f_head != NULL)
    {
        Flist *temp = f_head;
        f_head = f_head->link;
        free(temp);
    }
}

int update_db(Hash_t *ht, Flist **f_head, const char *backup_file)
{
    FILE *fptr;
    char line[500];

    Flist *backup_head = NULL;
    Flist *new_head = NULL;

    fptr = fopen(backup_file, "r");

    if (fptr == NULL)
    {
        printf("ERROR : Unable to open backup file\n");
        return FAILURE;
    }

    free_db(ht);

    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        char *token;
        int index;
        int fileCount;

        line[strcspn(line, "\n")] = '\0';

        token = strtok(line, "#;");

        if (token == NULL)
        {
            continue;
        }

        index = atoi(token);

        if (index < 0 || index > 26)
        {
            continue;
        }

        token = strtok(NULL, ";");

        if (token == NULL)
        {
            continue;
        }

        char word[100];
        strncpy(word, token, sizeof(word) - 1);
        word[sizeof(word) - 1] = '\0';

        token = strtok(NULL, ";");

        if (token == NULL)
        {
            continue;
        }

        fileCount = atoi(token);

        Mlist *new_main = malloc(sizeof(Mlist));

        if (new_main == NULL)
        {
            printf("INFO : Memory allocation failed\n");
            fclose(fptr);
            free_flist(backup_head);
            return FAILURE;
        }

        strncpy(new_main->word, word, sizeof(new_main->word) - 1);
        new_main->word[sizeof(new_main->word) - 1] = '\0';

        new_main->fileCount = fileCount;
        new_main->link = NULL;
        new_main->sublink = NULL;

        if (ht[index].link == NULL)
        {
            ht[index].link = new_main;
        }
        else
        {
            Mlist *temp_m = ht[index].link;

            while (temp_m->link != NULL)
            {
                temp_m = temp_m->link;
            }

            temp_m->link = new_main;
        }

        Slist *last_sub = NULL;

        for (int i = 0; i < fileCount; i++)
        {
            char fileName[100];
            int wordCount;

            token = strtok(NULL, ";");

            if (token == NULL)
            {
                printf("ERROR : Invalid backup file\n");
                fclose(fptr);
                free_flist(backup_head);
                return FAILURE;
            }

            strncpy(fileName, token, sizeof(fileName) - 1);
            fileName[sizeof(fileName) - 1] = '\0';

            token = strtok(NULL, ";");

            if (token == NULL)
            {
                printf("ERROR : Invalid backup file\n");
                fclose(fptr);
                free_flist(backup_head);
                return FAILURE;
            }

            wordCount = atoi(token);

            Slist *new_sub = malloc(sizeof(Slist));

            if (new_sub == NULL)
            {
                printf("INFO : Memory allocation failed\n");
                fclose(fptr);
                free_flist(backup_head);
                return FAILURE;
            }

            strncpy(new_sub->fileName, fileName, sizeof(new_sub->fileName) - 1);
            new_sub->fileName[sizeof(new_sub->fileName) - 1] = '\0';

            new_sub->wordCount = wordCount;
            new_sub->link = NULL;

            if (new_main->sublink == NULL)
            {
                new_main->sublink = new_sub;
            }
            else
            {
                last_sub->link = new_sub;
            }

            last_sub = new_sub;

            if (check_duplicates(backup_head, fileName) == FAILURE)
            {
                insert_last(&backup_head, fileName);
            }
        }
    }

    fclose(fptr);

    printf("INFO : Old Database loaded successfully\n");

    Flist *temp = *f_head;

    while (temp != NULL)
    {
        if (check_duplicates(backup_head, temp->arr) == SUCCESS)
        {
            printf("ERROR : File %s is already present in database\n", temp->arr);
        }
        else
        {
            insert_last(&new_head, temp->arr);
        }

        temp = temp->link;
    }

    free_flist(backup_head);

    if (new_head != NULL)
    {
        if (create_db(new_head, ht) == FAILURE)
        {
            free_flist(new_head);
            return FAILURE;
        }

        free_flist(new_head);
    }
    else
    {
        printf("INFO : No new files to update\n");
    }

    printf("INFO : Database updated successfully\n");

    return SUCCESS;
}