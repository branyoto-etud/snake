CC=gcc
CFLAGS=-ansi -Wall -pedantic
LDFLAGS=-lMLV
OBJ= Main.o Monde.o Serpent.o Pomme.o Case.o Affichage.o Clavier.o Regles.o Image.o Gestion_fichier.o

Jeu: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

Affichage.o: Affichage.c Affichage.h Gestion_fichier.h Monde.h Serpent.h Pomme.h Regles.h Image.h

Main.o: Main.c Monde.h Regles.h Gestion_fichier.h Affichage.h Clavier.h

Gestion_fichier.o: Gestion_fichier.c Gestion_fichier.h Regles.h

Monde.o: Monde.c Monde.h Pomme.h Serpent.h Regles.h Image.h

Pomme.o: Pomme.c Pomme.h Image.h Case.h

Clavier.o: Clavier.c Clavier.h Monde.h

Serpent.o: Serpent.c Serpent.h Case.h

Regles.o : Regles.c Regles.h

Image.o: Image.c Image.h

Case.o: Case.c Case.h

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f Jeu

uninstall: mrproper
	rm -f ./bin/Jeu
	rm -rf ./bin

install: Jeu
	mkdir ./bin
	mv Jeu ./bin
	make mrproper
