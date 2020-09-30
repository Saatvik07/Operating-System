#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main(int argc,char **argv) {
        char buffer[512];
        if(argv[1]==NULL) {
            time_t t;
            struct tm *local;
            t = time(NULL);
            local = localtime(&t);
            strftime(buffer,512,"%A %d %B %Y %r %Z\n",local);
            fputs(buffer,stdout);
        }
        if(strcmp(argv[1],"-R")==0 && argv[2]==NULL){
            time_t t;
            struct tm *local;
            t = time(NULL);
            local = localtime(&t);
            strftime(buffer,512,"%a, %d %b %Y %I:%M:%S %z\n",local);
            fputs(buffer,stdout);
            
        }
        else if(strcmp(argv[1],"-u")==0 && argv[2]==NULL){
            time_t t;
            struct tm *utc;
            t = time(NULL);
            utc = gmtime(&t);
            strftime(buffer,512,"%A %d %B %Y %r %Z\n",utc);
            fputs(buffer,stdout);
        }
        else if(strcmp(argv[1],"-R")==0 && strcmp(argv[2],"-u")==0 || strcmp(argv[2],"-R")==0 && strcmp(argv[1],"-u")==0){
            time_t t;
            struct tm *utc;
            t = time(NULL);
            utc = gmtime(&t);
            strftime(buffer,512,"%a, %d %b %Y %I:%M:%S %z\n",utc);
            fputs(buffer,stdout);
        }
        
        exit(0);
        
    }
