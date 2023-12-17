#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void printRules();
int playGame(int);
void pickCard(int*, int*, int*, int*, int);
int offerBet(int, int);

int main() {
    int balance = 1000;
    srand(time(NULL));

    printf("Welcome to my Fork of the Storm simulator! Would you like an overview of the rules? (yes/no/quit)\n");
    char input[5];
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
        else {
            printf("Would you like to play again?\n");
        }
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
        "The Rules\n"
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
    int dealerRolls[3], playerRolls[3];
    int totalBet = 0;

    printf("You currently have %dG.\n", balance);
    for (int i = 0; i < 3 && totalBet != -1; i ++) {
        int range = 8 - i * 2;
        pickCard(&dealerScore, &playerScore, &dealerRolls[i], &playerRolls[i], range);
        totalBet = offerBet(balance, totalBet);
    }

    printf("Let's reveal the dealer's rolls!\n");
    for (int i = 0; i < 3 && dealerRolls[i] != 0; i++) {
        printf("In Round %d, the dealer rolled a %d.\n", i, dealerRolls[i]);
    }

    if (totalBet != -1) {
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

void pickCard(int* dealerScore, int* playerScore, int* dealerRoll, int* playerRoll, int range) {
    *dealerRoll = rand() % range + 1;
    *playerRoll = rand() % range + 1;
    *dealerScore += *dealerRoll;
    *playerScore += *playerRoll;

    printf("You pulled a card with value %d. Your current score is %d.\n", *playerRoll, *playerScore);
    if (range != 8) {
        printf("The dealer pulled a card with value %d.\n", *dealerRoll);
    }
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
        printf("How much would you like to bet?\n");
        scanf("%d", &bet);
        while (bet <= 0 || (totalBet + bet) > balance) {
            if (bet <= 0) {
                printf("You must offer a bet amount greater than 0. Input your bet again.\n");
            }
            else {
                printf("You cannot bet more than your current balance, which is %d. Input your bet again.\n", balance);
            }
            scanf("%d", &bet);
        }
        printf("You raised %d, bringing your total bet to %d. Moving onto the next round...\n", bet, totalBet + bet);
        return totalBet + bet;
    }
    else {
        return -1;
    }
}