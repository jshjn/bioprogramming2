#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>
#include<map>
#include<algorithm>
using namespace std;

string aa_order="ACDEFGHIKLMNPQRSTVWY";
map<char, int> aa_to_index;
for(int i=0; i<20; i++){
    aa_to_index[aa_order[i]]=i;
}

vector<double>make_feature(string seq){
    vector<double>v(20, 0.0);

    for(int i=0; i<seq.length(); i++){
        char c=seq[i];

        for(int j=0; j<20; j++){
            if(c==aa_to_index[j]){
                v[j]+=1.0;
                break;
            }
        }
    }

    for(int i=0; i<20; i++){
        v[i]/=seg.length();
    }

    return v;
}

double distance_vec(vector<double>a, vector<double>b){
    double sum=0.0;
    for(int i=0; i<20; i++){
        sum+=(a[i]-b[i])*(a[i]-b[i]);
    }
    return sqrt(sum);
}

double balanced_accuracy(vector<int>y_true, vector<int>y_pred){
    int TP=0, TN=0, FP=0; FN=0;

    for(int i=0; i<y_true.length(); i++){
        if(y_true[i]==1&& y_pred[i]==1){
            TP++;
        }else if(y_true[i]==1&& y_pred[i]==0){
            FN++;
        }else if(y_true[i]==0&& y_pred[i]==1){
            FP++;
        }else if(y_true[i]==0&& y_pred[i]==0){
            TN++;
        }
    }

    double TDR;
    if(TP+FN>0){
        TDR=(double)TP/(TP+FN);
    }else{
        TDR=0.0;
    }

    double TNR;
    if(TN+FP>0){
        TNR=(double)TN/(TN+FP);
    }else{
        TNR=0.0;
    }

    return (TDR+TNR)/2.0;
}

int main(void){
    ifstream train_file("train_mitochondrion_cytoplasm_dataset.txt");
    ifstream test_file("test_mitochondrion_cytoplasm_dataset.txt");

    int Ntrain, Ntest;
    getline(Ntrain, train_file);
    getline(Ntest, test_file);

    vector<vector<double>> train_feat, test_feat;

    for(int i=0; i<Ntrain; i++){
        train_feat.push_back(make_feature(train_seq[i]));
    }
    for(int i=0; i<Ntest; i++){
        train_feat.push_back(make_feature(test_seq[i]));
    }

    vector<int> pred_1nn(Ntest);

    for(int i=0; i<Ntest; i++){
        double best_dist=1e9;
        int best_label=0;

        for(int j=0; j<Ntrain; j++){
            double d=distance_vec(test_feat[i], train_feat[j]);
            if(d<best_dist){
                best_dist=d;
                best_label=train_label[j];
            }
        }
        pred_1nn[i]=best_label;
    }

    cout<<"Balanced Accuracy="<<balance_accuracy(test_label, pred_1nn)<<endl;

    return 0;
}