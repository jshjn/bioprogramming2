#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double f1(double x){
    return exp(x)+x-5.0;
}

double f2(double x){
    return cbrt(x);
}

double bisection(double (*f)(double), double a, double b, double tol, int &count){
    double fa=f(a);
    double fb=f(b);

    if(fa*fb>0){
        cout<<"この区間には解はありません。"<<endl;
        return 0;
    }

    double mid;
    count=0;

    while((b-a)/2>tol){
        mid=(a+b)/2;
        double fmid=f(mid);
        count++;

        if(fabs(fmid)<tol){
            break;
        }

        if(fa*fmid<0){
            b=mid;
            fb=fmid;
        }else{
            a=mid;
            fa=fmid;
        }
    }

    return (a+b)/2;
}

int main(void){
    cout<<fixed<<setprecision(15);

    double tol=1e-12;
    int count;

    double root1=bisection(f1, 0, 2, tol, count);
    cout<<"(2) f1(x)=e^x + x-5の解"<<endl;
    cout<<"x="<<root1<<endl;
    cout<<"反復回数:"<<count<<"回"<<endl;

    double root2=bisection(f2, -0.1, 0.2, tol, count);
    cout<<"(2) f2(x)= x^(1/3) の解"<<endl;
    cout<<"x="<<root2<<endl;
    cout<<"反復回数:"<<count<<"回"<<endl;

    return 0;
}