#include<stdio.h>
#include<stdlib.h>

void drawBoard();
char checkWinner();
int newGame();
void clearRecords();

//game rom
char boardRecords[9]=
{
	'1','2','3',
	'4','5','6',
	'7','8','9'
};

//result states
enum results{
	noWinner,playerWins,draw
};

//to select the turn
char player=1;
//store games scores
int score[2]={0,0};

int main(){
	//store the winner player, 0 == draw
	int winner=0;

	while(1){
		//start new game
		winner=newGame();

		// store the game score
		if(winner==1)
			score[0]++;
		else if(winner==2)
			score[1]++;

		//get the user decision
		int decision='0';
		printf("Press(1)for new game,(2) to reset score and any key else to end the game: ");
		scanf("%d",&decision);

		if(decision==1)
			clearRecords();
		else if(decision==2){
			score[0]=0;score[1]=0;
			clearRecords();
		}else
			return 0;
	}
}

int newGame(){

	int input=0,validInput=1;
	enum results gameResult=noWinner;

	for(char i=0 ; i<9 ; i++){

		//draw new board
		drawBoard();

		//loop untill receive a valid input
		do{
			validInput=1;
			printf("\nPlayer %d turn, please enter a cell number: ",player);
			scanf("%d",&input);

			//check if the cell is empty
			if((input+'0') != boardRecords[input-1]){ //input+'0' to conver int to char
				validInput=0;
				printf("This cell isn't empty.\n");
			}

		}while(!validInput);


		//Record the input and move to the next player 
		if(player==1){
			boardRecords[input-1]='X';
			player++;
		}else if(player==2){
			boardRecords[input-1]='O';
			player--;
		}

		//check if there's a winner
		gameResult=checkWinner();
		
		if(gameResult==playerWins){
			//get the previous player id
			player=(player==1?2:1);
			printf("Player %d Wins!!\n",player);
			return player;
		}else if(gameResult==draw){
			printf("Game draw :(\n");
			return 0;
		}
	}
}
void clearRecords(){
	for(char i=0 ; i<9 ; i++){
		boardRecords[i]=i+49;
	}
}

void drawBoard(){
	system("clear"); //for linux, for windows use "cls" instead of "clear". 
	printf("Player1 [%d-%d] Player2\n",score[0],score[1]);
	for(char i=0 ; i<3 ; i++){

		if(i==0){
			printf(" _________________ \n");
			printf("|     |     |     |\n");
		}

		printf("|  %c  |  %c  |  %c  |",boardRecords[i*3],boardRecords[i*3+1],boardRecords[i*3+2]);
		printf("\n|_____|_____|_____|\n");

		if(i!=2){
			printf("|     |     |     |\n");
			
		}
		
	}

}

//function to check game rules
char checkWinner(){

	//check winner rules
	//cross × matched ?
	if((boardRecords[0]==boardRecords[4]&&boardRecords[4]==boardRecords[8])||
	   (boardRecords[2]==boardRecords[4]&&boardRecords[4]==boardRecords[6])){
		return playerWins;
	}

	//traverse all cols. and rows to check matched one
	for(char i=0 ; i<3 ; i++){
		if((boardRecords[i*3]==boardRecords[i*3+1]&&boardRecords[i*3+1]==boardRecords[i*3+2])||  //row matched ?
		   (boardRecords[i]==boardRecords[i+3]&&boardRecords[i+3]==boardRecords[i+6])){		// col. matched ?
			return playerWins;
		}
	}

	//check draw rules
	//check if all cells don't contain X-O
	for(char i=0 ; i<9 ; i++){
		if(boardRecords[i]!= 'X' && boardRecords[i]!= 'O' ){
			return noWinner;
		}	
	}

	//if all cells contain X-O
	return draw;

}