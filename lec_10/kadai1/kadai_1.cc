#include "image.hpp"
#include<iostream>
using namespace std;

using namespace std;

int main(void){
    Image img("sample.png");

    for(int y=0; y<img.h; y++){
        for(int x=0; x<img.w; x++){
            int r=img.GetPixel(y, x, 0);
            int g=img.GetPixel(y, x, 1);
            int b=img.GetPixel(y, x, 2);

            int gray=(r+g+b)/3;

            img.SetPixel(y,x,0,gray);
            img.SetPixel(y,x,1,gray);
            img.SetPixel(y,x,2,gray);
        }
    }

    img.save("gray.png");
    return 0;
}