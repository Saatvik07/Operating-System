#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv) {
        FILE *filePointer ; 
        char buffer[256];
        char dataToBeRead; 
        int count=1;
        if(argc==1){
            printf("Too few arguments\n");
        }
        if(argc==2){
            if((char)argv[1][0]=='-'){
                printf("Insuffecient arguments\n");
            }
            else{
                filePointer = fopen(argv[1], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "File failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            printf("%s",buffer);
                        }
                        fcelose(filePointer) ;     
                    } 
            }
        }
        else if(argc==3){
            if(strcmp(argv[1],"-n")==0){
                filePointer = fopen(argv[2], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "File failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            printf("%d\t%s",count,buffer);
                            count++;
                        }
                        fclose(filePointer) ;     
                    } 
            }
            else if(strcmp(argv[1],"-E")==0){
                filePointer = fopen(argv[2], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "File failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            int i=0;
                            while(buffer[i]!='\n'){
                                i++;
                            }
                            buffer[i]='$';
                            strcat(buffer,"\n");
                            printf("%s",buffer);
                        }
                        fclose(filePointer) ;     
                    } 
            }
            else if ((char)argv[1][0]!="-"){
                filePointer = fopen(argv[1], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "File failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            
                            printf("%s",buffer);
                        }
                        fclose(filePointer) ;     
                    } 
                filePointer = fopen(argv[2], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "File failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            printf("%s",buffer);
                        }
                        fclose(filePointer) ;     
                    } 
            }
            else{
                printf("these options are not available\n");
            }
        }
        else if (argc==4){
            if((char)argv[1][0]=='-' && (char)argv[2][0]=='-'){
                filePointer = fopen(argv[3], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "File failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            int i=0;
                            while(buffer[i]!='\n'){
                                i++;
                            }
                            buffer[i]='$';
                            strcat(buffer,"\n");
                            printf("%d\t%s",count,buffer);
                            count++;
                        }
                        fclose(filePointer) ;     
                    } 
            }
            else if (strcmp(argv[1],"-n")==0){
                filePointer = fopen(argv[2], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "Test.c file failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            printf("%d\t%s",count,buffer);
                            count++;
                        }
                        fclose(filePointer) ;     
                    } 
                filePointer = fopen(argv[3], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "Test.c file failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            printf("%d\t%s",count,buffer);
                            count++;
                        }
                        fclose(filePointer) ;     
                    } 
            }
            else if (strcmp(argv[1],"-E")==0){
                filePointer = fopen(argv[2], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "Test.c file failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            int i=0;
                            while(buffer[i]!='\n'){
                                i++;
                            }
                            buffer[i]='$';
                            strcat(buffer,"\n");
                            printf("%s",buffer);
                        }
                        fclose(filePointer) ;     
                    } 
                filePointer = fopen(argv[3], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "Test.c file failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            int i=0;
                            while(buffer[i]!='\n'){
                                i++;
                            }
                            buffer[i]='$';
                            strcat(buffer,"\n");
                            printf("%s",buffer);
                        }
                        fclose(filePointer) ;     
                    } 
            }
            else{
                printf("Bad arguments\n");
            }
        }
        else if (argc==5){
            if(strcmp(argv[1],"-n")==0 && strcmp(argv[2],"-E")==0 || strcmp(argv[2],"-n")==0 && strcmp(argv[1],"-E")==0){
                filePointer = fopen(argv[3], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "File failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            int i=0;
                            while(buffer[i]!='\n'){
                                i++;
                            }
                            buffer[i]='$';
                            strcat(buffer,"\n");
                            printf("%d\t%s",count,buffer);
                            count++;
                        }
                        fclose(filePointer) ;     
                    } 
                filePointer = fopen(argv[3], "r") ; 
                if ( filePointer == NULL ) 
                    { 
                        perror( "File failed to open." ) ; 
                    } 
                else
                    { 
                        while(fgets(buffer,255,filePointer) != NULL) 
                        {
                            int i=0;
                            while(buffer[i]!='\n'){
                                i++;
                            }
                            buffer[i]='$';
                            strcat(buffer,"\n");
                            printf("%d\t%s",count,buffer);
                            count++;
                        }
                        fclose(filePointer) ;     
                    } 
            }
            else{
                printf("Bad arguments\n");
            }
        }
        else{
            printf("More than two files are not supported\n");
        }

        
    }