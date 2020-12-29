#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT 3000 
  
int main() { 
    int socket_desc; 
    char buffer[512]; 
    struct sockaddr_in  server_address; 
    if ( (socket_desc = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&server_address, 0, sizeof(server_address)); 
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(PORT); 
    server_address.sin_addr.s_addr = INADDR_ANY; 
      
    int n, len;
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
             sendto(socket_desc, word, strlen(word),MSG_CONFIRM, (const struct sockaddr *) &server_address, sizeof(server_address)); 
            printf("Token Sent: %s \n", word);
            word = strtok(NULL, separator);
        }
    }
   char *eof = "\n\n";
    sendto(socket_desc, (char *)eof, strlen(eof),MSG_CONFIRM, (const struct sockaddr *) &server_address, sizeof(server_address));
    printf("Sent EOF character\n");
    n = recvfrom(socket_desc, (char *)buffer, 512, MSG_WAITALL, (struct sockaddr *) &server_address,&len); 
    buffer[n] = '\0'; 
    printf("Server says : %s\n", buffer); 
  
    close(socket_desc); 
    return 0; 
} 
