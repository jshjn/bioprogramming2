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

    vector<bool>valid_gene(NUM_GENS, true);

    for(int i=0; i<NUM_GENS; i++){
        for(int j=0; j<NUM_TISSUES; j++){
            if(expression_matrix[i][j]>100.0){
                expression_matrix[i][j]=100.0;
            }
        }
    }

    for(int i=0; i<NUM_GENS; i++){
        int low_count=0;
        for(int j=0; j<NUM_TISSUES; j++){
            if(expression_matrix[i][j]<1.0){
                low_count++;
            }
        }
        if(low_count>=0.8*NUM_TISSUES){
            valid_gene[i]=false;
        }
    }

    for(int i=0; i<NUM_GENS; i++){
        if(!valid_gene[i]){
            continue;
        }

        double sum=0.0;
        for(int j=0; j<NUM_TISSUES; j++){
            sum+=expression_matrix[i][j];
        }
        double mean=sum/NUM_TISSUES;

        double var=0.0;
        for(int j=0; j<NUM_TISSUES; j++){
            double diff=expression_matrix[i][j]-mean;
            var+=diff*diff;
        }
        var/=NUM_TISSUES;

        if(var<=100){
            valid_gene[i]=false;
        }
    }
    
    int target_gene=0;
    vector<double>corr(NUM_GENS, 0.0);

    double mean_x=0.0;
    for(int j=0; j<NUM_TISSUES; j++){
        mean_x+=expression_matrix[target_gene][j];
    }
    mean_x/=NUM_TISSUES;

    for(int i=0; i<NUM_GENS; i++){
        if(!valid_gene[i]){
            continue;
        }

        double mean_y=0.0;
        for(int j=0; j<NUM_TISSUES; j++){
            mean_y+=expression_matrix[i][j];
        }
        mean_y/=NUM_TISSUES;

        double num=0.0;
        double dx=0.0;
        double dy=0.0;

        for(int j=0; j<NUM_TISSUES; j++){
            double x=expression_matrix[target_gene][j]-mean_x;
            double y=expression_matrix[i][j]-mean_y;
            num+=x*y;
            dx+=x*x;
            dy+=y*y;
        }

        if(dx==0.0 || dy==0.0){
            corr[i]=0.0;
        }else{
            corr[i]=num/sqrt(dx*dy);
        }
    }

    for(int k=0; k<5; k++){
        int max_index=k;
        for(int i=k+1; i<NUM_GENS; i++){
            if(corr[i]>corr[max_index]){
                max_index=i;
            }
        }
        swap(corr[k], corr[max_index]);
        swap(gene_name[k], gene_name[max_index]);
    }

    cout<<"基準遺伝子 "<<gene_name[target_gene]<<endl;
    cout<<"共発現遺伝子 上位5"<<endl;
    for(int i=0; i<5; i++){
        cout<<gene_name[i]<<" : r ="<<corr[i]<<endl;
    }

    return 0;
}