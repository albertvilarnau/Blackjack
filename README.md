Bienvenido a la version 2.0 del Blackjack!!

En está version se ha implementado optimizacion de código al Blackjack. Pasamos unos ejemplos:

>> Se ha eliminado la función InitializeDeck, ya que solo se usaba una sola vez, y se ha implementado el código directamente. (Visto el la linía 53/59)

>> Se ha eliminado la función ShuffleDeck, ya que solo se usaba una sola vez, y se ha implementado el código directamente. (Visto el la linía 61/67)

>> Incluida la libreria <string.h>, ya que es usada para comparar algunos datos (Visto el la linía 4)

>> Usado en strcmp para comparar cadenas (if (strcmp(deck[i].value, "A") == 0) deck[i].numericValue = 11;) (Linía 59)

>> Cambiado el texto "Quieres otra carta?" por "Hit or Stand", ya que es como se utilitza el lenguaje del juego original, el Blackjack

>> Añadido el sistema "Dealer", (Ver Línia 99/113)


