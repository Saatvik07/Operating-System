#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
 int main(){
    printf("Welcome User\n");
    FILE *filePointer, *filePointerRead;
    char input[256];
    char ch;
    char args[32][32];
    char command[32];
    char cwd[256];
    while(1){
        char *arguments [8]= {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
        filePointer = fopen("shellHistory.txt","a");
        if(filePointer==NULL){
            printf("shellHistory canot be opened\n");
            break;
        }
        else{
            printf("$ ");
            gets(input);
             fputs(input,filePointer);
            fputs("\n",filePointer);
            fclose(filePointer);
            char *command,*token, *flag=NULL;
            token = strtok(input," ");
            int i=0,noFlag=0;
            while(token!=NULL){
                if(i==0){
                    command=token;
                }
                else if (i==1 && (char)token[0]=='-'){
                    flag=token;
                }
                else{
                    if(i==1){
                        noFlag=1;
                        arguments[0]=token;
                        
                    }
                    if(noFlag==1){
                        arguments[i-1] = token;
                    }
                    else{
                        arguments[i-2] = token;
                    }
                }
                token = strtok(NULL," ");
                i++;
            }
            arguments[i]=NULL;
            if(strcmp(command,"pwd")==0){
                if(getcwd(cwd,sizeof(cwd))!=NULL){
                    printf("%s\n",cwd);
                }
                else{
                    perror("Cannot print working directory");
                }
            }
            else if (strcmp(command,"history")==0){
                filePointerRead = fopen("shellHistory.txt","r");
                char buffer[256];
                int i=1;
                while(fgets(buffer,sizeof(buffer),filePointerRead)!=NULL){
                    printf("%d %s",i,buffer);
                    i++;
                }
            }
            else if (strcmp(command,"echo")==0){
                 int i=0;
                      while(arguments[i]!=NULL){
                          printf("%s ",arguments[i]);      
                          i++;
                      }
                      printf("\n");
            }
            else if (strcmp(command,"cd")==0){
                if(chdir(arguments[0])!=0){
                    perror("cd command Failed");
                }
            }
            else if (strcmp(command,"ls")==0){
                pid_t pid = fork();
                if(pid==0){
                    if(flag!=NULL){
                        char *args[] = {"lsSelf",flag,arguments[0],arguments[1],arguments[2],NULL};
                        execvp(args[0],args);
                    }
                    else{
                        char *args[] = {"lsSelf",arguments[0],NULL};
                        execvp(args[0],args);
                    }
                }
                else if (pid>0){
                    wait(pid,0);
                }
            }
            else if (strcmp(command,"cat")==0){
                    pid_t pid = fork();
                    if(pid==0){
                        if(flag!=NULL){
                            char *args[] = {"catSelf",flag,arguments[0],arguments[1],arguments[2],NULL};
                            execvp(args[0],args);
                        }
                        else{
                            char *args[] = {"catSelf",arguments[0],arguments[1],NULL};
                            execvp(args[0],args);
                        }
                    }
                    else if (pid>0){
                        wait(pid,0);
                    }
                else{
                    printf("insufficient arguments\n");
                }
                
            }
            else if (strcmp(command,"date")==0){
                    pid_t pid = fork();
                    if(pid==0){
                        if(flag!=NULL){
                            if (arguments[0]!=NULL){
                                char *args[] = {"dateSelf",flag,arguments[0],NULL};
                                execvp(args[0],args);
                            }
                            else{
                                char *args[] = {"dateSelf",flag,NULL};
                                execvp(args[0],args);
                            }

                        }
                        else{
                            char *args[] = {"dateSelf",NULL};
                            execvp(args[0],args);
                        }
                    }
                    else if (pid>0){
                        wait(pid,0);
                    }
                
            }
            else if (strcmp(command,"rm")==0){
                    pid_t pid = fork();
                    if(pid==0){
                        if(flag!=NULL){
                                char *args[] = {"rmSelf",flag,arguments[0],arguments[1],arguments[2],NULL};
                                execvp(args[0],args);
                        }
                        else{
                            char *args[] = {"rmSelf",arguments[0],NULL};
                            execvp(args[0],args);
                        }
                    }
                    else if (pid>0){
                        wait(pid,0);
                    }
                
            }
            else if (strcmp(command,"mkdir")==0){
                    pid_t pid = fork();
                    if(pid==0){
                        if(flag!=NULL){
                                char *args[] = {"mkdirSelf",flag,arguments[0],arguments[1],NULL};
                                execvp(args[0],args);
                        }
                        else{
                            char *args[] = {"mkdirSelf",arguments[0],NULL};
                            execvp(args[0],args);
                        }
                    }
                    else if (pid>0){
                        wait(pid,0);
                    }
                
            }
            else if (strcmp(command,"exit")==0){
                break;
            }
        }
        
    }
    return 0;

 }