/**
* @file yamsStat.c
* @brief This file contains a simulation to record how many tosses are needed 
*        to score each lower section categorie of the Yams/Yahtzee dice game.
* @author Servan CHARLOT
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
* @def N
* @brief Number of successful toss to do in each categorie.
*/
#define N 10000

// Prototypes
int electGoal(int dice[5], int *max);
void toss(int dice[5], int toToss[5]);
double yams_FOAK_TOAK_full(int fig, FILE *f);
void insertion_sort(int tab[5]);
double straight(FILE *f, int largeStraight);

/**
* @fn int main(int argc, char const *argv[])
* @brief Perform the simulations.
* @param argc Unused.
* @param argv Unused.
*/

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	FILE *fy = fopen("yams.data", "w");
	FILE *ffk = fopen("FOAK.data", "w");
	FILE *ftk = fopen("TOAK.data", "w");
	FILE *ff = fopen("full.data", "w");
	FILE *fss = fopen("ss.data", "w");
	FILE *fls = fopen("ls.data", "w");
	if (fy == NULL || ffk == NULL || ftk == NULL || ff == NULL || fss == NULL|| fls == NULL) return 1;

	double counts;
	double result;
	int i;

	printf("N = %d\n", N);

	// Running TOAK calculation
	counts = 0;
	for (i = 0; i < N; i++) {
		result = yams_FOAK_TOAK_full(3,ftk);
		counts += result;
	}
	result = counts/N;
	printf("Three Of A King: Average number of tosses: %f\n", result);

	// Running Full calculation
	counts = 0;
	for (i = 0; i < N; i++) {
		result = yams_FOAK_TOAK_full(1,ff);
		counts += result;
	}
	result = counts/N;
	printf("Full: Average number of tosses: %f\n", result);

	// Running FOAK calculation
	counts = 0;
	for (i = 0; i < N; i++) {
		result = yams_FOAK_TOAK_full(4,ffk);
		counts += result;
	}
	result = counts/N;
	printf("Four Of A King: Average number of tosses: %f\n", result);

	// Running small straight calculation
	counts = 0;
	for (i = 0; i < N; i++) {
		result = straight(fss,0);
		counts += result;
	}
	result = counts/N;
	printf("Small Straight: Average number of tosses: %f\n", result);

	// Running large straight calculation
	counts = 0;
	for (i = 0; i < N; i++) {
		result = straight(fls,1);
		counts += result;
	}
	result = counts/N;
	printf("Large Straight: Average number of tosses: %f\n", result);

	// Running Yams calculation
	counts = 0;
	for (i = 0; i < N; i++) {
		result = yams_FOAK_TOAK_full(5,fy);
		counts += result;
	}
	result = counts/N;
	printf("Yams: Average number of tosses: %f\n", result);

	fprintf(fy, "\n");
	fprintf(ffk, "\n");
	fprintf(ftk, "\n");
	fprintf(ff, "\n");
	fprintf(fss, "\n");
	fprintf(fls, "\n");
	fclose(fy);
	fclose(ffk);
	fclose(ftk);
	fclose(ff);
	fclose(fss);
	fclose(fls);
	return 0;
}

/**
* @fn int electGoal(int dice[5], int *max)
* @brief In the dice hand, searches which number is the most present
*        and in which quantity.
* @param[in, out] dice Array containing the dice hand.
* @param[out] max After the exectution, contains in which quantity the goal die is present.
* @return The value of the most present die.
*/
int electGoal(int dice[5], int *max) {
	int i;
	int goal = 0;
	int occurences[7];
	*max = 0;
	for (i = 0; i < 7; i++) occurences[i] = 0;
	// Counting the occurence of each number
	for (i = 0; i < 5; i++) {
		(occurences[dice[i]])++;
	}
	// Searching the number that is the most present
	for (i = 1; i < 7; i++) {
		if (occurences[i] > *max) {
			*max = occurences[i];
			goal = i;
		}
	}
	return goal;
}

/**
* @fn void toss(int dice[5], int toToss[5])
* @brief Toss the dice as indicated in the *toToss array.
* @param[in, out] dice Array containing the dice hand.
* @param[in] toToss Array indicating which die to toss. (Contains 1 if toss, 0 otherwise).
*/
void toss(int dice[5], int toToss[5]) {
	int i;
	for (i = 0; i < 5; i++) {
		if (toToss[i]) dice[i] = (int)(rand()%6)+1;
	}
}

/**
* @fn double yams_FOAK_TOAK_full(int fig, FILE *f)
* @brief Simulate the Yams, or the Four Of A King, or the Three Of A King, or the Full.
* @paraù[in] fig Indicate which simulation to run. 1=Full, 3=TOAK, 4=FOAK, 5=Yams.
* @paraù[in] f File where to output the data.
* @return How many tosses were needed to score the categorie.
*/
double yams_FOAK_TOAK_full(int fig, FILE *f) {
	int dice[5];
	int toToss[5];
	int i, goal = 0, max = 0;
	double count = 0;
	int full = 0;
	// If fig = 1, we want to simulate a full.
	if (fig == 1) {
		full = 1;
		fig = 3;
	}
	// Toss all the dice for the first time
	for (i = 0; i < 5; i++) {
		toToss[i] = 1;
	}
	while (max < fig) {
		count++;
		toss(dice, toToss);
		goal = electGoal(dice, &max);
		if (max == fig) continue;
		// Who does not match the goal and need to be tossed again
		for (i = 0; i < 5; i++) {
			if (dice[i] != goal) toToss[i] = 1;
			else toToss[i] = 0;
		}
	}
	// Special case for the full
	if (full) {
		int id1 = 0;
		int id2 = 0;
		int found = 0;
		// Select who to toss and their IDs
		while (!found) {
			electGoal(dice, &max);
			id1 = 0;
			id2 = 0;
			// The "who to toss" algo is different if we end up with 
			// a brealn, a full or a FOAK in last step.
			switch (max) {
				case 3:
					// TOAK, toss the two bad ones.
					id1 = -1;
					id2 = -1;
					for (i = 0; i < 5; i++) {
						if (dice[i] != goal) {
							toToss[i] = 1;
							if (id1 == -1) id1 = i;
							else if (id1 != -1 && id2 == -1) id2 = i;
						}
						else toToss[i] = 0;
					}
					break;
				case 4:
					// FOAK, toss the bad one and another one.
					for (i = 0; i < 5; i++) {
						if (dice[i] != goal) {
							toToss[i] = 1;
							id1 = i;
							if(id1 == 0) id2 = 1;
							else id2 = 0;
						}
						else toToss[i] = 0;
					}
					toToss[id2] = 1;
					break;
				case 5:
					// Yams, just toss the last two
					for (i = 0; i < 3; i++) toToss[i] = 0;
					toToss[3] = 1;
					id1 = 3;
					toToss[4] = 1;
					id2 = 4;
					break;
			}
			if ((dice[id1] == dice[id2]) && dice[id1] != goal){
				found = 1;
				continue;
			}			
			toss(dice, toToss);
			count++;
		}
	}
	fprintf(f, "%d;", (int)count);
	return count;
}

/**
* @fn void insertion_sort(int tab[J])
* @brief Insertion sort algorithm. More information here : https://en.wikipedia.org/wiki/Insertion_sort
* @param[in, out] tab[5] Array to sort.
*/
void insertion_sort(int tab[5]){
	int i,j,x;
	for(i = 1; i < 5; i++){
		x = tab[i];
		j = i;
		while(j > 0 && tab[j-1] > x){
			tab[j] = tab[j-1];
			j--;
		}
		tab[j] = x;
	}
}

/**
* @fn double straight(FILE *f, int largeStraight)
* @brief Simulate the Small Straight and the Large Straight.
* @param[in] f File where to output the data.
* @param[in] largeStraight 1 to simulate the LS, 0 to sumulate the SS.
* @return How many tosses were needed to score the categorie.
*/
double straight(FILE *f, int largeStraight) {
	int dice[5];
	int toToss[5];
	int chain1[5];
	int chain2[5];
	int switchToChain2;
	int i, last, chain = 0, chainMax = 0, len1, len2;
	double count = 0;
	// Toss all the dice for the first time
	for (i = 0; i < 5; i++) toToss[i] = 1;
	// Which straight to search
	if (largeStraight) largeStraight = 4;
	else largeStraight = 2;
	// Yeah I could have use another var for the small straight I know
	while(chainMax < largeStraight) {
		for (i = 0; i < 5; i++){
			chain1[i] = -1;
			chain2[i] = -1;
		}
		chain = 0;
		switchToChain2 = 0;
		toss(dice, toToss);
		count++;
		insertion_sort(dice);
		// Seaching for two chains max, whos ID will end up in *chain1 and *chain2
		for (i = 1, last = 0; i < 5; i++, last++) {
			if (dice[i] == dice[last] + 1) {
				chain++;
				if(chain > chainMax) chainMax = chain;
				if(!switchToChain2) {
					chain1[last] = last;
					chain1[i] = i;
				} else {
					chain2[last] = last;
					chain2[i] = i;
				}
			} else {
				chain = 0;
				// The chain breaker happened after *chain1 gathered some values
				if (chain1[0] != -1) switchToChain2 = 1;
			}
		}
		// Check which chain is the longest
		len1 = 0; len2 = 0;
		for (i = 0; i < 5; i++) {
			if (chain1[i] != -1) len1++;
			if (chain2[i] != -1) len2++;
		}
		// Update *toToss with the dice that don't belong to the longest chain.
		for (i = 0; i < 5; i++) {
			if (len1 > len2) {
				if (chain1[i] == -1) toToss[i] = 1;
				else toToss[i] = 0;
			} else {
				if (chain2[i] == -1) toToss[i] = 1;
				else toToss[i] = 0;
			}
		}
	}

	fprintf(f, "%d;", (int)count);
	return count;
}