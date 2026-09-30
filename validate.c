#include "main.h"

/* Function definitions */
int read_validate(int argc, char *argv[], Flist **f_head)
{
    int filecount = 0;

    for (int i = 1; i < argc; i++)
    {
        char *fileName = argv[i];

        if (strstr(fileName, ".txt") == NULL)
        {
            continue;
        }

        FILE *fptr = fopen(fileName, "r");

        if (fptr == NULL)
        {
            continue;
        }

        fseek(fptr, 0, SEEK_END);

        if (ftell(fptr) == 0)
        {
            fclose(fptr);
            continue;
        }

        fclose(fptr);

        if (check_duplicates(*f_head, fileName) == SUCCESS)
        {
            continue;
        }

        insert_last(f_head, fileName);
        filecount++;
    }

    return filecount ? SUCCESS : FAILURE;
}

int insert_last(Flist **f_head, char *arr)
{
    Flist *new_node = malloc(sizeof(Flist));

    if (new_node == NULL)
    {
        return FAILURE;
    }

    strncpy(new_node->arr, arr, sizeof(new_node->arr) - 1);
    new_node->arr[sizeof(new_node->arr) - 1] = '\0';
    new_node->link = NULL;

    if (*f_head == NULL)
    {
        *f_head = new_node;
        return SUCCESS;
    }
    else
    {
        Flist *temp = *f_head;

        while (temp->link != NULL)
        {
            temp = temp->link;
        }

        temp->link = new_node;
        return SUCCESS;
    }
}

int check_duplicates(Flist *f_head, char *fileName)
{
    Flist *temp = f_head;

    while (temp != NULL)
    {
        if (strcmp(temp->arr, fileName) == 0)
        {
            return SUCCESS;
        }

        temp = temp->link;
    }

    return FAILURE;
}

int print_filenames(Flist *f_head)
{
    if (f_head == NULL)
    {
        printf("No file available\n");
        return FAILURE;
    }
    else
    {
        while (f_head != NULL)
        {
            printf("%s->", f_head->arr);
            f_head = f_head->link;
        }

        printf("NULL\n");
    }

    return SUCCESS;
}

int validate_backup_file(const char *backup_file)
{
    char *extension = strrchr(backup_file, '.');

    if (extension == NULL || strcmp(extension, ".txt") != 0)
    {
        printf("Error: Backup file must have .txt extension\n");
        return FAILURE;
    }

    FILE *fptr = fopen(backup_file, "r");

    if (fptr == NULL)
    {
        printf("Error: Backup file '%s' not found\n", backup_file);
        return FAILURE;
    }

    fseek(fptr, 0, SEEK_END);

    if (ftell(fptr) == 0)
    {
        printf("Error: Backup file '%s' is empty\n", backup_file);
        fclose(fptr);
        return FAILURE;
    }

    rewind(fptr);

    char first_char = fgetc(fptr);

    if (first_char != '#')
    {
        printf("Error: Invalid backup database format\n");
        fclose(fptr);
        return FAILURE;
    }

    fclose(fptr);

    return SUCCESS;
}

void free_db(Hash_t *ht)
{
    for (int i = 0; i < 27; i++)
    {
        Mlist *m_node = ht[i].link;

        while (m_node != NULL)
        {
            Slist *s_node = m_node->sublink;

            while (s_node != NULL)
            {
                Slist *temp_s = s_node;
                s_node = s_node->link;
                free(temp_s);
            }

            Mlist *temp_m = m_node;
            m_node = m_node->link;
            free(temp_m);
        }

        ht[i].link = NULL;
    }
}