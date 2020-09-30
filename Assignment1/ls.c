#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
int main(int argc, char **argv){
    struct dirent **files;
    int n,type=0,dirChanged=0;
    if(argv[1]==NULL){
        n = scandir(".", &files , 0, alphasort);
            if (n < 0)
                perror("ls failed");
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
        exit(0);
    }
    if(argc==3 || argc==2 && strcmp(argv[1],"-i")!=0 && strcmp(argv[1],"-a")!=0 && (char)argv[1][0]!='-'){
        if(argc==3){
            if(chdir(argv[2])!=0){
                perror("cd command Failed");
            }
            else{
                dirChanged=1;
            }
        }
        else{
            if(chdir(argv[1])!=0){
                perror("cd command Failed");
            }
            else{
                dirChanged=1;
            }
        }
    }

        if(strcmp(argv[1],"-i")==0){
            n = scandir(".", &files , 0, alphasort);
            if (n < 0)
                perror("ls failed");
            else {
                int i=0;
                while(i<n) {
                    if(strcmp(files[i]->d_name,"..")!=0 && strcmp(files[i]->d_name,".")!=0){
                        printf("%d ", files[i]->d_ino);
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
        if(strcmp(argv[1],"-a")==0){
            n = scandir(".", &files , 0, alphasort);
            if (n < 0)
                perror("ls failed");
            else {
                 int i=0;
                while(i<n) {
                    printf("%d ", files[i]->d_ino);
                    printf("%s\n",files[i]->d_name);
                    free(files[i]);
                    i++;
                }
                if(dirChanged==1){
                    chdir("..");
                }
            }
        }
    exit(0);
}