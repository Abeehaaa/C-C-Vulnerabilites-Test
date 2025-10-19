#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXS 50

typedef struct {
    int id;
    char name[40];
    int m1,m2,m3;
    double avg;
} Student;

int cmp_name(const void *a,const void *b){
    const Student *x=a,*y=b;
    return strcmp(x->name,y->name);
}

int cmp_avg_desc(const void *a,const void *b){
    const Student *x=a,*y=b;
    if(y->avg>x->avg) return 1;
    if(y->avg<x->avg) return -1;
    return 0;
}

void calc(Student *s){ s->avg=(s->m1+s->m2+s->m3)/3.0; }

int main(){
    int n;
    printf("How many students: ");
    scanf("%d",&n);
    if(n<=0||n>MAXS) return 0;

    Student *arr = malloc(sizeof(Student)*n);
    for(int i=0;i<n;i++){
        printf("id name m1 m2 m3: ");
        scanf("%d%39s%d%d%d",&arr[i].id,arr[i].name,&arr[i].m1,&arr[i].m2,&arr[i].m3);
        calc(&arr[i]);
    }

    qsort(arr,n,sizeof(Student),cmp_name);
    printf("Sorted by name:\n");
    for(int i=0;i<n;i++)
        printf("%d %s %.2f\n",arr[i].id,arr[i].name,arr[i].avg);

    qsort(arr,n,sizeof(Student),cmp_avg_desc);
    printf("Top 3 by average:\n");
    for(int i=0;i<n && i<3;i++)
        printf("%d %s %.2f\n",arr[i].id,arr[i].name,arr[i].avg);

    double class_avg=0;
    for(int i=0;i<n;i++) class_avg+=arr[i].avg;
    class_avg/=n;
    printf("Class average: %.2f\n", class_avg);

    int idq;
    printf("Search id: ");
    scanf("%d",&idq);
    int found=-1;
    for(int i=0;i<n;i++) if(arr[i].id==idq){ found=i; break; }
    if(found>=0) printf("Found %s avg=%.2f\n",arr[found].name,arr[found].avg);
    else printf("Not found\n");

    free(arr);
    return 0;
}
