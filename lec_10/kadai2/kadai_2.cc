#include"image.hpp"
#include<iostream>
#include<vector>
using namespace std;

int otsu_threshold(const Image &img){
    vector<int> hist(256, 0);
    int N=img.w*img.h;

    for(int y=0; y<img.h; y++){
        for(int x=0; x<img.w; x++){
            int gray=img.GetPixel(x, y, 0);
            hist[gray]++;
        }
    }

    double mt=0.0;
    for(int k=0; k<256; k++){
        mt+=k*hist[k];
    }
    mt /=N;

    double max_sigma=-1.0;
    int best_t=0;

    for(int t=0; t<255; t++){
        double w1=0, w2=0;
        double m1=0, m2=0;

        for(int k=0; k<=t; k++){
            w1+=hist[k];
            m1+=k*hist[k];
        }
        for(int k=t+1; k<256; k++){
            w2+=hist[k];
            m2+=k*hist[k];
        }

        if(w1==0||w2==0){
            continue;
        }

        m1/=w1;
        m2/=w2;

        double sigma=
            w1*(m1-mt)*(m1-mt)+
            w2*(m2-mt)*(m2-mt);

        if(sigma>max_sigma){
            max_sigma=sigma;
            best_t=t;
        }
    }

    return best_t;
}

void binarize(Image &img, int t){
    for(int y=0; y<img.h; y++){
        for(int x=0; x<img.w; x++){
            int gray=img.GetPixel(x, y, 0);
            int v=(gray>t)?255:0;

            img.SetPixel(x, y, 0, v);
            img.SetPixel(x, y, 1, v);
            img.SetPixel(x, y, 2, v);
        }
    }
}

int main(void){
    Image img("sample.png");
    int t=otsu_threshold(img);
    cout<<"Otsu threshold="<<t<<endl;

    binarize(img, t);
    img.save("sample_otsu.png");

    return 0;
}