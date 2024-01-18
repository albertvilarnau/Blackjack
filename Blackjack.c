#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARDS 52
#define CARD_VALUES 13
#define MAX_HAND 10

// Representación de las cartas
char *values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};

// Estructura para una carta
struct card {
    char *value;
    char *suit;
    int numericValue;
};

struct card deck[TOTAL_CARDS];
struct card playerHand[MAX_HAND];
int numPlayerCards = 0;
int playerSum = 0;
char choice;

void initializeDeck() {
    for (int i = 0; i < TOTAL_CARDS; i++) {
        deck[i].value = values[i % CARD_VALUES];
        deck[i].suit = suits[i / CARD_VALUES];
        deck[i].numericValue = (i % CARD_VALUES) + 2;
        if (deck[i].numericValue > 10) deck[i].numericValue = 10;
        if (deck[i].value == "A") deck[i].numericValue = 11;
    }
}

    void shuffleDeck() {
        srand(time(NULL));
        for (int i = 0; i < TOTAL_CARDS; i++) {
            int j = rand() % TOTAL_CARDS;
            struct card temp = deck[i];
            deck[i] = deck[j];
            deck[j] = temp;
        }
    }

void showCard(struct card c) {
    printf("  %s of %s\n", c.value, c.suit);

}

int sumHand(struct card hand[], int numCards) {
    int sum = 0;
    int Aces = 0;

    for (int i = 0; i < numCards; i++) {
        sum += hand[i].numericValue;

        if (hand[i].numericValue == 11 && strcmp(hand[i].value, "A") == 0) {
            Aces++;
        }
    }

    while (sum > 21 && Aces > 0) {
        sum -= 10;
        Aces--;
    }

    return sum;
}

int main() {
    initializeDeck();
    shuffleDeck();

    printf("Welcome to Blackjack!\n");

    playerHand[numPlayerCards++] = deck[0];
    playerHand[numPlayerCards++] = deck[1];
    playerSum = sumHand(playerHand, numPlayerCards);

    printf("Your cards:\n");
    showCard(playerHand[0]);
    showCard(playerHand[1]);
    printf("Total amount: %d\n", playerSum);

    while (playerSum < 21) {
        printf("Take another card? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            playerHand[numPlayerCards] = deck[numPlayerCards + 1];
            playerSum = sumHand(playerHand, ++numPlayerCards);

            printf("New card:\n");
            showCard(playerHand[numPlayerCards - 1]);
            printf("Total amount: %d\n", playerSum);
        } else {
            break;
        }
    }

    if (playerSum == 21) {
        printf("Blackjack! You win the game.\n");
    } else if (playerSum > 21) {
        printf("You have gone too far. End of the game.\n");
    } else {
        printf("You're done with %d. End of the game.\n", playerSum);
    }

    return 0;
}
