#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOTAL_CARDS 52
#define CARD_VALUES 13
#define MAX_HAND 10

// Representación de las cartas
char *values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};

// Estructura para una carta
struct card
{
    char *value;
    char *suit;
    int numericValue;
};

struct card deck[TOTAL_CARDS];
struct card playerHand[MAX_HAND];
int numPlayerCards = 0, playerSum = 0;
char choice;

void showCard(struct card c)
{
    printf("  %s of %s\n", c.value, c.suit);
}

int sumHand(struct card hand[], int numCards)
{
    int sum = 0;
    int Aces = 0;

    for (int i = 0; i < numCards; i++)
    {
        sum += hand[i].numericValue;

        if (hand[i].numericValue == 11 && strcmp(hand[i].value, "A") == 0)
        {
            Aces++;
        }
    }

    while (sum > 21 && Aces > 0)
    {
        sum -= 10;
        Aces--;
    }

    return sum;
}

int main()
{

    int money, bet, out;
    char menu;

    printf("How much money do you bring?: ");
    scanf("%i", &money);

    do
    {

        numPlayerCards = 0;
        playerSum = 0;
        printf("\nDo you want to play Blackjack? (Y/N): ");
        scanf(" %c", &menu);

        switch (menu)
        {

        case 'Y':
        case 'y':

            printf("How much money do you want to bet?: ");
            scanf("%i", &bet);
            if (bet > money)
            {
                printf("You don't have that amount of money");
                break;
            }
            money -= bet;

            for (int i = 0; i < TOTAL_CARDS; i++)
            {
                deck[i].value = values[i % CARD_VALUES];
                deck[i].suit = suits[i / CARD_VALUES];
                deck[i].numericValue = (i % CARD_VALUES) + 2;
                if (deck[i].numericValue > 10)
                    deck[i].numericValue = 10;
                if (strcmp(deck[i].value, "A") == 0)
                    deck[i].numericValue = 11;
            }

            srand(time(NULL));
            for (int i = 0; i < TOTAL_CARDS; i++)
            {
                int j = rand() % TOTAL_CARDS;
                struct card temp = deck[i];
                deck[i] = deck[j];
                deck[j] = temp;
            }

            printf("Welcome to Blackjack!\n");

            playerHand[numPlayerCards++] = deck[0];
            playerHand[numPlayerCards++] = deck[1];
            playerSum = sumHand(playerHand, numPlayerCards);

            printf("Your cards:\n");
            showCard(playerHand[0]);
            showCard(playerHand[1]);
            printf("Total amount: %d\n", playerSum);

            while (playerSum < 21)
            {
                printf("Hit or stand (H/S): ");
                scanf(" %c", &choice);

                if (choice == 'H' || choice == 'h')
                {
                    playerHand[numPlayerCards] = deck[numPlayerCards + 1];
                    playerSum = sumHand(playerHand, ++numPlayerCards);

                    printf("New card:\n");
                    showCard(playerHand[numPlayerCards - 1]);
                    printf("Total amount: %d\n", playerSum);
                }
                else
                {
                    break;
                }
            }

            srand(time(NULL));
            int Dealer = rand() % 10 + 17;
            if (playerSum == 21 && Dealer == 21)
            {
                printf("Blackjack! But you draw with Dealer\n");
                money += bet;
            }
            else if (playerSum == 21 && Dealer != 21)
            {
                printf("Blackjack! You win the game!\nDealer's hand: %i \n", Dealer);
                money += bet * 2;
            }
            else if (playerSum > 21)
            {
                printf("You have gone too far. End of the game.\n");
            }
            else if (playerSum < 21 && Dealer > 21)
            {
                printf("You win the game! Dealer got %i", Dealer);
                money += bet * 2;
            }
            else if (playerSum > Dealer)
            {
                printf("You win the game! Dealer got %i, and you %i \n", Dealer, playerSum);
                money += bet * 2;
            }
            else if (playerSum == Dealer)
            {
                printf("You draw with the Dealer. Dealer's hand: %i \n", Dealer);
                money += bet;
            }

            printf("\n Now, you have %i dollars", money);
            if (money == 0)
            {
                out++;
            }

            break;

        case 'n':
        case 'N':
            printf("You ended the game with %i dollars", money);
            out++;
        }

    } while (out == 0);

    return 0;
}
