#ifndef INCLUDED_GLOBAL
#define INCLUDED_GLOBAL
#include"global.hpp"
#endif
#include"minesweeper.hpp"

#define BOMB '*'
#define FLAG '!'
#define UNDETERMINED '?'
#define UNFLIPPED '_'


const int dx[8]={-1,-1,-1,0,0,1,1,1},dy[8]={-1,0,1,-1,1,-1,0,1};

// char stoc(int x){
//     switch(x){
//         case -3: return UNDETERMINED;
//         case -2: return FLAG;
//         case -1: return BOMB;
//         case 0 ... 9: return char(x+48);
//         default: throw_error("Undefined grid state.");
//     }
// }
void Board::init(int n,int m,int tot,int seed){
    maxx=n;maxy=m;tot_bomb=tot;
    srand(seed);
    if(!tot_bomb) tot_bomb=rand()%((maxx+1)*(maxy+1))+1;
    for(int i=0;i<tot_bomb;i++){
        int x=rand()%maxx;
        int y=rand()%maxy;
        if(!inside(x,y)||real[x][y]==BOMB) continue;
        real[x][y]=BOMB;
    }
    for(int i=0;i<maxx;i++){
        for(int j=0;j<maxy;j++){
            map[i][j]=UNFLIPPED;
            if(real[i][j]==BOMB) continue;
            real[i][j]='0';
            for(int k=0;k<8;k++){
                int x=i+dx[k],y=j+dy[k];
                if(!inside(x,y)) continue;
                real[x][y]++;
            }
        }
    }
    tot_unflipped=maxx*maxy;
}
void Board::tick(int op,int x,int y){
    switch(op){
        case LEFT_CLICK:
            if(real[x][y]==BOMB) state=LOSE;
            else flip(x,y);
            printLog("tick: left click\n");
            break;
        case RIGHT_CLICK: change(x,y);printLog("tick: right click\n");break;
        case DOUBLE_CLICK:
            if(judge(x,y)){
                for(int i=0;i<8;i++){
                    int nowx=x+dx[i],nowy=y+dy[i];
                    if(!inside(nowx,nowy)) continue;
                    if(map[x][y]==FLAG) continue;
                    if(real[x][y]==BOMB) state=LOSE;
                    else flip(x,y);
                }
            }printLog("tick: double click\n");
            break;
        default: printError("Error: Undefined Move.\n");
    }
}
void Board::end(){
    filpAll();
}
void Board::flip(int x,int y){
    if(state==GOING&&(map[x][y]!=UNFLIPPED||real[x][y]==BOMB)) return;
    map[x][y]=real[x][y];
    if(state==GOING){
        if(tot_unflipped==tot_bomb) state=WIN;
        tot_unflipped--;
    }
    for(int i=0;i<8;i++){
        int nowx=x+dx[i],nowy=y+dy[i];
        if(inside(nowx,nowy)) continue;
        flip(nowx,nowy);
    }
}
bool Board::judge(int x,int y){
    int cnt=0;
    for(int i=0;i<8;i++){
        int nowx=x+dx[i],nowy=y+dy[i];
    }
}
void Board::change(int x,int y){
    switch(map[x][y]){
        case UNFLIPPED: map[x][y]=FLAG;printLog("change: _ to !\n");break;
        case FLAG: map[x][y]=UNDETERMINED;printLog("change: ! to ?\n");break;
        case UNDETERMINED: map[x][y]=UNFLIPPED;printLog("change: ? to _\n");break;
        default: printError("Undefined map state.\n");
    }printLog("change");
}
void Board::filpAll(){
    for(int i=0;i<maxx;i++) memcpy(map[i],real[i],sizeof(char)*maxy);
}
#undef BOMB
#undef FLAG
#undef UNDETERMINED
#undef UNFLIPPED