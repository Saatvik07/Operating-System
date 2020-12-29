#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <errno.h>

int main()
{
    char readChar;
    char filename[512];
    scanf( "%s", filename );

    char data[512];
	
    FILE *fileToOpen;
    fileToOpen = fopen(filename, "a+");
    if (fileToOpen == NULL)
    {
        return -EINVAL;
    }

    int fileDesc = fileno(fileToOpen);
    int lock = flock(fileDesc, LOCK_EX | LOCK_NB);

    if (lock != 0)
    {
        perror("Message: ");
            printf("Warning : The current resource is being used somewhere else too\nYou can still continue to edit the file :)");
    }
    else
    {
        printf("The current resource is available and is not being used \n");
    }

    int choice;
    while (1)
    {
        printf("1)Write\n2)Exit\n");

        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Enter your data \n");
            scanf("%d",&choice);
            fgets(data, 512, stdin);
            fputs(data, fileToOpen);
            fclose(fileToOpen);
            printf("Written \n");
        }
        else if (choice == 2)
        {
            break;
        }
        else
        {
            printf("Please enter 1,2 or 3  only\n");
            continue;
        }
    }

    return 0;
}

