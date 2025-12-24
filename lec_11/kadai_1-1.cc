#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

#define NUM_TISSUES 68
#define NUM_GENS 19594

void LoadExpressionFile(string file_name, vector<string>&tissue_name,
    vector<string>&gene_name, vector<vector<double>>&expression_matrix){

    ifstream ifs(file_name);
    if(!ifs){
        cerr<<"Cannot open expression file:"<<file_name<<endl;
        exit(1);
    }

    string tmp;
    ifs>>tmp;

    for(int i=0; i<NUM_TISSUES; i++){
        ifs>>tissue_name[i];
    }
    for(int i=0; i<NUM_GENS; i++){
        ifs>>gene_name[i];
        for(int j=0; j<NUM_TISSUES; j++){
            ifs>>expression_matrix[i][j];
        }
    }
    ifs.close();
}

int main(void){
    vector<string> tissue_name(NUM_TISSUES, "");
    vector<string> gene_name(NUM_GENS, "");
    vector<vector<double>>expression_matrix(NUM_GENS, vector<double>(NUM_TISSUES, 0.0));
    LoadExpressionFile("gene_expression.txt", tissue_name, gene_name, expression_matrix);

    vector<double> avg(NUM_GENS);

    for(int i=0; i<NUM_GENS; i++){
        double sum=0.0;
        for(int j=0; j<NUM_TISSUES; j++){
            sum+=expression_matrix[i][j];
        }
        avg[i]=sum / NUM_TISSUES;
    }

    for(int k=0; k<5; k++){
        int max=k;
        for(int i=k+1; i<NUM_GENS; i++){
            if(avg[i]>avg[max]){
                max=i;
            }
        }
        swap(avg[k], avg[max]);
        swap(gene_name[k], gene_name[max]);
    }

    cout<<"平均発現量　上位5"<<endl;
    for(int i=0; i<5; i++){
        cout<<gene_name[i]<<" : "<<avg[i]<<endl;
    }

    return 0;
}