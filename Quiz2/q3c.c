#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT    3000
  
// Driver code 
int main() { 
    int socket_desc; 
    char buffer[512]; 
    
    struct sockaddr_in server_address, client_address; 

    if ( (socket_desc = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&server_address, 0, sizeof(server_address)); 
    memset(&client_address, 0, sizeof(client_address)); 
       
    server_address.sin_family    = AF_INET; // IPv4 
    server_address.sin_addr.s_addr = INADDR_ANY; 
    server_address.sin_port = htons(PORT); 

    if ( bind(socket_desc, (const struct sockaddr *)&server_address,  
            sizeof(server_address)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int len, n; 
  
    len = sizeof(client_address); 
    n = recvfrom(socket_desc, (char *)buffer, 512,  
                MSG_WAITALL, ( struct sockaddr *) &client_address, 
                &len); 
    while(buffer[0]!='\n' && buffer[1]!='\n'){
    	buffer[n] = '\0'; 
    	printf("Client : %s\n", buffer);
    	
    	n = recvfrom(socket_desc, (char *)buffer, 512,MSG_WAITALL, ( struct sockaddr *) &client_address,&len);  
    }
    
    char *confirmation_message = "Hi client, I have read all your messages"; 
    
    sendto(socket_desc, (const char *)confirmation_message, strlen(confirmation_message),  
        MSG_CONFIRM, (const struct sockaddr *) &client_address, 
            len); 
    printf("Confirmation sent.\n");  
    n = recvfrom(socket_desc, (char *)buffer, 512,MSG_WAITALL, ( struct sockaddr *) &client_address,&len); 
    while(buffer[0]!='\n' && buffer[1]!='\n'){
    	buffer[n] = '\0'; 
    	printf("Client : %s\n", buffer);
    	
    	n = recvfrom(socket_desc, (char *)buffer, 512,MSG_WAITALL, ( struct sockaddr *) &client_address,&len);  
    }
    
    sendto(socket_desc, (const char *)confirmation_message, strlen(confirmation_message),  
        MSG_CONFIRM, (const struct sockaddr *) &client_address, 
            len); 
    printf("Confirmation sent.\n");  
      
    return 0; 
} 
