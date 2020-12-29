#include <unistd.h>
#include <stdio.h>
#include <limits.h>
int main(){
    char name[8]= "Saatvik\0";
    FILE *fp;
    fp = fopen("./q6.txt","w+");
    fputs(name,fp);
    fclose(fp);
    FILE *fp1;
    char buffer[255];
    fp1 = fopen("./q6.txt","r");
    fgets(buffer,255,(FILE*)fp);
    char cwd[256];
    printf("Reading name from the file present at %s:%s,\n",getcwd(cwd,sizeof(cwd)),buffer);
}

//Source:https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program