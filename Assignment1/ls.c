#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
int main(int argc, char **argv){
    struct dirent **files;
    int n,type=0,dirChanged=0;
    if(argc==1){
        n = scandir(".", &files , 0, alphasort);
            if (n < 0)
                perror("ls");
            else {
                int i=0;
                while(i<n) {
                    if(strcmp(files[i]->d_name,"..")!=0 && strcmp(files[i]->d_name,".")!=0){
                        printf("%s\n",files[i]->d_name);
                    }
                    free(files[i]);
                    i++;
                }
                free(files);
                if(dirChanged==1){
                    chdir("..");
                }
                
            }
    }
    else if (argc==2){
        if((char)argv[1][0]!='-'){
            if(chdir(argv[1])!=0){
                perror("ls");
            }
            else{
                n = scandir(".", &files , 0, alphasort);
                if (n < 0)
                    perror("ls");
                else {
                    int i=0;
                    while(i<n) {
                        if(strcmp(files[i]->d_name,"..")!=0 && strcmp(files[i]->d_name,".")!=0){
                            printf("%s\n",files[i]->d_name);
                        }
                        free(files[i]);
                        i++;
                    }
                    free(files);
                    chdir("..");
                }
            }
        }
        else if (strcmp(argv[1],"-i")==0){
            n = scandir(".", &files , 0, alphasort);
                if (n < 0)
                    perror("ls");
                else {
                    int i=0;
                    while(i<n) {
                        if(strcmp(files[i]->d_name,"..")!=0 && strcmp(files[i]->d_name,".")!=0){
                            printf("%ld ", files[i]->d_ino);
                            printf("%s\n",files[i]->d_name);
                        }
                        free(files[i]);
                        i++;
                    }
                    free(files);
                }
        }
        else if (strcmp(argv[1],"-a")==0){
             n = scandir(".", &files , 0, alphasort);
                if (n < 0)
                    perror("ls");
                else {
                    int i=0;
                    while(i<=n) {
                        printf("%s\n",files[i]->d_name);
                        free(files[i]);
                        i++;
                    }
                    free(files);
                    if(dirChanged==1){
                        chdir("..");
                    }
                    
                }
        }
        else{
            printf("No file name mentioned\n");
        }
    }
    else if (argc==3){
        if(strcmp(argv[1],"-i")==0 && strcmp(argv[2],"-a")!=0){
            if((char)argv[2][0]!='-'){
                if(chdir(argv[2])!=0){
                    perror("ls");
                }
                else{
                    n = scandir(".", &files , 0, alphasort);
                    if (n < 0)
                        perror("ls");
                    else {
                        int i=0;
                        while(i<n) {
                            if(strcmp(files[i]->d_name,"..")!=0 && strcmp(files[i]->d_name,".")!=0){
                                printf("%ld ", files[i]->d_ino);
                                printf("%s\n",files[i]->d_name);
                            }
                            free(files[i]);
                            i++;
                        }
                        free(files);
                        chdir("..");
                    }
                }
            }
            else{
                printf("Bad arguments\n");
            }
        }
        else if (strcmp(argv[1],"-a")==0 && strcmp(argv[2],"-i")!=0){
            if((char)argv[2][0]!='-'){
                if(chdir(argv[2])!=0){
                    perror("ls");
                }
                else{
                    n = scandir(".", &files , 0, alphasort);
                    if (n < 0)
                        perror("ls");
                    else {
                        int i=0;
                        while(i<=n) {
                            printf("%s\n",files[i]->d_name);
                            free(files[i]);
                            i++;
                        }
                        free(files);
                        chdir("..");
                        
                    }
                }
                
            }
            else{
                printf("Bad arguments\n");
            }

        }
        else if(strcmp(argv[1],"-i")==0 && strcmp(argv[1],"-a")==0 || strcmp(argv[2],"-i")!=0 && strcmp(argv[1],"-a")!=0){
            n = scandir(".", &files , 0, alphasort);
                if (n < 0)
                    perror("ls");
                else {
                    int i=0;
                    while(i<n) {
                        printf("%ld ", files[i]->d_ino);
                        printf("%s\n",files[i]->d_name);
                        free(files[i]);
                        i++;
                    }
                    free(files);
                    chdir("..");
                }
        }
    }
    else if (argc==4){
        if(strcmp(argv[1],"-i")==0 && strcmp(argv[1],"-a")==0 || strcmp(argv[2],"-i")!=0 && strcmp(argv[1],"-a")!=0){
            if(chdir(argv[3])!=0){
                perror("ls");
            }
            else{
                n = scandir(".", &files , 0, alphasort);
                if (n < 0)
                    perror("ls");
                else {
                    int i=0;
                    while(i<n) {
                        printf("%ld ", files[i]->d_ino);
                        printf("%s\n",files[i]->d_name);
                        free(files[i]);
                        i++;
                    }
                    free(files);
                    chdir("..");
                }
            }
        }
    }
    else{
        printf("Too many arguments\n");
    }
    exit(0);
}