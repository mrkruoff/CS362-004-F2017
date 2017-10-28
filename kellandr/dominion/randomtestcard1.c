/* 	Author: 	Andrius Kelly
	Date:		10/28/2017
	Description: Random test for "adventurer" card
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#ifndef NOISY_TEST
#define NOISY_TEST 1
#endif
#ifndef NUM_TESTS 
#define NUM_TESTS 1000
#endif

void validRandomGameState(struct gameState* G, int k[], int* numPlayers);
void printgameState(int k[], int kSize, int numPlayers);

int main(int argc, char* argv[]){

	int testSeed = 1000;
	if(argc == 2){
		testSeed = atoi(argv[1]);
	}
	srand(testSeed);

	struct gameState G;
    struct gameState pre;
    int k[10];
    int numPlayers;

    validRandomGameState(&G, k, &numPlayers,);


	//run series of tests with valid random gamestates
	for(int i=0; i < NUM_TESTS; i++){

	}


	return 0;
}






// ----------------------------FUNCTIONS-----------------------------

//prints gamestate Initializers
void printgameState(int k[], int kSize, int numPlayers){
	printf("numPlayers: %d ,  seed: %d\nk[%d]:", numPlayers, gameSeed, kSize);
	for(int i=0; i<kSize; i++){
		printf(" %d", k[i]);
	}
	printf("\n");
}


/* initializes a random gamestate using valid inputs. 
** k is filled with random nonrepeating enums from adventurer to treasure_map, inclusive
** gameSeed is set to rand()
** numPlayers is set between 1 and MAX_PLAYERS
*/
void validRandomGameState(struct gameState* G, int k[], int* numPlayers){
	
	int numValidCards = treasure_map - adventurer + 1;
	int cardoptions[numValidCards];
	int i, j;

	for( i=0; i < numValidCards; i++){
		cardoptions[i] = adventurer + i;
	}
	//randomly populate k without repitition
	for( i=0; i < 10; i++){
		j = rand() % (numValidCards - i) + i;
		k[i] = cardoptions[j];
		cardoptions[j] = cardoptions[i];
	}

	*numPlayers = rand() % MAX_PLAYERS + 1;
	*gameSeed = rand();

	initializeGame(*numPlayers, k, *gameSeed, G);
}

