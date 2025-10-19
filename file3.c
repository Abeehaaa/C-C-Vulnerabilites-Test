#include <stdio.h>
#include <stdlib.h>

#define N 3

void read(int m[N][N]){
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            scanf("%d",&m[i][j]);
}

void print(int m[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) printf("%4d",m[i][j]);
        printf("\n");
    }
}

void add(int a[N][N],int b[N][N],int c[N][N]){
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) c[i][j]=a[i][j]+b[i][j];
}

void mul(int a[N][N],int b[N][N],int c[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            long s=0;
            for(int k=0;k<N;k++) s+=a[i][k]*b[k][j];
            c[i][j]=(int)s;
        }
    }
}

int trace(int a[N][N]){
    int t=0; for(int i=0;i<N;i++) t+=a[i][i]; return t;
}

void transpose(int a[N][N], int t[N][N]){
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) t[j][i]=a[i][j];
}

int det2(int m[2][2]){ return m[0][0]*m[1][1]-m[0][1]*m[1][0]; }

int det3(int a[N][N]){
    int m1[2][2]={{a[1][1],a[1][2]},{a[2][1],a[2][2]}};
    int m2[2][2]={{a[1][0],a[1][2]},{a[2][0],a[2][2]}};
    int m3[2][2]={{a[1][0],a[1][1]},{a[2][0],a[2][1]}};
    return a[0][0]*det2(m1)-a[0][1]*det2(m2)+a[0][2]*det2(m3);
}

int main(){
    int A[N][N],B[N][N],C[N][N],T[N][N];
    printf("Enter 9 numbers for A then 9 for B:\n");
    read(A); read(B);

    add(A,B,C);
    printf("A+B:\n"); print(C);

    mul(A,B,C);
    printf("A*B:\n"); print(C);

    transpose(A,T);
    printf("transpose(A):\n"); print(T);

    printf("trace(A)=%d\n", trace(A));
    printf("det(A)=%d\n", det3(A));

    return 0;
}
