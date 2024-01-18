Bienvenido a la version 1.2 del Blackjack!!

En esta versión, hemos arreglado uno de los principales problemas del codigo, ahora suma perfectamente las cartas.

El problema residia en la funcion de asifnacion de valores, donde sumaba 1 en vez de 2, ya que la A es una variable que cambia, puede ser o 1 o 11, por lo tanto, la baraja debe empezar por el 2.

        (VERSION ANTIGUA)   deck[i].numericValue = (i % CARD_VALUES) + 1;
        (VERSION NUEVA)     deck[i].numericValue = (i % CARD_VALUES) + 2;

Esto se puede observar en la linea número 30


