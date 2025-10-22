#include<iostream>
#include<vector>
#include<string>
#include<unistd.h>   
#include<cstdlib> 
#include<limits>
using namespace std;

const int HEIGHT=20;
const int WIDTH=20;
const int STEPS=100;   
const useconds_t FRAME_USEC=100000; 

void clear_screen() {
    system("cls");
}

void print_board(const vector<vector<int>>& board, int t, const string& title) {
    cout<<title<<"--t="<<t<<endl;
    for(int y=0 ;y<HEIGHT ;++y){
        for(int x=0 ;x<WIDTH ;++x){
            cout<<(board[y][x]?'M':' ');
        }
        cout<<endl;
    }
}

inline bool in_bounds(int x, int y) {
    return (0<=x && x<WIDTH && 0<= y && y<HEIGHT);
}

void step(const vector<vector<int>>& cur, vector<vector<int>>& next) {
    for(int y=0; y<HEIGHT; ++y) {
        for(int x=0; x<WIDTH; ++x) {
            int alive_neighbors=0;
            for(int dy=-1; dy<=1; ++dy){
                for(int dx=-1; dx<=1; ++dx){
                    if(dx==0 && dy==0){
                        continue; 
                    }
                    int nx=x+dx;
                    int ny=y+dy;
                    if(in_bounds(nx, ny) && cur[ny][nx]){
                        ++alive_neighbors;
                    }
                }
            }
            if(cur[y][x]){
                next[y][x]=(alive_neighbors==2 || alive_neighbors==3)?1:0;
            }else{
                next[y][x]=(alive_neighbors==3)?1:0;
            }
        }
    }
}

void run_simulation(vector<vector<int>> board, const string& title) {
    vector<vector<int>> next=board;

    for(int t=0; t<=STEPS; ++t) {
        clear_screen();
        print_board(board, t, title);
        usleep(FRAME_USEC);

        step(board, next);
        board.swap(next);
    }
}

int main() {
    vector<vector<int>> board(HEIGHT, vector<int>(WIDTH, 0));

    vector<vector<int>> blinker=board;
    if(5<HEIGHT && 6<WIDTH){
        blinker[5][4]=1;
        blinker[5][5]=1;
        blinker[5][6]=1;
    }

    cout<<"ブリンカーを"<<STEPS<<"ステップ実行します。続行するには Enter を押してください...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
    run_simulation(blinker, "Blinker (ブリンカー)");

    vector<vector<int>> glider=board;
    if(0<HEIGHT && 2<WIDTH){
        glider[0][1]=1;
        glider[1][2]=1;
        glider[2][0]=1;
        glider[2][1]=1;
        glider[2][2]=1;
    }

    cout<<"グライダーを"<<STEPS<<"ステップ実行します。続行するには Enter を押してください...";
    cin.get();
    run_simulation(glider, "Glider (グライダー)");

    cout<<"シミュレーション終了。"<<endl;
    return 0;
}