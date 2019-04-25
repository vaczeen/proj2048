#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include <stack>
#include <vector>
#include <windows.h>
#include <string>
#include<fstream>
//#include "windows.h"
#include <conio.h>
#include<iostream>
#include<unistd.h>
#include<cmath>



using namespace std;

int score=0;//score ???

string name;

int undo_limit=0;// ????????

int undo_score=0;
class play{
	stack<vector<vector<int> > > undo_stack;
	stack<int> score_stack;


	int g[4][4];
	int g_copy[4][4];
	void initialize();
	void display();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	int check_full();
	int random_index(int x);
	void sum_up();
	void sum_down();
	void sum_left();
	void sum_right();
	void generate_new_index();
	int calculate_max();
	void instructions();
	int game_ends();
	void end_display();
	void win_display();
	void lose_display();
	void restart();
	void ledderbord();

	public:

	void play_game();
	
};

void play :: instructions(){
	system("cls");
	cout<<"\nInstructions for playing 2048 are:: \n"<<endl;
	cout<<"For moving tiles enter \nw-move up\na-move left\nd-move right\ns-move down\n"<<endl;
	cout<<"When two tiles with same number touch, they merge into one. \nWhen 2048 is created, the player wins!\n"<<endl;

	cout << "You can undo 1 time for per move\n";
	display();
}

int play :: random_index(int x){
	int index;
	index=rand()%x + 0;
	return index;
}

void play :: lose_display(){
	system("cls");
	cout<<"\t\t\tGAME OVER\n\n";
	cout<<"Your final score is "<<score<<"\n\n";
	cout<<"Thanks for trying!!!\n\n";
	
	ledderbord();
	exit(0);
}

void play :: restart(){
		score=0;
		undo_score=0;
		undo_stack = stack<vector<vector<int> > >();
		score_stack = stack<int>();
		initialize();
	
}

int play :: check_full(){
	int full_flag=1;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(g[i][j]==0){
				full_flag=0;
				break;
			}
		}
	}
	return full_flag;
}
void play :: win_display(){
	char ch;
	cout<<"\t\t\tYOU WON!!!\n\n";
	cout<<"Your total score is "<<score<<"\n\n";
	cout<<"Thanks for playing!!!\n\n";
	ledderbord();
	cout<<"Do you want to continue???\n";
	cout<<"Enter y to continue and n to quit\n\n";
	cin>>ch;
	while(ch!='y'&&ch!='n'){
		system("cls");
		cout<<"Wrong input\n";
		cout<<"Do you want to continue???\n";
		cout<<"Enter y to continue and n to quit\n\n";
		cin>>ch;
	}
	if(ch=='n'){
		exit(0);
	}
	else if(ch=='y'){
		play_game();
	}
}

int play :: calculate_max(){
	int i,j;
	int max=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(g[i][j]>max){
				max=g[i][j];
			}
		}
	}
	return max;
}

void play :: end_display(){
	system("cls");
	cout<<"\nYour final score is :: "<<score<<endl<<endl;
	cout<<"Thanks for trying!!!\n\n";
	cout<<"Good Bye!!!\n"<<endl;
	ledderbord();
	exit(0);
}

int play :: game_ends(){
	int i,j,flag=1;
	for(i=0;i<4;i++){
		for(j=0;j<3;j++){
			if(g[i][j]==g[i][j+1]){
				flag=0;
				break;
			}
		}
		if(flag==0){
				break;
		}
	}
	if(flag==1){
		for(i=0;i<3;i++){
			for(j=0;j<4;j++){
				if(g[i][j]==g[i+1][j]){
					flag=0;
					break;
				}
			}
			if(flag==0){
				break;
			}
		}
	}
	return flag;
}


void play :: generate_new_index(){
	int flag=1;
	if(!check_full()){
		while(flag){
			int i=random_index(4);
			int j=random_index(4);
			if(g[i][j]==0){
				int y=rand()%10+0;
				if(y<6){
					g[i][j]=2;
				}else{
					g[i][j]=4;
				}
				flag=0;
			}
		}
	}
}

void play :: initialize(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			g[i][j]=0;
			g_copy[i][j]=0;
		}
	}
	int i=random_index(4);
	int j=random_index(4);
	g[i][j]=2;
	i=random_index(4);
	j=random_index(4);
	g[i][j]=2;
	display();
}


void play :: move_up(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(!g[j][i]){
				for(int k=j+1;k<4;k++){
					if(g[k][i]){
						g[j][i]=g[k][i];
						g[k][i]=0;
						undo_limit=0;
						break;
					}
				}
			}
		}
	}
}

void play :: move_down(){
	for(int i=0;i<4;i++){
		for(int j=3;j>=0;j--){
			if(!g[j][i]){
				for(int k=j-1;k>=0;k--){
					if(g[k][i]){
						g[j][i]=g[k][i];
						g[k][i]=0;
						undo_limit=0;
						break;
					}
				}
            }
        }
    }
}

void play :: move_left(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(!g[i][j]){
				for(int k=j+1;k<4;k++){
					if(g[i][k]){
						g[i][j]=g[i][k];
						g[i][k]=0;
						undo_limit=0;
						break;
					}
				}
			}
		}
	}
}

void play :: move_right(){
	for(int i=0;i<4;i++){
		for(int j=3;j>=0;j--){
			if(!g[i][j]){
				for(int k=j-1;k>=0;k--){
					if(g[i][k]){
						g[i][j]=g[i][k];
						g[i][k]=0;
						undo_limit=0;
						break;
					}
				}
			}
		}
	}
}

void play :: sum_up(){
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			if(g[j][i] && g[j][i]==g[j+1][i]){
				g[j][i]=g[j][i] + g[j+1][i];
				g[j+1][i]=0;
				score+=g[j][i];
				undo_score+=g[j][i];
			}
		}
	}
}

void play :: sum_down(){
	for(int i=0;i<4;i++){
		for(int j=3;j>0;j--){
			if(g[j][i] && g[j][i]==g[j-1][i]){
				g[j][i]=g[j][i] + g[j-1][i];
				g[j-1][i]=0;
				score+=g[j][i];
				undo_score+=g[j][i];
			}
		}
	}
}

void play :: sum_left(){
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			if(g[i][j] && g[i][j]==g[i][j+1]){
				g[i][j]=g[i][j] + g[i][j+1];
				g[i][j+1]=0;
				score+=g[i][j];
				undo_score+=g[i][j];
			}
		}
	}
}

void play :: sum_right(){
	for(int i=0;i<4;i++){
		for(int j=3;j>0;j--){
			if(g[i][j] && g[i][j]==g[i][j-1]){
				g[i][j]=g[i][j] + g[i][j-1];
				g[i][j-1]=0;
				score=score + g[i][j];
				undo_score+=g[i][j];
			}
		}
	}
}


void play :: play_game(){
	int flag=0;
	char choice,ch;
	
	
	system("cls");
	initialize();
	cin>>choice;
	
	
	
	while((choice=='w' || choice=='a' || choice=='s' || choice=='d' || choice=='q' || choice=='i' || choice=='u' || choice=='r'||
	 choice=='W' || choice=='A' || choice=='S' || choice=='D' || choice=='Q' || choice=='I' || choice=='U' || choice=='R')){
		if(choice != 'u' || choice != 'U'){
			vector<vector <int> > current_copy;
			current_copy.resize(4);
			for(int m = 0;m<4; m++){
				for(int n=0; n<4; n++){
					current_copy[m].push_back(g[m][n]);
				}
			}
			undo_stack.push(current_copy);
		}

	

	switch(choice){
		//????????????????
		case 'W':
			undo_score=0;
			move_up();
			sum_up();
			move_up();
			generate_new_index();
			system("cls");
			display();
			score_stack.push(undo_score);
			break;
		case 'w':
			undo_score=0;
			move_up();
			sum_up();
			move_up();
			generate_new_index();
			system("cls");
			display();
			score_stack.push(undo_score);
			break;
		//????????????????
		case 'S':
			undo_score=0;
			move_down();
			sum_down();
			move_down();
			generate_new_index();
			system("cls");
			display();
			score_stack.push(undo_score);
			break;
		case 's':
			undo_score=0;
			move_down();
			sum_down();
			move_down();
			generate_new_index();
			system("cls");
			display();
			score_stack.push(undo_score);
			break;
		//??????????????
		case 'A':
			undo_score=0;
			move_left();
			sum_left();
			move_left();
			generate_new_index();
			system("cls");
			display();
			score_stack.push(undo_score);
			break;
		case 'a':
			undo_score=0;
			move_left();
			sum_left();
			move_left();
			generate_new_index();
			system("cls");
			display();
			score_stack.push(undo_score);
			break;
		//??????????????
		case 'D':
			undo_score=0;
			move_right();
			sum_right();
			move_right();
			generate_new_index();
			system("cls");
			display();
			score_stack.push(undo_score);
			break;
		case 'd':
			undo_score=0;
			move_right();
			sum_right();
			move_right();
			generate_new_index();
			system("cls");
			display();
			score_stack.push(undo_score);
			break;
		//quit
		case 'Q':
			cout<<"Are you sure you want to quit??\nEnter y to quit and n to continue!\n"<<endl;
			cin>>ch;
			while(ch!='y'&&ch!='n'&& ch!='Y'&&ch!='N'){
				system("cls");
				cout<<"Wrong input\n";
				cout<<"Are you sure you want to quit??\n";
				cout<<"Enter y to quit and n to continue!\n\n";
				cin>>ch;
			}
			if(ch=='y' || ch == 'Y'){
				end_display();
			}
			system("cls");
			display();
		case 'q':
			cout<<"Are you sure you want to quit??\nEnter y to quit and n to continue!\n"<<endl;
			cin>>ch;
			while(ch!='y'&&ch!='n'&& ch!='Y'&&ch!='N'){
				system("cls");
				cout<<"Wrong input\n";
				cout<<"Are you sure you want to quit??\n";
				cout<<"Enter y to quit and n to continue!\n\n";
				cin>>ch;
			}
			if(ch=='y' || ch == 'Y'){
				end_display();
			}
			system("cls");
			display();
			
			
			break;
		//?????????????????
		case 'I':
			instructions();
			break;
		case 'i':
			instructions();
			break;
		//restart game
		case 'R':
			char chh;
			cout<<"\nAre you sure to restart the game??\n\n";
			cout<<"enter y to restart and n to continue.\n\n";
			cin>>chh;
			while(chh!='y'&&chh!='n'&&chh!='Y'&&chh!='N'){
				system("cls");
				cout<<"Wrong input\n";
				cout<<"Are you sure to restart the game??\n";
				cout<<"Enter y to restart and n to continue.\n\n";
				cin>>chh;
			}
			if(chh=='y'|| chh=='Y'){
				restart();
			}
			system("cls");
			display();
			break;

		case 'r':
			char ch;
			cout<<"\nAre you sure to restart the game??\n\n";
			cout<<"enter y to restart and n to continue.\n\n";
			cin>>ch;
			while(ch!='y'&&ch!='n'&&ch!='Y'&&ch!='N'){
				system("cls");
				cout<<"Wrong input\n";
				cout<<"Are you sure to restart the game??\n";
				cout<<"Enter y to restart and n to continue.\n\n";
				cin>>ch;
			}
			if(ch=='y'||ch == 'Y'){
				restart();
			}
			system("cls");
			display();
			break;
			
		
			
		
		//??????????????
		case 'U':
			if(undo_limit < 1){
				if(!undo_stack.empty()){
					vector<vector<int> > previous_copy = undo_stack.top();
					undo_stack.pop();
					for(int m=0;m<4;m++){
						for(int n=0;n<4;n++){
							g[m][n]=previous_copy[m][n];
						}
					}
					score -= score_stack.top();
					score_stack.pop();
					undo_limit += 1;
					system("cls");
					display();
				}
				
			}else{
				system("cls");
				display();
				cout<<"\n\nYou cannot undo !!!\n"<<endl;
			}

		case 'u':
			if(undo_limit < 1){
				if(!undo_stack.empty()){
					vector<vector<int> > previous_copy = undo_stack.top();
					undo_stack.pop();
					for(int m=0;m<4;m++){
						for(int n=0;n<4;n++){
							g[m][n]=previous_copy[m][n];
						}
					}
					score -= score_stack.top();
					score_stack.pop();
					undo_limit += 1;
					system("cls");
					display();
				}
				
			}else{
				system("cls");
				display();
				cout<<"\n\nYou cannot undo !!!\n"<<endl;
			}
	}
	//?????????????? ?????????? 2048 ?????
	int find_max=calculate_max();
	if(find_max==2048){
		win_display();
	}

		if(check_full()){
			if(game_ends()){
				lose_display();
			}
		}
		cout<<"enter choice: "<<endl;
		cin>>choice;
		
		while(choice!='w'  && choice!='s'  && choice!='d'  && choice!='a' && choice!='q' && choice!='i' && choice!='u' && choice!='r'&&
			choice!='W'  && choice!='S'  && choice!='D'  && choice!='A' && choice!='Q' && choice!='I' && choice!='U' && choice!='R'){
			cout<<"\nYou had entered the wrong choice!\nPlease enter correct choice to continue!"<<endl;
			cin>>choice;
			
		}
	}
}

void play :: display(){
	cout<<"\n\t\t\t\t\t\t\t 2048\n\n";
	cout<<"  Player :: "<<name<<endl<<endl;
	cout<<"  score  :: "<<score<<endl<<endl;
	for(int i=0;i<4;i++){
		cout<<"                       ";
		for(int j=0;j<4;j++){
			cout<<setw(8)<<g[i][j]<<setw(8)<<"|"<<setw(8);
		}
		cout<<endl<<endl<<endl;
	}
	cout<<"\n\n\n";
	cout<<"\t\t\t\t\t\t\t\t\tr-restart\n\tw\t\t\t\t\t\t\t\ti-instructions\na\ts\td\t\t\t\t\t\t\tq-quit  u-undo\n\n";
}

void play :: ledderbord(){
	cout << "\t\t\tLedderbord\n\n\n";
	ofstream x("led.txt",ios::app);
	x << name << "  ::  "<<score<<"\n";
	x.close();
	ifstream y;
	y.open("led.txt");
	string textline;
	while(getline(y,textline)){
		cout << textline <<"\n";
	}
	y.close();
	
}

void Start(){
	system("cls");
	play p;
	srand(time(NULL));
	cout << "Wellcome to 2048 \nPlease enter your name: ";
	cin >> name;
	p.play_game();
}

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
int index=1;
    void colorit(int col){
        SetConsoleTextAttribute( hstdout, col );
    }

void exitGame(){
system("cls");
gotoxy(3,3);cout<<"GOOD BYE!";
colorit(15);
Sleep(2500);
}

int key;
int showMenu(){
    
    system("cls");

        key=0;
        system("cls");
        while(key!=13){
        gotoxy(3,3);
        colorit(15);
        cout<<"2048 GAME";
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
        colorit(15);cout<<"By:CPECMU 61";colorit(15);
        gotoxy(0,0);
        
        key=getch();
        if(key==80){index++;}
        else if(key==72){index--;}
        if(index==3){index=1;}
        if(index==0){index=2;}
        }
        if(index==1){
                Start();
        }
      

        else if (index==2){
                
            exitGame();
        }
    
}


int main(){
	showMenu();
	return 0;
}