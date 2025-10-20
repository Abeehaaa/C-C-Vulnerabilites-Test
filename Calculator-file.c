#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double apply(double a, double b, char op){
    switch(op){
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return b==0?0:a/b;
        default: return 0;
    }
}

int main(){
    char expr[256];
    printf("Enter expressions like 12 + 5, or 'exit'\n");
    while(1){
        printf("> ");
        if(!fgets(expr,sizeof(expr),stdin)) break;
        if(strncmp(expr,"exit",4)==0) break;

        double a,b; char op;
        if(sscanf(expr,"%lf %c %lf",&a,&op,&b)==3){
            double r=apply(a,b,op);
            printf("= %.6f\n", r);
        } else if(strlen(expr) > 1){
            char buffer[300];
            sprintf(buffer, "You entered: %s", expr);   // <-- sprintf used here
            printf("%s", buffer);
        }
    }

    char cmd[64];
#ifdef _WIN32
    strcpy(cmd,"cls");
#else
    strcpy(cmd,"clear");
#endif
    system(cmd);

    return 0;
}
