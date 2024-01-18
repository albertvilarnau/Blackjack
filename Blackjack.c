#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOTAL_CARDS 52
#define CARD_VALUES 13
#define MAX_HAND 10
#define BLACKJACK 21

// Valores y palos de las cartas
char *values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};

// Creación de la estructura, donde definimos que tendra un palo, un valor y un valor numérico
struct card
{
    char *value;
    char *suit;
    int numericValue;
};

struct card deck[TOTAL_CARDS]; 
struct card playerHand[MAX_HAND]; //Crea dos arrays de cartas, la mano del jugador y la baraja de cartas
int numPlayerCards = 0, playerSum = 0;
char choice; //Crea la variable choice, que se usara para saber si quiere una nueva carta o no el jugador
void showCard(struct card c) // Crea una funcion que usaremos para enseñar a los usuario las cartas
{
    printf("  %s of %s\n", c.value, c.suit);
}

int sumHand(struct card hand[], int numCards) //Crea una funcion para sumar las nuevas cartas a la mano del usuario y a la puntuacion total
{
    int sum = 0; // Declara suma, que empieza en 0, que es la puntuacion inicial
    int Aces = 0; // Declara los Aces que tiene el jugador, cosa que se usara para variar su valor

    for (int i = 0; i < numCards; i++)
    {
        sum += hand[i].numericValue; 

        if (hand[i].numericValue == 11 && strcmp(hand[i].value, "A") == 0) //Recorre las cartas que tiene el jugador en la mano para sumarlas todas
        {
            // Si la carta que recibe el jugador es un AS, sube uno en la cuenta de Ases. 
            Aces++; 
        }
    }

    while (sum > BLACKJACK && Aces > 0) // Si el jugador tiene mas de la puntuacion maxima (21 de base) y una As, ese as pasa a valer 1
    {
        sum -= 10; // Le resta diez a la puntuacion, ya que 11-10 = 1, que es el nuevo valor
        Aces--; // Le quita el As del contador
        printf("You passed 21, but you have an AS. It counts 1"); // Le informa de lo sucedido
    }

    return sum; // Finalmente, le devuelve la suma total
}

int main() // Empieza la funcion principal
{

    int money, bet, out; // Money = Dinero total ; Bet = Apuesta a la ronda; Out = Salir del juego 
    char menu; // Se declara para poder usar el switch para poder jugar una y otra vez
    
    printf("How much money do you bring?: "); 
    scanf("%i", &money); // Lee cuanto dinero quiere meter el jugador en total

    do
    {

        numPlayerCards = 0;
        playerSum = 0; // Reinicia la variable de playerSum y de numPlayerCards
        printf("\nDo you want to play Blackjack? (Y/N): ");
        scanf(" %c", &menu);
                
        switch (menu) 
        {

        case 'Y':
        case 'y':

            printf("How much money do you want to bet?: ");
            scanf("%i", &bet); // Crea la apuesta
            if (bet > money)
            {
                printf("You don't have that amount of money");
                break; // Le denega la apuesta si no tiene esa cantidad
            }
            money -= bet; // Le resta la apuesta del dinero disponible
 
            for (int i = 0; i < TOTAL_CARDS; i++) // Este bucle asocia todas las cartas a un palo, un valor y un valor numérico
            {
                deck[i].value = values[i % CARD_VALUES];
                deck[i].suit = suits[i / CARD_VALUES];
                deck[i].numericValue = (i % CARD_VALUES) + 2;
                if (deck[i].numericValue > 10) // Se ponen J, Q y K en valor 10
                    deck[i].numericValue = 10;
                if (strcmp(deck[i].value, "A") == 0) // Si el valor de la carta es A, le asigna 11
                    deck[i].numericValue = 11;
            }

            srand(time(NULL)); // En el siguiente bucle usa un método para barajar las cartas
            for (int i = 0; i < TOTAL_CARDS; i++)
            {
                int j = rand() % TOTAL_CARDS;
                struct card temp = deck[i];
                deck[i] = deck[j];
                deck[j] = temp;
            }

            printf("Welcome to Blackjack!\n");

            playerHand[numPlayerCards++] = deck[0]; // Reparte dos cartas al usuario
            playerHand[numPlayerCards++] = deck[1];
            playerSum = sumHand(playerHand, numPlayerCards); // Suma las dos cartas

            printf("Your cards:\n");
            showCard(playerHand[0]);
            showCard(playerHand[1]); // Muestra al usuario las dos cartas y el valor total
            printf("Total amount: %d\n", playerSum);

            while (playerSum < BLACKJACK) 
            {
                printf("Hit or stand (H/S): "); // Pregunta al usuario si quiere o no quiere otra carta
                scanf(" %c", &choice);

                if (choice == 'H' || choice == 'h') // Eleccion = Recoger otra carta
                {
                    playerHand[numPlayerCards] = deck[numPlayerCards + 1]; // Reparte la siguiente carta
                    playerSum = sumHand(playerHand, ++numPlayerCards); 
                    // Suma las cartas a la puntuacion y le muestra al usuario la nueva carta
                    printf("New card:\n");
                    showCard(playerHand[numPlayerCards - 1]);
                    printf("Total amount: %d\n", playerSum);
                }
                else
                {
                    break;
                }
            } // Esta funcion solo acaba si no coge carta o si se pasa de 21 el usuario.

            int Dealer = rand() % 10 + 17; /*Numero aleatorio entre 17 y 26, ya que en el Blackjack,
             el Dealer esta obligado a plantarse en 17, pero puede pasarse hasta un máximo de 26 
             (16 + 6 = 26). Las siguiente lineas definen todas las opciones que puede presentar el 
             juego respecto con el Dealer, y te suma la apuesta o te la deja restada dependiendo 
             de si has ganado o perdido*/
            if (playerSum == BLACKJACK && Dealer == BLACKJACK)
            {
                printf("Blackjack! But you draw with Dealer\n");
                money += bet;
            }
            else if (playerSum == BLACKJACK && Dealer != BLACKJACK)
            {
                printf("Blackjack! You win the game!\nDealer's hand: %i \n", Dealer);
                money += bet * 2;
            }
            else if (playerSum > BLACKJACK)
            {
                printf("You have gone too far. End of the game.\n");
            }
            else if (playerSum < BLACKJACK && Dealer > BLACKJACK)
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

            printf("\nNow, you have %i dollars", money); // Informa de cuanto dinero tiene el usuario
            if (money == 0) // Si te quedas en banca rota, se acaba el juego.
            {
                out++;
            }

            break;

        case 'n':
        case 'N':
            printf("You ended the game with %i dollars", money); // En caso de dejar de jugar
            out++;
        }

    } while (out == 0);

    return 0;
}