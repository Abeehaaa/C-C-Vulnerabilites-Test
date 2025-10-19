#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    long lines;
    long words;
    long bytes;
} Stats;

void update_stats(Stats *s, const char *buf){
    s->lines++;
    s->bytes += (long)strlen(buf);
    int in=0;
    for(int i=0;buf[i];i++){
        if(isspace((unsigned char)buf[i])) in=0;
        else if(!in){ s->words++; in=1; }
    }
}

int main(){
    char path[256];
    char outpath[256];
    char buf[1024];
    printf("Input file path: ");
    scanf("%255s", path);
    printf("Output summary file: ");
    scanf("%255s", outpath);

    FILE *f=fopen(path,"r");
    if(!f){ printf("cannot open\n"); return 1; }

    Stats s={0,0,0};
    while(fgets(buf,sizeof(buf),f)) update_stats(&s, buf);
    fclose(f);

    printf("lines:%ld words:%ld bytes:%ld\n", s.lines,s.words,s.bytes);

    FILE *g=fopen(outpath,"w");
    if(!g){ printf("cannot write\n"); return 1; }

    fprintf(g,"File: %s\n", path);
    fprintf(g,"Lines: %ld\n", s.lines);
    fprintf(g,"Words: %ld\n", s.words);
    fprintf(g,"Bytes: %ld\n", s.bytes);

    fclose(g);

    printf("done\n");
    return 0;
}
