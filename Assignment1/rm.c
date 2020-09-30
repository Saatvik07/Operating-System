#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc,char **argv) {
        if(argc==1){
            printf("Too few arguments\n");
        }
        else if(argc==2){
            if((char)argv[1][0]!='-'){
                if(remove(argv[1])!=0){
                    perror("rm");
                }
            }
            else{
                printf("Bad arguments\n");
            }
        }
        else if(argc==3){
            if(strcmp(argv[1],"-d")==0){
                if(rmdir(argv[2])!=0){
                    perror("rm");
                }
            }
            else if (strcmp(argv[1],"-v")==0){
                if(remove(argv[2])!=0){
                    perror("rm");
                }
                else{
                    printf("Deleted the file: %s\n",argv[2]);
                }
            }
            else if (strcmp(argv[1],"-i")==0){
                char input;
                printf("Delete the file: %s?(y/n) ",argv[2]);
                scanf("%c",&input);
                if(input=='y'){
                    if(remove(argv[2])!=0){
                        perror("rm");
                    }
                }
            }
        }
        else if(argc==4){
            if(strcmp(argv[1],"-d")==0 && strcmp(argv[2],"-v")==0 || strcmp(argv[2],"-d")==0 && strcmp(argv[1],"-v")==0){
                if(rmdir(argv[3])!=0){
                    perror("rm");
                }
                else{
                     printf("Deleted the empty directory: %s\n",argv[3]);
                }
            }
            else if (strcmp(argv[1],"-i")==0 && strcmp(argv[2],"-v")==0 || strcmp(argv[2],"-i")==0 && strcmp(argv[1],"-v")==0){
                 char input;
                printf("Delete the file: %s?(y/n) ",argv[3]);
                scanf("%c",&input);
                if(input=='y'){
                    if(remove(argv[3])!=0){
                        perror("rm");
                    }
                    else{
                        printf("Deleted the file: %s\n",argv[3]);
                    }
                }
            }
            else if (strcmp(argv[1],"-i")==0 && strcmp(argv[2],"-d")==0 || strcmp(argv[2],"-i")==0 && strcmp(argv[1],"-d")==0){
                char input;
                printf("Delete the directory: %s?(y/n) ",argv[3]);
                scanf("%c",&input);
                if(input=='y'){
                    if(rmdir(argv[3])!=0){
                        perror("rm");
                    }
                }
            }
            else{
                printf("Bad arguments\n");
            }
        }
        else if (argc==5){
            if((char)argv[1][0]=='-' && (char)argv[2][0]=='-' && (char)argv[3][0]=='-'){
                char input;
                printf("Delete the directory: %s?(y/n) ",argv[4]);
                scanf("%c",&input);
                if(input=='y'){
                    if(rmdir(argv[4])!=0){
                        perror("rm");
                    }
                    else{
                        printf("Deleted the directory: %s\n",argv[4]);
                    }
                }
            }
            else{
                printf("Bad arguments\n");
            }
        }
        else{
            printf("Too many arguments\n");
        }
        exit(0);
        
    }
