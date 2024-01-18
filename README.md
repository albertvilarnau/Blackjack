Bienvenido a la version 1.3 del Blackjack!!

En esta versión, hemos arreglado uno de los principales problemas del codigo, la no-variación del valor del As

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

Se ha añadido un contador de Ases, que se ejecuta si la siguiente carta es un As. Al hacer la suma, si es mas de 21 y hay algun As, 
te restara 10, para poder convertirlo de 11 a 1.

También se ha cambiado la forma de asignar el valor 11 al As en la asignacion de cartas

CODIGO ANTIGUO  >>>>    if (i % CARD_VALUES == CARD_VALUES - 1) deck[i].numericValue = 11;

CODIGO NUEVO    >>>>    if (deck[i].value == "A") deck[i].numericValue = 11;

En la próxima versión se añadirán mas actualizaciones de código
