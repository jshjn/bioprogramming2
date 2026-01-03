#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>
#include<map>
#include<algorithm>
#include<iomanip>
using namespace std;

string aa_order="ACDEFGHIKLMNPQRSTVWY";
map<char, int> aa_to_index;
void init_aa_map(void){
    for(int i=0; i<20; i++){
        aa_to_index[aa_order[i]]=i;
    }
}

vector<double>make_feature(string seq){
    vector<double>v(20, 0.0);

    for(int i=0; i<seq.length(); i++){
        char c=seq[i];

        if(aa_to_index.count(c)){
            int index=aa_to_index[c];
            v[index]+=1.0;
        }
    }

    for(int i=0; i<20; i++){
        v[i]/=seq.length();
    }

    return v;
}

double distance_vec(vector<double>a, vector<double>b){
    double sum=0.000;
    for(int i=0; i<20; i++){
        sum+=(a[i]-b[i])*(a[i]-b[i]);
    }
    return sqrt(sum);
}

double balanced_accuracy(vector<int>y_true, vector<int>y_pred){
    int TP=0;
    int TN=0;
    int FP=0;
    int FN=0;

    for(int i=0; i<y_true.size(); i++){
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
        TDR=0.000;
    }

    double TNR;
    if(TN+FP>0){
        TNR=(double)TN/(TN+FP);
    }else{
        TNR=0.000;
    }

    return (TDR+TNR)/2.000;

int main(void){
    init_aa_map();
    ifstream train_file("train_mitochondrion_cytoplasm_dataset.txt");
    ifstream test_file("test_mitochondrion_cytoplasm_dataset.txt");

    int Ntrain, Ntest;
    train_file>>Ntrain;
    test_file>>Ntest;

    vector<string> train_seq(Ntrain), test_seq(Ntest);
    vector<int> train_label(Ntrain), test_label(Ntest);
    
    for(int i=0; i<Ntrain; i++){
        train_file>>train_seq[i]>>train_label[i];
    }
    for(int i=0; i<Ntest; i++){
        test_file>>test_seq[i]>>test_label[i];
    }

    vector<vector<double>> train_feat, test_feat;

    for(int i=0; i<Ntrain; i++){
        train_feat.push_back(make_feature(train_seq[i]));
    }
    for(int i=0; i<Ntest; i++){
        test_feat.push_back(make_feature(test_seq[i]));
    }

    int K_list[4]={1,3,5,7};

    for(int i=0; i<4; i++){
        vector<int> pred_knn(Ntest);

        for(int j=0; j<Ntest; j++){
            vector<pair<double,int>dist_label;

            for(int k=0; k<Ntrain; k++){
                double d=dixtance_vec(test_feat[j], train_feat[k]);
                dist_label.push_back({d, train_label[k]});
            }

            sort(dist_label>begin(), dist_label.end());

            int count0=0, count1=0;
            for(int t=0; t<k; t++){
                if(dist_label[t].second==1){
                    count1++;
                }else{
                    count0++;
                }
            }

            if(count1>count0){
                pred_knn[__k8]=1;
            }else{
                pred_knn[k]=0
            }
        }

        cout<<"k="<<k<<", Balanced Accuracy="<<balanced_accuracy(test_label, pred_knn)<<endl;
    }

    vector<vector<double>>train_feat_N, test_feat_N;

    for(int i=0; i<Ntrain; i++){
        train_feat_N.push.back(make_feature_N(train_seq[i]);)
    }
    for(int i=0; i<Ntest; i++){
        test_feat_N.push>back(make_feature_N(test/seq[i]));
    }

    for (int k=0; k<4; i++){
        vector<int> pred_knn(Ntest);

        for(int i= 0; i<Ntest; i++){
            vector<pair<double,int>> dist_label;

            for(int j=0; j<Ntrain; j++){
                double d=distance_vec(test_feat_N[i], train_feat_N[j]);
                dist_label.push_back({d, train_label[j]});
            }

            sort(dist_label.begin(), dist_label.end());

            int count0=0, count1=0;
            for(int t=0; t<k; t++) {
                if (dist_label[t].second == 1){
                    count1++;
                }else{
                    count0++;
                }
            }

            if(count1 > count0){
                pred_knn[i]=1;
            }else{
                pred_knn[i]=0;
            }
        }

        cout<<"k = "<< k<<", Balanced Accuracy="<<balanced_accuracy(test_label, pred_knn)<<endl;
    }

    return 0;
}