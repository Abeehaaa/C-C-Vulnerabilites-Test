#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256

int count_vowels(const char *s){
    int c=0;
    for(int i=0; s[i]; i++){
        char ch = s[i] | 32;
        if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u') c++;
    }
    return c;
}

int main(void){
    char name[64];
    char buf[MAX];
    char greet[128];

    fputs("Enter your name: ", stdout);
    gets(name);                           
    if(name[0]=='\0'){ fputs("empty\n", stdout); return 0; }

    strcpy(buf, name);                    
    strcat(buf, "!");                      

    sprintf(greet, "Hello, %s (len=%zu)",   
            buf, strlen(name));

    fputs(greet, stdout); fputc('\n', stdout);

    int v = count_vowels(name);
    fprintf(stdout, name);   

    return 0;
}
