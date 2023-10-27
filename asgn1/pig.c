#include "names.h"

#include <stdio.h>
#include <stdlib.h>

int winner_index = 0;
int main(void) {

    //prompts the user to enter the number of players
    int num_players = 2;
    printf("Number of players (2 to 10)? ");
    int num_assignments = scanf("%d", &num_players);

    //checks for valid number of players. Sets num_players = 2 if invalid, and returns error.
    if (num_assignments < 1 || num_players < 2 || num_players > 10) {
        num_players = 2;
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
    }

    //prompts the user to enter the seed value for the random function
    unsigned seed = 2023;
    printf("Random-number seed? ");
    num_assignments = scanf("%u", &seed);

    //checks if input for seed is invalid.
    if (num_assignments < 1) {
        seed = 2023;
        fprintf(stderr, "Invalid seed. Using 2023 instead.\n");
    }
    //seeds the random function
    srandom(seed);

    //initalizes an array of 0's with length == to number of players. Will be used to keep track of score.
    int player_score[num_players];
    for (int i = 0; i <= num_players; i++) {
        player_score[i] = 0;
    }
    //game state tracker

    int is_game_over(int current_player_index, int current_player_score);
    int dice_roll(int roll, int player_score);
    //following code is taken from asng1 documentaion. Written by Dr. Long and edited by Dr. Veenstra

    /*
* Create a new type called "Position".
* Any variable of this type acts like an int.
* The enum defines contants with the names SIDE, RAZORBACK, etc.
* where SIDE == 0, RAZORBACK == 1, etc.
*/
    typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
    /*
* Define a constant array pig that assigns a pig position to each value
* of a pseudorandom number from 0 through 6.
* SIDE appears twice because it has 2/7 chance of being rolled.
* The same goes for JOWLER.
*/
    const Position pig[7] = {
        SIDE,
        SIDE,
        RAZORBACK,
        TROTTER,
        SNOUTER,
        JOWLER,
        JOWLER,
    };

    //end document code.
    int turn_number = 0;
    int roll = 0;
    int turn = turn_number % num_players;
    //outer game loop. Tracks whos turn it is and if game is over.
    while (is_game_over(turn_number % num_players, player_score[turn]) == 0) {
        turn = turn_number % num_players;
        printf("%s\n", player_name[turn]);
        do {
            roll = dice_roll(pig[random() % 7], player_score[turn]);
            player_score[turn] += roll;
        } while (roll != 0 && is_game_over(turn, player_score[turn]) == 0);
        if (is_game_over(turn, player_score[turn]) == 0) {
            turn_number++;
        }
    }
    printf("%s won!\n", player_name[winner_index]);

    return 0;
}
int is_game_over(int current_player_index, int current_player_score) {
    int game_is_over = 0;
    if (current_player_score >= 100) {
        game_is_over = 1;
        winner_index = current_player_index;
    }

    return game_is_over;
}

int dice_roll(int roll, int player_score) {
    if (roll == 0) {
        printf(" rolls %d, has %d\n", 0, player_score);
        return 0;
    } else if (roll == 1) {
        printf(" rolls %d, has %d\n", 10, player_score + 10);
        return 10;
    } else if (roll == 2) {
        printf(" rolls %d, has %d\n", 10, player_score + 10);
        return 10;
    } else if (roll == 3) {
        printf(" rolls %d, has %d\n", 15, player_score + 15);
        return 15;
    } else {
        printf(" rolls %d, has %d\n", 5, player_score + 5);
        return 5;
    }
}
