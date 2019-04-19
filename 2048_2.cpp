#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iomanip>

#include <stack>
#include <vector>

using namespace std;

int score=0;//score ???

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

	public:
	void play_game();
	play(){
		

	}
};

void play :: instructions(){
	cout<<"\nInstructions for playing 2048 are:: \n"<<endl;
	cout<<"For moving tiles enter \nw-move up/na-move left\nd-move right\ns-move down\n"<<endl;
	cout<<"When two tiles with same number touch, they merge into one. \nWhen 2048 is created, the player wins!\n"<<endl;

	cout << "maximum 5 undo operations are supported\n";
	display();
}

int play :: random_index(int x){
	int index;
	index=rand()%x + 0;
	return index;
}

void play :: lose_display(){
	system("clear");
	cout<<"\t\t\tGAME OVER\n\n";
	cout<<"Your final score is "<<score<<"\n\n";
	cout<<"Thanks for trying!!!\n\n";
	cout<<"\t\t\tA msdeep14 CREATION\n\n";
	exit(0);
}

void play :: restart(){
	char ch;
	cout<<"\nAre you sure to restart the game??\n\n";
	cout<<"enter y to restart and n to continue.\n\n";
	cin>>ch;
	if(ch=='y'){
		score=0;
		undo_score=0;
		undo_stack = stack<vector<vector<int> > >();
		score_stack = stack<int>();
		initialize();
	}
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