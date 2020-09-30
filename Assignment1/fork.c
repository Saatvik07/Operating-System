#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<fcntl.h>
int main() {
    pid_t pid = fork();
    if (pid < 0) {
        printf("Fork failed!\n");
        exit(-1);
    }

    else if (pid == 0) {
        printf("Beginning child process\n");
        FILE *filePointer ; 
        char buffer[65365];
        char dataToBeRead; 
        char section;
        int id,fileDesc;
        int count=0;
        int x1,x2,x3,x4,x5;
        fileDesc = open("Test.csv", O_RDONLY) ; 
        if (fileDesc==-1 ) 
        { 
            printf( "File failed to open." ) ; 
        } 
        else
        { 
            int count=0;
            while(read(fileDesc,buffer,sizeof(buffer)) != 0) 
            {
                char *token;
                token = strtok(buffer,",\n");
                while(token!=NULL){
                    if(count>=6){
                        if(count%6==0){
                            id = atoi(token);
                        }
                        else if (count%6==1){
                            section = (char)token[0];
                            if(section=='A'){
                                printf("Id: %d ",id);
                                printf("Section: %s ",token);
                            }
                            
                        }
                        else if(section=='A'){
                            if (count%6==2 && section=='A'){
                                x1 = atoi(token);
                                printf("A1: %d ",x1);
                            }  
                            else if (count%6==3){
                                x2 = atoi(token);
                                printf("A2: %d ",x2);
                            }  
                            else if (count%6==4){
                                x3 = atoi(token);
                                printf("A3: %d ",x3);
                            }  
                            else if (count%6==5){
                                x4 = atoi(token);
                                printf("A4: %d ",x4);
                                printf("Average: %f",(float)(x1+x2+x3+x4)/4);
                                printf("\n");
                            } 
                        }
                    }
                    token = strtok(NULL,",\n");  
                    count++;                                                                                                                                                                                                                                                                                            
                }
                
            }
            close(fileDesc) ;     
        }

        printf("\n\n\nCompleted the child process\n\n\n");
        exit(0);
    } 
    else {
        printf("Beggining the parent process\n");
        waitpid(pid,0);
        FILE *filePointer ; 
        char buffer1[65365];
        char dataToBeRead; 
        char section;
        int id,fileDesc;
        int x1,x2,x3,x4,x5;
        fileDesc = open("Test.csv", O_RDONLY) ; 
        if ( fileDesc == -1 ) 
        { 
            printf( "File failed to open." ) ; 
        } 
        else
        { 
            int count=0;
            while(read(fileDesc,buffer1,sizeof(buffer1)) != 0) 
            {
                char *token;
                token = strtok(buffer1,",\n");
                while(token!=NULL){
                    if(count>=6){
                        if(count%6==0){
                            id = atoi(token);
                        }
                        else if (count%6==1){
                            section = (char)token[0];
                            if(section=='B'){
                                printf("Id: %d ",id);
                                printf("Section: %s ",token);
                            }
                            
                        }
                        else if(section=='B'){
                            if (count%6==2 && section=='B'){
                                x1 = atoi(token);
                                printf("A1: %d ",x1);
                            }  
                            else if (count%6==3){
                                x2 = atoi(token);
                                printf("A2: %d ",x2);
                            }  
                            else if (count%6==4){
                                x3 = atoi(token);
                                printf("A3: %d ",x3);
                            }  
                            else if (count%6==5){
                                x4 = atoi(token);
                                printf("A4: %d ",x4);
                                printf("Average: %f",(float)(x1+x2+x3+x4)/4);
                                printf("\n");
                            } 
                        }
                    }
                    token = strtok(NULL,",\n");  
                    count++;                                                                                                                                                                                                                                                                                            
                }
                
            }
            close(fileDesc) ;     
        }
        printf("\n\nCompleted the parent process\n\n");
        
    }
}