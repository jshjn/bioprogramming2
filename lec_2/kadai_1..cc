#include<iostream>
#include<string>
using namespace std;

int HammingDistance(string a, string b){
    
    if(a.size()!=b.size()){
        return -1;
    }

    int distance=0;
    for(int i=0; i<a.size(); i++){
        if(a.at(i)!=b.at(i)){
            distance++;
        }
    }
    return distance;
}

int main(void){
    string a; string b;
    cout<<"同じ文字数の文字列を入力してください"<<endl;
    cout<<"1つ目:";
    getline(cin,a);
    cout<<endl<<"2つ目:"
    getline(cin,b);

    int result=HammingDistance(a,b);
    if(result==-1){
        cout<<"文字列の長さが異なります。";
    }else{
        cout<<"ハミング距離は"<<result<<"です。";
    }

    return 0;

}