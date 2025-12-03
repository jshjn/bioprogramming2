#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void){
    const int loop=65536, n=8192;
    float a[n],b[n], c[n], d[n];

    for(int i=0; i<n; i++){
        a[i]=(float)random()/RAND_MAX;
        b[i]=(float)random()/RAND_MAX;
        c[i]=(float)random()/RAND_MAX;
        d[i]=(float)random()/RAND_MAX;   
    }

    clock_t start=clock();
    float sum=0.0;
    for(int l=0; l<loop; l++){ 
        for(int j=0; j<n; j++){ 
            sum+=(a[j]/b[j])*(c[j]/d[j]);
        }
    }
    printf("%f\n", sum);
    clock_t end=clock();

    printf("time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}