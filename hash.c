#include "main.h"

/* Bucket 0-25 for a-z (case-insensitive), 26 for everything else */
int get_index(char ch)
{
    if (isalpha((unsigned char)ch))
    {
        return tolower((unsigned char)ch) - 'a';
    }

    return 26;
}

/* Insert a word for a file, or increment its count if already present */
int insert_hash(Hash_t *ht, int index, char *word, char *fileName)
{
    Mlist *m_node = ht[index].link;
    Mlist *m_prev = NULL;

    while (m_node != NULL)
    {
        if (strcmp(m_node->word, word) == 0)
        {
            Slist *s_node = m_node->sublink;
            Slist *s_prev = NULL;

            while (s_node != NULL)
            {
                if (strcmp(s_node->fileName, fileName) == 0)
                {
                    s_node->wordCount++;
                    return SUCCESS;
                }

                s_prev = s_node;
                s_node = s_node->link;
            }

            /* Word seen before, but first time in this file */
            Slist *new_sub = malloc(sizeof(Slist));

            if (new_sub == NULL)
            {
                return FAILURE;
            }

            strncpy(new_sub->fileName, fileName, sizeof(new_sub->fileName) - 1);
            new_sub->fileName[sizeof(new_sub->fileName) - 1] = '\0';
            new_sub->wordCount = 1;
            new_sub->link = NULL;

            s_prev->link = new_sub;
            m_node->fileCount++;
            return SUCCESS;
        }

        m_prev = m_node;
        m_node = m_node->link;
    }

    /* New word: create the main node and its first sub node */
    Mlist *new_main = malloc(sizeof(Mlist));
    Slist *new_sub = malloc(sizeof(Slist));

    if (new_main == NULL || new_sub == NULL)
    {
        free(new_main);
        free(new_sub);
        return FAILURE;
    }

    strncpy(new_main->word, word, sizeof(new_main->word) - 1);
    new_main->word[sizeof(new_main->word) - 1] = '\0';
    new_main->fileCount = 1;
    new_main->link = NULL;
    new_main->sublink = new_sub;

    strncpy(new_sub->fileName, fileName, sizeof(new_sub->fileName) - 1);
    new_sub->fileName[sizeof(new_sub->fileName) - 1] = '\0';
    new_sub->wordCount = 1;
    new_sub->link = NULL;

    if (m_prev == NULL)
    {
        ht[index].link = new_main;
    }
    else
    {
        m_prev->link = new_main;
    }

    return SUCCESS;
}