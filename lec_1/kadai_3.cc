#include<iostream>

class Matrix{
public:
    double a,b,c,d;
    Matrix(){}
    Matrix(double x, double y, double z, double w){
        a=x, b=y;
        c=z, d=w;
    }
    Matrix operator + (const Matrix &q) const{
        Matrix m;
        m.a=a+q.a;
        m.b=b+q.b;
        m.c=c+q.c;
        m.d=d+q.d;
        return(m);
    }
    Matrix operator *(const Matrix &q) const{
        Matrix m;
        m.a=a*q.a+b*q.c;
        m.b=a*q.a+b*q.d;
        m.c=c*q.a+d*q.c;
        m.d=c*q.a+d*q.d;
        return(m);
    }

    double trace() const{
        return a+d;
    }

    Matrix inverse() const{
        Matrix m;
        m.a=1*d/(a*d-b*c);
        m.b=1*(-b)/(a*d-b*c);
        m.c=1*(-c)/(a*d-b*c);
        m.d=1*a/(a*d-b*c);
        return(m);
    }

    bool operator



