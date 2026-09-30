#include "main.h"

int search_db(Hash_t *ht)
{
    char word[100];

    printf("Enter the word to search: ");
    scanf("%99s", word);

    printf("-------------------------------------------------------------------\n");
    printf("Word   Filecount        Filename     Wordcount         Occurrences\n");
    printf("-------------------------------------------------------------------\n");

    int index = get_index(word[0]);

    if (ht[index].link == NULL)
    {
        printf("Word '%s' not found in database\n", word);
        return DATA_NOT_FOUND;
    }
    else
    {
        int found = 0;
        Mlist *m_node = ht[index].link;

        while (m_node != NULL)
        {
            if (strcmp(m_node->word, word) == 0)
            {
                found = 1;
                printf("%s      %d", m_node->word, m_node->fileCount);

                Slist *s_node = m_node->sublink;

                while (s_node != NULL)
                {
                    printf("            %s      %d", s_node->fileName, s_node->wordCount);
                    s_node = s_node->link;
                }
            }

            m_node = m_node->link;
        }

        if (found == 0)
        {
            printf("Word '%s' not found in database\n", word);
            return DATA_NOT_FOUND;
        }

        printf("\n");
        printf("------------------------------------------------------\n");
    }

    return SUCCESS;
}