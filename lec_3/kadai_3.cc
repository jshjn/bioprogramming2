#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double TOL=1e-12;
const int MAX_IT=1000;

double f1(double x) {
    return exp(x)+x-5;
}
double df1(double x) {
    return exp(x)+1; 
}

double f2(double x) {
    return cbrt(x); 
}

double df2(double x) {
    if(x==0){
        return HUGE_VAL;
    }
    double c=cbrt(x);
    return 1/(3*c*c);
}

double newton(double (*f)(double), double (*df)(double), double x0, int &count) {
    double x=x0;
    count=0;

    for(int k=0; k<MAX_IT; ++k) {
        double fx=f(x);
        double dfx=df(x);
        ++count;

        if(fabs(dfx)<1e-16){
            cout<<"-> 導関数がほぼ0です。Newton法は使えません。"<<endl;
            return 0;
        }

        double xnext=x-fx/dfx;

        if (fabs(xnext-x)<TOL){
            return xnext;
        }

        if(fabs(fx)<TOL){
            return x;
        }

        x=xnext;
    }
    cout<<"-> 最大反復回数に達しました"<<endl;
    return 0;
}

int main(void){
    cout<<fixed<<setprecision(15);

    int iter1=0;
    double x0_1=0.0;
    cout<<"(1) f1(x)=e^x + x-5, x0="<<x0_1<<endl;
    double root1=newton(f1, df1, x0_1, iter1);
    cout<<"近似解 x="<<root1<<endl;
    cout<<"反復回数="<<iter1<<endl;

    int iter2=0;
    double x0_2=-0.1;
    cout<<"(2) f2(x)=x^(1/3), x0="<<x0_2<<endl;
    double root2=newton(f2, df2, x0_2, iter2);
    cout<<"近似解 x="<<root2<<endl;
    cout<<"反復回数="<<iter2<<endl;

    cout << "二分法では (1) 約40回, (2) 約38回"<<endl;
    cout << " Newton法は通常二分法よりずっと少ない反復回数で収束する"<<endl;

    return 0;
}


