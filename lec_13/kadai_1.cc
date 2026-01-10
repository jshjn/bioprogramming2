#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main(void){
    ifstream ist("genome.txt");
    if(!ist){
        cerr<<"Cannot open genome.txt."<<endl;
        exit(1);
    }

    string T, line;
    while(getline(ist,line)){
        T+=line;
    }

    string S;
    cout<<"文字列パターンの入力:";
    cin>>S;

    cout<<"Tの中に出現するパターンSの位置"<<endl;

    for(int i=0; i+S.size()<=T.size(); i++){
        bool ok=true;
        for(int j=0; j<S.size(); j++){
            if(T[i+j]!=S[j]){
                ok=false;
                break;
            }
        }
        if(ok){
            cout<<i<<endl;
        }
    }

    return 0;
}