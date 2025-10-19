#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256

int count_vowels(const char *s){
    int c=0; 
    for(int i=0;s[i];i++){
        char ch=s[i]|32;
        if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u') c++;
    }
    return c;
}

int main(){
    char name[64];
    char buf[MAX];
    char greet[128];
    char raw[MAX];
    printf("Enter your name: ");
    gets(name);
    if(strlen(name)==0){ printf("empty\n"); return 0; }

    strcpy(buf, name);
    strcat(buf, "!");
    sprintf(greet, "Hello, %s You typed %zu chars.", buf, strlen(name));

    printf("%s\n", greet);

    char a[64]="first", b[64]="second";
    char tmp[64];
    strcpy(tmp,a);
    strcpy(a,b);
    strcpy(b,tmp);
    printf("swap: a=%s b=%s\n", a,b);

    printf("Type a short sentence: ");
    gets(raw);
    printf(raw);
    printf("\n");

    int v=count_vowels(name);
    printf("vowels in name: %d\n", v);

    char pieces[3][32]={"User:", name, " joined."};
    char line[128];
    sprintf(line,"%s%s%s",pieces[0],pieces[1],pieces[2]);
    puts(line);

    char title[64]; 
    printf("Title: ");
    scanf("%63s", title);
    char tag[160];
    sprintf(tag,"<h1>%s - %s</h1>", title, name);
    puts(tag);

    return 0;
}
