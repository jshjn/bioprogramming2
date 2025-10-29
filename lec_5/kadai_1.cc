#include<iostream>
#include<vector>
#include<fstream>
#include<time.h>
using namespace std;

const int H=50;
const int W=50;
const double beta=0.3;
const double gamma_=0.05;
const int INFECTED_INIT=2;

const int S=0;
const int I=1;
const int R=2;

const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};

int main(void){
    srandom((unsigned)time(NULL));

    vector<vector<int>> cur(H,vector<int>(W,S));
    vector<vector<int>> nxt=cur;

    for(int n=0; n<INFECTED_INIT; n++){
        int y=random()%H;
        int x=random()%W;
        cur[y][x]=I;
    }

    ofstream fout("sir_result.csv");
    fout<<"step,S,I,R\n";

    int step=0;
    while(true){
        int countS=0, countI=0, countR=0;

        for(int y=0; y<H; y++){
            for(int x=0; x<W; x++){
                if(cur[y][x]==S){
                    countS++;
                }else if(cur[y][x]==I){
                    countI++;
                }else{
                    countR++;
                }
            }
        }

        double total=H*W;
        fout<<step<<"," <<(double)countS/total<< ","<<(double)countI/total<< ","<< (double)countR/total<<"\n";

        if(countI==0){
            break;
        }

        nxt=cur;
        for(int y=0; y<H; y++){
            for(int x=0; x<W; x++){
                if(cur[y][x]==S){
                    bool infected=false;
                    for(int d=0; d<4; d++){
                        int ny=y+dy[d];
                        int nx=x+dx[d];
                        if(ny>=0 && ny<H && nx>=0 && nx<W){
                            if(cur[ny][nx]==I && (double)random()/RAND_MAX<beta){
                                infected=true;
                                break;
                            }
                        }
                    }
                    if(infected){
                        nxt[y][x]=I;
                    }
                }else if(cur[y][x]==I){
                    if((double)random()/RAND_MAX<gamma_){
                        nxt[y][x]=R;
                    }
                }
            }
        }
        cur.swap(nxt);
        step++;

    }

    fout.close();
    return 0;
}