#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void){
    const int loop=1024, n=1024;
    float a[n][n], b[n], c[n];

    for(int i=0; i<n; i++){
        b[i]=(float)random()/RAND_MAX;
        c[i]=0.0;
        
        for(int j=0; j<n; j++){
            a[i][j]=(float)random()/RAND_MAX;
        }
    }

    clock_t start=clock();
    for(int l=0; l<loop; l++){
        for(int j=0; j<n; j++){
           c[l]+=a[l][j]*b[j];
        }
    }
    clock_t end=clodk();

    printf("time1: %f\n", (double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}