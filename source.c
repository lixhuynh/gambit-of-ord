#include <stdio.h>
#include <string.h>

void printRules();
int playGame(int);

int main() {
    int balance = 1000;

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
            printf("Looks like you went into debt... Would you like to restart? (yes/quit)\n");
            scanf("%4s", input);
            while (strcmp(input, "yes") != 0 && strcmp(input, "quit") != 0) {
                printf("Please enter a valid option. (yes/quit)\n");
                scanf("%4s", input);
            }
            if (strcmp(input, "yes") == 0) {
                printf("Let's try this one more time!\n");
                balance = 1000;
            }
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
    printf("You currently have %dG.", balance);
    // do something  
    return balance - 100;  // placeholder to prevent inf loop
}