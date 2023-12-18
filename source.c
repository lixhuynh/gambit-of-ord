#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

void printRules();
int playGame(int);
void pickCard(int*, int*, int, bool);
int offerBet(int, int);

int main() {
    char input[5];
    int balance = 1000;

    srand(time(NULL));
    printf("Welcome to my Fork of the Storm simulator! Would you like an overview of the rules? (yes/no/quit)\n");
    scanf("%4s", input);
    while (strcmp(input, "yes") != 0 && strcmp(input, "no") != 0 && strcmp(input, "quit") != 0) {
        printf("Please enter a valid option. (yes/no/quit)\n");
        scanf("%4s", input);
    }

    if (strcmp(input, "yes") == 0) {
        printRules();
        printf("Would you like to play? (yes/quit)\n");
        scanf("%4s", input);
        while (strcmp(input, "yes") != 0 && strcmp(input, "quit") != 0) {
            printf("Please enter a valid option. (yes/quit)\n");
            scanf("%4s", input);
        }
    }

    while (strcmp(input, "quit") != 0) {
        balance = playGame(balance);
        if (balance <= 0) {
            balance = 1000;
            printf("Looks like you went into debt... Would you like to restart? (yes/quit)\n");
        }
        else
            printf("Would you like to play again? (yes/quit)\n");
        scanf("%4s", input);
        while (strcmp(input, "yes") != 0 && strcmp(input, "quit") != 0) {
            printf("Please enter a valid option. (yes/quit)\n");
            scanf("%4s", input);
        }
    }
    printf("Thanks for playing!\n");
    
    return 0;
}

void printRules() {
    printf(
        "===========================================\n"
        "THE RULES\n"
        "===========================================\n"
        "Round 1: Players pull one of 8 cards with replacement, keeping the result hidden.\n"
        "Round 2: Players pull one of 6 cards with replacement, revealing the result.\n"
        "Round 3: Players pull one of 4 cards with replacement, revealing the result.\n"
        "Final Round: Players reveal the results of all of their card pulls, pulling another one of four cards if there were any duplicates.\n"
        "\n"
        "Whoever ends with the highest sum is victorious! It's that simple.\n"
        "===========================================\n"
    );
}

int playGame(int balance) {
    int dealerScore = 0;
    int playerScore = 0;
    int dealerRolls[4], playerRolls[4];
    int totalBet = 0;

    printf("You currently have %dG.\n", balance);
    for (int i = 0; i < 3 && totalBet != -1; i ++) {
        int range = 8 - i * 2;
        pickCard(&dealerScore, &dealerRolls[i], range, true);
        pickCard(&playerScore, &playerRolls[i], range, false);
        totalBet += offerBet(balance, totalBet);
    }

    printf("Let's reveal the dealer's pulls!\n");
    for (int i = 0; i < 3 && dealerRolls[i] != 0; i++)
        printf("In Round %d, the dealer pulled a %d.\n", i, dealerRolls[i]);

    if (totalBet != -1) { // player did not fold

        if (playerRolls[0] == playerRolls[1] || playerRolls[0] == playerRolls[2] || playerRolls[1] == playerRolls[2]) {
            do { // player score explodes
                printf("Because you pulled doubles, you pull another card from the pool of 4!\n");
                pickCard(&playerScore, &playerRolls[3], 4, false);
            } while (playerRolls[3] == playerRolls[0] || playerRolls[3] == playerRolls[1] || playerRolls[3] == playerRolls[2]);
        }
        if (dealerRolls[0] == dealerRolls[1] || dealerRolls[0] == dealerRolls[2] || dealerRolls[1] == dealerRolls[2]) {
            do { // dealer score explodes
                printf("Because the dealer pulled doubles, they pull another card from the pool of 4!\n");
                pickCard(&dealerScore, &dealerRolls[3], 4, true);
            } while (dealerRolls[3] == dealerRolls[0] || dealerRolls[3] == dealerRolls[1] || dealerRolls[3] == dealerRolls[2]);
        }

        printf("The dealer's score was %d, and your score was %d.\n", dealerScore, playerScore);

        if (dealerScore > playerScore) {
            balance -= totalBet;
            printf("You lost %dG. Your current balance is %dG.\n", totalBet, balance);
        }
        else {
            balance += totalBet;
            printf("You won %dG! Your current balance is %dG.\n", totalBet, balance);
        }
    }

    return balance;
}

void pickCard(int* score, int* roll, int range, bool isDealer) {
    *roll = rand() % range + 1;
    *score += *roll;
    if (isDealer) {
        if (range == 8)
            printf("The dealer pulled a card.\n");
        else
            printf("The dealer pulled a card with value %d.\n", *roll);
    }
    else
        printf("You pulled a card with value %d. Your current total score is %d.\n", *roll, *score);
}

int offerBet(int balance, int totalBet) {
    char input[6];
    int bet;

    printf("What would you like to do? (check/raise/fold)\n");
    scanf("%5s", input);
    while (strcmp("check", input) != 0 && strcmp("raise", input) != 0 && strcmp("fold", input) != 0) {
        printf("Please enter a valid option. (check/raise/fold)\n");
        scanf("%5s", input);
    }

    if (strcmp("check", input) == 0) {
        printf("You checked! Moving onto the next round...\n");
        return 0;
    }
    else if (strcmp("raise", input) == 0) {
        if (balance == totalBet) {
            printf("You've already bet the maximum amount! Moving onto the next round...\n");
            return 0;
        }
        else {
            printf("How much would you like to bet?\n");
            scanf("%d", &bet);
            while (bet <= 0 || (totalBet + bet) > balance) {
                if (bet <= 0)
                    printf("You must offer a bet amount greater than 0. Input your bet again.\n");
                else
                    printf("You cannot bet more than your current balance, which is %d. Input your bet again.\n", balance);
                scanf("%d", &bet);
            }
            printf("You raised %dG, bringing your total bet to %dG. Moving onto the next round...\n", bet, totalBet + bet);
            return bet;
        }
    }
    else
        return -1;
}