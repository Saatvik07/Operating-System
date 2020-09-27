# include <stdio.h> 
# include <string.h> 
#include <stdlib.h>
int main( ) 
{ 

    FILE *filePointer ; 
      char buffer[256];
    char dataToBeRead; 
    char section;
    int id;
    int x1,x2,x3,x4,x5;

    filePointer = fopen("Test.csv", "r") ; 
    if ( filePointer == NULL ) 
    { 
        printf( "Test.c file failed to open." ) ; 
    } 
    else
    { 
        int count=0;
        while(fgets(buffer,255,filePointer) != NULL) 
        {
            char *token;
            token = strtok(buffer,",");
            while(token!=NULL){
                if(count<6)
                printf("%s ",token);
                else{
                    if(count%6==0){
                    id = atoi(token);
                    printf("Id: %d ",id);
                }
                else if (count%6==1){
                    section = (char)token[0];
                    printf("Section: %c ",section);
                }
                else if (count%6==2){
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
                }  
                }
                
                

                token = strtok(NULL,",");  
                count++;                                                                                                                                                                                                                                                                                            
            }
            
             printf("\n");
        }
        fclose(filePointer) ;     
    } 
    return 0;         
} 