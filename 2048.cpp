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
void play :: win_display(){
	char ch;
	cout<<"\t\t\tYOU WON!!!\n\n";
	cout<<"Your total score is "<<score<<"\n\n";
	cout<<"Do you wish to continue???\n";
	cout<<"Enter y to continue and n to quit\n\n";
	cin>>ch;
	if(ch=='n'){
		end_display();
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
	system("clear");
	cout<<"\nYour final score is :: "<<score<<endl<<endl;
	cout<<"Thanks for trying!!!\n\n";
	cout<<"Good Bye!!!\n"<<endl;
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
						break;
					}
				}
			}
		}
	}
}