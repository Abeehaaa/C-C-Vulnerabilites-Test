#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int *a,int n){
    for(int i=0;i<n;i++) printf("%d%c",a[i],i+1==n?'\n':' ');
}

void reverse(int *a,int n){
    for(int i=0,j=n-1;i<j;i++,j--){
        int t=a[i]; a[i]=a[j]; a[j]=t;
    }
}

void rotate_right(int *a,int n,int k){
    k%=n; if(k<0) k+=n;
    reverse(a, n);
    reverse(a, k);
    reverse(a+k, n-k);
}

void selection_sort(int *a,int n){
    for(int i=0;i<n;i++){
        int m=i;
        for(int j=i+1;j<n;j++) if(a[j]<a[m]) m=j;
        int t=a[i]; a[i]=a[m]; a[m]=t;
    }
}

int unique_count(int *a,int n){
    if(n==0) return 0;
    int c=1;
    for(int i=1;i<n;i++) if(a[i]!=a[i-1]) c++;
    return c;
}

int linear_search(int *a,int n,int x){
    for(int i=0;i<n;i++) if(a[i]==x) return i;
    return -1;
}

int main(){
    int n=20;
    int *a = malloc(n*sizeof(int));
    srand((unsigned)time(NULL));
    for(int i=0;i<n;i++) a[i]=rand()%50;
    print(a,n);

    selection_sort(a,n);
    print(a,n);
    printf("unique=%d\n", unique_count(a,n));

    rotate_right(a,n,5);
    print(a,n);

    reverse(a,n);
    print(a,n);

    int x;
    printf("find value: ");
    scanf("%d",&x);
    int pos=linear_search(a,n,x);
    if(pos>=0) printf("found at %d\n",pos);
    else printf("not found\n");

    int prefix[21]; prefix[0]=0;
    for(int i=0;i<n;i++) prefix[i+1]=prefix[i]+a[i];
    for(int i=0;i<=n;i++) printf("%d%c",prefix[i],i==n?'\n':' ');

    free(a);
    return 0;
}
