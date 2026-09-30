#ifndef MAIN_H
#define MAIN_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
#define FILE_EMPTY -1
#define DATA_NOT_FOUND -2

typedef struct main_node Mlist;
typedef struct sub_node Slist;

// Hash Table
typedef struct hash_table
{
    int index;
    Mlist *link;
} Hash_t;

// Main Node
struct main_node
{
    int fileCount;
    char word[100];
    Mlist *link;
    Slist *sublink;
};

// Sub Node
struct sub_node
{
    int wordCount;
    char fileName[100];
    Slist *link;
};

// FileList Node
typedef struct node
{
    char arr[100];
    struct node *link;
} Flist;

/* ================== Function Prototypes ================== */

// validate.c
int read_validate(int argc, char *argv[], Flist **f_head);
int insert_last(Flist **f_head, char *arr);
int check_duplicates(Flist *f_head, char *fileName);
int print_filenames(Flist *f_head);
int validate_backup_file(const char *backup_file);
void free_db(Hash_t *ht);

// create_db.c
int create_db(Flist *f_head, Hash_t *ht);

// display.c
void display_db(Hash_t *ht);

// save.c
int save_db(Hash_t *ht);

// search.c
int search_db(Hash_t *ht);

// update.c
int update_db(Hash_t *ht, Flist **f_head, const char *backup_file);

// hash helpers
int get_index(char ch);
int insert_hash(Hash_t *ht, int index, char *word, char *fileName);

#endif