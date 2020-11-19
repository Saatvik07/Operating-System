#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct message_struct
{
    long message_type;
    char message_text[512];
} message_body;
int main()
{
    key_t mqKey;
    int mqID;
    mqKey = ftok("saatvik", 65);
    mqID = msgget(mqKey, 0666 | IPC_CREAT);
    message_body.message_type = 1;
    FILE *fileptr;
    const int strLength = 512;
    char str[512];
    const char separator[2] = " ";
    char *word;
    fileptr = fopen("./para2.txt", "r");
    if (fileptr == NULL)
    {
        exit(-1);
    }
    while (fgets(str, strLength, fileptr))
    {
        word = strtok(str, separator);
        while (word != NULL)
        {
            strcpy(message_body.message_text,word);
            msgsnd(mqID, &message_body, sizeof(message_body), 0);
    	    printf("Token Sent: %s \n", message_body.message_text);
            word = strtok(NULL, separator);
        }
    }
    strcpy(message_body.message_text,"\n\n"); //denotes EOF
    msgsnd(mqID, &message_body, sizeof(message_body), 0);
    return 0;
}

