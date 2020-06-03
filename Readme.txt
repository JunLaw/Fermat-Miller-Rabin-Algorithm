PROJET MENÉ PAR DOUBI DYLAN, RAKOTOMANGA ANDRIANINA, SY CHÉRIF AMANATOULHA

Le projet est séparé en deux partie : Fermat et Miller Rabin.

pour compiler Fermat :
gcc -c func.c func.h Fermat.c -lgmp
gcc func.o Fermat.o -o Fermat -lgmp
pour executer Fermat :
./Fermat 10 787
premier argument : nombre de répétition.
deuxième argument : nombre à tester

pour compiler Miller-Rabin:
gcc -c func.c func.h Miller_Rabin.c -lgmp
gcc func.o Miller_Rabin.o -o Miller_Rabin -lgmp
pour executer Miller-Rabin
./Miller_Rabin 10 787

premier argument : nombre de répétition.
deuxième argument : nombre à tester
