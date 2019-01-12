/*
 * 	playPokerMain.c
 *	This is a simple program that plays a draw poker game. You're dealt 5 cards then you get to choose which cards to keep
 *  and which cards to give up. Then you get new cards and your payout is set based on the value of your hand. You're then given
 *  the option to continue.
 *  Created on: Jan 12, 2019
 *      Author: Adriel Perkins
 */


#include "playPoker.h"


//Getting into the practice of always prototyping your functions for consistency. Default is integer, but best to declare anyway.

void printGreeting();
int getBet();
char getSuit(int suit);
char getRank(int rank);
void getFirstHand(int cardRank[], int cardSuit[]);
void getFinalHand(int cardRank[], int cardSuit[], int finalRank[],
                  int finalSuit[], int ranksInHand[], int suitsInHand[]);
int analyzeHand(int ranksInHand[], int suitsInHand[]);


int main(int argc, const char * argv[]) {

    //declare variables that will be needed for main program
    int bet;
    int bank = 100;
    int i;
    int cardRank[5];//1 of 13 values for Ace through King
    int cardSuit[5];//1 of 4 values for clubs, diamonds, hearts, and spades
    int finalRank[5];
    int finalSuit[5];
    int ranksInHand[13];
    int suitsInHand[4];
    int winnings;
    time_t t;
    char suit, rank, stillPlaying;


    printGreeting();

    //going to make a do - while loop for the game to play dependent on how much the user wants to play

    do {
        bet = getBet();
        srand(time(&t));
        getFirstHand(cardRank, cardSuit);

        printf("Your five cards are \n");
        for (i = 0; i < 5; i++) {
            suit = getSuit(cardSuit[i]);
            rank = getRank(cardRank[i]);
            printf("Card #%d is %c %c\n", i+1, suit, rank);
        }

        //going to figure out the value of the hand by using two arrays. each array has to be zeroed out since the player can play multiple hands

        for (i=0; i <4; i++){
        	suitsInHand[i] =0;
        }

        for (i = 0; i <13; i++){
        	ranksInHand[i] = 0;
        }

        getFinalHand(cardRank, cardSuit, finalRank, finalSuit, ranksInHand, suitsInHand);

        printf("Your 5 final cards are:\n");
		for (i = 0; i < 5; ++i) {
			suit = getSuit(finalSuit[i]);
			rank = getRank(finalRank[i]);
			printf("Card #%d: %c %c\n", i+1, suit, rank);
		}



		winnings = analyzeHand(ranksInHand, suitsInHand);
		printf("You won %d!\n", bet*winnings);

		bank = bank - bet + (bet*winnings);
		printf("\nYour bank is now at %d", bank);
		printf("\nDo you want to play again? (Y/N");
		scanf(" %c", &stillPlaying);







    } while (toupper(stillPlaying) == 'Y');



    return 0;
}

//functions
//below is the printGreetting() function that prints the information you see at the very beginning of the game.

void printGreeting(){
	printf("Greetings!!! - Are you ready to play some Poker?!\n");
	printf("*************************************************\n");
	printf("Here are the rules...\n");
	printf("You start with 100 chips, and make a bet from 1 to 5 chips.\n");
	printf("You're dealt 5 cards, and then you get to choose which cards you want to keep and which ones you want to get rid of. \n");
	printf("You want to make the best possible hand so that you can WIN!!\n");
	printf("Here is the table for winnings if you bet 1 chip.\n\n");
	printf("\nPair\t\t1 chips");
	printf("\nTwo pairs\t\t2 chips");
	printf("\nThree of a kind\t\t3 chips");
	printf("\nA Straight\t\t4 chips");
	printf("\nA flush\t\t5 chips");
	printf("\nA full house\t\t8 chips");
	printf("\nFour of a kind\t\t10 chips");
	printf("\nA Straight Flush\t\t20 chips");
	printf("\nNow, it's time to have some fun!!");

}

//below is the getFirstHand() function that deals the first 5 cards of the game.

void getFirstHand(int cardRank[], int cardSuit[]){
	int i, j;
	int duplicateCard;

	for (i = 0; i < 5; i++){
		duplicateCard = 0;
		do {
			cardRank[i] = (rand() % 13);
			cardSuit[i] = (rand() % 4);

			for (j = 0; j < i; j++){
				if ((cardRank[i] == cardRank[j]) && (cardSuit[i] == cardSuit[j])){
					duplicateCard = 1;
				}
			}
		} while (duplicateCard == 1);

	}
}

//below is the getSuit() function that changes the integer value to a character that makes up the suit.

char getSuit(int suit){
	switch (suit)
	{
	case 0:
		return ('c');
	case 1:
		return('d');
	case 2:
		return('h');
	case 3:
		return('s');
	}
}

//below is the getRank() function that changes the integer value to a character that makes up the rank.

char getRank(int rank) {
	switch (rank)
		{
		case 0:
			return ('A');
		case 1:
			return('2');
		case 2:
			return('3');
		case 3:
			return('4');
		case 4:
			return('5');
		case 5:
			return('6');
		case 6:
			return('7');
		case 7:
			return('8');
		case 8:
			return('9');
		case 9:
			return('10');
		case 10:
			return('J');
		case 11:
			return('Q');
		case 12:
			return('K');
		}
}

//below is the getBet() function that gets the users bet between 1 and 5 chips

int getBet(){
	int bet;

	do {
		printf("How much do you want to bet? (1 through 5 chips, 0 quits the game..)\n");
		scanf(" %d", &bet);

		if(bet >=1 && bet <= 5){
			return(bet);
		}
		else if (bet == 0){
			exit(1);
		}
		else{
			printf("\n\nPlease enter a bet from 1 through 5 or enter 0 to quit the game.\n");
		}
	} while((bet < 0) || (bet > 5));
}


//below is the analyzeHand() function that reviews the final hand and figures out the value of the hand.

int analyzeHand(int ranksInHand[], int suitsInHand[]){
	int consecNum = 0;
	int i, rank, suit;
	int straight = FALSE;
	int flush = FALSE;
	int four = FALSE;
	int three = FALSE;
	int pairs = 0;



	for (suit = 0; suit < 4; suit++){
		if(suitsInHand[suit] == 5){
			flush = TRUE;
		}
	}
	rank = 0;

	while (ranksInHand[rank] == 0){
		rank++;
	}

	for (; rank <13 && ranksInHand[rank]; rank++){
		consecNum++;
	}

	if (consecNum == 5){
		straight = TRUE;
	}

	for (rank = 0; rank < 13; rank++){
		if(ranksInHand[rank] == 4){
			four = TRUE;
		}
		if(ranksInHand[rank] == 3){
			three = TRUE;
		}
		if(ranksInHand[rank] == 2){
			pairs++;
		}
	}

	if(straight && flush){
		printf("You got a straight flush!!!\n\n");
		return(20);
	} else if (four){
		printf("You got four in a row!!\n\n");
		return(10);
	} else if (three && pairs == 1){
		printf("You got a full house!\n\n");
		return(8);
	} else if (flush){
		printf("You got a flush.\n\n");
		return(5);
	} else if (straight){
		printf("You got a straight.\n\n");
		return(4);
	} else if (three) {
		printf("You got three in a row.\n\n");
		return(3);
	} else if (pairs == 2){
		printf("You got two pairs.\n\n");
		return(2);
	} else if (pairs == 1){
		printf("You got a pair.\n\n");
		return(1);
	} else {
		printf("You got a high card. LOL. Because in all reality, you're not playing against anyone. ");
		return(0);
	}




}


//below is the getFinalHand() function that looks through your 5 cards and asks you if you want to keep the card. If you say no, you get a new card.

void getFinalHand(int cardRank[], int cardSuit[], int finalRank[], int finalSuit[], int ranksInHand[], int suitsInHand[]){
	int i, j, duplicateCard;
	char suit, rank, ans;

	for(i = 0; i < 5; i++){
		suit = getSuit(cardSuit[i]);
		rank = getRank(cardRank[i]);
		printf("Do you want to keep card #%d: %c%c ?", i+1, suit, rank);
		printf("\nAnswer Y for Yes and N for No.\n");
		scanf(" %c", &ans);
		if(toupper(ans) == 'Y'){
			finalRank[i] = cardRank[i];
			finalSuit[i] = cardSuit[i];
			ranksInHand[finalRank[i]]++;
			suitsInHand[finalSuit[i]]++;
			continue;
		} else if (toupper(ans) == 'N'){
			duplicateCard = 0;
			do{
				duplicateCard = 0;
				finalRank[i] = (rand() % 13);
				finalSuit[i] = (rand() % 4);

				for(j= 0; j < 5; j++){
					if ((finalRank[i] == cardRank[j]) && (finalSuit[i] == cardSuit[j])){
						duplicateCard =1;
					}
				}

			} while(duplicateCard == 1);
			ranksInHand[finalRank[i]]++;
			suitsInHand[finalSuit[i]]++;
		}
	}
}








