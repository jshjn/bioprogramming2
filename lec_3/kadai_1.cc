#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

float sign(float x){
    if(x>0){
        return 1.0f;
    }else if(x<0){
        return -1.0f;
    }else{
        return 0.0f;
    }
}

int main(void){
    float a=1, b=10000, c=1;
    float discriminant=b*b-4*a*c;
    float D=sqrt(discriminant);

    cout<<fixed<<setprecision(10);

    float x1=(-b+D)/(2*a);
    float x2=(-b-D)/(2*a);

    float y1=(-b-sign(b)*D)/(2*a);
    float y2=c/(a*y1);

    cout<<"桁落ちを考慮しない場合の解："<<x1<<","<<x2<<endl;
    cout<<"桁落ちを考慮した場合の解："<<y1<<","<<y2<<endl;

    cout<<"差の比較"<<endl;
    cout<<fabs(x1-y1)<<","<<fabs(x2-y2);

    return 0;
}