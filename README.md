# Labyrinth-SDL
Un labyrinthe en C avec la lib' SDL avec une IA capable de le résoudre avec la route la plus courte

Les fichiers maps sont composés d'un header suivi de la map en elle même.

Le header est composé de 14 octets (7 entiers signés sur 2 octets)
\[1\]\[nombre de colonnes\]\[nombre de lignes\]\[numero colonne du joueur\]\[numero ligne du joueur\]\[numero colonne de la sortie\]\[numero ligne de la sortie]

La map est une suite d'entier signé sur 1 octet. Chaque entier détermine le contenu de la case associée à sa position.

-1 => vide
0 => Mur
1 => Joueur
2 => Sortie
