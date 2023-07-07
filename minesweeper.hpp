#ifndef INCLUDED_MINESWEEPER_HPP
#define INCLUDED_MINESWEEPER_HPP

#define BOMB '*'
#define FLAG '!'
#define UNDETERMINED '?'
#define UNFLIPPED '_'

class Board{
    #define MAXN 1005
public:
    void init(int n,int m,int tot,int seed);
    void tick(int op,int x,int y);
    void end();
    char getMap(int x,int y){return map[x][y];}
private:
    char map[MAXN][MAXN],real[MAXN][MAXN];
    int state,maxx,maxy,tot_unflipped,tot_bomb;
    bool inside(int x,int y){return 0<=x&&x<maxx&&0<=y&&y<maxy;}
    void flip(int x,int y);
    bool judge(int x,int y);
    void change(int x,int y);
    void filpAll();
    #undef MAXN
};

#undef BOMB
#undef FLAG
#undef UNDETERMINED
#undef UNFLIPPED

#endif