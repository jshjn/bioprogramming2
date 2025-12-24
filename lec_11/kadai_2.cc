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


    vector<double>tau_value(NUM_GENS, 0.0);
    vector<double>mean_value(NUM_GENS, 0.0);
    vector<int>max_tissue(NUM_GENS, 0);

    for(int i=0; i<NUM_GENS; i++){
        double sum=0.0;
        double max=0.0;
        int max_index=0;

        for(int j=0; j<NUM_TISSUES; j++){
            double x=expression_matrix[i][j];
            sum+=x;
            if(x>max){
                max=x;
                max_index=j;
            }
        }

        if(max==0.0){
            continue;
        }

        double mean=sum/NUM_TISSUES;
        mean_value[i]=mean;
        max_tissue[i]=max_index;

        double tau=0.0;
        for(int j=0; j<NUM_TISSUES; j++){
            tau+=(1.0-expression_matrix[i][j]/max);
        }
        tau/=(NUM_TISSUES-1);

        tau_value[i]=tau;
    }

    vector<int>tissue_specific_count(NUM_TISSUES, 0);

    for(int i=0; i<NUM_GENS; i++){
        if(tau_value[i]>=0.85){
            tissue_specific_count[max_tissue[i]]++;
        }
    }

    cout<<endl;
    cout<<"組織特異的発現遺伝子数"<<endl;
    for(int i=0; i<NUM_TISSUES; i++){
        cout<<tissue_name[i]<<": "<<tissue_specific_count[i]<<endl;
    }

    cout<<endl;
    cout<<"τ>=0.95かつ平均TPM>=30の遺伝子"<<endl;

    for(int i=0; i<NUM_GENS; i++){
        if(tau_value[i]>=0.95 && mean_value[i]>=30.0){
            cout<<gene_name[i]<<" | "<<"平均TPM="<<mean_value[i]<<" | "<<"特異組織="<<tissue_name[max_tissue[i]]<<endl;
        }
    }

    return 0;
}