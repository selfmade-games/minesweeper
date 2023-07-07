#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
typedef std::string str;

#define WIN 0
#define LOSE 1
#define GOING 2

#define LEFT_CLICK 0
#define RIGHT_CLICK 1
#define DOUBLE_CLICK 2

FILE* stdlog=fopen("minesweeper.log","w");
int totlog=0;

void printLog(str e){
    e="("+std::to_string(totlog)+") "+e;
    fprintf(stdlog,e.c_str());
    totlog++;
}
void printError(str e){
    e="("+std::to_string(totlog)+") "+e;
    fprintf(stderr,e.c_str());
    totlog++;
}