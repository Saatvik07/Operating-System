#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
int main(int argc,char **argv) {
        if(argc==1){
            printf("Too few arguments");
        }
        else if (argc==2){
            if((char)argv[1][0]!='-'){
                if(mkdir(argv[1],0777)!=0){
                    perror("mkdir");
                }
            }
            else{
                printf("Bad arguments\n");
            }
        }
        else if (argc==3){
            if(strcmp(argv[1],"-p")==0){
                char *token;
                struct dirent **files;
                int n,chDirCount=0;
                token = strtok(argv[2],"/");
                while(token!=NULL){
                    n = scandir(".", &files , 0, alphasort);
                    if (n < 0)
                        perror("mkdir");
                    else {
                        
                        int i=0;
                        while(i<n) {
                            if(strcmp(files[i]->d_name,token)==0){
                                chdir(token);
                                chDirCount++;
                                break;
                            }
                            free(files[i]);
                            i++;
                        }
                        if(i==n){
                            if(mkdir(token,0777)!=0){
                                perror("mkdir");
                            }
                            else{
                                chdir(token);
                                chDirCount++;
                            }
                        }
                        free(files);
                    }
                    token=strtok(NULL,"/");
                }
                while(chDirCount--){
                    chdir("..");
                }
            }
            else if(strcmp(argv[1],"-v")==0){
                if(mkdir(argv[2],0777)!=0){
                    perror("mkdir");
                }
                else{
                    printf("Created directory: %s\n",argv[2]);
                }
            }
            else{
                printf("Bad arguments\n");
            }
        }
        else if (argc==4){
            if(strcmp(argv[1],"-v")==0 && strcmp(argv[2],"-p")==0|| strcmp(argv[2],"-v")==0 && strcmp(argv[1],"-p")==0){
                char *token;
                struct dirent **files;
                int n,chDirCount=0;
                token = strtok(argv[3],"/");
                while(token!=NULL){
                    n = scandir(".", &files , 0, alphasort);
                    if (n < 0)
                        perror("mkdir");
                    else {
                        int i=0;
                        while(i<n) {
                            if(strcmp(files[i]->d_name,token)==0){
                                chdir(token);
                                chDirCount++;
                                break;
                            }
                            free(files[i]);
                            i++;
                        }
                        if(i==n){
                            if(mkdir(token,0777)!=0){
                                perror("mkdir");
                            }
                            else{
                                printf("Created directory: %s\n",token);
                                chdir(token);
                                chDirCount++;
                            }
                        }
                        free(files);
                    }
                    token=strtok(NULL,"/");
                }
                while(chDirCount--){
                    chdir("..");
                }
            }
            else{
                printf("Bad arguments\n");
            }
        }
        else{
            printf("too many arguments\n");
        }
        exit(0);
        
    }
