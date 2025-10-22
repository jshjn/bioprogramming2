#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;

int main(void){
    int rule;
    cout<<"ルール番号を入力してください：";
    cin>>rule;

    int cells=401;
    int steps=200;

    vector<int> current(cells, 0), next(cells, 0);
    current[cells/2]=1;

    int ruleBits[8];
    for(int i=0; i<8; i++){
        ruleBits[i]=(rule>>i)&1;
    }

    string filename="rule" + to_string(rule) + ".txt";
    ofstream fout(filename);
    if(!fout){
        cout<<"ファイルを開けません："<<filename<<endl;
        return 1;
    }

    for(int t=0; t<=steps; t++){
        for(int i=0; i<cells; i++){
            fout<<(current[i]? "█":" ");
        }
        fout<<"\n";

        for(int i=0; i<cells; i++){
            int left=(i==0)? 0:current[i-1];
            int self=current[i];
            int right=(i==cells-1)?0:current[i+1];
            int pattern=(left<<2) | (self<<1) | right;
            next[i]=ruleBits[pattern];
        }

        current.swap(next);
    }

    fout.close();
    cout<<"結果を"<<filename<<"に出力しました"<<endl;

    return 0;
}