#include<iostream>
#include<string>
#include<fstream>
using namespace std;

const int a=257, M=1000003;

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
    int m=S.size();

    long power=1;
    for(int i=0; i<m-1; i++){
        power=(power*a)%M;
    }

    long hashS=0;
    for(int i=0; i<m; i++){
        hashS=(hashS*a+S[i])%M;
    }

    long hashT=0;
    for(int i=0; i<m; i++){
        hashT=(hashT*a+T[i])%M;
    }
    
    for(int i=0; i+S.size()<=T.size(); i++){
        if(hashS==hashT){
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
        if(i+m<T.size()){
            hashT=(hashT+M-(T[i]*power)%M)%M;
            hashT=(hashT*a+T[i+m])%M;
        }
    }
    return 0;
}