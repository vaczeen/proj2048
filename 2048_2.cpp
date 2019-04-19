#include <iostream>
#include "windows.h"
#include <conio.h>
#include<ctime>
#include<unistd.h>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>

using namespace std;

int mat[6][16];
int g=0,bul=1,l=0,r;
int score = 0; 
void gotoxy(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void resetb(){
     for(int j=0;j<16;j++){
             for(int i=0;i<6;i++){mat[i][j]=0;}

             }
}

void drawp(int x,int y){
	if(x>=0&x<6&y>=0&y<16){mat[x][y]=1;}
}

void drawc(int x,int y){
	drawp(1+x,0+y);
	drawp(0+x,1+y);drawp(1+x,1+y);drawp(2+x,1+y);
	drawp(1+x,2+y);
	drawp(0+x,3+y);drawp(1+x,3+y);drawp(2+x,3+y);
}

int getr(){
	int n;
	if(rand()%2==0){n=0;}else{n=3;}
  return n;
}

HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
int index=1;
    void colorit(int col){
        SetConsoleTextAttribute( hstdout, col );
    }






int showMenu();

DWORD WINAPI ThreadFn(LPVOID vpParam){
	while (1) {
		for(int i=8;i<=190;i++)
            {
               if(GetAsyncKeyState(i)==-32767){
               if(i==37){l=0;}else if(i==39){l=3;}
               }
            }
	}
	return 0;
}






int board[4][4];
int dirline[] = {1,0,-1,0};
int dirColumn[] = {0,1,0,-1};

pair<int , int > generateUnoccupiedPosition(){
	int occupied = 1, line, column;
	while (occupied){
		line = rand()%4;
		column = rand()%4;
		if(board[line][column] == 0)
			occupied = 0;
	}
	return make_pair(line, column);
}
void addPiece(){
	pair<int , int > pos = generateUnoccupiedPosition();
	board[pos.first][pos.second] = 2;
}

void newGame(){
	for(int i = 0;i < 4;++i)
		for(int j = 0;j < 4 ;++j)
			board[i][j] = 0;
	addPiece();
}

void printUI(){
	system("cls");
	for(int i = 0; i<4 ;++i){
		for(int j = 0; j<4 ;++j){
			if(board[i][j]==0)
				cout <<setw(4)<< ".";
			else
				cout <<setw(4)<< board[i][j];
		}
		cout << "\n";
	}
	cout << "n: newGame, q:quit,  w: up, s:down d:right, a: left \n";
	cout << "your score = " << score << endl;
}
bool canDoMove(int line, int column, int nextLine, int nextColumn){
	if(nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >=4
    || (board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0))
		return false;
	return true;
}

void applyMove(int direction){
	int startLine = 0, startColumn = 0 , lineStep = 1 , columnStep = 1;
	if(direction == 0){
		startLine = 3;
		lineStep = -1;
	}
	if(direction == 1){
		startColumn = 3;
		columnStep = -1;
	}
	int movePossible , canAddPiece=0;
	do{
		movePossible=0;
		for(int i = startLine; i>= 0 && i<4 ; i += lineStep)
			for(int j = startColumn; j>= 0 && j<4 ;j += columnStep){
				int nextI = i + dirline[direction], nextJ = j + dirColumn[direction];

				if(board[i][j] && canDoMove(i, j, nextI, nextJ)){
					board[nextI][nextJ] += board[i][j];
					board[i][j] = 0;
					movePossible = canAddPiece = 1;
					score+=((log2(board[nextI][nextJ]))-1)*board[nextI][nextJ];
				}
			}

		printUI();
	}while (movePossible);

	if (canAddPiece)
		addPiece();
    }



void startGame(){
	system("cls");
		srand(time(0));
	char commandToDir[128];
	commandToDir['s'] = 0;
	commandToDir['d'] = 1;
	commandToDir['w'] = 2;
	commandToDir['a'] = 3;
	newGame();
	while (true){
		printUI();
		char command;
		cin >> command;
		if(command == 'n')
			newGame();
		else if(command == 'q')
			break;
		else {
			int currentDirection = commandToDir[command];
			applyMove(currentDirection);
		}
	}
    

}

int key;
int showMenu(){
    int ret=1;
    system("cls");

        key=0;
        system("cls");
        while(key!=13){
        gotoxy(3,3);
        colorit(15);
        cout<<"2048 GAME";//cout<<key<<"---"<<index;
        gotoxy(3,4);
        cout<<"================";
        gotoxy(3,5);
        colorit(15);
        if(index==1){colorit(12);}
        cout<<"START GAME";
        gotoxy(3,6);
        colorit(15);
    	if(index==2){colorit(12);}
        cout<<"EXIT";
        gotoxy(20,12);
        colorit(15);cout<<"By:CPE 61";colorit(15);
        gotoxy(0,0);
        
        key=getch();
        if(key==80){index++;}
        else if(key==72){index--;}
        if(index==5){index=1;}
        if(index==0){index=4;}
        }
        if(index==1){
                startGame();
        }
      

        else if (index==2){
                ret=1;
                system("cls");
             cout<<"GOOD BEY";
        }
    return ret;
}
int main()
{
    showMenu();
    return 0;
}

