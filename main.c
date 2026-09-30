#include "main.h"

int main(int argc, char *argv[])
{
    Flist *f_head = NULL;
    Hash_t ht[27];

    for (int i = 0; i < 27; i++)
    {
        ht[i].index = i;
        ht[i].link = NULL;
    }

    if (argc < 2)
    {
        printf("Error argc should be greater than 1\n");
        return 0;
    }

    if (read_validate(argc, argv, &f_head) == FAILURE)
    {
        printf("File Validation Failed\n");
        return 0;
    }

    int db_created = 0;
    int option = 0;

    do
    {
        printf("Select your choice among following operations:\n"
               "1. Create Database\n"
               "2. Display Database\n"
               "3. Save Database\n"
               "4. Search\n"
               "5. Update Database\n"
               "6. Exit\n\n"
               "Enter your choice :  ");

        if (scanf("%d", &option) != 1)
        {
            printf("INFO : Please enter a valid option\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                continue;
            option = 0;
        }

        switch (option)
        {
            case 1:
                if (db_created == 1)
                {
                    printf("Database already created. Cannot create again.\n");
                    break;
                }
                else
                {
                    if (create_db(f_head, ht) == SUCCESS)
                    {
                        db_created = 1;
                        printf("Database created successfully.\n");
                    }
                    else
                    {
                        printf("ERROR: Database creation failed\n");
                    }
                }
                break;

            case 2:
                if (db_created == 0)
                {
                    printf("ERROR: Database is not created\n");
                    break;
                }
                display_db(ht);
                break;

            case 3:
                if (db_created == 0)
                {
                    printf("ERROR: Database is not created\n");
                    break;
                }
                save_db(ht);
                break;

            case 4:
                if (db_created == 0)
                {
                    printf("ERROR: Database is not created\n");
                    break;
                }
                search_db(ht);
                break;

            case 5:
            {
                char backup_file[50];

                printf("Enter the backup file name: ");
                scanf("%49s", backup_file);

                if (validate_backup_file(backup_file) == FAILURE)
                {
                    printf("ERROR : Invalid backup file\n");
                    break;
                }

                if (update_db(ht, &f_head, backup_file) == SUCCESS)
                {
                    db_created = 1;
                }
                break;
            }

            case 6:
                break;

            default:
                printf("INFO : Please enter the valid option\n");
        }
    } while (option != 6);

    return 0;
}

