#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;

int main(void){
    ifstream ist("human_protein_interaction.txt");
    if(!ist){
        cerr<<"ファイルを開けませんでした。"<<endl;
        return 1;
    }

    map<string, int>interaction_count;
    string line;

    while(getline(ist,line)){
        size_t pos=line.find('');
        if(pos==string::npos) continue;

        string protein1=line.substr(0,pos);
        string protein2=line.substr(pos + 1);

        interaction_count[protein1]++;
        interaction_count[protein2]++;

        string max_protein;
        int max_count=0;
    }
        
    for(auto& p: interaction_count){
        if(p.second>max_count){
            max_count=p.second;
            max_protein=p.first;
        }
    }

    cout<<"最も多くの相互作用を持つタンパク質："<<max_protein<<endl;
    count<<"相互作用の数："max_count<<endl;

    return 0;
}