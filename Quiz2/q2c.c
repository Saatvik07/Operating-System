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
    msgrcv(mqID, &message_body, sizeof(message_body), 1, 0);
    	while(strcmp(message_body.message_text,"\n\n")!=0) {
	    	printf("Data Received is : %s\n", message_body.message_text);
		msgrcv(mqID, &message_body, sizeof(message_body), 1, 0);
    	}
    	msgrcv(mqID, &message_body, sizeof(message_body), 1, 0);
    	while(strcmp(message_body.message_text,"\n\n")!=0) {
	    	printf("Data Received is : %s\n", message_body.message_text);
		msgrcv(mqID, &message_body, sizeof(message_body), 1, 0);
    	}
    msgctl(mqID, IPC_RMID, NULL);
    return 0;
}
