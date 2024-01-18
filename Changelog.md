### Bienvenido al Changelog del BlackJack de Albert Vilarnau, donde se especificará los cambios hechos en cada versión publicada en Github

https://github.com/albertvilarnau/Blackjack

## VERSIÓN 1.0

>> Nada añadido. Esta es la version mas cruda del código.

## VERSIÓN 1.1

>> Traducido al Inglés, arreglada la mezcla de idiomas que se producía.

## VERSIÓN 1.2

>> En esta versión, hemos arreglado uno de los principales problemas del codigo, ahora suma perfectamente las cartas.

    El problema residia en la funcion de asignacion de valores, donde sumaba 1 en vez de 2, ya que la A es una variable que cambia, puede ser o 1 o 11, por lo tanto, la baraja debe empezar por el 2.

        (VERSION ANTIGUA)   deck[i].numericValue = (i % CARD_VALUES) + 1;
        (VERSION NUEVA)     deck[i].numericValue = (i % CARD_VALUES) + 2;
    Esto se puede observar en la linea número 30 de la versión 1.2

## VERSIÓN 1.3

>> En esta versión, hemos arreglado uno de los principales problemas del codigo, la no-variación del valor del As

A partir de ahora, se ha implementado un código, donde el valor de As variará entre 1 y 11 dependiendo de si te vas a pasar o no de 21.

CODIGO IMPLEMENTADO:

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

Se ha añadido un contador de Ases, que se ejecuta si la siguiente carta es un As. Al hacer la suma, si es mas de 21 y hay algun As, te restara 10, para poder convertirlo de 11 a 1.

>> También se ha cambiado la forma de asignar el valor 11 al As en la asignacion de cartas

CODIGO ANTIGUO >>>> if (i % CARD_VALUES == CARD_VALUES - 1) deck[i].numericValue = 11;

CODIGO NUEVO >>>> if (deck[i].value == "A") deck[i].numericValue = 11;

## VERSIÓN 2.0

>> Se ha eliminado la función InitializeDeck, ya que solo se usaba una sola vez, y se ha implementado el código directamente. (Visto el la linía 53/59)

>> Se ha eliminado la función ShuffleDeck, ya que solo se usaba una sola vez, y se ha implementado el código directamente. (Visto el la linía 61/67)

>> Incluida la libreria <string.h>, ya que es usada para comparar algunos datos (Visto el la linía 4)

>> Usado en strcmp para comparar cadenas (if (strcmp(deck[i].value, "A") == 0) deck[i].numericValue = 11;) (Linía 59)

>> Cambiado el texto "Quieres otra carta?" por "Hit or Stand", ya que es como se utilitza el lenguaje del juego original, el Blackjack

>> Añadido el sistema "Dealer", (Ver Línia 99/113)

## VERSIÓN 2.1

>> Se ha añadido un sistema donde puedes jugar todas las veces que quieras sin tener que volver a complilar el juego, con un switch y un menu

>> Se ha añadido un sistema de apuestas, juega para descubrirlo!

# VERSIÓN 2.2

>> Eliminado un srand(time(NULL));, debido a que habian dos en el código 

>> Definida la constante BLACKJACK como 21 para facilitar la versatilidad del código

>> Añadidos comentarios para facilitar la legibilidad del código

>> Añadido un README.md estructurado, y añadido el changelog.md, para documentar los cambios, en vez de usar el README.md como se estaba haciendo